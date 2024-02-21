#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Prot�tipos de fun��o
bool isSimetrica(double** matrizA, int linhas, int colunas);
bool verifyDiagonalZero(double** matriz, int linhas, int colunas);
bool verifyLinearidade(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o combina��o linear
bool verifyZero(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o todas zerada
void zeros(double** matriz, int linhas, int colunas); // Fun��o para verificar e ordenar a disposi��o dos zeros na matriz
double** inversivel(double** matrizLU, int linhas, int colunas); // Fun��o inverter a matriz (Fiz, mas n�o � usada)
double** resolveSistemaTriangularSup(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
double** resolveSistemaTriangularInf(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
double** multMatriz(double** matrizXY, double** matrizB, int linhasXY, int colunasXY, int colunasB); // fun��o para multiplicar duas matrizes
void decomposicaoCholesky(double** matrizA, double** matrizL, int linhas, int colunas); // Fun��o para decompor matrizes L e U
void transposta(double** matrizA, double** matrizAT, int linhas, int colunas);

int main() {
    system("chcp 1250 > nul");
    cout << std::fixed << setprecision(2);

    cout << "=========================\nMatriz A" << endl;

    // Definindo as dimens�es da matriz
    int linhasA, colunasA;
    cout << "Digite o n�mero de linhas da matriz A: ";
    cin >> linhasA;
    cout << "Digite o n�mero de colunas da matriz A: ";
    cin >> colunasA;

    // Alocando mem�ria para a matriz (array 2D)
    double** matrizA = new double* [linhasA];
    // Alocando mem�ria para cada array de colunas
    for (int i = 0; i < linhasA; ++i) {
        matrizA[i] = new double[colunasA];
    }

    // Preenchendo a matriz
    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasA; ++j) {
            cout << "Digite o valor para a posi��o [" << i << "][" << j << "]: ";
            cin >> matrizA[i][j];
        }
    }

    bool check = verifyLinearidade(matrizA, linhasA, colunasA);

    if (check == true) {
        cout << "A matriz A n�o � invert�vel!" << endl;
    }
    else {
        cout << "=========================\nMatriz B" << endl;

        // Definindo as dimens�es da matriz
        int linhasB, colunasB;
        cout << "Digite o n�mero de linhas da matriz B: ";
        cin >> linhasB;
        cout << "Digite o n�mero de colunas da matriz B: ";
        cin >> colunasB;

        // Alocando mem�ria para a matriz (array 2D)
        double** matrizB = new double* [linhasB];
        // Alocando mem�ria para cada array de colunas
        for (int i = 0; i < linhasB; ++i) {
            matrizB[i] = new double[colunasB];
        }

        // Preenchendo a matriz
        for (int i = 0; i < linhasB; ++i) {
            for (int j = 0; j < colunasB; ++j) {
                cout << "Digite o valor para a posi��o [" << i << "][" << j << "]: ";
                cin >> matrizB[i][j];
            }
        }

        cout << "\n=============================\nMatrizA:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizA[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n=============================\nMatrizB:" << endl;
        for (int i = 0; i < linhasB; ++i) {
            for (int j = 0; j < colunasB; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizB[i][j] << " ";
            }
            cout << endl;
        }

        // Alocando mem�ria para a matrizL (array 2D)
        double** matrizL = new double* [linhasA];
        // Alocando mem�ria para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            matrizL[i] = new double[colunasA];
        }

        // Alocando mem�ria para a matrizL (array 2D)
        double** matrizLT = new double* [linhasA];
        // Alocando mem�ria para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            matrizLT[i] = new double[colunasA];
        }

        decomposicaoCholesky(matrizA, matrizL, linhasA, colunasA);

        cout << "\n=============================\nMatrizL:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizL[i][j] << " ";
            }
            cout << endl;
        }

        bool check1 = ((verifyZero(matrizL, linhasA, colunasA)) || (verifyDiagonalZero(matrizL, linhasA, colunasA)));

        if (check1 == true) {
            cout << "\nA matriz L n�o � invert�vel, certamente o determinante da matrizA = 0" << endl;
        }
        else {

            transposta(matrizL, matrizLT, linhasA, colunasA);

            cout << "\n=============================\nMatrizLT:" << endl;
            for (int i = 0; i < linhasA; ++i) {
                for (int j = 0; j < colunasA; ++j) {
                    // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                    cout << setw(6) << matrizLT[i][j] << " ";
                }
                cout << endl;
            }

            double** matrizY = resolveSistemaTriangularInf(matrizL, matrizB, linhasA, colunasA, colunasB);
            double** matrizX = resolveSistemaTriangularSup(matrizLT, matrizY, linhasA, colunasA, colunasB);

            cout << "\n=============================\nMatrizY:" << endl;
            for (int i = 0; i < linhasB; ++i) {
                for (int j = 0; j < colunasB; ++j) {
                    // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                    cout << setw(6) << matrizY[i][j] << " ";
                }
                cout << endl;
            }

            cout << "\n=============================\nMatriz X:" << endl;
            for (int i = 0; i < linhasB; ++i) {
                for (int j = 0; j < colunasB; ++j) {
                    // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                    cout << setw(6) << matrizX[i][j] << " ";
                }
                cout << endl;
            }

            // Libera a mem�ria alocada
            for (int i = 0; i < linhasB; ++i) {
                delete[] matrizB[i];
                delete[] matrizA[i];
                delete[] matrizL[i];
                delete[] matrizLT[i];
                delete[] matrizY[i];
                delete[] matrizX[i];
            }
            delete[] matrizA;
            delete[] matrizL;
            delete[] matrizLT;
            delete[] matrizB;
            delete[] matrizY;
            delete[] matrizX;
        }
    }

    return 0;
}

double** resolveSistemaTriangularInf(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB) {
    // Criar a matriz X
    double** matrizY = new double* [linhasA];
    for (int i = 0; i < linhasA; ++i) {
        matrizY[i] = new double[colunasB];
    }

    // Resolve um sistema com uma matriz triangular inferior
    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasB; ++j) {
            double soma = 0.0;
            for (int k = 0; k < i; ++k) {
                soma += matrizA[i][k] * matrizY[k][j];
            }
            matrizY[i][j] = (matrizB[i][j] - soma) / matrizA[i][i];
        }
    }

    return matrizY;
}

double** resolveSistemaTriangularSup(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB) {
    // Criar a matriz X
    double** matrizX = new double* [linhasA];
    for (int i = 0; i < linhasA; ++i) {
        matrizX[i] = new double[colunasB];
    }

    // Resolver para uma matriz triangular superior
    for (int i = linhasA - 1; i >= 0; --i) {
        for (int j = 0; j < colunasB; ++j) {
            double soma = 0.0;
            for (int k = i + 1; k < linhasA; ++k) {
                soma += matrizA[i][k] * matrizX[k][j];
            }
            matrizX[i][j] = (matrizB[i][j] - soma) / matrizA[i][i];
        }
    }

    return matrizX;
}

// Fun��o para multiplicar duas matrizes
double** multMatriz(double** matrizXY, double** matrizB, int linhasXY, int colunasXY, int colunasB) {
    // Cria a matriz de retorno para armazenar o resultado da multiplica��o
    double** matrizResult = new double* [linhasXY];

    // Aloca mem�ria para as linhas da matriz de resultado
    for (int i = 0; i < linhasXY; i++) {
        matrizResult[i] = new double[colunasB] {0}; // Inicializa cada elemento como zero
    }

    // Multiplica as matrizes e armazena o resultado na matriz de retorno
    for (int i = 0; i < linhasXY; i++) {
        for (int j = 0; j < colunasB; j++) {
            double soma = 0.0;
            // Calcula o produto interno entre a linha i da matrizXY e a coluna j da matrizB
            for (int k = 0; k < colunasXY; k++) {
                soma += matrizXY[i][k] * matrizB[k][j];
            }
            // Armazena o resultado na posi��o (i, j) da matriz de resultado
            matrizResult[i][j] = soma;
        }
    }

    return matrizResult; // Retorna a matriz resultante da multiplica��o
}

// Fun��o para calcular a inversa de uma matriz. N�o � ultilizado nesse programa, fiz apenas por fazer.
double** inversivel(double** matrizA, int linhas, int colunas) {

    bool check = verifyZero(matrizA, linhas, colunas);
    check = verifyDiagonalZero(matrizA, linhas, colunas);
    if (check == true) {
        return nullptr;
    }

    // Cria uma matriz aumentada contendo a matriz original e a matriz identidade
    double** matrizAumentada = new double* [linhas];
    for (int i = 0; i < linhas; ++i) {
        matrizAumentada[i] = new double[colunas * 2];
        for (int j = 0; j < colunas; ++j) {
            matrizAumentada[i][j] = matrizA[i][j];
            matrizAumentada[i][j + colunas] = (i == j) ? 1.0 : 0.0; // Matriz identidade
        }
    }

    // Aplica o m�todo de elimina��o de Gauss-Jordan
    for (int i = 0; i < linhas; ++i) {
        // Faz o pivoteamento parcial
        int pivot_row = i;
        for (int j = i + 1; j < linhas; ++j) {
            if (fabs(matrizAumentada[j][i]) > fabs(matrizAumentada[pivot_row][i])) {
                pivot_row = j;
            }
        }
        // Troca as linhas se necess�rio
        if (pivot_row != i) {
            for (int k = 0; k < colunas * 2; ++k) {
                double temp = matrizAumentada[i][k];
                matrizAumentada[i][k] = matrizAumentada[pivot_row][k];
                matrizAumentada[pivot_row][k] = temp;
            }
        }

        // Normaliza a linha piv�
        double pivot = matrizAumentada[i][i];
        for (int j = 0; j < colunas * 2; ++j) {
            matrizAumentada[i][j] /= pivot;
        }

        // Zera as outras entradas na coluna piv�
        for (int k = 0; k < linhas; ++k) {
            if (k != i) {
                double factor = matrizAumentada[k][i];
                for (int j = 0; j < colunas * 2; ++j) {
                    matrizAumentada[k][j] -= factor * matrizAumentada[i][j];
                }
            }
        }
    }

    // Extrai a parte da matriz identidade (a inversa) da matriz aumentada
    double** matrizInversa = new double* [linhas];
    for (int i = 0; i < linhas; ++i) {
        matrizInversa[i] = new double[colunas];
        for (int j = 0; j < colunas; ++j) {
            matrizInversa[i][j] = matrizAumentada[i][j + colunas];
        }
    }

    // Libera a mem�ria alocada para a matriz aumentada
    for (int i = 0; i < linhas; ++i) {
        delete[] matrizAumentada[i];
    }
    delete[] matrizAumentada;

    return matrizInversa;
}

void decomposicaoCholesky(double** matrizA, double** matrizL, int linhas, int colunas) {
    // Inicializa a matriz L com zeros
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matrizL[i][j] = 0.0;
        }
    }

    // Calcula os elementos da matriz L
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j <= i; ++j) {
            double soma = 0.0;
            if (i == j) {
                // Calcula os elementos da diagonal principal
                for (int k = 0; k < j; ++k) {
                    soma += pow(matrizL[j][k], 2);
                }
                matrizL[j][j] = sqrt(matrizA[j][j] - soma);
            }
            else {
                // Calcula os elementos fora da diagonal principal
                for (int k = 0; k < j; ++k) {
                    soma += matrizL[i][k] * matrizL[j][k];
                }
                matrizL[i][j] = (matrizA[i][j] - soma) / matrizL[j][j];
            }
        }
    }
}

bool verifyZero(double** matriz, int linhas, int colunas) {
    // Verifica se h� linhas completamente zeradas
    for (int i = 0; i < linhas; ++i) {
        bool linhaZerada = true;
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] != 0) {
                linhaZerada = false;
                break;
            }
        }
        if (linhaZerada) { // Se toda a linha for zerada, retorna true
            return true;
        }
    }

    // Verifica se h� colunas completamente zeradas
    for (int j = 0; j < colunas; ++j) {
        bool colunaZerada = true;
        for (int i = 0; i < linhas; ++i) {
            if (matriz[i][j] != 0) {
                colunaZerada = false;
                break;
            }
        }
        if (colunaZerada) { // Se toda a coluna for zerada, retorna true
            return true;
        }
    }

    return false; // Retorna false se n�o houver linhas ou colunas completamente zeradas
}

bool verifyDiagonalZero(double** matriz, int linhas, int colunas) {
    // Verifica se algum elemento na diagonal principal � zero
    for (int i = 0; i < linhas; ++i) {
        if (matriz[i][i] == 0) {
            return true; // Se algum elemento na diagonal for zero, retorna true
        }
    }
    return false; // Retorna false se nenhum elemento na diagonal for zero
}

// Fun��o para verificar se a matriz possui linhas ou colunas que s�o combina��o linear
bool verifyLinearidade(double** matriz, int linhas, int colunas) {
    // Verifica se a matriz tem linhas ou colunas completamente zeradas
    if (verifyZero(matriz, linhas, colunas)) {
        return true;
    }

    bool check = false;
    double quociente = 0.0;

    // Verifica se h� linhas que s�o combina��o linear
    for (int i = 0; i < linhas; ++i) {
        for (int l = i + 1; l < linhas; ++l) {
            quociente = abs(matriz[i][0] / matriz[l][0]); // Calcula o quociente entre os elementos das primeiras colunas de linhas consecutivas
            check = true;
            for (int j = 1; j < colunas; ++j) {
                double quocienteT = abs(matriz[i][j] / matriz[l][j]); // Calcula o quociente entre os elementos das demais colunas de linhas consecutivas
                if (quocienteT != quociente) {
                    check = false;
                    break;
                }
            }
            if (check) {
                return true; // Se todas as rela��es de quociente forem iguais, h� combina��o linear
            }
        }
    }

    // Verifica se h� colunas que s�o combina��o linear
    for (int j = 0; j < colunas; ++j) {
        for (int j2 = j + 1; j2 < colunas; ++j2) {
            quociente = abs(matriz[0][j] / matriz[0][j2]); // Calcula o quociente entre os elementos das primeiras linhas de colunas consecutivas
            check = true;
            for (int i = 1; i < linhas; ++i) {
                double quocienteT = abs(matriz[i][j] / matriz[i][j2]); // Calcula o quociente entre os elementos das demais linhas de colunas consecutivas
                if (quocienteT != quociente) {
                    check = false;
                    break;
                }
            }
            if (check) {
                return true; // Se todas as rela��es de quociente forem iguais, h� combina��o linear
            }
        }
    }

    return false; // Se n�o houver combina��o linear, retorna falso
}

// Fun��o para reorganizar os zeros na matriz
void zeros(double** matriz, int linhas, int colunas) {
    // Array para contar o n�mero de zeros em cada linha
    int* contador = new int[linhas] {};

    // Conta o n�mero de zeros em cada linha
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] == 0) {
                contador[i]++;
            }
        }
    }

    // Vari�veis auxiliares para ordena��o
    int aux;
    double* auxi;

    // Ordena as linhas por quantidade de zeros (algoritmo de bubble sort)
    for (int i = 0; i < linhas - 1; ++i) {
        for (int j = 0; j < linhas - i - 1; ++j) {
            if (contador[j] > contador[j + 1]) {
                // Troca o n�mero de zeros
                aux = contador[j];
                contador[j] = contador[j + 1];
                contador[j + 1] = aux;
                // Troca as linhas correspondentes
                auxi = matriz[j];
                matriz[j] = matriz[j + 1];
                matriz[j + 1] = auxi;
            }
        }
    }

    delete[] contador; // Libera a mem�ria alocada para o array contador
}

void transposta(double** matrizA, double** matrizAT, int linhas, int colunas) {
    // Itera sobre cada elemento da matriz original
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            // Atribui o elemento correspondente da matriz original � sua posi��o transposta
            matrizAT[j][i] = matrizA[i][j];
        }
    }
}


bool isSimetrica(double** matrizA, int linhas, int colunas) {

    // Verifica se a matriz original � igual � sua transposta
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (i != j) {
                if (matrizA[i][j] != matrizA[j][i]) {
                    return false; // Se houver elementos diferentes, a matriz n�o � sim�trica
                }
            }
        }
    }

    return true; // Se n�o houver elementos diferentes, a matriz � sim�trica
}

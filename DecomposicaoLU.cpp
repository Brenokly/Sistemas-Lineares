#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Prot�tipos de fun��o
double frobeniusNorm(double** matriz, int tam);
double** inverseMatrix(double** matrix, int n);
double determinant(double** matrix, int n);
void swapRows(double** matrix, int row1, int row2);
bool verifyDiagonalZero(double** matriz, int linhas, int colunas);
bool verifyLinearidade(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o combina��o linear
bool verifyZero(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o todas zerada
void zeros(double** matriz, int linhas, int colunas); // Fun��o para verificar e ordenar a disposi��o dos zeros na matriz
double** inversivel(double** matrizLU, int linhas, int colunas); // Fun��o inverter a matriz (Fiz, mas n�o � usada)
double** resolveSistemaTriangularSup(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
double** resolveSistemaTriangularInf(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
double** multMatriz(double** matrizXY, double** matrizB, int linhasXY, int colunasXY, int colunasB); // fun��o para multiplicar duas matrizes
void decomposicao(double** matrizA, double** matrizL, double** matrizU, int linhas, int colunas); // Fun��o para decompor matrizes L e U

int main() {
    system("chcp 1250 > nul");
    cout << std::fixed << setprecision(2);

    cout << "========================================\nMatriz A" << endl;

    // Definindo as dimens�es da matriz
    int linhasA, colunasA;
    cout << "Digite o tamanho da matriz quadrada A: ";
    cin >> linhasA;
    colunasA = linhasA;

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
        cout << "========================================\nMatriz B" << endl;

        int linhasB = linhasA;
        int colunasB = 1;

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

        cout << "\n========================================\nMatrizA:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizA[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n========================================\nMatrizB:" << endl;
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

        // Alocando mem�ria para a matrizU (array 2D)
        double** matrizU = new double* [linhasA];
        // Alocando mem�ria para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            matrizU[i] = new double[colunasA];
        }

        // Preenchendo a matrizL e matrizU
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                if (i == j) {
                    matrizL[i][j] = 1;
                }
                else if (i < j) {
                    matrizL[i][j] = 0;
                }

                if (i > j) {
                    matrizU[i][j] = 0;
                }
            }
        }

        decomposicao(matrizA, matrizL, matrizU, linhasA, colunasA);

        cout << "\n========================================\nMatrizL:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizL[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n========================================\nMatrizU:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizU[i][j] << " ";
            }
            cout << endl;
        }

        bool check1 = ((verifyZero(matrizL, linhasA, colunasA)) || (verifyDiagonalZero(matrizL, linhasA, colunasA)));
        bool check2 = ((verifyZero(matrizU, linhasA, colunasA)) || (verifyDiagonalZero(matrizU, linhasA, colunasA)));

        if (check1 == true || check2 == true) {
            cout << "\nA matriz U ou L n�o � invert�vel, certamente o determinante da matrizA = 0" << endl;
        }
        else {

            double** matrizY = resolveSistemaTriangularInf(matrizL, matrizB, linhasA, colunasA, colunasB);
            double** matrizX = resolveSistemaTriangularSup(matrizU, matrizY, linhasA, colunasA, colunasB);

            cout << "\n========================================\nMatrizY:" << endl;
            for (int i = 0; i < linhasB; ++i) {
                for (int j = 0; j < colunasB; ++j) {
                    // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                    cout << setw(6) << matrizY[i][j] << " ";
                }
                cout << endl;
            }

            cout << "\n========================================\nMatriz X:" << endl;
            for (int i = 0; i < linhasB; ++i) {
                for (int j = 0; j < colunasB; ++j) {
                    // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                    cout << setw(6) << matrizX[i][j] << " ";
                }
                cout << endl;
            }

            cout << "\n========================================\nMatrizA:" << endl;
            cout << "Determinante: " << determinant(matrizA, linhasA) << endl;
            cout << "Numero de condicionamento: " << frobeniusNorm(matrizA, linhasA);

            // Libera a mem�ria alocada
            for (int i = 0; i < linhasB; ++i) {
                delete[] matrizB[i];
                delete[] matrizA[i];
                delete[] matrizL[i];
                delete[] matrizU[i];
                delete[] matrizY[i];
                delete[] matrizX[i];
            }
            delete[] matrizA;
            delete[] matrizL;
            delete[] matrizU;
            delete[] matrizB;
            delete[] matrizY;
            delete[] matrizX;
        }
    }

    return 0;
}

double** resolveSistemaTriangularInf(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB) {
    // Criar a matriz X
    double** matrizX = new double* [linhasA];
    for (int i = 0; i < linhasA; ++i) {
        matrizX[i] = new double[colunasB];
    }

    // Resolve um sistema com uma matriz triangular inferior
    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasB; ++j) {
            double soma = 0.0;
            for (int k = 0; k < i; ++k) {
                soma += matrizA[i][k] * matrizX[k][j];
            }
            matrizX[i][j] = (matrizB[i][j] - soma);
        }
    }

    return matrizX;
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

void decomposicao(double** matrizA, double** matrizL, double** matrizU, int linhas, int colunas) {
    // Loop para iterar pelas linhas da matriz A
    for (int i = 0; i < linhas; ++i) {
        // Loop para iterar pelas colunas da matriz A
        for (int j = 0; j < colunas; ++j) {
            // Se a linha for menor ou igual � coluna, preenche a matriz U
            if (i <= j) {
                double soma = 0.0;
                // Loop para calcular a soma dos produtos das entradas correspondentes de L e U
                for (int k = 0; k < i; ++k) {
                    soma += matrizL[i][k] * matrizU[k][j];
                }
                // Calcula o elemento de U subtraindo a soma da entrada correspondente de A
                matrizU[i][j] = matrizA[i][j] - soma;
            }
            // Se a linha for maior que a coluna, preenche a matriz L
            else {
                double soma = 0.0;
                // Loop para calcular a soma dos produtos das entradas correspondentes de L e U
                for (int k = 0; k < j; ++k) {
                    soma += matrizL[i][k] * matrizU[k][j];
                }
                // Se o elemento diagonal de U for zero, ajusta a entrada correspondente de L para zero
                if (matrizU[j][j] == 0.0) {
                    matrizL[i][j] = 0.0;
                }
                // Calcula o elemento de L dividindo a diferen�a entre a entrada correspondente de A e a soma pela entrada diagonal de U
                else {
                    matrizL[i][j] = (matrizA[i][j] - soma) / matrizU[j][j];
                }
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

// Fun��o para trocar duas linhas de uma matriz
void swapRows(double** matrix, int row1, int row2) {
    double* temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}

// Fun��o para calcular o determinante de uma matriz usando decomposi��o LU
double determinant(double** matrix, int n) {
    double det = 1.0;

    // Decomposi��o LU
    for (int i = 0; i < n; ++i) {
        // Procura o elemento m�ximo na coluna atual
        int maxRow = i;
        for (int j = i + 1; j < n; ++j) {
            if (fabs(matrix[j][i]) > fabs(matrix[maxRow][i])) {
                maxRow = j;
            }
        }

        // Troca as linhas para colocar o elemento m�ximo na diagonal
        if (maxRow != i) {
            swapRows(matrix, i, maxRow);
            det *= -1; // Troca de linhas altera o sinal do determinante
        }

        // Fator de escala
        double pivot = matrix[i][i];

        // Se o elemento na diagonal for zero, matriz � singular
        if (fabs(pivot) < 1e-10) {
            return 0.0;
        }

        // Faz a elimina��o gaussiana
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / pivot;
            for (int k = i; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }

        // Atualiza o determinante
        det *= pivot;
    }

    return det;
}

// Fun��o para encontrar a inversa de uma matriz
double** inverseMatrix(double** matrix, int n) {

    // Criando uma matriz de identidade para armazenar a inversa
    double** identity = new double * [n];

    for (int i = 0; i < n; i++)
    {
        identity[i] = new double[n];
    }
    for (int i = 0; i < n; ++i) {
        identity[i][i] = 1;
    }

    // Implementando a decomposi��o LU para encontrar a inversa
    for (int i = 0; i < n; ++i) {
        // Se matrix[i][i] for zero, a matriz � singular
        if (fabs(matrix[i][i]) < 1e-10) {
            cout << "A matriz � singular. A inversa n�o pode ser calculada." << endl;
            exit(1);
        }

        // Normalizando a linha i da matriz e da matriz de identidade
        double pivot = matrix[i][i];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] /= pivot;
            identity[i][j] /= pivot;
        }

        // Subtraindo outras linhas para zerar as entradas abaixo do piv�
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i];
            for (int k = 0; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
                identity[j][k] -= factor * identity[i][k];
            }
        }
    }

    // Aplicando a elimina��o gaussiana para reduzir a matriz � identidade
    for (int i = n - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            double factor = matrix[j][i];
            for (int k = 0; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
                identity[j][k] -= factor * identity[i][k];
            }
        }
    }

    return identity;
}

// Fun��o para calcular a norma Frobenius de uma matriz
double frobeniusNorm(double** matriz, int tam) {
    double norm = 0.0;

    for (size_t i = 0; i < tam; i++)
    {
        for (size_t j = 0; j < tam; j++)
        {
            norm += matriz[i][j] * matriz[i][j];
        }
    }

    return sqrt(norm);
}
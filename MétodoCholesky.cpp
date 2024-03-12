#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Prot�tipos de fun��o
bool isSimetrica(double** matrizA, int linhas, int colunas);
bool verifyDiagonalZero(double** matriz, int linhas, int colunas);
bool verifyLinearidade(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o combina��o linear
bool verifyZero(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o todas zerada
double** resolveSistemaTriangularSup(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
double** resolveSistemaTriangularInf(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
bool decomposicaoCholesky(double** matrizA, double** matrizL, int linhas, int colunas); // Fun��o para decompor matrizes L e U
void transposta(double** matrizA, double** matrizAT, int linhas, int colunas);

int main() {
    cout << fixed << setprecision(2);

    cout << "=========================\nMatriz A" << endl;

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
            cout << "Digite o valor para a posicao [" << i << "][" << j << "]: ";
            cin >> matrizA[i][j];
        }
    }

    bool check = verifyLinearidade(matrizA, linhasA, colunasA);
    if (verifyLinearidade(matrizA, linhasA, colunasA) || !isSimetrica(matrizA, linhasA, colunasA)) {
        cout << "A matriz {A} e singular ou nao e simetrica, logo nao e possivel utilizar esse metodo!" << endl;
    }
    else {
        cout << "=========================\nMatriz B" << endl;

        // Definindo as dimens�es da matriz
        int linhasB = linhasA, colunasB = 1;

        // Alocando mem�ria para a matriz (array 2D)
        double** matrizB = new double* [linhasB];
        // Alocando mem�ria para cada array de colunas
        for (int i = 0; i < linhasB; ++i) {
            matrizB[i] = new double[colunasB];
        }

        // Preenchendo a matriz
        for (int i = 0; i < linhasB; ++i) {
            for (int j = 0; j < colunasB; ++j) {
                cout << "Digite o valor para a posicao [" << i << "][" << j << "]: ";
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

        bool check3 = decomposicaoCholesky(matrizA, matrizL, linhasA, colunasA);

        if (check3 == true) {
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
                cout << "\nA matriz L nao e invertivel, certamente o determinante da matrizA = 0" << endl;
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

                cout << fixed << setprecision(4);

                cout << "\n=============================\nMatrizY:" << endl;
                for (int i = 0; i < linhasB; ++i) {
                    for (int j = 0; j < colunasB; ++j) {
                        // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                        cout << setw(7) << matrizY[i][j] << " ";
                    }
                    cout << endl;
                }

                cout << "\n=============================\nMatriz X:" << endl;
                for (int i = 0; i < linhasB; ++i) {
                    for (int j = 0; j < colunasB; ++j) {
                        // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                        cout << setw(7) << matrizX[i][j] << " ";
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
        else {
            cout << "\n==========================================\nA matriz A nao e definida positiva!" << endl;
        }
    }

    return 0;
}

double** resolveSistemaTriangularInf(double** matrizL, double** matrizB, int linhasA, int colunasA, int colunasB) {
    // Criar a matriz Y
    // Faz o c�lculo L * Y = B e descobre os coeficientes de Y
    double** matrizY = new double* [linhasA];
    for (int i = 0; i < linhasA; ++i) {
        matrizY[i] = new double[colunasB];
    }

    // Resolve um sistema com uma matriz triangular inferior
    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasB; ++j) {
            double soma = 0.0;
            for (int k = 0; k < i; ++k) {
                soma += matrizL[i][k] * matrizY[k][j];
            }
            matrizY[i][j] = (matrizB[i][j] - soma) / matrizL[i][i];
        }
    }

    return matrizY;
}

double** resolveSistemaTriangularSup(double** matrizLT, double** matrizY, int linhasA, int colunasA, int colunasB) {
    // Criar a matriz X
    // Faz o c�lculo L^T * X = Y e descobre os coeficientes de X
    double** matrizX = new double* [linhasA];
    for (int i = 0; i < linhasA; ++i) {
        matrizX[i] = new double[colunasB];
    }

    // Resolver para uma matriz triangular superior
    for (int i = linhasA - 1; i >= 0; --i) {
        for (int j = 0; j < colunasB; ++j) {
            double soma = 0.0;
            for (int k = i + 1; k < linhasA; ++k) {
                soma += matrizLT[i][k] * matrizX[k][j];
            }
            matrizX[i][j] = (matrizY[i][j] - soma) / matrizLT[i][i];
        }
    }

    return matrizX;
}

bool decomposicaoCholesky(double** matrizA, double** matrizL, int linhas, int colunas) {
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

                if (isnan(matrizL[j][j])) {
                    matrizL[j][j] = 0;
                    return false;
                }
            }
            else {
                // Calcula os elementos fora da diagonal principal
                for (int k = 0; k < j; ++k) {
                    soma += matrizL[j][k] * matrizL[i][k];
                }
                matrizL[i][j] = (matrizA[i][j] - soma) / matrizL[j][j];

                if (isnan(matrizL[i][j])) {
                    matrizL[i][j] = 0;
                    return false;
                }
            }
        }
    }

    return true;
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
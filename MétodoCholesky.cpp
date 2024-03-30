#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Protótipos de função
double frobeniusNorm(double** matriz, int tam);
double** inverseMatrix(double** matrix, int n);
double determinant(double** matrix, int n);
void swapRows(double** matrix, int row1, int row2);
bool isSimetrica(double** matrizA, int linhas, int colunas);
bool verifyDiagonalZero(double** matriz, int linhas, int colunas);
bool verifyLinearidade(double** matriz, int linhas, int colunas); // Função para verificar se a matriz possui linhas ou colunas que são combinação linear
bool verifyZero(double** matriz, int linhas, int colunas); // Função para verificar se a matriz possui linhas ou colunas que são todas zerada
double** resolveSistemaTriangularSup(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
double** resolveSistemaTriangularInf(double** matrizA, double** matrizB, int linhasA, int colunasA, int colunasB);
bool decomposicaoCholesky(double** matrizA, double** matrizL, int linhas, int colunas); // Função para decompor matrizes L e U
void transposta(double** matrizA, double** matrizAT, int linhas, int colunas);

int main() {
    cout << fixed << setprecision(2);

    cout << "=========================\nMatriz A" << endl;

    // Definindo as dimensões da matriz
    int linhasA, colunasA;
    cout << "Digite o tamanho da matriz quadrada A: ";
    cin >> linhasA;
    colunasA = linhasA;

    // Alocando memória para a matriz (array 2D)
    double** matrizA = new double* [linhasA];
    // Alocando memória para cada array de colunas
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

        // Definindo as dimensões da matriz
        int linhasB = linhasA, colunasB = 1;

        // Alocando memória para a matriz (array 2D)
        double** matrizB = new double* [linhasB];
        // Alocando memória para cada array de colunas
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

        // Alocando memória para a matrizL (array 2D)
        double** matrizL = new double* [linhasA];
        // Alocando memória para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            matrizL[i] = new double[colunasA];
        }

        // Alocando memória para a matrizL (array 2D)
        double** matrizLT = new double* [linhasA];
        // Alocando memória para cada array de colunas
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

                cout << "\n========================================\nMatrizA:" << endl;
                cout << "Determinante: " << determinant(matrizA, linhasA) << endl;
                cout << "Numero de condicionamento: " << frobeniusNorm(matrizA, linhasA);

                // Libera a memória alocada
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
    // Faz o cálculo L * Y = B e descobre os coeficientes de Y
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
    // Faz o cálculo L^T * X = Y e descobre os coeficientes de X
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
    // Verifica se há linhas completamente zeradas
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

    // Verifica se há colunas completamente zeradas
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

    return false; // Retorna false se não houver linhas ou colunas completamente zeradas
}

bool verifyDiagonalZero(double** matriz, int linhas, int colunas) {
    // Verifica se algum elemento na diagonal principal é zero
    for (int i = 0; i < linhas; ++i) {
        if (matriz[i][i] == 0) {
            return true; // Se algum elemento na diagonal for zero, retorna true
        }
    }
    return false; // Retorna false se nenhum elemento na diagonal for zero
}

// Função para verificar se a matriz possui linhas ou colunas que são combinação linear
bool verifyLinearidade(double** matriz, int linhas, int colunas) {
    // Verifica se a matriz tem linhas ou colunas completamente zeradas
    if (verifyZero(matriz, linhas, colunas)) {
        return true;
    }

    bool check = false;
    double quociente = 0.0;

    // Verifica se há linhas que são combinação linear
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
                return true; // Se todas as relações de quociente forem iguais, há combinação linear
            }
        }
    }

    // Verifica se há colunas que são combinação linear
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
                return true; // Se todas as relações de quociente forem iguais, há combinação linear
            }
        }
    }

    return false; // Se não houver combinação linear, retorna falso
}

void transposta(double** matrizA, double** matrizAT, int linhas, int colunas) {
    // Itera sobre cada elemento da matriz original
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            // Atribui o elemento correspondente da matriz original à sua posição transposta
            matrizAT[j][i] = matrizA[i][j];
        }
    }
}

bool isSimetrica(double** matrizA, int linhas, int colunas) {

    // Verifica se a matriz original é igual à sua transposta
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (i != j) {
                if (matrizA[i][j] != matrizA[j][i]) {
                    return false; // Se houver elementos diferentes, a matriz não é simétrica
                }
            }
        }
    }

    return true; // Se não houver elementos diferentes, a matriz é simétrica
}

// Função para encontrar a inversa de uma matriz
double** inverseMatrix(double** matrix, int n) {

    // Criando uma matriz de identidade para armazenar a inversa
    double** identity = new double* [n];

    for (int i = 0; i < n; i++)
    {
        identity[i] = new double[n];
    }
    for (int i = 0; i < n; ++i) {
        identity[i][i] = 1;
    }

    // Implementando a decomposição LU para encontrar a inversa
    for (int i = 0; i < n; ++i) {
        // Se matrix[i][i] for zero, a matriz é singular
        if (fabs(matrix[i][i]) < 1e-10) {
            cout << "A matriz é singular. A inversa não pode ser calculada." << endl;
            exit(1);
        }

        // Normalizando a linha i da matriz e da matriz de identidade
        double pivot = matrix[i][i];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] /= pivot;
            identity[i][j] /= pivot;
        }

        // Subtraindo outras linhas para zerar as entradas abaixo do pivô
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i];
            for (int k = 0; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
                identity[j][k] -= factor * identity[i][k];
            }
        }
    }

    // Aplicando a eliminação gaussiana para reduzir a matriz à identidade
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

// Função para calcular a norma Frobenius de uma matriz
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

// Função para trocar duas linhas de uma matriz
void swapRows(double** matrix, int row1, int row2) {
    double* temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}

// Função para calcular o determinante de uma matriz usando decomposição LU
double determinant(double** matrix, int n) {
    double det = 1.0;

    // Decomposição LU
    for (int i = 0; i < n; ++i) {
        // Procura o elemento máximo na coluna atual
        int maxRow = i;
        for (int j = i + 1; j < n; ++j) {
            if (fabs(matrix[j][i]) > fabs(matrix[maxRow][i])) {
                maxRow = j;
            }
        }

        // Troca as linhas para colocar o elemento máximo na diagonal
        if (maxRow != i) {
            swapRows(matrix, i, maxRow);
            det *= -1; // Troca de linhas altera o sinal do determinante
        }

        // Fator de escala
        double pivot = matrix[i][i];

        // Se o elemento na diagonal for zero, matriz é singular
        if (fabs(pivot) < 1e-10) {
            return 0.0;
        }

        // Faz a eliminação gaussiana
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
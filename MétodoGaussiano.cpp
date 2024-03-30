#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Protótipos de função
double frobeniusNorm(double** matriz, int tam);
double** inverseMatrix(double** matrix, int n);
double determinant(double** matrix, int n);
void swapRows(double** matrix, int row1, int row2);
bool verifyLinearidade(double** matriz, int linhas, int colunas); // Função para verificar se a matriz possui linhas ou colunas que são combinação linear
bool verifyZero(double** matriz, int linhas, int colunas); // Função para verificar se a matriz possui linhas ou colunas que são todas zerada
void zeros(double** matriz, double* igualdade, int linhas, int colunas); // Função para verificar e ordenar a disposição dos zeros na matriz
bool escalonar(double** matriz, double* igualdade, double* coeficientes, int linhas, int colunas); // Função para escalonar a matriz.
void truncamento(double & num);

int main() {
    system("chcp 1250 > nul");
    cout << std::fixed << setprecision(2);

    // Sistema A * X = B

    // Definindo as dimensões da matriz
    int linhas, colunas;
    cout << "Digite o tamanho da matriz quadrada A: ";
    cin >> linhas;
    colunas = linhas;

    // Alocando memória para a matriz (array 2D)
    double** matriz = new double* [linhas];
    // Alocando memória para cada array de colunas
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new double[colunas];
    }

    // Preenchendo a matriz
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << "Digite o valor para a posição [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }

    // Array para os valores do lado direito das equações
    double* igualdade = new double[linhas] {0.0};
    // Array para os coeficientes das variáveis
    double* coeficientes = new double[linhas] {0.0};

    cout << "Digite os coeficientes (Matriz B):" << endl;
    for (int i = 0; i < linhas; i++) {
        cout << "x" << (i + 1) << " = ";
        cin >> igualdade[i];
    }

    // Verifica se há combinação linear nas linhas da matriz
    bool deltcheck = verifyLinearidade(matriz, linhas, colunas);
    if (deltcheck == true) {
        cout << "\nA matriz possui linhas que são combinação linear, logo o determinante é igual a 0." << endl;
    }
    else {
        // Reorganiza os zeros na matriz para facilitar a escalonamento
        zeros(matriz, igualdade, linhas, colunas);

        // Escalona a matriz
        bool escacheck = escalonar(matriz, igualdade, coeficientes, linhas, colunas);

        // Exibe a matriz escalonada
        cout << "\n=============================\nMatriz Escalonada:\n" << endl;
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matriz[i][j] << " ";
            }
            cout << "| " << igualdade[i];
            cout << endl;
        }

        if (escacheck == false) {
            // Exibe a solução do sistema
            cout << "\n=============================\nResolução do sistema:\n" << endl;
            for (int i = 0; i < linhas; i++) {
                cout << "x" << (i + 1) << ": " << coeficientes[i] << endl;
            }
            cout << "=============================\n";
        }
        else {
            cout << "\nO sistema não possui solução única determinada!" << endl;
        }

        cout << "\n========================================\nMatrizA:" << endl;
        cout << "Determinante: " << determinant(matriz, linhas) << endl;
        cout << "Numero de condicionamento: " << frobeniusNorm(matriz, linhas);
    }

    // Libera a memória alocada
    for (int i = 0; i < linhas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}

// Função para escalonar a matriz
bool escalonar(double** matriz, double* igualdade, double* coeficientes, int linhas, int colunas) {
    double mk = 0.0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == j) {
                for (int k = i + 1; k < linhas; k++) {
                    mk = matriz[k][j] / matriz[i][j];
                    matriz[k][j] = 0;

                    truncamento(mk);

                    igualdade[k] = igualdade[k] - (igualdade[i] * mk);

                    truncamento(igualdade[k]);

                    for (int c = j + 1; c < colunas; c++) {
                        matriz[k][c] = matriz[k][c] - (matriz[i][c] * mk);

                        truncamento(matriz[k][c]);

                        if (k == c && matriz[k][c] == 0) {
                           zeros(matriz, igualdade, linhas, colunas);
                        }
                    }

                    
                }
            }
        }
    }

    bool check = verifyZero(matriz, linhas, colunas);

    if (check == true) {
        return true;
    }

    // Inicialização do vetor de coeficientes pegando o último coeficiente de graça
    coeficientes[linhas - 1] = igualdade[linhas - 1] / matriz[linhas - 1][linhas - 1];

    // Loop reverso para calcular os coeficientes
    for (int k = linhas - 2; k >= 0; k--) {
        double s = 0.0;
        for (int j = k + 1; j < linhas; j++) {
            s += matriz[k][j] * coeficientes[j];
        }
        coeficientes[k] = (igualdade[k] - s) / matriz[k][k];
    }

    return false;
}

bool verifyZero(double** matriz, int linhas, int colunas) { // Função para verificar se a matriz possui linhas ou colunas que são todas zerada
    
    // Verifica se há linhas ou colunas completamente zeradas
    for (int i = 0; i < linhas; ++i) {
        bool linhaZerada = true;
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] != 0) {
                linhaZerada = false;
                break;
            }
        }
        if (linhaZerada == true) {
            return true;
        }
    }

    for (int j = 0; j < colunas; ++j) {
        bool colunaZerada = true;
        for (int i = 0; i < linhas; ++i) {
            if (matriz[i][j] != 0) {
                colunaZerada = false;
                break;
            }
        }
        if (colunaZerada == true) {
            return true;
        }
    }

    return false;
}
// Função para verificar se a matriz possui linhas ou colunas que são combinação linear
bool verifyLinearidade(double** matriz, int linhas, int colunas) {
    bool check = false;
    double quociente = 0.0;

    // Verifica se há linhas que são combinação linear
    for (int i = 0; i < linhas; ++i) {
        for (int l = i + 1; l < linhas; l++) {
            quociente = abs(matriz[i][0] / matriz[l][0]);
            check = true;
            for (int j = 1; j < colunas; ++j) {
                double quocienteT = abs(matriz[i][j] / matriz[l][j]);
                if (quocienteT != quociente) {
                    check = false;
                    break;
                }
            }
            if (check == true) {
                break;
            }
        }
        if (check == true) {
            return true;
            break;
        }
    }

    // Verifica se há colunas que são combinação linear
    for (int j = 0; j < colunas; ++j) {
        for (int j2 = j + 1; j2 < colunas; j2++) {
            quociente = abs(matriz[0][j] / matriz[0][j2]);
            check = true;
            for (int i = 1; i < linhas; ++i) {
                double quocienteT = abs(matriz[i][j] / matriz[i][j2]);
                if (quocienteT != quociente) {
                    check = false;
                    break;
                }
            }
            if (check == true) {
                break;
            }
        }
        if (check == true) {
            return true;
        }
    }

    return false;
}

// Função para reorganizar os zeros na matriz
void zeros(double** matriz, double* igualdade, int linhas, int colunas) {
    int* contador = new int[linhas] {};

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 0) {
                contador[i] = contador[i] + 1;
            }
        }
    }

    int aux = 0;
    double aux2 = 0.0;
    double* auxi;

    // Ordena as linhas por quantidade de zeros
    for (int i = 0; i < (linhas - 1); i++) {
        if (contador[i] > contador[i + 1]) {
            aux = contador[i];
            contador[i] = contador[i + 1];
            contador[i + 1] = aux;

            auxi = matriz[i];
            matriz[i] = matriz[i + 1];
            matriz[i + 1] = auxi;

            aux2 = igualdade[i];
            igualdade[i] = igualdade[i + 1];
            igualdade[i + 1] = aux2;

            i = i - 2;
        }
    }

    delete[] contador;
}

void truncamento(double & num) {
    double truncatedNum = trunc(num * 1000.0) / 1000.0;
    // Arredonda para garantir que a terceira casa decimal seja a última
    num = std::round(truncatedNum * 1000.0) / 1000.0;
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

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Protótipos de função
bool verifyLinearidade(double** matriz, int linhas, int colunas); // Função para verificar se a matriz possui linhas ou colunas que são combinação linear
bool verifyZero(double** matriz, int linhas, int colunas); // Função para verificar se a matriz possui linhas ou colunas que são todas zerada
void zeros(double** matriz, int linhas, int colunas); // Função para verificar e ordenar a disposição dos zeros na matriz
double** inversivel(double** matrizLU, int linhas, int colunas); // Função inverter a matriz.
double** multMatriz(double** matrizXY, double** matrizB, int linhasXY, int colunasXY, int colunasB); // função para multiplicar duas matrizes
void truncamento(double& num); // função de truncamento
void decomposicao(double** matrizA, double** matrizL, double** matrizU, int linhas, int colunas); // Função para decompor matrizes L e U
bool verifyDiagonalZero(double** matriz, int linhas, int colunas);

int main() {
    system("chcp 1250 > nul");
    cout << std::fixed << setprecision(2);

    cout << "=========================\nMatriz A" << endl;

    // Definindo as dimensões da matriz
    int linhasA, colunasA;
    cout << "Digite o número de linhas da matriz A: ";
    cin >> linhasA;
    cout << "Digite o número de colunas da matriz A: ";
    cin >> colunasA;

    // Alocando memória para a matriz (array 2D)
    double** matrizA = new double* [linhasA];
    // Alocando memória para cada array de colunas
    for (int i = 0; i < linhasA; ++i) {
        matrizA[i] = new double[colunasA];
    }

    // Preenchendo a matriz
    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasA; ++j) {
            cout << "Digite o valor para a posição [" << i << "][" << j << "]: ";
            cin >> matrizA[i][j];
        }
    }

    bool check = verifyLinearidade(matrizA, linhasA, colunasA);

    if (check == true) {
        cout << "A matriz A não é invertível!" << endl;
    }
    else {
        cout << "=========================\nMatriz B" << endl;

        // Definindo as dimensões da matriz
        int linhasB, colunasB;
        cout << "Digite o número de linhas da matriz B: ";
        cin >> linhasB;
        cout << "Digite o número de colunas da matriz B: ";
        cin >> colunasB;

        // Alocando memória para a matriz (array 2D)
        double** matrizB = new double* [linhasB];
        // Alocando memória para cada array de colunas
        for (int i = 0; i < linhasB; ++i) {
            matrizB[i] = new double[colunasB];
        }

        // Preenchendo a matriz
        for (int i = 0; i < linhasB; ++i) {
            for (int j = 0; j < colunasB; ++j) {
                cout << "Digite o valor para a posição [" << i << "][" << j << "]: ";
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

        // Alocando memória para a matrizU (array 2D)
        double** matrizU = new double* [linhasA];
        // Alocando memória para cada array de colunas
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

        cout << "\n=============================\nMatrizL:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizL[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n=============================\nMatrizU:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizU[i][j] << " ";
            }
            cout << endl;
        }

        matrizL = inversivel(matrizL, linhasA, colunasA);
        matrizU = inversivel(matrizU, linhasA, colunasA);

        if (matrizL == nullptr || matrizU == nullptr) {
            cout << "\nA matriz U ou L não é invertível, certamente o determinante da matrizA = 0" << endl;
        }
        else {
            cout << "\n=============================\nMatrizL Invertida:" << endl;
            for (int i = 0; i < linhasA; ++i) {
                for (int j = 0; j < colunasA; ++j) {
                    // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                    cout << setw(6) << matrizL[i][j] << " ";
                }
                cout << endl;
            }

            cout << "\n=============================\nMatrizU Invertida:" << endl;
            for (int i = 0; i < linhasA; ++i) {
                for (int j = 0; j < colunasA; ++j) {
                    // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                    cout << setw(6) << matrizU[i][j] << " ";
                }
                cout << endl;
            }

            double** matrizY = multMatriz(matrizL, matrizB, linhasA, colunasA, colunasB);
            double** matrizX = multMatriz(matrizU, matrizY, linhasA, colunasA, colunasB);

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

            // Libera a memória alocada
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

// Função para multiplicar duas matrizes
double** multMatriz(double** matrizXY, double** matrizB, int linhasXY, int colunasXY, int colunasB) {
    // Cria a matriz de retorno para armazenar o resultado da multiplicação
    double** matrizResult = new double* [linhasXY];

    // Aloca memória para as linhas da matriz de resultado
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
            // Armazena o resultado na posição (i, j) da matriz de resultado
            matrizResult[i][j] = soma;
        }
    }

    return matrizResult; // Retorna a matriz resultante da multiplicação
}

// Função para calcular a inversa de uma matriz
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

    // Aplica o método de eliminação de Gauss-Jordan
    for (int i = 0; i < linhas; ++i) {
        // Faz o pivoteamento parcial
        int pivot_row = i;
        for (int j = i + 1; j < linhas; ++j) {
            if (fabs(matrizAumentada[j][i]) > fabs(matrizAumentada[pivot_row][i])) {
                pivot_row = j;
            }
        }
        // Troca as linhas se necessário
        if (pivot_row != i) {
            for (int k = 0; k < colunas * 2; ++k) {
                double temp = matrizAumentada[i][k];
                matrizAumentada[i][k] = matrizAumentada[pivot_row][k];
                matrizAumentada[pivot_row][k] = temp;
            }
        }

        // Normaliza a linha pivô
        double pivot = matrizAumentada[i][i];
        for (int j = 0; j < colunas * 2; ++j) {
            matrizAumentada[i][j] /= pivot;
        }

        // Zera as outras entradas na coluna pivô
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

    // Libera a memória alocada para a matriz aumentada
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
            // Se a linha for menor ou igual à coluna, preenche a matriz U
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
                // Calcula o elemento de L dividindo a diferença entre a entrada correspondente de A e a soma pela entrada diagonal de U
                else {
                    matrizL[i][j] = (matrizA[i][j] - soma) / matrizU[j][j];
                }
            }
        }
    }
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

// Função para reorganizar os zeros na matriz
void zeros(double** matriz, int linhas, int colunas) {
    // Array para contar o número de zeros em cada linha
    int* contador = new int[linhas] {};

    // Conta o número de zeros em cada linha
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] == 0) {
                contador[i]++;
            }
        }
    }

    // Variáveis auxiliares para ordenação
    int aux;
    double* auxi;

    // Ordena as linhas por quantidade de zeros (algoritmo de bubble sort)
    for (int i = 0; i < linhas - 1; ++i) {
        for (int j = 0; j < linhas - i - 1; ++j) {
            if (contador[j] > contador[j + 1]) {
                // Troca o número de zeros
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

    delete[] contador; // Libera a memória alocada para o array contador
}

// Função para truncar um número para três casas decimais
void truncamento(double& num) {
    // Multiplica o número por 1000 e trunca para remover as casas decimais excedentes
    double truncatedNum = trunc(num * 1000.0) / 1000.0;
    // Arredonda o número truncado para garantir que a terceira casa decimal seja a última
    num = std::round(truncatedNum * 1000.0) / 1000.0;
}
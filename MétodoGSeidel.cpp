#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

bool Diagonaldominante(double** matriz, int linhas, int coluna); // Checa se a matriz é diagonal dominante
double** GausSeidel(double** matrizA, double** matrizB, double** solucao0, int linhasA, int colunasA, double epsilon, int & cont); // Método de Gaus-Jacobi
double NormaMaxima(double** solucao1, double** solucao2, int linhas); // Cálcula o erro entre duas soluções

int main() {
    cout << std::fixed << setprecision(2);

    // Definindo as dimensões da matriz A
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
            cout << "Digite o valor para a posiaco [" << i << "][" << j << "]: ";
            cin >> matrizA[i][j];
        }
    }

    if (Diagonaldominante(matrizA, linhasA, colunasA)) {
        // Alocando memória para a matriz (array 2D)
        double** matrizB = new double* [linhasA];
        // Alocando memória para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            matrizB[i] = new double[1];
        }

        cout << "=========================\nPreencha a Matriz B" << endl;
        // Preenchendo a matriz
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                cout << "Digite o valor para a posicao [" << i << "][" << j << "]: ";
                cin >> matrizB[i][j];
            }
        }

        // Alocando memória para a matriz (array 2D)
        double** solucao = new double* [linhasA];
        // Alocando memória para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            solucao[i] = new double[1] {0};
        }

        cout << "\n=====================================================\nEntre solucao Inicial:" << endl;;
        // Preenchendo a matriz
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                cout << "Digite o valor para a posição [" << i << "][" << j << "]: ";
                cin >> solucao[i][j];
            }
        }

        cout << "\n=====================================================\nQual a precisao de Epsilon (Ex: 0.000001)? ";
        double epsilon;
        cin >> epsilon;

        system("cls");

        cout << "=====================================================\nMatrizA:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < colunasA; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizA[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n=====================================================\nMatriz B:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << matrizB[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n=====================================================\nSolucao Inicial:" << endl;;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << solucao[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n=====================================================\nCom a precisao Epsilon = ";
        std::cout << std::defaultfloat << epsilon;

        int cont = 0;

        cout << "\n=====================================================\nIteracoes:";

        solucao = GausSeidel(matrizA, matrizB, solucao, linhasA, colunasA, epsilon, cont);

        cout << std::fixed << setprecision(4);

        cout << "\n\n=====================================================\nSolucao para o sistema:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << solucao[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n=====================================================\nConvergiu em: " << cont << " iteracoes!" << endl;

        // Libera a memória alocada
        for (int i = 0; i < linhasA; ++i) {
            delete[] matrizB[i];
            delete[] solucao[i];
        }
        delete[] matrizB;
        delete[] solucao;
    }
    else {
        cout << "A matriz não é diagonal dominante, logo ela nao convergirá, tente outra matriz!" << endl;
    }

    // Libera a memória alocada
    for (int i = 0; i < linhasA; ++i) {
        delete[] matrizA[i];
    }
    delete[] matrizA;

    return 0;
}

double** GausSeidel(double** matrizA, double** matrizB, double** solucao0, int linhasA, int colunasA, double epsilon, int & cont) {
    double** solucao1 = new double* [linhasA];
    for (int i = 0; i < linhasA; ++i) {
        solucao1[i] = new double[1] {0};
    }

    double normaAtual = epsilon + 1; // Inicializa a norma com um valor maior que epsilon
    while (normaAtual >= epsilon) {
        // Atualiza a solução
        for (int i = 0; i < linhasA; ++i) {
            double soma = matrizB[i][0] / matrizA[i][i];

            for (int c = 0; c < i; c++)
            {
                if (i != c) {
                    soma -= (matrizA[i][c] * solucao1[c][0]) / matrizA[i][i];
                }
            }

            for (int j = i; j < colunasA; ++j) {
                if (i != j) {
                    soma -= (matrizA[i][j] * solucao0[j][0]) / matrizA[i][i];
                }
            }

            solucao1[i][0] = soma;
        }

        // Calcula a norma entre as soluções
        double norma = NormaMaxima(solucao1, solucao0, linhasA);

        // Atualiza a norma atual
        normaAtual = norma;

        // Atualiza a solução anterior para a próxima iteração
        for (int i = 0; i < linhasA; ++i) {
            solucao0[i][0] = solucao1[i][0];
        }

        cont++;

        if (normaAtual >= epsilon) {
            if (cont == 1) {
                cout << "\n\nIteracao " << cont << " :" << endl;
            }
            else {
                cout << "\n=====================================================\nIteracao " << cont << " :" << endl;
            }

            for (int i = 0; i < linhasA; ++i) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << std::fixed << setprecision(4);
                cout << setw(6) << solucao1[i][0] << " ";
                cout << endl;
            }
        }
    }

    return solucao1;
}

double NormaMaxima(double** solucao1, double** solucao2, int linhas) {
    double maxDiferenca = 0.0;

    for (size_t i = 0; i < linhas; i++) {
        double diferenca = abs(solucao2[i][0] - solucao1[i][0]);
        if (diferenca > maxDiferenca) {
            maxDiferenca = diferenca;
        }
    }

    return maxDiferenca;
}

bool Diagonaldominante(double** matriz, int linhas, int colunas) {

    double soma = 0.0;

    for (size_t i = 0; i < linhas; i++) {
        soma = 0.0;
        for (size_t j = 0; j < colunas; j++) {
            if (i != j) {
                soma += abs(matriz[i][j]);
            }
        }
        if (abs(matriz[i][i]) <= soma) {
            return false;
        }
    }

    return true;
}
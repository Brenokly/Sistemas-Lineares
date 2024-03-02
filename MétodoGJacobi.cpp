#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

bool Diagonaldominante(double ** matriz, int linhas, int coluna); // Checa se a matriz � diagonal dominante
double** GausJacobi(double** matrizA, double** matrizB, double** solucao, int linhasA, int colunasA, double epsilon); // M�todo de Gaus-Jacobi
double NormaMatricial(double** solucao1, double** solucao2, int linhas); // C�lcula o erro entre duas solu��es

int main() {
    cout << std::fixed << setprecision(2);
    system("chcp 1252 > nul");

    // Definindo as dimens�es da matriz A
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

    if (Diagonaldominante(matrizA, linhasA, colunasA)) {
        // Alocando mem�ria para a matriz (array 2D)
        double** matrizB = new double* [linhasA];
        // Alocando mem�ria para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            matrizB[i] = new double[1];
        }

        cout << "=========================\nPreencha a Matriz B" << endl;
        // Preenchendo a matriz
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                cout << "Digite o valor para a posi��o [" << i << "][" << j << "]: ";
                cin >> matrizB[i][j];
            }
        }

        // Alocando mem�ria para a matriz (array 2D)
        double** solucao = new double* [linhasA];
        // Alocando mem�ria para cada array de colunas
        for (int i = 0; i < linhasA; ++i) {
            solucao[i] = new double[1] {0};
        }

        cout << "\n=====================================================\nEntre solu��o Inicial:" << endl;;
        // Preenchendo a matriz
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                cout << "Digite o valor para a posi��o [" << i << "][" << j << "]: ";
                cin >> solucao[i][j];
            }
        }
      
        cout << "\n=====================================================\nQual a precis�o de Epsilon (Ex: 0.000001)? ";
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

        cout << "\n=====================================================\nSolu��o Inicial:" << endl;;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << solucao[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n=====================================================\nCom a precis�o Epsilon = ";
        std::cout << std::defaultfloat << epsilon;

        solucao = GausJacobi(matrizA, matrizB, solucao, linhasA, colunasA, epsilon);

        cout << std::fixed << setprecision(2);
        
        cout << "\n\n=====================================================\nSolu��o para o sistema:" << endl;
        for (int i = 0; i < linhasA; ++i) {
            for (int j = 0; j < 1; ++j) {
                // Ajuste o campo de largura para 10 caracteres para alinhar os elementos
                cout << setw(6) << solucao[i][j] << " ";
            }
            cout << endl;
        }

        // Libera a mem�ria alocada
        for (int i = 0; i < linhasA; ++i) {
            delete[] matrizB[i];
            delete[] solucao[i];
        }
        delete[] matrizB;
        delete[] solucao;
    }

    // Libera a mem�ria alocada
    for (int i = 0; i < linhasA; ++i) {
        delete[] matrizA[i];
    }
    delete[] matrizA;
		
	return 0;
}

double** GausJacobi(double** matrizA, double** matrizB, double** solucao0, int linhasA, int colunasA, double epsilon) {
    double** solucao1 = new double* [linhasA];
    for (int i = 0; i < linhasA; ++i) {
        solucao1[i] = new double[1] {0};
    }

    double normaAtual = epsilon + 1; // Inicializa a norma com um valor maior que epsilon
    while (normaAtual >= epsilon) {
        // Atualiza a solu��o
        for (int i = 0; i < linhasA; ++i) {
            double soma = matrizB[i][0] / matrizA[i][i];
            for (int j = 0; j < colunasA; ++j) {
                if (i != j) {
                    soma -= (matrizA[i][j] * solucao0[j][0]) / matrizA[i][i];
                }
            }
            solucao1[i][0] = soma;
        }

        // Calcula a norma entre as solu��es
        double norma = NormaMatricial(solucao1, solucao0, linhasA);

        // Atualiza a norma atual
        normaAtual = norma;

        // Atualiza a solu��o anterior para a pr�xima itera��o
        for (int i = 0; i < linhasA; ++i) {
            solucao0[i][0] = solucao1[i][0];
        }
    }

    return solucao1;
}

double NormaMatricial(double** solucao1, double** solucao2, int linhas) {
    
    double normaNumerador = 0.0;
    double normaDenominador = 0.0;

    for (size_t i = 0; i < linhas; i++)
    {
        normaNumerador += solucao2[i][0] - solucao1[i][0] ;
        normaDenominador += solucao2[i][0];
    }

    return abs(normaNumerador) / abs(normaDenominador);
}

bool Diagonaldominante(double** matriz, int linhas, int colunas) {

	double soma = 0.0;

	for (size_t i = 0; i < linhas; i++){
		soma = 0.0;
		for (size_t j = 0; j < colunas; j++){
			if (i != j) {
				soma += abs(matriz[i][j]);
			}
		}
		if (abs(matriz[i][i]) < soma) {
			return false;
		}
	}

	return true;
}
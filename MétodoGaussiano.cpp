#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Prot�tipos de fun��o
bool verifyLinearidade(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o combina��o linear
bool verifyZero(double** matriz, int linhas, int colunas); // Fun��o para verificar se a matriz possui linhas ou colunas que s�o todas zerada
void zeros(double** matriz, double* igualdade, int linhas, int colunas); // Fun��o para verificar e ordenar a disposi��o dos zeros na matriz
bool escalonar(double** matriz, double* igualdade, double* coeficientes, int linhas, int colunas); // Fun��o para escalonar a matriz.
void truncamento(double & num);

int main() {
    system("chcp 1250 > nul");
    cout << std::fixed << setprecision(2);

    // Definindo as dimens�es da matriz
    int linhas, colunas;
    cout << "Digite o n�mero de linhas da matriz: ";
    cin >> linhas;
    cout << "Digite o n�mero de colunas da matriz: ";
    cin >> colunas;

    // Alocando mem�ria para a matriz (array 2D)
    double** matriz = new double* [linhas];
    // Alocando mem�ria para cada array de colunas
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new double[colunas];
    }

    // Preenchendo a matriz
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << "Digite o valor para a posi��o [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }

    // Array para os valores do lado direito das equa��es
    double* igualdade = new double[linhas] {0.0};
    // Array para os coeficientes das vari�veis
    double* coeficientes = new double[linhas] {0.0};

    cout << "Digite os coeficientes:" << endl;
    for (int i = 0; i < linhas; i++) {
        cout << "x" << (i + 1) << " = ";
        cin >> igualdade[i];
    }

    // Verifica se h� combina��o linear nas linhas da matriz
    bool deltcheck = verifyLinearidade(matriz, linhas, colunas);
    if (deltcheck == true) {
        cout << "\nA matriz possui linhas que s�o combina��o linear, logo o determinante � igual a 0." << endl;
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
            // Exibe a solu��o do sistema
            cout << "\n=============================\nResolu��o do sistema:\n" << endl;
            for (int i = 0; i < linhas; i++) {
                cout << "x" << (i + 1) << ": " << coeficientes[i] << endl;
            }
            cout << "=============================\n";
        }
        else {
            cout << "\nO sistema n�o possui solu��o �nica determinada!" << endl;
        }
    }

    // Libera a mem�ria alocada
    for (int i = 0; i < linhas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}

// Fun��o para escalonar a matriz
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

    // Inicializa��o do vetor de coeficientes pegando o �ltimo coeficiente de gra�a
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

bool verifyZero(double** matriz, int linhas, int colunas) { // Fun��o para verificar se a matriz possui linhas ou colunas que s�o todas zerada
    
    // Verifica se h� linhas ou colunas completamente zeradas
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
// Fun��o para verificar se a matriz possui linhas ou colunas que s�o combina��o linear
bool verifyLinearidade(double** matriz, int linhas, int colunas) {
    bool check = false;
    double quociente = 0.0;

    // Verifica se h� linhas que s�o combina��o linear
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

    // Verifica se h� colunas que s�o combina��o linear
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

// Fun��o para reorganizar os zeros na matriz
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
    // Arredonda para garantir que a terceira casa decimal seja a �ltima
    num = std::round(truncatedNum * 1000.0) / 1000.0;
}
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Função para trocar duas linhas de uma matriz
void swapRows(vector<vector<double>>& matrix, int row1, int row2) {
    vector<double> temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}

// Função para calcular o determinante de uma matriz usando decomposição LU
double determinant(vector<vector<double>>& matrix) {
    int n = matrix.size(); // Tamanho da matriz
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

int main() {
    int n;
    cout << "Digite o tamanho da matriz quadrada: ";
    cin >> n;

    // Criando a matriz
    vector<vector<double>> matrix(n, vector<double>(n));

    // Pedindo os elementos da matriz
    cout << "Digite os elementos da matriz:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Digite o valor para a posição [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }

    // Calculando o determinante
    double det = determinant(matrix);

    // Exibindo o determinante com 5 casas decimais
    cout.precision(5);
    cout << "Determinante: " << fixed << det << endl;

    return 0;
}

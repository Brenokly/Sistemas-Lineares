#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Função para encontrar a inversa de uma matriz
vector<vector<double>> inverseMatrix(vector<vector<double>>& matrix) {
    // Obtenção do tamanho da matriz
    int n = matrix.size();

    // Criando uma matriz de identidade para armazenar a inversa
    vector<vector<double>> identity(n, vector<double>(n, 0));
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
double frobeniusNorm(vector<vector<double>>& matrix) {
    double norm = 0.0;
    for (const auto& row : matrix) {
        for (double element : row) {
            norm += element * element;
        }
    }
    return sqrt(norm);
}

// Função para calcular o número de condição de uma matriz
double conditionNumber(vector<vector<double>>& matrix) {
    // Encontrando a inversa da matriz
    vector<vector<double>> inverse = inverseMatrix(matrix);

    // Calculando as normas Frobenius da matriz e de sua inversa
    double normA = frobeniusNorm(matrix);
    double normAInverse = frobeniusNorm(inverse);

    // Calculando o número de condição
    return normA * normAInverse;
}

int main() {
    system("chcp 1252 > nul");

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

    // Calculando o número de condição
    double condNumber = conditionNumber(matrix);

    // Exibindo o número de condição
    cout << "Número de condicionamento: " << condNumber << endl;

    return 0;
}
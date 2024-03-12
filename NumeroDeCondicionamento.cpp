#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

// Fun��o para encontrar a inversa de uma matriz
vector<vector<double>> inverseMatrix(vector<vector<double>>& matrix) {
    // Obten��o do tamanho da matriz
    int n = matrix.size();

    // Criando uma matriz de identidade para armazenar a inversa
    vector<vector<double>> identity(n, vector<double>(n, 0));
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
double frobeniusNorm(vector<vector<double>>& matrix) {
    double norm = 0.0;
    for (const auto& row : matrix) {
        for (double element : row) {
            norm += element * element;
        }
    }
    return sqrt(norm);
}

int main() {
    system("chcp 1252 > nul");
    cout << std::fixed << setprecision(2);

    int n;
    cout << "Digite o tamanho da matriz quadrada: ";
    cin >> n;

    // Criando a matriz
    vector<vector<double>> matrix(n, vector<double>(n));

    // Pedindo os elementos da matriz
    cout << "Digite os elementos da matriz:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Digite o valor para a posi��o [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }

    // Linha de separa��o e t�tulo da matriz A
    cout << "=====================================================\nMatriz A:" << endl;

    // Imprimindo a matriz original
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(6) << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Encontrando a inversa da matriz
    vector<vector<double>> inverse = inverseMatrix(matrix);

    // Imprimindo a matriz inversa
    cout << "=====================================================\nMatriz A^-1:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(6) << inverse[i][j] << " ";
        }
        cout << endl;
    }

    cout << std::fixed << setprecision(4);

    // Calculando e exibindo a norma de A
    double normA = frobeniusNorm(matrix);
    cout << "=====================================================\nNorma de A: " << normA << endl;

    cout << "\n";

    // Calculando e exibindo a norma de A^-1
    double normAInverse = frobeniusNorm(inverse);
    cout << "Norma de A^-1: " << normAInverse << endl;

    // Calculando e exibindo o n�mero de condi��o
    double condNumber = normA * normAInverse;
    cout << "=====================================================\nN�mero de condicionamento: " << condNumber << endl;

    return 0;
}
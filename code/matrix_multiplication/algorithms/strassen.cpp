
/***************************************************************************************
*    Title: strassenMultiply source code
*    Author: Basado en artículo de GeeksforGeeks
*    Date: 2025
*    Code version: Modificado
*    Availability: https://www.geeksforgeeks.org/strassens-matrix-multiplication/
***************************************************************************************/
#include <vector>

using Matrix = std::vector<std::vector<int>>;

// Función única para suma/resta con parámetro de signo
Matrix matrixOperation(const Matrix& A, const Matrix& B, int sign = 1) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + (sign * B[i][j]);
        }
    }
    return C;
}

Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));

    // Caso base
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    
    // Submatrices
    Matrix A11(newSize, std::vector<int>(newSize, 0));
    Matrix A12(newSize, std::vector<int>(newSize, 0));
    Matrix A21(newSize, std::vector<int>(newSize, 0));
    Matrix A22(newSize, std::vector<int>(newSize, 0));
    Matrix B11(newSize, std::vector<int>(newSize, 0));
    Matrix B12(newSize, std::vector<int>(newSize, 0));
    Matrix B21(newSize, std::vector<int>(newSize, 0));
    Matrix B22(newSize, std::vector<int>(newSize, 0));

    // Dividir matrices en submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Las 7 multiplicaciones de Strassen
    Matrix M1 = strassenMultiply(matrixOperation(A11, A22), matrixOperation(B11, B22));
    Matrix M2 = strassenMultiply(matrixOperation(A21, A22), B11);
    Matrix M3 = strassenMultiply(A11, matrixOperation(B12, B22, -1));
    Matrix M4 = strassenMultiply(A22, matrixOperation(B21, B11, -1));
    Matrix M5 = strassenMultiply(matrixOperation(A11, A12), B22);
    Matrix M6 = strassenMultiply(matrixOperation(A21, A11, -1), matrixOperation(B11, B12));
    Matrix M7 = strassenMultiply(matrixOperation(A12, A22, -1), matrixOperation(B21, B22));

    // Calcular submatrices del resultado
    Matrix C11 = matrixOperation(matrixOperation(M1, M4), matrixOperation(M7, M5, -1));
    Matrix C12 = matrixOperation(M3, M5);
    Matrix C21 = matrixOperation(M2, M4);
    Matrix C22 = matrixOperation(matrixOperation(M1, M3), matrixOperation(M6, M2, -1));

    // Combinar submatrices en el resultado final
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}
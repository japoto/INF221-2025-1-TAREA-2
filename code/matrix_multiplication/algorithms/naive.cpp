/***************************************************************************************
*    Title: naiveMultiply source code
*    Author: Basado en código de Dev-XYS
*    Date: 2025
*    Code version: Modificado
*    Availability: https://github.com/Dev-XYS/Algorithms/blob/master/Matrix-Multiplication(Naive).cpp
***************************************************************************************/

#include <vector>

std::vector<std::vector<int>> naiveMultiply(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B
) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

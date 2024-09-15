#include <array>
#include <utility>
#include <iostream>

template <int N>
constexpr std::array<std::array<int, N - 1>, N - 1> Minor(const std::array<std::array<int, N>, N>& matrix, int col) 
{
    std::array<std::array<int, N - 1>, N - 1> minor{};
    for (int i = 0; i < N - 1; ++i)
        for (int j = 0; j < N - 1; ++j)
            (&std::get<0>(((&std::get<0>(minor))[i])))[j] = matrix[i + 1][j + (j >= col ? 1 : 0)];
            //minor[i][j] = matrix[i + 1][j + (j >= col ? 1 : 0)];

    return minor;
}

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N>& matrix) 
{
    if (N <= 1) 
        return matrix[0][0];

    int result = 0;
    for (int col = 0; col < N; ++col) {
        int sign = (col % 2 == 0) ? 1 : -1;
        result += sign * matrix[0][col] * Det<N - 1>(Minor<N>(matrix, col));
    }
    return result;
}

template <>
constexpr int Det<1>(const std::array<std::array<int, 1>, 1>& matrix)
{
    return matrix[0][0];
}

int main() {
    constexpr std::array<std::array<int, 3>, 3> matrix = { {
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 7}
    } };
    constexpr std::array<std::array<int, 4>, 4> matrix4 = { {
        {0, 1, 2, 1},
        {1, 2, 3, 2},
        {2, 3, 7, 3},
        {1, 0, 6, 4}
    } };

    constexpr int result = Det<3>(matrix);
    std::cout << result << std::endl;
    constexpr int result1 = Det<4>(matrix4);
    std::cout << result1 << std::endl;
    return 0;
}

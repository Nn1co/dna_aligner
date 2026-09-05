#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int match{1};
const int mismatch{-1};
const int gap{-2};

std::vector<std::vector<int>> matrix_create(size_t rows, size_t columns);
int best_op(int dia, int up, int left, char a, char b);

int main(int argc,char* argv[]) {
    if (argc != 2) {std::cerr << "not good numbers of arguments"; return 1;}

    std::vector<std::string> adns;

    std::ifstream file(argv[1]);
    if (!file) {std::cerr << "error opening the file";  return 1;}
    std::string line;

    while (std::getline(file, line)) {
        if (line.at(0) == '>' && !adns.empty()) {
           adns.emplace_back();
        } else {
            adns.back() += line;
        }
    }

    size_t f_adn_len{adns[0].size()};
    size_t s_adn_len{adns[1].size()};

    std::vector<std::vector<int>> matrix{matrix_create(f_adn_len, s_adn_len)};

    for (size_t i{1}; i < f_adn_len - 1; i++) {
        for (size_t j{1}; j < s_adn_len - 1; j++) {
            matrix[i][j] = best_op(matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1], adns[0].at(i), adns[1].at(j));
        }
    }

}

std::vector<std::vector<int>> matrix_create(size_t rows, size_t columns) {
    std::vector<std::vector<int>> matrix{rows};
    for (size_t i{0}; i < rows; i++) {
        matrix.resize(columns);
    }
    for (size_t i{0}; i < rows; i++) {
        matrix[i][0] = -i * gap;
    }
    for (size_t i{1}; i < columns; i++) {
        matrix[0][i] = -i * gap;
    }
    return matrix;
}

int best_op(int dia, int up, int left, char a, char b) {
    int r_dia{};
    int r_up{up + gap};
    int r_left{left + gap};

    if (a == b) {
        r_dia = dia + match;
    } else {r_dia = dia + mismatch;}

    int max = std::max(r_up, r_left);
    return std::max(max, r_dia);
}

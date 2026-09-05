#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> matrix_create(size_t rows, size_t columns, int gap);

int main(int argc,char* argv[]) {
    if (argc != 2) {std::cerr << "net good numbers of arguments"; return 1;}

    std::vector<std::vector<std::string>> adns;
    int index = -1;

    const int match{1};
    const int mismatch{-1};
    const int gap{-2};

    std::ifstream file(argv[1]);
    if (!file) {std::cerr << "error opening the file";  return 1;}
    std::string line;

    while (std::getline(file, line)) {
        if (line.at(0) == '>') {
            adns.push_back(std::vector<std::string>{});
            index++;
        } else {
            adns[index].push_back(line);
        }
    }

    size_t f_adn_len{adns[0].size()};
    size_t s_adn_len{adns[1].size()};

    std::vector<std::vector<int>> matrix{matrix_create(f_adn_len, s_adn_len, gap)};
    

}

std::vector<std::vector<int>> matrix_create(size_t rows, size_t columns, int gap) {
    std::vector<std::vector<int>> matrix{rows};
    for (size_t i{0}; i < rows; i++) {
        matrix.resize(columns);
    }
    for (size_t i{0}; i < rows; i++) {
        matrix[i][0] = -i * gap;
        matrix[0][i] = -i * gap;
    }
    return matrix;
}

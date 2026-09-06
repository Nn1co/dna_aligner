#pragma once

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



class DnsSequece {
    private:
        const int match{1};
        const int mismatch{-1};
        const int gap{-2};

        std::vector<std::string> adns;
        size_t f_adn_len{};
        size_t s_adn_len{};

        std::vector<std::vector<int>> matrix{};
        std::vector<char> a{};
        std::vector<char> b{};
        std::string sequence_a{};
        std::string sequence_b{};

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

    public:
        DnsSequece(char* file_name) {
            std::ifstream file(file_name);
            if (!file) {std::cerr << "error opening the file";}
            std::string line;

            while (std::getline(file, line)) {
                if (line.at(0) == '>') {
                   adns.emplace_back();
                } else {
                    adns.back() += line;
                }
            }
            f_adn_len = adns[0].size() + 1;
            s_adn_len = adns[1].size() + 1;

            matrix = matrix_create(f_adn_len, s_adn_len);
        }

        std::string get_original_a() {
            return adns[0];
        }

        std::string get_original_b() {
            return adns[1];
        }

        std::string get_modif_a() {
            if (a.empty()) return "empty";
            if (sequence_a.empty()) {
                for (char leter: a) {
                    sequence_a.push_back(leter);
                }
            }
            return sequence_a;
        }

        std::string get_modif_b() {
            if (b.empty()) return "empty";
            if (sequence_b.empty()) {
                for (char leter: b) {
                    sequence_b.push_back(leter);
                }
            }
            return sequence_b;
        }



};

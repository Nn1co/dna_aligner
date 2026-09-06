#pragma once

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "node.hpp"


class DnsSequece {
    private:
        const int match{1};
        const int mismatch{-1};
        const int gap{-2};

        std::vector<std::string> adns;
        size_t f_adn_len{};
        size_t s_adn_len{};

        std::vector<std::vector<Node>> matrix{};
        std::vector<char> a{};
        std::vector<char> b{};
        std::string sequence_a{};
        std::string sequence_b{};

        std::vector<std::vector<Node>> matrix_create(size_t rows, size_t columns) {
            std::vector<std::vector<Node>> matrix{rows};
            for (size_t i{0}; i < rows; i++) {
                for (size_t j{0}; j < columns; j++) {
                    matrix[i].emplace_back(
                        static_cast<int>(i),
                        static_cast<int>(j)
                    );
                }
            }
            for (size_t i{0}; i < rows; i++) {
                matrix[i][0].change_value(-i * gap);
            }
            for (size_t i{1}; i < columns; i++) {
                matrix[0][i].change_value(-i * gap);
            }
            return matrix;
        }
        void fill_matrix() {
            for (size_t i{1}; i < f_adn_len; i++) {
                for (size_t j{1}; j < s_adn_len; j++) {
                    int dia{matrix[i - 1][j - 1].get_value()};
                    if (adns[0].at(i - 1) == adns[1].at(j - 1)) dia += match;
                    else dia += mismatch;
                    int up{matrix[i - 1][j].get_value() + gap};
                    int left{matrix[i][j - 1].get_value() + gap};

                    if (dia >= left && dia >= up) {
                        matrix[i][j].change_value(dia);
                        matrix[i][j].change_prev(&matrix[i - 1][j - 1]);
                    } else if (left >= up) {
                        matrix[i][j].change_value(left);
                        matrix[i][j].change_prev(&matrix[i][j - 1]);
                    } else {
                        matrix[i][j].change_value(up);
                        matrix[i][j].change_prev(&matrix[i - 1][j]);
                    }
                }
            }
        }
        void make_sequence() {
            Node* act = matrix[f_adn_len - 1][s_adn_len - 1].get_prev();
            sequence_a = adns[0].at(f_adn_len - 2);
            sequence_b = adns[1].at(s_adn_len - 2);
            int i = f_adn_len;
            int j = s_adn_len;
            while (act->get_prev() != nullptr) {
                if (act->get_i() == 0 && act->get_j() == 0) break;
                if (i != act->get_i()) {
                    sequence_a.push_back(adns[0].at(act->get_i() - 1));
                } else {
                    sequence_a.push_back(' ');
                }
                if (j != act->get_j()) {
                    sequence_b.push_back(adns[1].at(act->get_j() - 1));
                } else {
                    sequence_b.push_back(' ');
                }
                i = act->get_i();
                j = act->get_j();
                act = act->get_prev();
            }
            std::reverse(sequence_a.begin(), sequence_a.end());
            std::reverse(sequence_b.begin(), sequence_b.end());
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
            fill_matrix();
            make_sequence();
        }

        std::string get_original_a() {return adns[0];}
        std::string get_original_b() {return adns[1];}
        std::string get_modif_a() {
            return sequence_a;
        }
        std::string get_modif_b() {
            return sequence_b;
        }

};

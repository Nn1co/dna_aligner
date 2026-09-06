#include <cstddef>
#include <iostream>
#include "dnsSequence.hpp"

int main(int argc,char* argv[]) {
    if (argc != 2) {std::cerr << "not good numbers of arguments"; return 1;}

    DnsSequece data = DnsSequece(argv[1]);
    std::cout << data.get_original_a() << "\n";
    std::cout << data.get_original_b() << "\n";
    std::cout << data.get_modif_a() << "\n";
    std::cout << data.get_modif_b() << "\n";
}

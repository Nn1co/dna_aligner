cmake_minimum_required(VERSION 3.16)
project(dna_aligner LANGUAGES CXX)

add_executable(dna_aligner src/main.cpp)
target_compile_features(dna_aligner PRIVATE cxx_std_17)
set_target_properties(dna_aligner PROPERTIES CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(dna_aligner PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME toy_pair
    COMMAND dna_aligner "${CMAKE_CURRENT_SOURCE_DIR}/fasta_files/toy_pair.fasta"
)
set_tests_properties(toy_pair PROPERTIES TIMEOUT 5)

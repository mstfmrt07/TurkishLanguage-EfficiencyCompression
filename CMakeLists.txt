cmake_minimum_required(VERSION 3.10)
project(TurkishLanguage-CompressionEfficiency)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

add_executable(huffman src/main.cpp)
target_link_libraries(huffman huffman_lib)
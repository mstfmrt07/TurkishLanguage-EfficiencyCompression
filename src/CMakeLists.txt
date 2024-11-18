file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library(huffman_lib ${SOURCES})

target_include_directories(huffman_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
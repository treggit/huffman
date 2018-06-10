cmake_minimum_required(VERSION 3.8)
project(huffman_lib)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funsigned-char")

add_library(huffman_lib include/huffman_tree.h huffman_tree.cpp
        include/huffman_encoder.h huffman_encoder.cpp
        include/huffman_decoder.h huffman_decoder.cpp
        include/huffman_code.h
        include/packager.h
        include/frequency.h
        frequency.cpp include/huffman_consts.h)

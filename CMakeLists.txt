cmake_minimum_required(VERSION 3.9)
project(huffman)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -funsigned-char")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fprofile-instr-generate -fcoverage-mapping -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-instr-generate -fcoverage-mapping -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories({$CMAKE_SOURCE_DIR}/lib/huffman-lib/include)
include_directories({$CMAKE_SOURCE_DIR}/lib)

add_subdirectory(lib/huffman-lib)

add_executable(huffman src/main.cpp src/buffered_reader.cpp src/buffered_reader.h src/buffered_writer.cpp src/buffered_writer.h src/compress_utills.cpp src/compress_utills.h)

target_link_libraries(huffman huffman_lib)

add_executable(huffman_testing test/huffman_testing.cpp lib/gtest/gtest-all.cc lib/gtest/gtest.h lib/gtest/gtest_main.cc test/randomizer.cpp test/randomizer.h)

target_link_libraries(huffman_testing huffman_lib -lgmp -lgmpxx -lpthread)
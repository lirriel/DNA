cmake_minimum_required(VERSION 3.6)
project(dna)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dna_element.h dna_repairer.cpp dna_repairer.h linked_list.h linked_list.hpp dna_element.cpp)
add_executable(dna ${SOURCE_FILES})
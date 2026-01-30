cmake_minimum_required(VERSION 3.10)
project(SumaArreglosParalela)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(suma_arreglos_paralela suma_arreglos_paralela.cpp)
target_link_libraries(suma_arreglos_paralela OpenMP::OpenMP_CXX)

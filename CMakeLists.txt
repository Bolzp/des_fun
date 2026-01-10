cmake_minimum_required(VERSION 3.25)
project(des_fun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(des_fun
  src/des_fun.cpp)

target_include_directories(des_fun PRIVATE include)

set_target_properties(des_fun PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

target_compile_options(des_fun PRIVATE -g -O0 -Wall -Wextra)
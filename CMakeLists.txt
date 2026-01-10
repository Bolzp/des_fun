cmake_minimum_required(VERSION 3.25)
project(des_fun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

option(DES_FUN_BUILD_SHARED "Build des_fun as a shared library" ON)
if(DES_FUN_BUILD_SHARED)
  add_library(des_fun_lib SHARED src/des_fun.cpp)
else()
  add_library(des_fun_lib STATIC src/des_fun.cpp)
endif()

target_include_directories(des_fun_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(des_fun_lib PRIVATE -g -O0 -Wall -Wextra)

add_executable(des_fun src/main.cpp)
target_link_libraries(des_fun PRIVATE des_fun_lib)
target_compile_options(des_fun PRIVATE -g -O0 -Wall -Wextra)

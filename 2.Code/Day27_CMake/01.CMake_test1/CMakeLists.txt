# 1. 指定CMake最低版本
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称（随便起）
project(single_file_program)

# 3. 生成可执行文件：add_executable(生成的程序名 源码文件)
add_executable(single_file_program main.cc)

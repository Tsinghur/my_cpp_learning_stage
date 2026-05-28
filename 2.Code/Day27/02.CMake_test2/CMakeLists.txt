# CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(TCP_Server_Client)

# 指定 C++17 标准（Linux 开发必备）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==============================================
# 关键：用 add_executable 分别生成两个可执行文件！
# ==============================================

# 生成服务端程序：server
add_executable(server src/server.cc)

# 生成客户端程序：client
add_executable(client src/client.cc)

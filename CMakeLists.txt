cmake_minimum_required(VERSION 3.14)
project(runax C)

set(CMAKE_C_STANDARD 11)

add_executable(runax main.c runAsX.c runAsX.h)
target_link_libraries(runax Userenv)

add_executable(lsp lsp/main.c)
target_link_libraries(lsp psapi)
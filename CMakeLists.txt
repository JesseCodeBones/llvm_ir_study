cmake_minimum_required(VERSION 3.0.0)
project(llvm_ir_exec VERSION 0.1.0 LANGUAGES C CXX)
find_package(LLVM REQUIRED CONFIG)
include(CTest)
enable_testing()

add_executable(llvm_ir_exec main.cpp)
target_link_libraries(llvm_ir_exec LLVM)
include_directories(/usr/include/llvm-15)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

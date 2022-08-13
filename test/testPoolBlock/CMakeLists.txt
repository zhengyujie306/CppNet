cmake_minimum_required(VERSION 3.10)
project(testPoolBlock)

add_executable(${PROJECT_NAME} testPoolBlock.cpp)

target_link_libraries(${PROJECT_NAME} cppnet)

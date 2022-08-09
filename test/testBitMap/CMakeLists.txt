cmake_minimum_required(VERSION 3.10)
project(testBitMap)

add_executable(${PROJECT_NAME} testBitMap.cpp)

target_link_libraries(${PROJECT_NAME} cppnet)

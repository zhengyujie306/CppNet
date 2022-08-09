cmake_minimum_required(VERSION 3.10)
project(testTimer)

add_executable(${PROJECT_NAME} testTimer.cpp)

target_link_libraries(${PROJECT_NAME} cppnet)

cmake_minimum_required(VERSION 3.16)
project(IOSet)

set(CMAKE_CXX_STANDARD 20)


add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC "-fconcepts")
#target_compile_options(${PROJECT_NAME} PUBLIC "-ftemplate-depth=10000") # Only uncomment if sufficient RAM is available

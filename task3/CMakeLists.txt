cmake_minimum_required(VERSION 3.28)


set(PROJECT_NAME task_12)
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDART_REQUIRED TRUE)


add_executable("${PROJECT_NAME}" main.cpp class.cpp class.hpp)

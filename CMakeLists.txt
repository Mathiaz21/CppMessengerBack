cmake_minimum_required(VERSION 3.20)

project(MessengerppBack VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("./src")

add_executable(MessengerppBack main.cpp)


target_link_libraries(MessengerppBack 
    BackFunctions
    )
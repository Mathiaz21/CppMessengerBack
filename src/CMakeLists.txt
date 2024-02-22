cmake_minimum_required(VERSION 3.20)

project(MessengerppBack VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MessengerppBack main.cpp)


target_include_directories( MessengerppBack
    PUBLIC "/usr/local/include/mongocxx/v_noabi"
    PUBLIC "/usr/local/include/bsoncxx/v_noabi"
    PUBLIC "/usr/local/include/bsoncxx/v_noabi/bsoncxx/third_party/mnmlstc"
    PUBLIC "/usr/local/lib"
    )

link_directories("/usr/local/lib")

target_link_libraries(MessengerppBack 
    mongocxx
    bsoncxx
    )
add_library(BackFunctions DbCommunication.cpp)

target_include_directories( BackFunctions
    PUBLIC "/usr/local/include/mongocxx/v_noabi"
    PUBLIC "/usr/local/include/bsoncxx/v_noabi"
    PUBLIC "/usr/local/include/bsoncxx/v_noabi/bsoncxx/third_party/mnmlstc"
    )

link_directories("/usr/local/lib")

target_link_libraries(BackFunctions
    mongocxx
    bsoncxx
    )
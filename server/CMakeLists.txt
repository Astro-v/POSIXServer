add_executable(POSIXServer main.cpp POSIXClient.cpp POSIXServer.cpp Server.cpp)

target_link_libraries(POSIXServer PUBLIC libPosix)

target_include_directories(POSIXServer PUBLIC include)
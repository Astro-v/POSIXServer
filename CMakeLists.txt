cmake_minimum_required(VERSION 3.10)

project(POSIXServer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libPosix)

add_subdirectory(server)
add_subdirectory(client)
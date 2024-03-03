add_executable(POSIXClient main.cpp)

target_link_libraries(POSIXClient PUBLIC libPosix)

target_include_directories(POSIXClient PUBLIC include)
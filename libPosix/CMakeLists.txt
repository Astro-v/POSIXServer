add_library(libPosix POSIXSocket.cpp POSIXListener.cpp POSIXAddress.cpp)

target_include_directories(libPosix PUBLIC include)
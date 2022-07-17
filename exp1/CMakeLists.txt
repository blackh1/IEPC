cmake_minimum_required(VERSION 3.2)
project(exp1 VERSION 1.0)
add_subdirectory(./src)
# add_subdirectory(./include)
link_directories("../thirdparty/ssl/lib64")
include_directories("../thirdparty/ssl/include")
# set(CMAKE_CXX_FLAGS -std=c++11)


cmake_minimum_required(VERSION 3.13)
project(sm3_birthday_attack VERSION 1.0)
add_subdirectory(./src)
# add_subdirectory(./include)
link_directories("../thirdparty/ssl/lib64")
include_directories("../thirdparty/ssl/include/openssl")
target_link_libraries(main ssl)
target_link_libraries(main crypto)
# set(CMAKE_CXX_FLAGS -std=c++11)


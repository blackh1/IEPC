cmake_minimum_required(VERSION 3.13)
project(sm3_length_extension VERSION 1.0)
add_subdirectory(./src)
add_subdirectory(./include)
# link_directories("../thirdparty/openssl/")
# include_directories("../thirdparty/openssl/include")
# include_directories("../thirdparty/crypto/evp")
include_directories("../thirdparty/sm3")
target_link_libraries(main ssl)
target_link_libraries(main crypto)
# set(CMAKE_CXX_FLAGS -std=c++11)


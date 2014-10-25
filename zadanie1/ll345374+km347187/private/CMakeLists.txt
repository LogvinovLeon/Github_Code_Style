cmake_minimum_required(VERSION 2.8.4)
project(monety)

#set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

add_executable(monety ll345374+km347187/monety.cc)
target_link_libraries(monety boost_regex)
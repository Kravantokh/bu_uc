cmake_minimum_required(VERSION 3.24.1)

project(bu_unicode VERSION 1.0)

set(CMAKE_C_STANDARD 90)


add_library(bu_unicode STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/unicode.c)

target_include_directories(bu_unicode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(bu_unicode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


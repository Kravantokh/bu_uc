cmake_minimum_required(VERSION 3.24.1)

project(bu_unicode VERSION 1.0)

set (CMAKE_C_STANDARD C89)

set(BU_UNICODE_INCLUDE ${PROJECT_SOURCE_DIR}/include/) 
set(BU_UNICODE_INCLUDE ${PROJECT_SOURCE_DIR}/include/ PARENT_SCOPE) 

add_library(bu_unicode STATIC ${PROJECT_SOURCE_DIR}/src/unicode.c)

include_directories(${BU_UNICODE_INCLUDE})



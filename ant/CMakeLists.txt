cmake_minimum_required(VERSION 3.15)

project(AntLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3)

include_directories(
  ${CMAKE_SOURCE_DIR}/../common
  ${CMAKE_SOURCE_DIR}/lib
)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cc *.h)

add_library(${PROJECT_NAME} STATIC ${ALL_SOURCE_FILES})

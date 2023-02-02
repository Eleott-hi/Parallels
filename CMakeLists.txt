cmake_minimum_required(VERSION 3.15)

project(Transactions VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3)

include_directories(
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/ant
    ${CMAKE_SOURCE_DIR}/winograd
    ${CMAKE_SOURCE_DIR}/gauss
)

add_subdirectory(ant)
add_subdirectory(common)
add_subdirectory(gauss)
add_subdirectory(winograd)

add_executable(ant.out main.cc)
target_link_libraries(ant.out PUBLIC AntLib CommonLib)

add_executable(gauss.out main.cc)
target_link_libraries(gauss.out PUBLIC GaussLib CommonLib)

add_executable(winograd.out main.cc)
target_link_libraries(winograd.out PUBLIC WinogradLib CommonLib)

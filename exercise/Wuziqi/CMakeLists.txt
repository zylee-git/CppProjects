cmake_minimum_required(VERSION 3.29.0)

project(
    WuziqiProject
    DESCRIPTION "五子棋游戏"
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(BOARD_PATH ${CMAKE_SOURCE_DIR}/src/board)
set(SHOW_PATH ${CMAKE_SOURCE_DIR}/src/show)

add_subdirectory(src)
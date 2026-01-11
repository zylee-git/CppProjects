cmake_minimum_required(VERSION 3.29.0)

PROJECT(GetAwayWhiteBlock
    VERSION 1.0
    DESCRIPTION "别踩白块小游戏"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    easyx
)
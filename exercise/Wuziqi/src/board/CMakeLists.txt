project(board)

add_library(
    ${PROJECT_NAME}
    SHARED
    board.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${BOARD_PATH}
)
project(show)

add_library(
    ${PROJECT_NAME}
    SHARED
    show.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${SHOW_PATH}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    easyx
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${BOARD_PATH}
)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    board
)
project(Wuziqi)

add_subdirectory(board)
add_subdirectory(show)

add_executable(
    ${PROJECT_NAME}
    main.cpp
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

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${SHOW_PATH}
)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    show
)


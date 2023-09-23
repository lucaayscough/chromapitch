set(SOURCES
    Main.cpp
)

add_executable(Tests ${SOURCES})

target_link_libraries(Tests gtest gtest_main)

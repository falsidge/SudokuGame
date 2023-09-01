cmake_minimum_required(VERSION 3.22)

project(Sudoku CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SUDOKU_SRC_FILES
source/sudoku.h
source/sudoku.cpp)

add_executable(sudoku ${SUDOKU_SRC_FILES} source/sudoku_main.cpp)

add_executable(Sudoku_gtest gtest/sudoku_gtests.cpp)

find_package(GTest)
if (GTest_FOUND)
    set(SUDOKU_TEST_FILES
    gtest/sudoku_gtests.cpp
    )

    add_executable(sudoku_gtests gtest/gtestmain.cpp ${SUDOKU_SRC_FILES} ${SUDOKU_SRC_FILES})
    target_include_directories(sudoku_gtests PRIVATE src ${GTEST_INCLUDE_DIRS})
    target_link_libraries(sudoku_gtests PRIVATE ${GTEST_LIBRARIES})
endif()
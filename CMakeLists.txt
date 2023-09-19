cmake_minimum_required(VERSION 3.22)

project(Sudoku CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SUDOKU_SRC_FILES
source/sudoku.h
source/sudoku.cpp)

add_executable(sudoku_main ${SUDOKU_SRC_FILES} source/sudoku_main.cpp)

if(MSVC)
  target_compile_options(sudoku_main PUBLIC "/ZI")
  target_link_options(sudoku_main PUBLIC "/INCREMENTAL")
endif()

find_package(GTest)
if (GTest_FOUND)
    set(SUDOKU_TEST_FILES
    gtests/sudoku_gtests.cpp
    )

    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(sudoku_gtests gtests/gtestmain.cpp ${SUDOKU_SRC_FILES} ${SUDOKU_TEST_FILES})
    target_include_directories(sudoku_gtests PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(sudoku_gtests PRIVATE ${GTEST_LIBRARIES})
endif()
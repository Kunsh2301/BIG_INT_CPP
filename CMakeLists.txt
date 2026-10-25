cmake_minimum_required(VERSION 4.3.3)
project(BIG_INT LANGUAGES CXX)

enable_testing()

add_library(BIG_INT_LIBRARY
    src/Constructors.cpp
    src/Arithmetic_operators.cpp
    src/Comparison_operators.cpp
    src/Arithmetic_assignment_operators.cpp
    src/IO_operators.cpp
    src/Unary_operators.cpp
)

target_include_directories(BIG_INT_LIBRARY PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(BIG_INT main.cpp)
target_link_libraries(BIG_INT PRIVATE BIG_INT_LIBRARY)

add_executable(BIG_INT_TESTS
    tests/test_main.cpp
    tests/Constructors_test.cpp
    tests/Comparison_operators_test.cpp
    tests/Arithmetic_operators_test.cpp
    tests/Arithmetic_assignment_operators_test.cpp
    tests/IO_operators_test.cpp
    tests/Unary_operators_test.cpp
)
target_link_libraries(BIG_INT_TESTS PRIVATE BIG_INT_LIBRARY)

add_test(NAME BIG_INT_TESTS COMMAND BIG_INT_TESTS)
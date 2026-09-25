cmake_minimum_required(VERSION 4.3.3)
project(BIG_INT LANGUAGES CXX)
set(SOURCE_FILES
    main.cpp 
    src/BigInt.cpp
    src/Arithmetic_operators.cpp
    src/Comparison_operators.cpp
    src/Arithmetic_assignment_operators.cpp
)
add_executable(BIG_INT ${SOURCE_FILES})

target_include_directories(BIG_INT PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(BIG_INT_TESTS
    tests/test_main.cpp
    tests/Comparison_operators_test.cpp
    tests/Arithmetic_operators_test.cpp
    tests/Arithmetic_assignment_operators_test.cpp
    src/BigInt.cpp
    src/Arithmetic_operators.cpp
    src/Comparison_operators.cpp
    src/Arithmetic_assignment_operators.cpp
)

target_include_directories(BIG_INT_TESTS PRIVATE

    ${PROJECT_SOURCE_DIR}/include

)
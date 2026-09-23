cmake_minimum_required(VERSION 4.3.3)
project(BIG_INT LANGUAGES CXX)
set(SOURCE_FILES
    main.cpp 
    src/BigInt.cpp
    src/Arithmetic_operators.cpp
    src/Comparison_operators.cpp
)
add_executable(BIG_INT ${SOURCE_FILES})

target_include_directories(BIG_INT PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
cmake_minimum_required(VERSION 4.3.3)
project(BIG_INT LANGUAGES CXX)
set(SOURCE_FILES
    main.cpp 
    BigInt.cpp
)
add_executable(BIG_INT ${SOURCE_FILES})
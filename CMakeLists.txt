cmake_minimum_required(VERSION 3.8)

set(EXECUTABLE_NAME he)

project(${EXECUTABLE_NAME} LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include_directories("src/include/")

set(SOURCES
    "src/main.cpp"
    "src/Lexer.cpp"
    "src/Token.cpp"
    )

add_executable(${EXECUTABLE_NAME} ${SOURCES})
install(TARGETS ${EXECUTABLE_NAME})



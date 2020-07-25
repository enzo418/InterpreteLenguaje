cmake_minimum_required(VERSION 3.12)
project(Interprete VERSION 2.0)

file(GLOB FUENTES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB FUENTESLex "${PROJECT_SOURCE_DIR}/src/AnalizadorLexico/*.cpp") 
file(GLOB FUENTESSinta "${PROJECT_SOURCE_DIR}/src/AnalizadorSintactico/*.cpp")
file(GLOB FUENTESSinte "${PROJECT_SOURCE_DIR}/src/Sintesis/*.cpp")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(Interprete ${FUENTES} ${FUENTESLex} ${FUENTESSinta} ${FUENTESSinte})
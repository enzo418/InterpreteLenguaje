cmake_minimum_required(VERSION 3.12)
project(Interprete VERSION 2.0)

file(GLOB FUENTES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB FUENTES_Lexico "${PROJECT_SOURCE_DIR}/src/AnalizadorLexico/*.cpp") 
file(GLOB FUENTES_Sintactico "${PROJECT_SOURCE_DIR}/src/AnalizadorSintactico/*.cpp")
file(GLOB FUENTES_Sintesis "${PROJECT_SOURCE_DIR}/src/Sintesis/*.cpp")

#LIST(REMOVE_ITEM FUENTES ${PROJECT_SOURCE_DIR}/src/main.cpp)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

#  -sLLD_REPORT_UNDEFINED  -> allows addfunction

# -sALLOW_TABLE_GROWTH -sASYNCIFY -lembind --em-config /home/enzo/builds/emsdk/.emscripten
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")



set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_C_COMPILER "gcc-4.2")

#set(CMAKE_CXX_COMPILER "emcc")

add_executable(Interprete ${FUENTES} ${FUENTES_Lexico} ${FUENTES_Sintactico} ${FUENTES_Sintesis})

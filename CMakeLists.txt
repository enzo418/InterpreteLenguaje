cmake_minimum_required(VERSION 3.12)
project(Interprete VERSION 2.0)

SET(USE_EMSCRIPTEN 0 CACHE STRING "Llama a funciones de javascript con emscripten")

file(GLOB FUENTES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB FUENTES_Lexico "${PROJECT_SOURCE_DIR}/src/AnalizadorLexico/*.cpp") 
file(GLOB FUENTES_Sintactico "${PROJECT_SOURCE_DIR}/src/AnalizadorSintactico/*.cpp")
file(GLOB FUENTES_Sintesis "${PROJECT_SOURCE_DIR}/src/Sintesis/*.cpp")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")


if(USE_EMSCRIPTEN)
    add_compile_definitions(USE_EMSCRIPTEN)
    add_definitions(-DUSE_EMSCRIPTEN)
    set(USE_EMSCRIPTEN true)

    # -sLLD_REPORT_UNDEFINED  -> allows addfunction
    # -sEXIT_RUNTIME=1
    # sALLOW_TABLE_GROWTH -> maybe is not even necessary since we just call with val
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -sEXCEPTION_CATCHING_ALLOWED=[ManejarErrorYSalir] -sEXIT_RUNTIME=1 -sALLOW_TABLE_GROWTH -sASYNCIFY -lembind")
endif()

set(CMAKE_BUILD_TYPE Debug)

add_executable(Interprete ${FUENTES} ${FUENTES_Lexico} ${FUENTES_Sintactico} ${FUENTES_Sintesis})

#pragma once

// #include <emscripten/bind.h>

#include <fstream>
#include <functional>  // std::ref
#include <iostream>

#include "AnalizadorLexico/tipos.hpp"
#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "InstancePointers.hpp"
#include "Sintesis/ettd.hpp"
#include "utiles.hpp"

using Complex = AnalizadorLexico::ComponenteLexico;

class Interprete {
   public:
    static void Interpretar(std::string& input, intptr_t write_func_ptr,
                            intptr_t read_func_ptr);

   private:
    static AnalizadorSintactico::TAS tas;

    // iniciamos la tabla con las palabras reservadas
    static AnalizadorLexico::TablaSimbolos ts;

    static const char* SimboloInicial;

    static intptr_t write_func_ptr;
    static intptr_t read_func_ptr;
};
#pragma once

#include <emscripten/bind.h>

#include <cstdint>
#include <fstream>
#include <functional>  // std::ref
#include <iostream>
#include <sstream>

#include "AnalizadorLexico/tipos.hpp"
#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "InstancePointers.hpp"
#include "Sintesis/ettd.hpp"
#include "utiles.hpp"

using Complex = AnalizadorLexico::ComponenteLexico;
using namespace emscripten;

class Interprete {
   public:
    Interprete() {};
    static void Interpretar(std::string input, intptr_t write_func_ptr,
                            intptr_t read_func_ptr,
                            intptr_t write_before_read_func_ptr);

   private:
    static AnalizadorSintactico::TAS tas;

    // iniciamos la tabla con las palabras reservadas
    static AnalizadorLexico::TablaSimbolos ts;

    static const char* SimboloInicial;

    static intptr_t write_func_ptr;
    static intptr_t read_func_ptr;
};

/*
EMSCRIPTEN_BINDINGS(interprete) {
  class_<Interprete>("Interprete")
    //.constructor<std::string, intptr_t, intptr_t>()
    .class_function("Interpretar", &Interprete::Interpretar)
    ;
}
*/

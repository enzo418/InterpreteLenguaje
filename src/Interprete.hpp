#pragma once

#include <cstdint>
#include <fstream>
#include <functional>  // std::ref
#include <iostream>
#include <sstream>

#include "AnalizadorLexico/tipos.hpp"
#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "Error.hpp"
#include "Sintesis/ettd.hpp"
#include "utiles.hpp"

using Complex = AnalizadorLexico::ComponenteLexico;

#ifdef USE_EMSCRIPTEN
#include <emscripten/bind.h>
using namespace emscripten;
#endif

class Interprete {
   public:
    Interprete() {};
    static int Interpretar(std::string input);

   private:
    static AnalizadorSintactico::TAS tas;

    // iniciamos la tabla con las palabras reservadas
    static AnalizadorLexico::TablaSimbolos ts;

    static const char* SimboloInicial;
};

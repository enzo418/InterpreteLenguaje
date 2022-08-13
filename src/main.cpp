#include <cstdint>
#include <fstream>
#include <functional>  // std::ref
#include <iostream>
#include <sstream>

#include "AnalizadorLexico/tipos.hpp"
#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "Interprete.hpp"
#include "Sintesis/ettd.hpp"
#include "utiles.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

std::string _CodigoFuente;  // utilizada en utils

int main(int cant_args, char* args[]) {
    std::ifstream t("test.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    _CodigoFuente = buffer.str();

    Interprete::Interpretar(_CodigoFuente);

    return 0;
}

int ___main____(int, char* arg[]) {}

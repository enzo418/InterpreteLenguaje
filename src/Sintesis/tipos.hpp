#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "../AnalizadorLexico/tipos.hpp"

namespace Sintesis{    
    typedef std::vector<double> ListaOperandos;
    typedef std::vector<AnalizadorLexico::ComponenteLexico> ListaOperadores;

    struct ListaOperadoresOperando{
        ListaOperadores operadores;
        ListaOperandos operandos;
    };

    typedef unsigned char uchar;

    // Tabla VariablexPrimera produccion = ReglaSemantica
    typedef std::map<std::pair<std::string, std::string>, const char*> ListaVarReglas;
}
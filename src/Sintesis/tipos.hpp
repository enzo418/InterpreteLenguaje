#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "../AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "../AnalizadorLexico/tipos.hpp"

namespace Sintesis{    
    typedef std::vector<double> ListaOperandos;
    typedef std::vector<AnalizadorLexico::ComponenteLexico> ListaOperadores;

    struct ListaOperadoresOperando{
        ListaOperadores operadores;
        ListaOperandos operandos;
    };

    typedef unsigned char uchar;

    /* std::multimap<clave, valor>
            multimap tiene los mismos beneficios que map, solamente que permite mas de una clave igual
    */

    // Mapa de Variable como clave y una lista de producciones mas un puntero a una funcion como valor.
    typedef std::multimap<std::pair<std::string, std::string>, void*> ListaVarReglas;
}
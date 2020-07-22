#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "../AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "../AnalizadorLexico/tipos.hpp"

namespace Sintesis{    
    // utilizamos punteros para saber cual es el elemento activo, sino caeria en UB
    union OperadorDoble {
        double* valor;
        AnalizadorLexico::ComponenteLexico* operador;
    };
    
    typedef std::vector<OperadorDoble> ListaOperadorDoble;

    /* std::multimap<clave, valor>
            multimap tiene los mismos beneficios que map, solamente que permite mas de una clave igual
    */

    // Mapa de Variable como clave y una lista de producciones mas un puntero a una funcion como valor.
    typedef std::multimap<std::pair<std::string, std::string>, void*> ListaVarReglas;
}
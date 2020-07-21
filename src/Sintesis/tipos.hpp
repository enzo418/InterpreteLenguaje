#pragma once
#include <iostream>
#include <map>
#include "../AnalizadorSintactico/AnalizadorSintactico.hpp"

namespace Sintesis{
    /* std::multimap<clave, valor>
            multimap tiene los mismos beneficios que map, solamente que permite mas de una clave igual
    */

    // Mapa de Variable como clave y una lista de producciones mas un puntero a una funcion como valor.
    typedef std::multimap<std::string, std::pair<AnalizadorSintactico::Produccion, void*>> ListaVarReglas;
}
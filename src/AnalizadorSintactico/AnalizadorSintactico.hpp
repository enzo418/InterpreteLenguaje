#pragma once

#include "tipos.hpp"

namespace AnalizadorSintactico {
    void LimpiarArbol(Nodo* raiz, Nodo* padre = nullptr);
    int ObtenerArbolDerivacion(Nodo* arbol, TAS& tas, const char* SimboloInicial);    
}
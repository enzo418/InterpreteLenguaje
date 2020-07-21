#pragma once

#include "AnalizadorLexico/AnalizadorLexico.hpp"
#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "tipos.hpp"

// En esta funcion se va a implementar la Definicion Dirigida por la Sintaxis
void DDS(AnalizadorLexico::TablaSimbolos& ts, AnalizadorSintactico::Nodo* arbol, Sintesis::ListaVarReglas &reglas);
#pragma once

#include "tipos.hpp"

void LimpiarArbol(AnalizadorSintactico::Nodo* raiz, 
					AnalizadorSintactico::Nodo* padre = nullptr);

int ObtenerArbolDerivacion(std::ifstream& fuente,
							AnalizadorSintactico::Nodo* arbol, 
							AnalizadorSintactico::TAS& tas, AnalizadorLexico::TablaSimbolos& ts,
							const char* SimboloInicial, bool& volcar);

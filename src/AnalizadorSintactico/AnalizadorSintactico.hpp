#pragma once

#include "../Error.hpp"
#include "../utiles.hpp"
#include "tipos.hpp"

void LimpiarArbol(AnalizadorSintactico::Nodo* raiz, 
					AnalizadorSintactico::Nodo* padre = nullptr);

bool ObtenerArbolDerivacion(std::istream& fuente,
                            AnalizadorSintactico::Nodo* arbol,
                            AnalizadorSintactico::TAS& tas,
                            AnalizadorLexico::TablaSimbolos& ts,
                            const char* SimboloInicial, const bool& volcar,
                            Error& error);

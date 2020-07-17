#pragma once

#include <iostream>
#include "tipos.hpp"

using namespace AnalizadorLexico;

/*
 * Declaraciones
*/

void AgregarEnTablaSimbolos(std::string& lexema, ComponenteLexico& complex, TablaSimbolos& ts);

ComponenteLexico StringAComplex(const char* X);

/*
 * Definiciones
*/

void AgregarEnTablaSimbolos(std::string& lexema, ComponenteLexico& complex, TablaSimbolos& ts) {
	ElementoTabla el;
	el.complex = complex;
	el.lexema = lexema;

	ts.push_back(el);
}

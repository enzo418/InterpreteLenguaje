#pragma once

#include <iostream>
#include "tipos.hpp"

using namespace AnalizadorLexico;

/*
 * Declaraciones
*/

void AgregarEnTablaSimbolos(std::string& lexema, ComponenteLexico& complex, TablaSimbolos& ts);

/*	ExisteEnTS
		* Devuelve verdadero si el lexema esta en la tabla de simbolos, 
		* ademas de cambiar el complex al del elemento encontrado en la tabla

		** Parametros:
		* 		ts: 	Tabla de simbolos
		* 	lexema: 	Cadena con la cual se va a verificar si el identificador esta en la tabla
		*  complex: 	Componente lexico pasado como referencia que se va a actualizar al complex del elemento coincidente (si se encontro)
*/
bool ExisteEnTS(TablaSimbolos& ts, std::string& lexema, ComponenteLexico& complex){
	for(ElementoTabla const& el: ts){
		if(el.lexema == lexema){
			complex = el.complex;
			return true;
		}
	}
	return false;
}

ElementoTabla* ObtenerElementoTabla(TablaSimbolos& ts, std::string& lexema){
	for(ElementoTabla& el: ts){
		if(el.lexema == lexema){
			return &el;
		}
	}

	return nullptr;
}

ComponenteLexico StringAComplex(const char* X);

/*
 * Definiciones
*/

void AgregarEnTablaSimbolos(std::string& lexema, ComponenteLexico& complex, TablaSimbolos& ts) {
	ElementoTabla el(complex, lexema, false);
	ts.push_back(el);
}

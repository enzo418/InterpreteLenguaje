#pragma once

#include <iostream>
#include "tipos.hpp"

void AgregarEnTablaSimbolos(std::string& lexema, AnalizadorLexico::ComponenteLexico& complex, AnalizadorLexico::TablaSimbolos& ts);

/*	ExisteEnTS
		* Devuelve verdadero si el lexema esta en la tabla de simbolos, 
		* ademas de cambiar el complex al del elemento encontrado en la tabla

		** Parametros:
		* 		ts: 	Tabla de simbolos
		* 	lexema: 	Cadena con la cual se va a verificar si el identificador esta en la tabla
		*  complex: 	Componente lexico pasado como referencia que se va a actualizar al complex del elemento coincidente (si se encontro)
*/
bool ExisteEnTS(AnalizadorLexico::TablaSimbolos& ts, std::string& lexema, AnalizadorLexico::ComponenteLexico& complex);

AnalizadorLexico::ElementoTabla* ObtenerElementoTabla(AnalizadorLexico::TablaSimbolos& ts, std::string& lexema);

AnalizadorLexico::ComponenteLexico StringAComplex(std::string X);
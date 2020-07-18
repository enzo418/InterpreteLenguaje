#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "../tipos.hpp"

/**
 * 
 * En este archivo se definen los tipos utilizados en el Analizador Lexico
 * 
*/

// Utilizamos un nombre de espacio para evitar posibles colisiones
namespace AnalizadorLexico {
	typedef std::map<std::tuple<ushort, int>, ushort> Delta;

	enum ComponenteLexico {
		Igual, DobleIgual, And, Or, LlavesA, LlavesC, Si, Sino, Mientras, Leer, 
		Escribir, ParantesisA, ParentesisC, Coma, Mas, Menos, Multiplicacion, 
		Division, Potencia, RaizCuadrada, Var, Id, Constante, Cadena, OpRel,  ErrorLexico, 
		FDA /* Fin de Archivo */,
		Menor, Mayor, Diferente, MenorIgual, MayorIgual /* Esta fila no iria */
	};

	struct ElementoTabla {
		ComponenteLexico complex;

		std::string lexema;

		bool esReservado = false;
	};

	typedef std::vector<ElementoTabla> TablaSimbolos;
}
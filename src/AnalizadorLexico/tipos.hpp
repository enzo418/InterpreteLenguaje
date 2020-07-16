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
		ErrorLexico, Identificador, ConstanteReal, ConstanteEntera, ConstanteCaracter,
		PuntoComa, Mayor, Menor, Igual, ParantesisA, ParentesisC, LlavesA, LlavesC,
		Mas, Menos, Asterisco, BarraInclinada, Punto, DosPuntos, Coma, Pesos	
	};

	struct ElementoTabla {
		ComponenteLexico complex;

		std::string lexema;

		bool esReservado = false;
	};

	typedef std::vector<ElementoTabla> TablaSimbolos;
}
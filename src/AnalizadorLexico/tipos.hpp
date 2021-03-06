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
		Igual, DobleIgual, And, Not, Or, LlavesA, LlavesC, Si, Sino, Mientras, Leer, 
		Escribir, ParentesisA, ParentesisC, CorcheteA, CorcheteC, Coma, Mas, Menos, Multiplicacion, 
		Division, Potencia, RaizCuadrada, Var, Id, Constante, Cadena, OpRel,  ErrorLexico, Modulo,
		FDA /* Fin de Archivo */,
		Menor, Mayor, Diferente, MenorIgual, MayorIgual
	};

	struct ElementoTabla {
		ComponenteLexico complex;

		std::string lexema;

		bool esReservado = false;

		double* valor = nullptr;

		ElementoTabla(ComponenteLexico _c, std::string _l, bool _r){
			complex=_c;
			lexema=_l;
			esReservado=_r;
		}

		~ElementoTabla(){
			if(valor) delete valor;
		}
	};

	/* 	* para que la busqueda de un elemento sea mas rapida podriamos utilizar el contenedor map de std
		* con el lexema como llave y el valor como un par de complex y esReservado, ya que map ordena
		* los elementos por la llave.
	*/
	typedef std::vector<ElementoTabla> TablaSimbolos;
}
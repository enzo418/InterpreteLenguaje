#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include "../AnalizadorLexico/AnalizadorLexico.hpp"

#include "../Sintesis/tipos.hpp"

namespace AnalizadorSintactico{
	// Nodo de un arbol
	struct Nodo {
		std::string contenido;
		
		std::vector<struct Nodo*> hijos;

		AnalizadorLexico::ComponenteLexico complex;

		// la iniciamos con nullptr asi no le asigna una direccion cualquiera
		double* valor = nullptr; 

		const char* lexema;

		Sintesis::ListaOperadoresOperando* listaOO = nullptr;
		
		// inicializador
		Nodo(const char* cont): contenido(cont){}

		~Nodo(){
			if(valor)
			 	delete valor;
			
			if(listaOO)
				delete listaOO;			
		}
	};
	
	struct comparador{
		template<typename T>
		bool operator()(const T &l, const T &r) const {
			if(l.first == r.first)
				return l.second > r.second;
			return l.first < r.first;
		}
	};

	union VarComplex
	{
		const char* variable;

		AnalizadorLexico::ComponenteLexico complex;
	};
	
	
	// Producciones resultantes de un par Variable - Token
	typedef std::vector<const char*> Produccion;

	/*	std::map<clave, valor>
	  		map nos ayuda a implementar rapidamente una estructura que almacena los elementos 
	  		de forma ordenada por clave para asi aplicar la busqueda binaria.
	*/

	// Tabla de Analisis Sintactico
	typedef std::map<std::pair<std::string, AnalizadorLexico::ComponenteLexico>, Produccion> TAS;

	// Pila de Simbolos
	typedef std::stack<std::pair<const char*, Nodo*>> Pila;
}

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include "../AnalizadorLexico/AnalizadorLexico.hpp"

namespace AnalizadorSintactico{
	// Nodo de un arbol
	struct Nodo {
		std::string contenido;
		// std::vector<std::unique_ptr<struct Nodo>> hijos;
		std::vector<struct Nodo*> hijos;
		
		// inicializador
		Nodo(const char* cont): contenido(cont){}
	};

	// Producciones resultantes de un par Variable - Token
	typedef std::vector<const char*> Produccion;

	// Tabla de Analisis Sintactico
	typedef std::map<std::pair<std::string, AnalizadorLexico::ComponenteLexico>, Produccion> TAS;

	// Pila de Simbolos
	typedef std::stack<std::pair<const char*, Nodo*>> Pila;
}

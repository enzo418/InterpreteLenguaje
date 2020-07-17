#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <stack>

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
	typedef std::map<std::pair<std::string, std::string>, Produccion> TAS;

	// Pila de Simbolos
	typedef std::stack<std::pair<const char*, Nodo*>> Pila;
}

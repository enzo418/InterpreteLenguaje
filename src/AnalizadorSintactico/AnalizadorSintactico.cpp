#include <iostream>
#include "string.h"
#include "AnalizadorSintactico.hpp"
#include "../AnalizadorLexico/AnalizadorLexico.hpp"
#include "../utiles.hpp"
#include "../tipos.hpp"
#include "tipos.hpp"

using namespace AnalizadorSintactico;

constexpr bool EsVariable(const char* X) { return X[0] == '<' && X[strlen(X)-1] == '>'; }

void LimpiarArbol(Nodo* raiz, Nodo* padre){
	while(raiz->hijos.size() > 0){
		LimpiarArbol(raiz->hijos[0], raiz);
	}

	raiz->hijos.~vector(); // Desasignar memoria del vector
	delete raiz; // Desasignar memoria del Nodo

	if(padre) padre->hijos.erase(padre->hijos.begin()); // borrar el primer elem del vector
}

int ObtenerArbolDerivacion(Nodo* arbol, TAS& tas, const char* SimboloInicial){
	Nodo* raiz = arbol;

	Pila pilaSimbolos;
	pilaSimbolos.push(std::pair<const char*, Nodo*>("$", nullptr));
	pilaSimbolos.push(std::pair<const char*, Nodo*>(SimboloInicial, raiz));

	bool exito = false;
	bool error = false;
	
	// Declararamos las variables que necesita analizador lexico
	std::ifstream fuente;

	if(!AbrirArchivo(fuente, "input.txt")){
		if (!AbrirArchivo(fuente, "/input.txt")) {
			std::cout << "El archivo no existe" << std::endl;
			delete arbol;
			return 0;
		}
	}
	
	ulong control = 0;
	std::string lexema;
	AnalizadorLexico::ComponenteLexico complex;	

	AnalizadorLexico::TablaSimbolos ts;
	
	if (!ObtenerSiguienteComplex(fuente, control, complex, lexema, ts)) {
		std::cout << "El archivo esta vacio" << std::endl;
		delete arbol;
		return 0;
	}

	// bucle principal del analizador sintactico
	while (!exito && !error) {      
		// Obtener X
		std::pair<const char*, Nodo*> par = pilaSimbolos.top();
		const char* X = par.first;
		raiz = par.second;

		// Quitar el elemento
		pilaSimbolos.pop();

		if(EsVariable(X)){
			Produccion produccion = tas[{X, complex}];
			if(!produccion.empty()){
				size_t sz = produccion.size(); 
				// apilar todos los simbolos (de derecha a izquierda) y crear sus nodos
				for(int i = sz-1; i >= 0; i--) {
					// Crear nodo hijo de X en el arbol
					Nodo* nodo = new Nodo(produccion[i]);
					raiz->hijos.push_back(nodo);

					// Apilar el simbolo, si no es variable quitar la referencia al nodo ya que no se va a derivar
					if(!EsVariable(produccion[i])) 
						nodo = nullptr;
					pilaSimbolos.push(std::pair<const char*, Nodo*>(produccion[i], nodo));
				}
			} else {
				error = true;
			}
		} else {
		  if(X == lexema){
			if(X == "$"){
			  exito = true;
			}
			ObtenerSiguienteComplex(fuente, control, complex, lexema, ts);
		  }else{
			error = true;
		  }
		}
	}

	return 0;
}
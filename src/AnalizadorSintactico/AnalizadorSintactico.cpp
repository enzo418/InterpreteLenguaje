#include <iostream>
#include "string.h"

#include "AnalizadorSintactico.hpp"
#include "../AnalizadorLexico/AnalizadorLexico.hpp"
#include "../AnalizadorLexico/utiles.hpp"
#include "../tipos.hpp"
#include "tipos.hpp"

#include "../utiles.hpp"

using namespace AnalizadorSintactico;
using Complex=AnalizadorLexico::ComponenteLexico;

constexpr bool EsVariable(const char* X) { return X[0] == '<' && X[strlen(X)-1] == '>'; }

void LimpiarArbol(Nodo* raiz, Nodo* padre){
	while(raiz->hijos.size() > 0){
		LimpiarArbol(raiz->hijos[0], raiz);
	}
	
	delete raiz; // Desasignar memoria del Nodo

	if(padre) padre->hijos.erase(padre->hijos.begin()); // borrar el primer elem del vector
}

int ObtenerArbolDerivacion(std::ifstream& fuente, Nodo* arbol, TAS& tas, AnalizadorLexico::TablaSimbolos& ts, const char* SimboloInicial, bool& volcar){
	Nodo* raiz = arbol;

	Pila pilaSimbolos;
	pilaSimbolos.push(std::pair<const char*, Nodo*>("$", nullptr));
	pilaSimbolos.push(std::pair<const char*, Nodo*>(SimboloInicial, raiz));

	bool exito = false;
	bool error = false;
	std::string mensajeError = "";
	
	ulong control = 0;
	std::string lexema = "";
	AnalizadorLexico::ComponenteLexico complex = AnalizadorLexico::ComponenteLexico::Id;	
	
	// lista de las producciones generadas por una VariablexToken
	Produccion produccion;

	if (!ObtenerSiguienteComplex(fuente, control, complex, lexema, ts)) {
		std::cout << "El archivo esta vacio" << std::endl;	
		return 0;
	}

	ulong* controlPunt = new ulong(0);

	// bucle principal del analizador sintactico
	while (!exito && !error) {      
		// Obtener X
		std::pair<const char*, Nodo*> par = pilaSimbolos.top();
		const char* X = par.first;
		raiz = par.second;

		// Quitar el elemento
		pilaSimbolos.pop();

		if(EsVariable(X)){
			produccion = tas[{X, complex}];

			if(volcar)
			{				
				std::cout << "\nDesapilada Variable: \n\t"
					<< "X: " << X
					<< " | lexema: " << lexema
					<< " | producciones: ";

				for (auto const& val : produccion) {
					std::cout << val << " ";
				}

				std::cout << std::endl;
			}

			if(!produccion.empty()){
				size_t sz = produccion.size(); 
				
				// cambiamos el tamaño del vector para asegurarnos al menos sz posiciones disponibles
				raiz->hijos.resize(sz);

				// apilar todos los simbolos (de derecha a izquierda) y crear sus nodos
				for(int i = sz-1; i >= 0; i--) {
					/**
					 * strcmp(x,y): Compara la longitud de la cadena x con la longitud de la cadena y
					*/
				
					// Crear nodo hijo de X en el arbol
					Nodo* nodo = new Nodo(produccion[i]);
					raiz->hijos[i] = nodo;
					raiz->control = controlPunt;
										
					// Si es epsilon va en el arbol pero no en la pila de simbolos.
					if(strcmp(produccion[i], "epsilon") != 0)
						pilaSimbolos.push(std::pair<const char*, Nodo*>(produccion[i], nodo));
				}
			} else {
				error = true;

				if(pilaSimbolos.size() > 2){
					while (EsVariable(par.first))
					{
						par = pilaSimbolos.top();
						pilaSimbolos.pop();
					}

					std::string _F(par.first);

					if(_F == "opRel")
						_F = "operador relacional";

					mensajeError = "Se esperaba \"" + _F + "\", se obtuvo \"" + lexema + "\"";
				} else				
					mensajeError = "Caracter no esperado \"" + lexema + "\" Con la variable " + std::string(X);
			}
		} else {	
			if(volcar)
			{
				std::cout 	<< "\nDesapilado Terminal: \n\t"
						<< "X = " << X 
						<< " | lexema = " << lexema 
						<< " | complex iguales? " << (StringAComplex(X) == complex ? "si" : "no") 
						<< std::endl;
			}

			if(StringAComplex(X) == complex){
				if(strcmp(X, "$") == 0){
					exito = true;
				}

				if(raiz) {
					raiz->complex = complex;
					raiz->lexema = lexema;
					raiz->control = controlPunt;
				}

				// si no se pudo obtener el siguiente complex significa que llegamos al final del archivo
				ObtenerSiguienteComplex(fuente, control, complex, lexema, ts);
				controlPunt = new ulong(control);

				if(volcar)
				{
					std::cout 	<< "\nObterner nuevo Complex: \n\t"
							<< "lexema = " << lexema 
							<< " | control = " << control 
							<< std::endl;
				}
			}else{
				error = true;

				std::string _X(X);

				if(_X == "opRel")
					_X = "operador relacional";

				mensajeError = "Se esperaba \"" + _X + "\", se obtuvo \"" + lexema + "\"";
			}
		}
	}

	if (exito && volcar){
		std::cout << "\n# FASE: Analisis finalizada sin errores." << std::endl;
		
	}else if(!exito) {
		/*
		std::cout	<< "\nERROR [AS]: " << std::endl
					<< "\t " << mensajeError << std::endl

					<< "\t En la posicion: " << control << std::endl;
		*/

		ManejarErrorYSalir(mensajeError, &control);
		
		std::exit(EXIT_FAILURE);		
	}

	return 0;
}
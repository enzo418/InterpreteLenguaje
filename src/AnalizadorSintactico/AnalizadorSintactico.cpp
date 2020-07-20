#include <iostream>
#include "string.h"
#include "AnalizadorSintactico.hpp"
#include "../AnalizadorLexico/AnalizadorLexico.hpp"
#include "../utiles.hpp"
#include "../tipos.hpp"
#include "tipos.hpp"

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

int ObtenerArbolDerivacion(Nodo* arbol, TAS& tas, const char* SimboloInicial){
	Nodo* raiz = arbol;

	Pila pilaSimbolos;
	pilaSimbolos.push(std::pair<const char*, Nodo*>("$", nullptr));
	pilaSimbolos.push(std::pair<const char*, Nodo*>(SimboloInicial, raiz));

	bool exito = false;
	bool error = false;
	std::string mensajeError = "";

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
	std::string lexema = "";
	AnalizadorLexico::ComponenteLexico complex = AnalizadorLexico::ComponenteLexico::Id;	

	// iniciamos la trabla con las palabras reservadas
	AnalizadorLexico::TablaSimbolos ts = {
		{Complex::Si, "si", true},
		{Complex::Or, "or", true},
		{Complex::Var, "var", true},
		{Complex::And, "and", true},
		{Complex::Sino, "sino", true},
		{Complex::Leer, "leer", true},	
		{Complex::RaizCuadrada, "rcd", true},
		{Complex::Escribir, "escribir", true},
		{Complex::Mientras, "mientras", true}
	};
	
	// lista de las producciones generadas por una VariablexToken
	Produccion produccion;

	if (!ObtenerSiguienteComplex(fuente, control, complex, lexema, ts)) {
		std::cout << "El archivo esta vacio" << std::endl;
		delete arbol;
		return 0;
	}

	// bucle principal del analizador sintactico
	while (!exito && !error) {      
		
		// No deberia ser necesario comprobar esto, ya que el ultimo caracter es $ y deberia parar antes
		// pero lo voy a dejar hasta que se terminen de completar todos los automatas
		if (pilaSimbolos.size() == 0) {
			std::cout << "Evitada excepcion al intentar desapilar de la pila simbolos vacia. Saliendo." << std::endl;
			error = true;
			break;
		}

		// Obtener X
		std::pair<const char*, Nodo*> par = pilaSimbolos.top();
		const char* X = par.first;
		raiz = par.second;

		// Quitar el elemento
		pilaSimbolos.pop();

		if(EsVariable(X)){
			produccion = tas[{X, complex}];

			std::cout << "\nVariable: \n\t"
				<< "X: " << X
				<< " | lexema: " << lexema
				<< " | producciones: ";

			for (auto const& val : produccion) {
				std::cout << val << " ";
			}

			std::cout << std::endl;

			if(!produccion.empty()){
				size_t sz = produccion.size(); 
				// apilar todos los simbolos (de derecha a izquierda) y crear sus nodos
				for(int i = sz-1; i >= 0; i--) {
					/**
					 * strcmp(x,y): Compara la longitud de la cadena x con la longitud de la cadena y
					*/

					// si es un identificador, para el contenido del nodo utilizamos identificador que se encontro
					// lo mismo si es constante y opRel
					const char* contenido = ((complex == Complex::Id && strcmp(produccion[i], "id") == 0) 
											|| (complex == Complex::Constante && strcmp(produccion[i], "constante") == 0)) 
															? lexema.c_str() : produccion[i];
					
					// Crear nodo hijo de X en el arbol
					Nodo* nodo = new Nodo(contenido);
					raiz->hijos.push_back(nodo);

					// Apilar el simbolo, si no es variable quitar la referencia al nodo ya que no se va a derivar
					if(!EsVariable(produccion[i])) 
						nodo = nullptr;
					
					// Si es epsilon va en el arbol pero no en la pila de simbolos.
					if(strcmp(produccion[i], "epsilon") != 0)
						pilaSimbolos.push(std::pair<const char*, Nodo*>(produccion[i], nodo));
				}
			} else {
				error = true;
				mensajeError = "Caracter no esperado \"" + lexema + "\" Con la variable " + std::string(X);
			}
		} else {	
			std::cout 	<< "\nTerminal: \n\t"
						<< "X = " << X 
						<< " | lexema = " << lexema 
						<< " | igual? " << (StringAComplex(X) == complex ? "si" : "no") << std::endl;
			if(StringAComplex(X) == complex){
				if(strcmp(X, "$") == 0){
					exito = true;
				}

				// si no se pudo obtener el siguiente complex significa que llegamos al final del archivo
				if (!ObtenerSiguienteComplex(fuente, control, complex, lexema, ts)) {
					lexema = "$";
					complex = AnalizadorLexico::ComponenteLexico::FDA;
				}
				std::cout 	<< "\nObterner nuevo Complex: \n\t"
							<< "lexema = " << lexema 
							<< " | control = " << control << std::endl;
			}else{
				error = true;
				mensajeError = "Se esperaba \"" + std::string(X) + "\", se obtuvo \"" + lexema + "\"";
			}
		}
	}

	if (exito)
		std::cout << "\n# FASE: Analizador Sintactico finalizada sin errores." << std::endl;
	else {
		std::cout	<< "\n# FASE: Analizador Sintactico finalizada con un error." << std::endl
					<< "\t " << mensajeError << std::endl

		/*std::cout << "\t Se esperaba " << produccion[0] << std::endl
					<< "\t Se encontro " << lexema << std::endl;*/
					<< "\t En la posicion: " << control << std::endl;
		
	}

	return 0;
}
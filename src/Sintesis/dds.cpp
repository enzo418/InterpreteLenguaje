#include "dds.hpp"
#include "string.h"
#include "reglas.hpp"

#define _Iguales(a,b) strcmp(a, b) == 0

using Nodo = AnalizadorSintactico::Nodo;

void DDS(AnalizadorLexico::TablaSimbolos& ts, Nodo* arbol, Sintesis::ListaVarReglas &reglas){
	//RecorrerArbolAplicandoReglas(arbol, reglas);

	// Para saber que regla semantica aplicar luego de pasar por los mas de un hijo en un nodo X
	// obtener el primer hijo N y buscar en la lista por una produccion que sea producida por X y empieze con N.
	// esto basado en que la gramatica es LL(1) por lo que cada produccion empieza diferente y con solo saber el 
	// primer simbolo ya podemos saber a que produccion ir.

	// luego de esto buscamos en la lista de variables por una que sea Padre(X) y produzca X (Padre(X)  -> X)
}

void RecorrerArbolAplicandoReglas(Nodo* raiz, Sintesis::ListaVarReglas &reglas, Nodo* padre = nullptr){
	size_t act = 0;
	size_t sz = raiz->hijos.size();
	while(act < sz){
		RecorrerArbolAplicandoReglas(raiz->hijos[act], reglas, raiz);
		act++;
	}

	// si tiene mas de dos hijos
	if(act > 0){
		Nodo* primerHijo = raiz->hijos[0];

		const char* regla = reglas[{raiz->contenido, primerHijo->contenido}];
		if(_Iguales(regla, "AsignarReal")){
			//AsignarReal()
		}
	}
}
#include "dds.hpp"
#include "string.h"
#include "reglas.hpp"

#define _Iguales(a,b) strcmp(a, b) == 0

using Nodo = AnalizadorSintactico::Nodo;

// --

void RecorrerArbolAplicandoReglas(Nodo* raiz, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts, Nodo* padre);

void EjecutarReglas(Nodo* raiz, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts);

void ResolverSi(Nodo* raizCondiciones, Nodo* raizCuerpo, Nodo* raizSino, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts);

void EjectuarMientras(Nodo* raizCondiciones, Nodo* raizCuerpo, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts);
// --

void DDS(AnalizadorLexico::TablaSimbolos& ts, Nodo* arbol, Sintesis::ListaVarReglas &reglas){
	//RecorrerArbolAplicandoReglas(arbol, reglas);

	// Para saber que regla semantica aplicar luego de pasar por los mas de un hijo en un nodo X
	// obtener el primer hijo N y buscar en la lista por una produccion que sea producida por X y empieze con N.
	// esto basado en que la gramatica es LL(1) por lo que cada produccion empieza diferente y con solo saber el 
	// primer simbolo ya podemos saber a que produccion ir.

	// luego de esto buscamos en la lista de variables por una que sea Padre(X) y produzca X (Padre(X)  -> X)
}

void RecorrerArbolAplicandoReglas(Nodo* raiz, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts, Nodo* padre = nullptr){
	/* Nota:
		Seria ideal una implementacion no recursiva de este metodo, ya que para arboles muy largos
		seguramente cause stack overflow.
	*/

	size_t hijo = 0;
	size_t sz = raiz->hijos.size();
	while(hijo < sz){
		RecorrerArbolAplicandoReglas(raiz->hijos[hijo], reglas, ts, raiz);
		hijo++;
	}

	// No debe ser una hoja, ya que las reglas las tomamos basadas en un par Padre <-> primerhijo
	if(hijo > 0){
		EjecutarReglas(raiz, reglas, ts);
	}
}

void EjecutarReglas(Nodo* raiz, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts){
	Nodo* primerHijo = raiz->hijos[0];

	const char* regla = reglas[{raiz->contenido, primerHijo->contenido}];

	if(_Iguales(regla, "AsignarReal")){
		if(primerHijo->complex == Complex::Id)
			AsignarReal(raiz->hijos[0]->lexema, ts);
		else
			AsignarReal(raiz->hijos[1]->lexema, ts);
	} else if(_Iguales(regla, "CambiarValorVariable")){
		CambiarValorVariable(raiz->hijos[0]->lexema, raiz->hijos[2]->listaOO, ts);
	} else if(_Iguales(regla, "Leer")){
		Leer(raiz->hijos[2]->lexema, raiz->hijos[4]->lexema, ts);
	} else if(_Iguales(regla, "Escribir")){
		Escribir(raiz->hijos[2]->lexema, raiz->hijos[4]->listaOO);
	} else if(_Iguales(regla, "EjectuarMientras")){
		EjectuarMientras(raiz->hijos[2], raiz->hijos[5], reglas, ts);
	} else if(_Iguales(regla, "ResolverSi")){
		ResolverSi(raiz->hijos[2], raiz->hijos[5], raiz->hijos[7], reglas, ts);
	} else if(_Iguales(regla, "GuardarValorYCopiarListaIdConstyT")){
		GuardarValorYCopiarListaIdConstyT(*raiz->hijos[0]->valor, raiz->hijos[1]->listaOO, raiz->hijos[0]->listaOO, raiz->listaOO);
	} else if(_Iguales(regla, "GuardarOperadorYCopiarListaOpA")){
		GuardarOperadorYCopiarListaOpA(raiz->hijos[0]->complex, raiz->hijos[1]->listaOO, raiz->listaOO);
	} else if(_Iguales(regla, "CopiarValorDeId")){
		CopiarValorDeId(raiz->hijos[0]->lexema, raiz->valor, ts);
	} else if(_Iguales(regla, "CopiarValorDeHijo")){
		CopiarValorDeHijo(raiz->valor, raiz->hijos[0]->valor);
	} 
}

void ResolverSi(Nodo* raizCondiciones, Nodo* raizCuerpo, Nodo* raizSino, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts) {
	// De esta forma no funcionaria para cuando Condiciones => (Condiciones)A
	// Solo funcionaria para Condiciones => OpAritmeticas opRel OpAritmeticas
	if(ResolverCondicional(raizCondiciones->hijos[0]->listaOO, raizCondiciones->hijos[1]->complex,  raizCondiciones->hijos[2]->listaOO)){
		RecorrerArbolAplicandoReglas(raizCuerpo, reglas, ts);
	}else{
		RecorrerArbolAplicandoReglas(raizSino, reglas, ts);
	}
}

void EjectuarMientras(Nodo* raizCondiciones, Nodo* raizCuerpo, Sintesis::ListaVarReglas &reglas, AnalizadorLexico::TablaSimbolos& ts){
	// De esta forma no funcionaria para cuando Condiciones => (Condiciones)A
	// Solo funcionaria para Condiciones => OpAritmeticas opRel OpAritmeticas
	while(ResolverCondicional(raizCondiciones->hijos[0]->listaOO, raizCondiciones->hijos[1]->complex,  raizCondiciones->hijos[2]->listaOO)){
		RecorrerArbolAplicandoReglas(raizCuerpo, reglas, ts);
	}
}
#include "reglas.hpp"

#include <math.h> 
#include <algorithm> // std::reverse
#include <iterator> // std::advance

#include "../AnalizadorLexico/utiles.hpp"

#include "tipos.hpp"
#include "utiles.hpp"

#include "operaciones_aritmeticas.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){	
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == Complex::Id){        
		// le asignamos un lugar de memoria inicializado con 0
		elemento->valor = new double(0);
	} // else... manejar error de identificador no válido.	
}

void CopiarValorDeId(std::string identificador, double* destino, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, identificador);
	if(elemento && elemento->complex == Complex::Id){        
		*destino = *elemento->valor;
	} // else... manejar error de identificador no válido.	
}

void CopiarValorDeHijo(double* destino, double* fuente){
	destino = fuente;
}

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){
	
}

void AgregarParentesisExtremosYCopiarLista(Sintesis::ListaOperadoresOperando* listaOpa, Sintesis::ListaOperadoresOperando* destino){
	/* 	Nota:
		Considerar utilizar deque en lugar de vector para hacer este tipo de operaciones de insercion en los extremos.
		Realiza esa accion mucho mas rapido en cantidades grandes.
	*/ 

	listaOpa->operadores.insert(listaOpa->operadores.begin(), Complex::ParentesisA);
	listaOpa->operadores.push_back(Complex::ParentesisC);

	destino = listaOpa;
}

void CambiarValorVariable(std::string& lexema, Sintesis::ListaOperadoresOperando& lista, AnalizadorLexico::TablaSimbolos& ts){	
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == Complex::Id){
		*elemento->valor = CalcularValorLista(lista.operadores, lista.operandos);
	} // else... manejar error de identificador no válido.
}

void ResolverListaYCalcularRaizCuadrada(Sintesis::ListaOperadoresOperando& lista, double* destino){
	*destino = sqrt(CalcularValorLista(lista.operadores, lista.operandos));
}

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, var);
	if(elemento && elemento->complex == Complex::Id){
		std::cin >> *(elemento->valor);
	}// else... manejar error de identificador no válido.	
}

void GuardarValorYCopiarListaIdConstyT(double& valor, Sintesis::ListaOperadoresOperando* listaT, 
										Sintesis::ListaOperadoresOperando* listaIdConst,
										Sintesis::ListaOperadoresOperando* listaOpA){
	// si IdConst tiene lista 
	if(listaIdConst){
		if(listaT){
			// a la lista T le agregamos la lista IdConst
			listaT->operadores.insert(listaT->operadores.end(), listaIdConst->operadores.begin(), listaIdConst->operadores.end());
			listaT->operandos.insert(listaT->operandos.end(), listaIdConst->operandos.begin(), listaIdConst->operandos.end());
			listaOpA = listaT;
		}else{
			listaOpA = listaIdConst;
		}
	}else{
		// si hay lista (T no se derivo en epsilon)
		if(listaT){
			// agregamos el operador a la lista de T
			listaT->operandos.push_back(valor);

			// y ahora la lista de OpAritmeticas (el padre de T) apunta a la lista de T
			listaOpA = listaT;
		} else{ // si T se derivo en epsilon
			// Creamos una lista (Asignar vector en memoria y que listaOpA apunte a esa direccion)
			listaOpA = new Sintesis::ListaOperadoresOperando;

			// agregamos el valor
			listaOpA->operandos.push_back(valor);
		}
	}
}

void GuardarOperadorYCopiarListaOpA(Complex& operador, Sintesis::ListaOperadoresOperando* listaOpA, Sintesis::ListaOperadoresOperando* listaT){	
	// agregamos el operador a la lista de operaciones aritmeticas
	listaOpA->operandos.push_back(operador);

	// y ahora la lista de T (el padre de OpAritmeticas) apunta a la lista de OpAritmeticas
	listaT = listaOpA;
}

void ResolverCondicional(Sintesis::ListaOperadoresOperando* listaOpAi, Complex& operador, Sintesis::ListaOperadoresOperando* listaOpAd, bool& res){
	// inicializamos valor en 0
	double valori = 0;
	// calculamos su valor en base a la lista
	valori = CalcularValorLista(listaOpAi->operadores , listaOpAi->operandos);

	double valord = 0;
	valord = CalcularValorLista(listaOpAd->operadores , listaOpAd->operandos);

	switch (operador)
	{
		case Complex::Mayor:
			res = valori > valord;
			break;
		case Complex::Menor:
			res = valori < valord;
			break;
		case Complex::DobleIgual:
			res = valori == valord;
			break;
		case Complex::Diferente:
			res = valori != valord;
			break;
		case Complex::MayorIgual:
			res = valori >= valord;
			break;
		case Complex::MenorIgual:
			res = valori <= valord;
			break;
	}
}

void Escribir(std::string& cadena, Sintesis::ListaOperadoresOperando& lista){
	// inicializamos valor en 0
	double valor = CalcularValorLista(lista.operadores, lista.operandos);

	// imprimimos en pantalla la cadena seguida de el valor
	std::cout << cadena << valor << std::endl;
}

void RaizCuadrada(double* fuente, double* destino){
	*destino = sqrt(*fuente);
}
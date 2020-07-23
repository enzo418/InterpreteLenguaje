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

void CopiarValorDeHijo(double* destino, double* fuente){
	destino = fuente;
}

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){
	
}

void CambiarValorVariable(std::string& lexema, Sintesis::ListaOperadoresOperando& lista, AnalizadorLexico::TablaSimbolos& ts){	
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == Complex::Id){
		*elemento->valor = CalcularValorLista(lista.operadores, lista.operandos);
	} // else... manejar error de identificador no válido.	
}

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, var);
	if(elemento && elemento->complex == Complex::Id){
		std::cin >> *(elemento->valor);
	}// else... manejar error de identificador no válido.	
}

void GuardarValorYCopiarListaT(double& valor, Sintesis::ListaOperadoresOperando* listaT, Sintesis::ListaOperadoresOperando* listaOpA){		
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
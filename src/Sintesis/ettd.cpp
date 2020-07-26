#include "ettd.hpp"
#include "../AnalizadorSintactico/tipos.hpp"
#include "tipos.hpp"
#include "ettd.hpp"

#include "../AnalizadorLexico/utiles.hpp"

#include "../utiles.hpp"

#include <string>
#include <math.h>

#include <algorithm>

using Nodo=AnalizadorSintactico::Nodo;
using Variables=Sintesis::Variables;
using Complex=AnalizadorLexico::ComponenteLexico;

#define VariableNoExiste(var, vars) vars.find(var) == vars.end()
#define VariableExiste(var, vars) vars.find(var) != vars.end()

double ObtenerValorVariable(std::string lexema, Variables& variables, ulong* controlMasCercano){
	if(VariableExiste(lexema, variables)){
		return variables[lexema];
	} else {
		ManejarErrorYSalir("ERROR: Uso de la variable " + lexema + " no declarada.", controlMasCercano);
	}
}

void AgregarVariable(std::string lexema, Variables& variables, ulong* controlMasCercano){	
	if(VariableNoExiste(lexema, variables)){
		variables.insert({lexema, 0});
	} else {
		ManejarErrorYSalir("ERROR: Variable " + lexema + " ya declarada.", controlMasCercano);
	}
}

void EvaluarPrograma(Nodo* arbol){
	Variables variables;
	EvaluarVariables(arbol->hijos[1], variables);
	EvaluarCuerpo(arbol->hijos[3], variables);
}

void EvaluarVariables(Nodo* arbol, Variables& variables){
	AgregarVariable(arbol->hijos[0]->lexema, variables, arbol->control);
	EvaluarIdVar(arbol->hijos[1], variables);
}

void EvaluarIdVar(Nodo* IdVar, Variables& variables){
	Nodo* primerHijo = IdVar->hijos[0];
	if(primerHijo->complex == Complex::Coma){
		AgregarVariable(IdVar->hijos[1]->lexema, variables, IdVar->control);
		EvaluarIdVar(IdVar->hijos[2], variables);
	}
}

void EvaluarCuerpo(Nodo* Cuerpo, Variables& variables){
	Nodo* primerHijo = Cuerpo->hijos[0];
	if(primerHijo->contenido != "epsilon"){
		EvaluarSent(primerHijo, variables);
		EvaluarCuerpo(Cuerpo->hijos[1], variables);
	}
}

void EvaluarSent(Nodo* Sent, Variables& variables){
	Nodo* primerHijo = Sent->hijos[0];
	switch (primerHijo->complex) {
		case Complex::Id:
			EvaluarAsignacion(Sent->hijos[2], primerHijo->lexema, variables);
			break;
		case Complex::Leer:
			EvaluarLeer(Sent->hijos[2]->lexema, Sent->hijos[4]->lexema, variables, Sent->control);
			break;
		case Complex::Escribir:
			EvaluarEscribir(Sent->hijos[2]->lexema, Sent->hijos[4], variables);
			break;
		case Complex::Mientras:
			EvaluarMientras(Sent->hijos[2], Sent->hijos[5], variables);
			break;
		case Complex::Si:
			EvaluarSi(Sent->hijos[2], Sent->hijos[5], Sent->hijos[7], variables);
			break;
		default:
			break;
	}
}

void EvaluarAsignacion(Nodo* OperacionAritmetica, std::string lexema, Variables& variables){
	if(VariableExiste(lexema, variables)){
		double res = 0;
		EvaluarOpAritmeticas(OperacionAritmetica, variables, res);

		variables[lexema] = res;
	}else{		
		ManejarErrorYSalir("ERROR: Uso de la variable " + lexema + " no declarada", OperacionAritmetica->control);
	}
}

void EvaluarLeer(std::string cadena, std::string lexema, Variables& variables, ulong* controlMasCercano){
	if(VariableExiste(lexema, variables)){
		std::cout << cadena;
		std::cin >> variables[lexema];
	}else{
		ManejarErrorYSalir("ERROR: Uso de la variable " + lexema + " no declarada.", controlMasCercano);
	}
}

void EvaluarEscribir(std::string cadena, Nodo* OperacionAritmetica, Variables& variables){
	double res = 0;
	EvaluarOpAritmeticas(OperacionAritmetica, variables, res);
	cadena.erase(std::remove( cadena.begin(), cadena.end(), '\"' ),cadena.end());
	
	std::cout << cadena << res << std::endl;
}

void EvaluarMientras(Nodo* Condiciones, Nodo* Cuerpo, Variables& variables){
	while (EvaluarCondiciones(Condiciones, variables))
	{
		EvaluarCuerpo(Cuerpo, variables);
	}
	
}

void EvaluarSi(Nodo* Condiciones, Nodo* Cuerpo, Nodo* Sino, Variables& variables){
	if (EvaluarCondiciones(Condiciones, variables)) {
		EvaluarCuerpo(Cuerpo, variables);
	}else{
		EvaluarSino(Sino, variables);
	}	
}

bool EvaluarCondiciones(Nodo* Condiciones, Variables& variables){
	bool res = EvaluarCond3(Condiciones->hijos[0], variables);

	// Si B no se deriva en epsilon
	if(Condiciones->hijos[1]->hijos[0]->contenido != "epsilon"){
		res &= EvaluarB(Condiciones->hijos[1], variables);
	}

	// Si A no se deriva en epsilon
	if(Condiciones->hijos[2]->hijos[0]->contenido != "epsilon"){
		res |= EvaluarA(Condiciones->hijos[2], variables);
	}

	return res;
}

bool EvaluarA(Nodo* A, Variables& variables){
	return EvaluarCondiciones(A->hijos[1], variables);
}

bool EvaluarB(Nodo* B, Variables& variables){
	bool res = EvaluarCond3(B->hijos[1], variables);
	if(B->hijos[2]->hijos[0]->contenido != "epsilon"){
		res &= EvaluarB(B, variables);
	}
	return res;
}

bool EvaluarCond3(Nodo* Cond3, Variables& variables){
	Nodo* primerHijo = Cond3->hijos[0];
	if(primerHijo->complex == Complex::Not){
		return !EvaluarCond3(Cond3->hijos[1], variables);
	} else if(primerHijo->complex == Complex::CorcheteA){
		return EvaluarCondiciones(Cond3->hijos[1], variables);
	} else {
		double izq = 0;
		EvaluarOpAritmeticas(Cond3->hijos[0], variables, izq);

		double der = 0;
		EvaluarOpAritmeticas(Cond3->hijos[2], variables, der);

		bool res = false;
		Complex complex = StringAComplex(Cond3->hijos[1]->lexema);

		switch (complex) {
			case Complex::Mayor:
				res = izq > der;
				break;
			case Complex::Menor:
				res = izq < der;
				break;
			case Complex::MayorIgual:
				res = izq >= der;
				break;
			case Complex::MenorIgual:
				res = izq <= der;
				break;
			case Complex::DobleIgual:
				res = izq == der;
				break;
			case Complex::Diferente:
				res = izq != der;
				break;
		}
		
		return res;
	}
}

void EvaluarSino(Nodo* Sino, Variables& variables){
	if(Sino->hijos[0]->complex == Complex::Sino)
		EvaluarCuerpo(Sino->hijos[2], variables);
}

void EvaluarOpAritmeticas(Nodo* OpAritmeticas, Variables& variables, double& res){	
	EvaluarT(OpAritmeticas->hijos[0], variables, res);
	EvaluarW(OpAritmeticas->hijos[1], variables, res, res);
}

// W controla los operadores suma y resta
void EvaluarW(Nodo* W, Variables& variables, double& izq, double& res){
	Nodo* primerHijo = W->hijos[0];
	if (primerHijo->complex == Complex::Mas) {
		double resT = 0;
		EvaluarT(W->hijos[1], variables, resT);

		double resW = 0;
		EvaluarW(W->hijos[2], variables, resT, resW);

		res = izq + resW;
	} else if (primerHijo->complex == Complex::Menos){
		double resT = 0;
		EvaluarT(W->hijos[1], variables, resT);

		double resW = 0;
		EvaluarW(W->hijos[2], variables, resT, resW);

		res = izq - resW;
	} else{
		res = izq;
	}
}

// T controla la prioridad de la potencia sobre la multiplicacion y division
void EvaluarT(Nodo* T, Variables& variables, double& res){
	EvaluarF(T->hijos[0], variables, res);
	EvaluarZ(T->hijos[1], variables, res, res);
}

// Z controla el producto y la division 
void EvaluarZ(Nodo* Z, Variables& variables, double& izq, double& res){
	Nodo* primerHijo = Z->hijos[0];
	if (primerHijo->complex == Complex::Multiplicacion) {
		double resF = 0;
		EvaluarF(Z->hijos[1], variables, resF);

		double resZ = 0;
		EvaluarZ(Z->hijos[2], variables, resF, resZ);

		res = izq * resZ;
	} else if (primerHijo->complex == Complex::Division) {
		double resF = 0;
		EvaluarF(Z->hijos[1], variables, resF);

		double resZ = 0;
		EvaluarZ(Z->hijos[2], variables, resF, resZ);

		res = izq / resZ;
	} else {
		res = izq;
	}
}

// F controla la raiz cuadrada y se deriva en la potencia y terminales
void EvaluarF(Nodo* F, Variables& variables, double& res){
	Nodo* primerHijo = F->hijos[0];
	if (primerHijo->complex == Complex::RaizCuadrada) {
		EvaluarOpAritmeticas(F->hijos[2], variables, res);
		res = sqrt(res);

		EvaluarX(F->hijos[4], variables, res, res);
	}else{
		EvaluarR(primerHijo, variables, res);
		EvaluarX(F->hijos[1], variables, res, res);
	}
}

// X controla el operador potencia
void EvaluarX(Nodo* X, Variables& variables, double& base, double& res){
	Nodo* primerHijo = X->hijos[0];
	if (primerHijo->complex == Complex::Potencia) {
		double resR = 0;
		EvaluarR(X->hijos[1], variables, resR);

		double resX = 0;
		EvaluarX(X->hijos[2], variables, resR, resX);

		res = pow(base, resX);
	}else{
		res = base;
	}	
}

// R controla los operadores
void EvaluarR(Nodo* R, Variables& variables, double& res){
	Nodo* primerHijo = R->hijos[0];
	switch (primerHijo->complex)
	{
		case Complex::Id:
			res = ObtenerValorVariable(primerHijo->lexema, variables, R->control);
			break;
		case Complex::Constante:
			res = std::stod(primerHijo->lexema);
			break;
		case Complex::ParentesisA:
			EvaluarOpAritmeticas(R->hijos[1], variables, res);
			break;
		case Complex::Menos:
			EvaluarR(R->hijos[1], variables, res);
			res *= -1;
			break;
	}
}
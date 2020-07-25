#include "ettd.hpp"
#include "../AnalizadorSintactico/tipos.hpp"
#include "tipos.hpp"

using Nodo=AnalizadorSintactico::Nodo;
using Variables=Sintesis::Variables;
using Complex=AnalizadorLexico::ComponenteLexico;

#define VariableNoExiste(var, vars) vars.find(var) == vars.end()
#define VariableExiste(var, vars) vars.find(var) != vars.end()

// decimos que _ERROR esta en otro archivo
extern bool _ERROR;

void AgregarVariable(std::string lexema, Variables& variables){	
	if(VariableNoExiste(lexema, variables)){
		variables.insert({lexema, 0});
	} else {
		_ERROR = true;		
		std::cout << "Error: Variable " << lexema << " ignorada, ya que ya fue declarada previamente." << std::endl;
	}
}

void EvaluarPrograma(Nodo* arbol, Variables& variables){
	EvaluarVariables(arbol->hijos[1], variables);
	EvaluarCuerpo(arbol->hijos[3], variables);
}

void EvaluarVariables(Nodo* arbol, Variables& variables){
	AgregarVariable(arbol->hijos[0]->lexema, variables);
	EvaluarIdVar(arbol->hijos[1], variables);
}

void EvaluarIdVar(Nodo* IdVar, Variables& variables){
	Nodo* primerHijo = IdVar->hijos[0];
	if(primerHijo->contenido != "epsilon"){
		AgregarVariable(IdVar->hijos[1]->lexema, variables);
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
			EvaluarLeer(Sent->hijos[2]->lexema, Sent->hijos[4]->lexema, variables);
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
		// ERROR		
		std::cout << "Error! Variable " << lexema << " no declarada." << std::endl;
	}
}

void EvaluarLeer(std::string cadena, std::string lexema, Variables& variables){
	if(VariableExiste(lexema, variables)){
		std::cout << cadena;
		std::cin >> variables[lexema];
	}else{
		// ERROR
		std::cout << "Error! Variable " << lexema << " no declarada en leer(" << cadena << ", " << lexema  << std::endl;
	}
}

void EvaluarEscribir(std::string cadena, Nodo* OperacionAritmetica, Variables& variables){
	double res = 0;
	EvaluarOpAritmeticas(OperacionAritmetica, variables, res);

	std::cout << cadena << res;
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
	if(Condiciones->hijos[1]->contenido != "epsilon"){
		res &= EvaluarB(Condiciones->hijos[1], variables);
	}

	// Si A no se deriva en epsilon
	if(Condiciones->hijos[2]->contenido != "epsilon"){
		res |= EvaluarA(Condiciones->hijos[2], variables);
	}
}

bool EvaluarA(Nodo* A, Variables& variables){
	return EvaluarCondiciones(A->hijos[1], variables);
}

bool EvaluarB(Nodo* B, Variables& variables){
	if(B->contenido != "epsilon"){
		return EvaluarCond3(B->hijos[1], variables);
	}
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

		switch (Cond3->hijos[1]->complex) {
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
	}
}

void EvaluarSino(Nodo* arbol, Variables& variables){

}

double EvaluarOpAritmeticas(Nodo* arbol, Variables& variables, double& res){

}

void EvaluarW(Nodo* arbol, Variables& variables){

}

void EvaluarT(Nodo* arbol, Variables& variables){

}

void EvaluarZ(Nodo* arbol, Variables& variables){

}

void EvaluarF(Nodo* arbol, Variables& variables){

}

void EvaluarX(Nodo* arbol, Variables& variables){

}

void EvaluarR(Nodo* arbol, Variables& variables){

}
#include "reglas.hpp"
#include <math.h> 
#include "../AnalizadorLexico/utiles.hpp"
#include "tipos.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == Complex::Id){        
		elemento->valor = new double;
	} // else... manejar error de identificador no válido.
}

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){
	
}

void CambiarValorVariable(std::string& lexema, Sintesis::ListaOperadorDoble* lista, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == Complex::Id){
		ResolverLista(lista, elemento->valor);		
	} // else... manejar error de identificador no válido.
}

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, var);
	if(elemento && elemento->complex == Complex::Id){
		std::cin >> *(elemento->valor);
	}// else... manejar error de identificador no válido.
}

void GuardarValorYCopiarListaT(double& valor, Sintesis::ListaOperadorDoble* listaT, Sintesis::ListaOperadorDoble* listaOpA){	
	// Creamos el operador-doble con un valor
	Sintesis::OperadorDoble el = {&valor}; 	// primer argumento = OperadorDoble.valor	== 		&valor
											// segundo = OperadorDoble.operador    		==   	nullptr
	
	// si hay lista (T no se derivo en epsilon)
	if(listaT){
		// agregamos el operador a la lista de T
		listaT->push_back(el);

		// y ahora la lista de OpAritmeticas (el padre de T) apunta a la lista de T
		listaOpA = listaT;
	} else{ // si T se derivo en epsilon
		// Creamos una lista (Asignar vector en memoria y que listaOpA apunte a esa direccion)
		new (&listaOpA) Sintesis::ListaOperadorDoble;

		// agregamos el valor
		listaOpA->push_back(el);
	}
}

void GuardarOperadorYCopiarListaOpA(Complex& operador, Sintesis::ListaOperadorDoble* listaOpA, Sintesis::ListaOperadorDoble* listaT){	
	// Creamos el operador-doble con un operador
	Sintesis::OperadorDoble el;
	el.operador = &operador;

	// agregamos el operador a la lista de operaciones aritmeticas
	listaOpA->push_back(el);

	// y ahora la lista de T (el padre de OpAritmeticas) apunta a la lista de OpAritmeticas
	listaT = listaOpA;
}

void ResolverCondicional(LOD* listaOpAi, Complex& operador, LOD* listaOpAd, bool& res){
	// inicializamos valor en 0
	double valori = 0;
	// calculamos su valor en base a la lista
	ResolverLista(listaOpAi, valori);

	double valord = 0;
	ResolverLista(listaOpAd, valord);

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
		default:
			//manejar error operador no soportado
			break;
	}
}

// En esta funcion se calcula el valor numerico de una lista de Operador-Doble
void ResolverLista(Sintesis::ListaOperadorDoble* lista, double* res){
	if(lista->size() == 1){
		res = lista->at(0).valor;
	}else{
		bool masDeUnOperador = false;
		// recorrer lista buscando si hay mas de un operador 
		if(!masDeUnOperador){
			// resolver lista aplicando asociatividad por izquierda, excepto en la potencia
		}else{
			// resolver lista respetando la precedencias
		}
	}
}

/*
void CalcularOperacion(AnalizadorLexico::ComponenteLexico* operador, std::pair<double, double>* operandos, double* val){
	// si el operador es un nullptr quiere decir que la produccion hijo T de OpAritmeticas se derivo en epsilon, no hay op.
	if(!operador){
		
	}
}*/

void Escribir(std::string& cadena, Sintesis::ListaOperadorDoble* lista){
	// inicializamos valor en 0
	double valor = 0;

	// calculamos su valor en base a la lista
	ResolverLista(lista, valor);

	// imprimimos en pantalla la cadena seguida de el valor
	std::cout << cadena << valor << std::endl;
}

void Suma(double& a, double &b, double& res){
	res = a+b;
}

void Resta(double& a, double &b, double& res){
	res = a-b;
}

void Multiplicacion(double& a, double &b, double& res){
	res = a*b;
}

void Division(double& a, double &b, double& res){
	res = a/b;
}

void Potencia(double& a, double &b, double& res){
	res = pow(a, b);
}

void RaizCuadrada(double& a, double& res){
	res = sqrt(a);
}
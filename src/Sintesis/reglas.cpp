#include "reglas.hpp"

#include <math.h> 
#include <algorithm> // std::reverse
#include <iterator> // std::advance

#include "../AnalizadorLexico/utiles.hpp"

#include "tipos.hpp"
#include "utiles.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){	
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == Complex::Id){        
		// le asignamos un lugar de memoria inicializado con 0
		elemento->valor = new double(0);
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
		listaOpA = new Sintesis::ListaOperadorDoble;

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
	ResolverLista(listaOpAi, &valori);

	double valord = 0;
	ResolverLista(listaOpAd, &valord);

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
		*res = *(*lista)[0].valor;
	}else{
		if(!ExisteMasDeUnOperador(lista)){
			Complex* complex = (*lista)[1].operador;
			
			switch (*complex)
			{
				case Complex::Mas:
					SumarLista(lista, res);
					break;	
				case Complex::Multiplicacion:
					MultiplicarLista(lista, res);
					break;
				case Complex::Menos:
					RestarLista(lista, true, res);
					break;	
				case Complex::Division:
					DivisionLista(lista, true, res);
					break;	
				case Complex::Potencia:
					PotenciaLista(lista, res);
					break;	
				default:
					// manejar error operador no reconocido
					break;		
			}
		}else{
			// resolver lista respetando la precedencias (RECORDAR! LA LISTA ESTA DADA DADA VUELTA!),
			// si nos dieron la cadena 1+2*5, la lista sera {5,*,2,+,1}
		}
	}
}

void Escribir(std::string& cadena, Sintesis::ListaOperadorDoble* lista){
	// inicializamos valor en 0
	double valor = 0;

	// calculamos su valor en base a la lista
	ResolverLista(lista, &valor);

	// imprimimos en pantalla la cadena seguida de el valor
	std::cout << cadena << valor << std::endl;
}

void SumarLista(Sintesis::ListaOperadorDoble* lista, double* res){
	*res = 0;
	for (auto &el : *(lista)) 
		if(el.valor) *res += *el.valor;					
}

void RestarLista(Sintesis::ListaOperadorDoble* lista, bool invertida, double* res){
	// ej. entrada {10,-,2,-,2}
	if(invertida){
		// {2,-,2,-,10} -leer> {2, ,2, ,10}
		*res = *(lista->back().valor) * 2;
		for(auto it = lista->rbegin(); it < lista->rend(); std::advance(it, 2))
        	if(it->valor) *res -= *it->valor;
	}else{
		// {10,-,2,-,2} -leer> {10, 2, ,2}
		*res = *(*lista)[0].valor * 2;
		for (auto it = lista->begin(); it < lista->end(); std::advance(it, 2)) 
			if(it->valor) *res -= *it->valor;    
	}
}

void MultiplicarLista(Sintesis::ListaOperadorDoble* lista, double* res){	
	*res = 1;
	for (auto it = lista->begin(); it < lista->end(); std::advance(it, 2)) 
		*res *= *it->valor;  
}

void DivisionLista(Sintesis::ListaOperadorDoble* lista, bool invertida, double* res){	
	// ej. entrada {10,/,2,/,2}
	if(invertida){
		// {10,/,2,/,2} -leer> {2, 2, 10}
		*res = *lista->back().valor;

		auto it = lista->rbegin();
		std::advance(it, 2);

		for(; it < lista->rend(); std::advance(it, 2))
        	*res /= *it->valor;
	}else{
		// {10,/,2,/,2} -leer> {10, 2, 2}
		*res = *(*lista)[0].valor;

		auto it = lista->begin();
		std::advance(it, 2);

		for (; it < lista->end(); std::advance(it, 2)) 
			*res /= *it->valor;    
	}
}

void PotenciaLista(Sintesis::ListaOperadorDoble* lista, double* res){	
	// {10,^,2,^,2} -leer> {10, 2, 2}		
	*res = *(*lista)[0].valor;
	auto it = lista->begin();
	std::advance(it, 2);

	for (; it < lista->end(); std::advance(it, 2)) 
		*res = pow(*it->valor, *res);
}

void RaizCuadrada(double* a, double* res){
	*res = sqrt(*a);
}
#include "reglas.hpp"
#include <math.h> 
#include "../AnalizadorLexico/utiles.hpp"

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == AnalizadorLexico::ComponenteLexico::Id){        
		elemento->valor = new double;
	}
}

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts){
	
}

void CambiarValorVariable(std::string& lexema, double valor, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, lexema);
	if(elemento && elemento->complex == AnalizadorLexico::ComponenteLexico::Id){
		*(elemento->valor) = valor;
	}
}

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts){
	AnalizadorLexico::ElementoTabla* elemento = ObtenerElementoTabla(ts, var);
	if(elemento && elemento->complex == AnalizadorLexico::ComponenteLexico::Id){
		std::cin >> *(elemento->valor);
	}
}

void Escribir(std::string& cadena, double& val){
	std::cout << cadena << val << std::endl;
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
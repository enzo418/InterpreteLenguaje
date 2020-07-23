#include "utiles.hpp"
#include "tipos.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

void AgregarEnTablaSimbolos(std::string& lexema, AnalizadorLexico::ComponenteLexico& complex, AnalizadorLexico::TablaSimbolos& ts) {
	AnalizadorLexico::ElementoTabla el(complex, lexema, false);
	ts.push_back(el);
}

bool ExisteEnTS(AnalizadorLexico::TablaSimbolos& ts, std::string& lexema, AnalizadorLexico::ComponenteLexico& complex){
	for(AnalizadorLexico::ElementoTabla const& el: ts){
		if(el.lexema == lexema){
			complex = el.complex;
			return true;
		}
	}
	return false;
}

AnalizadorLexico::ElementoTabla* ObtenerElementoTabla(AnalizadorLexico::TablaSimbolos& ts, std::string& lexema){
	for(AnalizadorLexico::ElementoTabla& el: ts){
		if(el.lexema == lexema){
			return &el;
		}
	}

	return nullptr;
}


Complex StringAComplex(std::string X){
	Complex c = Complex::ErrorLexico;
	if(X == "=")
		c=Complex::Igual;
	else if(X == "==")
		c=Complex::DobleIgual;
	else if(X == "and")
		c=Complex::And;
	else if(X == "or")
		c=Complex::Or;
	else if(X == "{")
		c=Complex::LlavesA;
	else if(X == "}")
		c=Complex::LlavesC;
	else if(X == "si")
		c=Complex::Si;
	else if(X == "sino")
		c=Complex::Sino;
	else if(X == "mientras")
		c=Complex::Mientras;
	else if(X == "leer")
		c=Complex::Leer;
	else if(X == "escribir")
		c=Complex::Escribir;
	else if(X == "(")
		c=Complex::ParantesisA;
	else if(X == ")")
		c=Complex::ParentesisC;
	else if(X == ",")
		c=Complex::Coma;
	else if(X == "+")
		c=Complex::Mas;
	else if(X == "-")
		c=Complex::Menos;
	else if(X == "*")
		c=Complex::Multiplicacion;
	else if(X == "/")
		c=Complex::Division;
	else if(X == "^")
		c=Complex::Potencia;
	else if(X == "rcd")
		c=Complex::RaizCuadrada;
	else if(X == "var")
		c=Complex::Var;
	else if(X == "id")
		c=Complex::Id;
	else if(X == "constante")
		c=Complex::Constante;
	else if(X == "cadena")
		c=Complex::Cadena;
	else if(X == "oprel")
		c=Complex::OpRel;
	else if(X == "<")
		c=Complex::Menor;
	else if(X == ">")
		c=Complex::Mayor;
	else if(X == "<>")
		c=Complex::Diferente;
	else if(X == "<=")
		c=Complex::MenorIgual;
	else if(X == ">=")
		c=Complex::MayorIgual;
	else if (X == "opRel")
		c = Complex::OpRel;
	else if (X == "$")
		c = Complex::FDA;
	return c;
}
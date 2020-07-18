#include <iostream>
#include <fstream>

using Complex=AnalizadorLexico::ComponenteLexico;

bool AbrirArchivo(std::ifstream& fuente, const char* archivo){
    // Abrimos el archivo con permisos de lectura
    fuente.open(archivo);

    if(!fuente.good()){ // si no se pudo abrir
        return false;         
    }
    
    return true;
}

Complex StringAComplex(std::string X){
	Complex c = Complex::Id;
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
	else if(X == "menor")
		c=Complex::Menor;
	else if(X == "mayor")
		c=Complex::Mayor;
	else if(X == "diferente")
		c=Complex::Diferente;
	else if(X == "menorigual")
		c=Complex::MenorIgual;
	else if(X == "mayorigual")
		c=Complex::MayorIgual;
	else if (X == "$")
		c = Complex::FDA;
	return c;
}
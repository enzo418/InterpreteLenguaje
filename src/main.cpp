#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include <iostream>
#include <functional>           // std::ref

int main(){
	AnalizadorSintactico::TAS tas = {
	//    Variable          Token     Produccion
	  { {"<Programa>",        "var"}, {"var", "<Variables>", "{", "<Cuerpo>", "}"} },
	  { {"<Variables>",       "id"}, {"id", "<IdVar>"} },
	  { {"<IdVar>",           "{"}, {"epsilon"} },
	  { {"<IdVar>",           ","}, {",", "id", "<IdVar>"} },
	  { {"<IdVar>",           ")"}, {"epsilon"} },
	  { {"<Cuerpo>",          "}"}, {"epsilon"} },
	  { {"<Cuerpo>",          "id"}, {"<Sent>", "<Cuerpo>"} },
	  { {"<Cuerpo>",          "leer"}, {"<Sent>", "<Cuerpo>"} },
	  { {"<Cuerpo>",          "escribir"}, {"<Sent>", "<Cuerpo>"} },
	  { {"<Cuerpo>",          "si"}, {"<Sent>", "<Cuerpo>"} },
	  { {"<Cuerpo>",          "mientras"}, {"<Sent>", "<Cuerpo>"} },
	  { {"<Sent>",            "id"}, {"id", "=", "<OpAritmeticas>"} },
	  { {"<Sent>",            "leer"}, {"leer","(", "cadena", "<OpAritmeticas>",")"} },
	  { {"<Sent>",            "escribir"}, {"escribir", "(", "cadena", "<OpAritmeticas>", ")"} },
	  { {"<Sent>",            "si"}, {"si", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}", "<Sino>"} },
	  { {"<Sent>",            "mientras"}, {"mientras", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}"} },                 
	  { {"<Condiciones>",     "rcd"}, {"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	  { {"<Condiciones>",     "id"}, {"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	  { {"<Condiciones>",     "constante"}, {"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	  { {"<Condiciones>",     "("}, {"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	  { {"<A>",               "and"}, {"and", "<Condiciones>"} },
	  { {"<A>",               "or"}, {"or", "<Condiciones>"} },
	  { {"<A>",               ")"}, {"epsilon"} },     
	  { {"<Sino>",            "}"}, {"epsilon"} },
	  { {"<Sino>",            "id"}, {"epsilon"} },
	  { {"<Sino>",            "leer"}, {"epsilon"} },
	  { {"<Sino>",            "escribir"}, {"epsilon"} },
	  { {"<Sino>",            "sino"}, {"sino", "{", "<Cuerpo>", "}"} },
	  { {"<Sino>",            "si"}, {"epsilon"} },
	  { {"<Sino>",            "mientras"}, {"epsilon"} },
	  { {"<OpAritmeticas>",   "rcd"}, {"<IdCosnt>", "<T>"} },
	  { {"<OpAritmeticas>",   "id"}, {"<IdCosnt>", "<T>"} },
	  { {"<OpAritmeticas>",   "constante"}, {"<IdCosnt>", "<T>"} },
	  { {"<OpAritmeticas>",   "("}, {"<IdCosnt>", "<T>"} },
	  { {"<T>",               "+"}, {"+", "<OpAritmeticas>"} },
	  { {"<T>",               "-"}, {"-", "<OpAritmeticas>"} },
	  { {"<T>",               "/"}, {"/", "<OpAritmeticas>"} },
	  { {"<T>",               "*"}, {"*", "<OpAritmeticas>"} },
	  { {"<T>",               "}"}, {"epsilon"} },
	  { {"<T>",               "^"}, {"^","<OpAritmeticas>"} },
	  { {"<T>",               "and"}, {"epsilon"} },
	  { {"<T>",               "or"}, {"epsilon"} },
	  { {"<T>",               "id"}, {"epsilon"} },
	  { {"<T>",               "opRel"}, {"epsilon"} },
	  { {"<T>",               "leer"}, {"epsilon"} },
	  { {"<T>",               "escribir"}, {"epsilon"} },
	  { {"<T>",               "si"}, {"epsilon"} },
	  { {"<T>",               "mientras"}, {"epsilon"} },
	  { {"<T>",               ")"}, {"epsilon"} },
	  { {"<IdConst>",         "rcd"}, {"rcd", "(", "<OpAritmeticas>", ")"} },
	  { {"<IdConst>",         "id"}, {"id"} },
	  { {"<IdConst>",         "constante"}, {"constante"} },
	  { {"<IdConst>",         "("}, {"(", "<OpAritmeticas>", ")"} }
	};

	const char* SimboloInicial = "<Programa>";

    AnalizadorSintactico::Nodo* arbol = new AnalizadorSintactico::Nodo(SimboloInicial);

    int codigo = ObtenerArbolDerivacion(arbol, std::ref(tas), SimboloInicial);
    
    // por ahora limpiamos el arbol, si quisieramos utilizar el interprete tendriamos que guardarlo.
	LimpiarArbol(arbol);
    
    return 0;
}

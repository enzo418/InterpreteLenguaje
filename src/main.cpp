#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include <iostream>
#include <functional>           // std::ref

using Complex=AnalizadorLexico::ComponenteLexico;

int main(){
	AnalizadorSintactico::TAS tas = {
	//    Variable          	Token     									Produccion
	{	{"<Programa>",        Complex::Var},					{"var", "<Variables>", "{", "<Cuerpo>", "}"} },
	{	{"<Variables>",       Complex::Id},						{"id", "<IdVar>"} },
	{ 	{"<IdVar>",           Complex::LlavesA},				{"epsilon"} },
	{ 	{"<IdVar>",           Complex::Coma},					{",", "id", "<IdVar>"} },
	{ 	{"<IdVar>",           Complex::ParentesisC},			{"epsilon"} },
	{ 	{"<Cuerpo>",          Complex::LlavesC},				{"epsilon"} },
	{ 	{"<Cuerpo>",          Complex::Id},						{"<Sent>", "<Cuerpo>"} },
	{ 	{"<Cuerpo>",          Complex::Leer},					{"<Sent>", "<Cuerpo>"} },
	{	{"<Cuerpo>",          Complex::Escribir},				{"<Sent>", "<Cuerpo>"} },
	{ 	{"<Cuerpo>",          Complex::Si},						{"<Sent>", "<Cuerpo>"} },
	{ 	{"<Cuerpo>",          Complex::Mientras},				{"<Sent>", "<Cuerpo>"} },
	{ 	{"<Sent>",            Complex::Id},						{"id", "=", "<OpAritmeticas>"} },
	{ 	{"<Sent>",            Complex::Leer},					{"leer","(", "cadena", "<OpAritmeticas>",")"} },
	{ 	{"<Sent>",            Complex::Escribir},				{"escribir", "(", "cadena", "<OpAritmeticas>", ")"} },
	{ 	{"<Sent>",            Complex::Si},						{"si", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}", "<Sino>"} },
	{ 	{"<Sent>",            Complex::Mientras},				{"mientras", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}"} },                 
	{ 	{"<Condiciones>",     Complex::RaizCuadrada},			{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	{ 	{"<Condiciones>",     Complex::Id},						{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	{ 	{"<Condiciones>",     Complex::Constante},				{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	{ 	{"<Condiciones>",     Complex::ParantesisA},			{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "A"} },
	{ 	{"<A>",               Complex::And},					{"and", "<Condiciones>"} },
	{ 	{"<A>",               Complex::Or},						{"or", "<Condiciones>"} },
	{ 	{"<A>",               Complex::ParentesisC},			{"epsilon"} },     
	{ 	{"<Sino>",            Complex::LlavesC},				{"epsilon"} },
	{ 	{"<Sino>",            Complex::Id},						{"epsilon"} },
	{ 	{"<Sino>",            Complex::Leer},					{"epsilon"} },
	{ 	{"<Sino>",            Complex::Escribir},				{"epsilon"} },
	{ 	{"<Sino>",            Complex::Sino},					{"sino", "{", "<Cuerpo>", "}"} },
	{ 	{"<Sino>",            Complex::Si},						{"epsilon"} },
	{ 	{"<Sino>",            Complex::Mientras},				{"epsilon"} },
	{ 	{"<OpAritmeticas>",   Complex::RaizCuadrada},			{"<IdCosnt>", "<T>"} },
	{ 	{"<OpAritmeticas>",   Complex::Id},						{"<IdCosnt>", "<T>"} },
	{ 	{"<OpAritmeticas>",   Complex::Constante},				{"<IdCosnt>", "<T>"} },
	{ 	{"<OpAritmeticas>",   Complex::ParantesisA},			{"<IdCosnt>", "<T>"} },
	{ 	{"<T>",               Complex::Mas},					{"+", "<OpAritmeticas>"} },
	{ 	{"<T>",               Complex::Menos},					{"-", "<OpAritmeticas>"} },
	{ 	{"<T>",               Complex::Division},				{"/", "<OpAritmeticas>"} },
	{ 	{"<T>",               Complex::Multiplicacion},			{"*", "<OpAritmeticas>"} },
	{ 	{"<T>",               Complex::LlavesC},				{"epsilon"} },
	{ 	{"<T>",               Complex::Potencia},				{"^","<OpAritmeticas>"} },
	{ 	{"<T>",               Complex::And},					{"epsilon"} },
	{ 	{"<T>",               Complex::Or},						{"epsilon"} },
	{ 	{"<T>",               Complex::Id},						{"epsilon"} },
	{ 	{"<T>",               Complex::OpRel},					{"epsilon"} },
	{ 	{"<T>",               Complex::Leer},					{"epsilon"} },
	{ 	{"<T>",               Complex::Escribir},				{"epsilon"} },
	{ 	{"<T>",               Complex::Si},						{"epsilon"} },
	{ 	{"<T>",               Complex::Mientras},				{"epsilon"} },
	{ 	{"<T>",               Complex::ParentesisC},			{"epsilon"} },
	{ 	{"<IdConst>",         Complex::RaizCuadrada},			{"rcd", "(", "<OpAritmeticas>", ")"} },
	{ 	{"<IdConst>",         Complex::Id},						{"id"} },
	{ 	{"<IdConst>",         Complex::Constante},				{"constante"} },
	{ 	{"<IdConst>",         Complex::ParantesisA},			{"(", "<OpAritmeticas>", ")"} }
	};

	const char* SimboloInicial = "<Programa>";

    AnalizadorSintactico::Nodo* arbol = new AnalizadorSintactico::Nodo(SimboloInicial);

    int codigo = ObtenerArbolDerivacion(arbol, std::ref(tas), SimboloInicial);
    
    // por ahora limpiamos el arbol, si quisieramos utilizar el interprete tendriamos que guardarlo.
	LimpiarArbol(arbol);
    
    return 0;
}

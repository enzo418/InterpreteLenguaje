#include <iostream>
#include <functional>           // std::ref

#include <fstream>

#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include "Sintesis/dds.hpp"

#include "utiles.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

int main(int cant_args, char* args[]){	
	std::string archivoFuente;

	LeerArgumentos(cant_args, args, archivoFuente);

	std::ifstream fuente;

	if(!AbrirArchivo(fuente, archivoFuente)){
		std::cout << "El archivo no existe" << std::endl;
		return 0;
	}
    
	AnalizadorSintactico::TAS tas = 
	{
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
        { 	{"<Sent>",            Complex::Leer},					{"leer","(", "cadena", ",", "<OpAritmeticas>",")"} },
        { 	{"<Sent>",            Complex::Escribir},				{"escribir", "(", "cadena", ",", "<OpAritmeticas>", ")"} },
        { 	{"<Sent>",            Complex::Si},						{"si", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}", "<Sino>"} },
        { 	{"<Sent>",            Complex::Mientras},				{"mientras", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}"} },                 
        { 	{"<Condiciones>",     Complex::RaizCuadrada},			{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "<A>"} },
        { 	{"<Condiciones>",     Complex::Id},						{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "<A>"} },
        { 	{"<Condiciones>",     Complex::Constante},				{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "<A>"} },
     // { 	{"<Condiciones>",     Complex::ParentesisA},			{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "<A>"} },
        { 	{"<Condiciones>",     Complex::ParentesisA},			{"(", "<Condiciones>", ")", "<A>"} },
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
        { 	{"<OpAritmeticas>",   Complex::RaizCuadrada},			{"<IdConst>", "<T>"} },
        { 	{"<OpAritmeticas>",   Complex::Id},						{"<IdConst>", "<T>"} },
        { 	{"<OpAritmeticas>",   Complex::Constante},				{"<IdConst>", "<T>"} },
        { 	{"<OpAritmeticas>",   Complex::ParentesisA},			{"<IdConst>", "<T>"} },
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
        { 	{"<IdConst>",         Complex::ParentesisA},			{"(", "<OpAritmeticas>", ")"} }
	};
   
	// iniciamos la tabla con las palabras reservadas
	AnalizadorLexico::TablaSimbolos ts = {
		{Complex::Si, "si", true},
		{Complex::Or, "or", true},
		{Complex::Var, "var", true},
		{Complex::And, "and", true},
		{Complex::Sino, "sino", true},
		{Complex::Leer, "leer", true},	
		{Complex::RaizCuadrada, "rcd", true},
		{Complex::Escribir, "escribir", true},
		{Complex::Mientras, "mientras", true}
	};

	const char* SimboloInicial = "<Programa>";

    AnalizadorSintactico::Nodo* arbol = new AnalizadorSintactico::Nodo(SimboloInicial);

    int codigo = ObtenerArbolDerivacion(fuente, arbol, std::ref(tas), std::ref(ts), SimboloInicial);
    
    ArbolAArchivo(arbol);
    
    Sintesis::ListaVarReglas tablaVars = {
        {{"<Variables>", "id"}, "AsignarReal"},

		{{"<IdVar>", ","}, "AsignarReal"},

        {{"<Sent>", "id"}, "CambiarValorVariable"},
        {{"<Sent>", "leer"}, "Leer"},
        {{"<Sent>", "escribir"}, "Escribir"},
		{{"<Sent>", "si"}, "ResolverSi"},

        {{"<Condiciones>", "<OpAritmeticas>"}, "ResolverCondicional"},

        {{"<OpAritmeticas>", "<IdConst>"}, "GuardarValorYCopiarListaT"},
        
        {{"<T>", "+"}, "GuardarOperadorYCopiarListaOpA"},
        {{"<T>", "-"}, "GuardarOperadorYCopiarListaOpA"},
        {{"<T>", "*"}, "GuardarOperadorYCopiarListaOpA"},
        {{"<T>", "/"}, "GuardarOperadorYCopiarListaOpA"},
        {{"<T>", "^"}, "GuardarOperadorYCopiarListaOpA"},
        //{{"<T>", "epsilon"}, "GuardarOperadorYCopiarListaOpA"},

        {{"<IdConst>", "id"}, "CopiarValorDeId"},
        {{"<IdConst>", "constante"}, "CopiarValorDeHijo"},
        {{"<IdConst>", "("}, "AgregarParentesisExtremosYCopiarLista"},
        {{"<IdConst>", "rcd"}, "ResolverListaYCalcularRaizCuadrada"},
    };
    
    //DDS(ts, arbol, tablaVars);

	LimpiarArbol(arbol);
    
    return 0;
}

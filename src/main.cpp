#include "AnalizadorSintactico/AnalizadorSintactico.hpp"
#include <iostream>
#include <functional>           // std::ref

#include <sstream>
#include <fstream>

using Complex=AnalizadorLexico::ComponenteLexico;

void RaizAString(AnalizadorSintactico::Nodo* raiz, std::string& texto){
	std::ostringstream dirraiz;
	dirraiz << (void const *)raiz;

	texto += dirraiz.str() + "_" + raiz->contenido + ":";

	// agregar todos los hijos a la cadena separados por $
	size_t sz = raiz->hijos.size(); 
    // apilar todos los simbolos (de derecha a izquierda) y crear sus nodos
    for(int i = sz-1; i >= 0; i--) {
        std::ostringstream dirhijo;
	    dirhijo << (void const *)raiz->hijos[i];
		texto += "[" + dirhijo.str() +"_"+ raiz->hijos[i]->contenido + "]$";
	}

    if(sz > 0)
        // remplezar el ultimo $ con \n
        texto[texto.length() - 1] = '\n';
    else
        texto += "\n";

	// Para cada hijo de esta raiz hacer lo mismo
	for(AnalizadorSintactico::Nodo* nodo: raiz->hijos){
		RaizAString(nodo, texto);
	}
}

void ArbolAArchivo(AnalizadorSintactico::Nodo* arbol){
    std::ifstream archivo;
	std::string texto = "";
	
	RaizAString(arbol, texto);

	std::ofstream outfile ("arbol.txt");

	outfile << texto << std::endl;

	outfile.close();	    
}

int main(){
    
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
     // { 	{"<Condiciones>",     Complex::ParantesisA},			{"<OpAritmeticas>", "opRel", "<OpAritmeticas>", "<A>"} },
        { 	{"<Condiciones>",     Complex::ParantesisA},			{"(", "<Condiciones>", ")", "<A>"} },
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
        { 	{"<OpAritmeticas>",   Complex::ParantesisA},			{"<IdConst>", "<T>"} },
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
    
    ArbolAArchivo(arbol);

    // por ahora limpiamos el arbol, si quisieramos utilizar el interprete tendriamos que guardarlo.
	LimpiarArbol(arbol);
    
    return 0;
}

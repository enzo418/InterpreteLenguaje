#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <stack>
#include <memory> 
#include "AnalizadorLexico/AnalizadorLexico.hpp"
#include "utiles.hpp"

#define EsVariable(X) X[0] == '<' && X[strlen(X)-1] == '>'

// typedef std::map<std::tuple<std::string, std::string>, std::string> TAS;

// Nodo de un arbol
struct Nodo {
    std::string contenido;
    // std::vector<std::unique_ptr<struct Nodo>> hijos;
    std::vector<struct Nodo*> hijos;
    
    // inicializador
    Nodo(const char* cont): contenido(cont){}
};

// Producciones resultantes de un par Variable - Token
typedef std::vector<const char*> Produccion;

// Tabla de Analisis Sintactico
typedef std::map<std::tuple<const char*, const char*>, Produccion> TAS;

// Pila de Simbolos
typedef std::stack<std::pair<const char*, Nodo*>> Pila;

void LimpiarArbol(Nodo* raiz, Nodo* padre = nullptr){
	while(raiz->hijos.size() > 0){
		LimpiarArbol(raiz->hijos[0], raiz);
	}

	delete raiz;

	if(padre) padre->hijos.erase(padre->hijos.begin()); // borrar el primer elem del vector
}

int main(){
    // std::make_tuple
    TAS tas = {
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

    // std::unique_ptr<Nodo> raiz(new Nodo(SimboloInicial));
    Nodo* arbol = new Nodo(SimboloInicial);
    Nodo* raiz = arbol;

    Pila pilaSimbolos;
    pilaSimbolos.push(std::pair<const char*, Nodo*>("$", nullptr));
    pilaSimbolos.push(std::pair<const char*, Nodo*>(SimboloInicial, raiz));

    bool exito;
    bool error;
    
    // Declararamos las variables que necesita analizador lexico
    std::ifstream fuente;
    if(!AbrirArchivo(fuente, "./input.txt")){
      std::cout << "El archivo no existe" << std::endl; 
      return 1;
    }
    
    ulong control = 0;
    std::string lexema;
    AnalizadorLexico::ComponenteLexico complex;	

    AnalizadorLexico::TablaSimbolos ts;
    
    ObtenerSiguienteComplex(fuente, control, complex, lexema, ts);

    // bucle principal del analizador sintactico
    while (!exito && !error) {      
        // Obtener X
        std::pair<const char*, Nodo*> par = pilaSimbolos.top();
        const char* X = par.first;
        raiz = par.second;

        // Quitar el elemento
        pilaSimbolos.pop();

        if(EsVariable(X)){
          Produccion produccion = tas[{X, lexema.c_str()}];
          
          if(!produccion.empty()){
            size_t sz = produccion.size(); 
            // apilar todos los simbolos (de derecha a izquierda) y crear sus nodos
            for(int i = sz-1; i >= 0; i--) {
              // Crear nodo hijo de X en el arbol
              Nodo* nodo = new Nodo(produccion[i]);
              raiz->hijos.push_back(nodo);

              // Apilar el simbolo, si no es variable quitar la referencia al nodo ya que no se va a derivar
              if(!EsVariable(produccion[i])) nodo = nullptr;
              pilaSimbolos.push(std::pair<const char*, Nodo*>(produccion[i], nodo));
            }
          } else {
            error = true;
          }
        } else {
          if(X == lexema || (X == "id" && complex == AnalizadorLexico::Identificador)){
            if(X == "$"){
              exito = true;
            }
            ObtenerSiguienteComplex(fuente, control, complex, lexema, ts);
          }else{
            error = true;
          }
        }
    }
    
    // por ahora limpiamos el arbol, si quisieramos utilizar el interprete tendriamos que guardarlo.
    LimpiarArbol(arbol);
    return 0;
}

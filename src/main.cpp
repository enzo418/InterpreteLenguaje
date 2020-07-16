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

void LimpiarArbol(Nodo* raiz){
  // reccorrer arbol y dar delete
}


int main(){
    // std::make_tuple
    TAS tas = {
    //    Variable          Token     Produccion
      { {"<Programa>",        "var"}, {"var", "<Variables>", "{", "<Cuerpo>", "}"} },
      { {"<Variables>",       "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<IdVar>",           "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Cuerpo>",          "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Sent>",            "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Asignacion>",      "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Funcion>",         "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Mientras>",        "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Condiciones>",     "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<A>",               "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<OpLogico>",        "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Si>",              "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Sino>",            "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<OpAritmeticas>",   "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<T>",               "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<Operador>",        "TOKEN"}, {"<P>", "R", "O", "D"} },
      { {"<IdConst>",         "TOKEN"}, {"<P>", "R", "O", "D"} }
    };

    const char* SimboloInicial = "<Programa>";

    // std::unique_ptr<Nodo> raiz(new Nodo(SimboloInicial));
    Nodo* arbol = new Nodo(SimboloInicial);
    Nodo** raiz = &arbol;

    Pila pilaSimbolos;
    pilaSimbolos.push(std::pair<const char*, Nodo*>("$", nullptr));
    pilaSimbolos.push(std::pair<const char*, Nodo*>(SimboloInicial, *raiz));

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

    // bucle principal del analizador sintactico
    while (!exito && !error) {
        ObtenerSiguienteComplex(fuente, control, complex, lexema, ts);

        // Obtener X
        std::pair<const char*, Nodo*> par = pilaSimbolos.top();
        const char* X = par.first;
        raiz = &par.second;

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
              (*raiz)->hijos.push_back(nodo);

              // Apilar el simbolo, si no es variable quitar la referencia al nodo ya que no se va a derivar
              if(!EsVariable(produccion[i])) nodo = nullptr;
              pilaSimbolos.push(std::pair<const char*, Nodo*>(produccion[i], nodo));
            }
          } else {
            error = true;
          }
        } else {
          if(X == lexema){
            if(X == "$"){
              exito = true;
            }
            /// TODO: avanzar el control al siguiente simbolo de entrada.
          }else{
            error = true;
          }
        }
    }
    
    // por ahora limpiamos el arbol, si quisieramos utilizar el interprete tendriamos que guardarlo.
    LimpiarArbol(arbol);
    return 0;
}
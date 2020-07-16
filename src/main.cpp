#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <stack>
#include <memory> 
#include "AnalizadorLexico/AnalizadorLexico.hpp"
#include "utiles.hpp"

// typedef std::map<std::tuple<std::string, std::string>, std::string> TAS;

// Nodo de un arbol
struct Nodo {
    std::string contenido;
    std::vector<std::unique_ptr<struct Nodo>> hijos;
    
    // inicializador
    Nodo(const char* cont): contenido(cont){}
};

// Producciones resultantes de un par Variable - Token
typedef std::vector<const char*> Produccion;

// Tabla de Analisis Sintactico
typedef std::map<std::tuple<const char*, const char*>, Produccion> TAS;

// Pila de Simbolos
typedef std::stack<const char*> Pila;

int main(){
    // std::make_tuple
    TAS tas = {
    //    Variable          Token     Produccion
      { {"<Programa>",        "TOKEN"}, {"<A>", "id", "+", "<Cuerpo>"} },
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
    Pila pilaSimbolos;
    pilaSimbolos.push("$");
    pilaSimbolos.push(SimboloInicial);

    bool exito;
    bool error;

    bool esElInicial = true;

    std::unique_ptr<Nodo> raiz(new Nodo(SimboloInicial));
    
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
    while (exito || error) {
        ObtenerSiguienteComplex(fuente, control, complex, lexema, ts);
        /* Procedimiento:

         * Voy a la tabla de analisis sintactico (TAS) y me fijo que produccion tengo que aplicar para la variable y token 
           que tengo.
        */
        const char* X = Desapilar(pilaSimbolos);
        if(!esElInicial){
          // Bucsar a X en el arbol y obtener el puntero, para luego utilizarlo en raiz->hijos...
        }
        
        // si es variable <...>
        if(X[0] == '<' && X[strlen(X)-1] == '>'){
          Produccion produccion = tas[{X, lexema.c_str()}];
          
          if(!produccion.empty()){      
            size_t sz = produccion.size(); 
            // apilar todos los simbolos (de derecha a izquierda)
            for(int i = sz-1; i >= 0; i--) {
              pilaSimbolos.push(produccion[i]);
              raiz->hijos.push_back(std::unique_ptr<Nodo>(new Nodo(produccion[i])));
            }
          }else{
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
        /* 
         * Voy al arbol de derivacion y transforma al inicial en la produccion
         
         * Apilo la parte derecha de la produccion, con el simbolo que esta mas a la izquierda al tope de la pila. 
           Entonces en esa pila voy a estar apilando las producciones.

         * Cuando apilo las producciones puede ser que en el tope me quede un terminal, si es asi ese terminal tiene que 
           ser igual al terminal que esta en la entrada (AL). Entonces si tengo variable (en pila) con terminal (entrada) 
           voy a la TAS y aplico la produccion que me dice, y si tengo terminal con terminal tienen que ser iguales. 
           Si no es el mismo hay un error sintactico.
    
         * Si voy a la TAS y la celda que obtuve esta vacia, entonces hay un error.
         
         */
    }
    
    return 0;
}

inline const char* Desapilar(Pila& pila){
  const char* Y = pila.top(); 
  pila.pop();
  return Y;
}
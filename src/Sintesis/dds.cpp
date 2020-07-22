#include "dds.hpp"

void DDS(AnalizadorLexico::TablaSimbolos& ts, AnalizadorSintactico::Nodo* arbol, Sintesis::ListaVarReglas &reglas){
    // Para saber que regla semantica aplicar luego de pasar por los mas de un hijo en un nodo X
    // obtener el primer hijo N y buscar en la lista por una produccion que sea producida por X y empieze con N.
    // esto basado en que la gramatica es LL(1) por lo que cada produccion empieza diferente y con solo saber el 
    // primer simbolo ya podemos saber a que produccion ir.

    // luego de esto buscamos en la lista de variables por una que sea Padre(X) y produzca X (Padre(X)  -> X)
}
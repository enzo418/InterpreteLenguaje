#include "Interprete.hpp"

#include "utiles.hpp"

int Interprete::Interpretar(std::string input) {
    bool sucess = true;
    AnalizadorSintactico::Nodo* arbol =
        new AnalizadorSintactico::Nodo(SimboloInicial);

    Error error;

    _CodigoFuente = input;

    std::istringstream fuente(input.c_str());

    bool arbolObtenidoConExito = false;

    try {
        arbolObtenidoConExito = ObtenerArbolDerivacion(
            fuente, arbol, tas, ts, SimboloInicial, false, error);
    } catch (...) {
        sucess = false;
    }

    // guardar y enviar arbol al cliente
#ifdef USE_EMSCRIPTEN
    std::string cadenaArbol;  // reservar?
    RaizAString(arbol, cadenaArbol);
    val interprete = val::global("interprete");
    interprete.call<void>("setSyntaxTree", cadenaArbol);
#else
    ArbolAArchivo(arbol);
#endif

    // Evaluar el codigo
    if (arbolObtenidoConExito) {
        try {
            EvaluarPrograma(arbol);
        } catch (...) {
            sucess = false;
        }
    } else {
        ManejarErrorYSalir(error, false);
        sucess = false;
    }

    LimpiarArbol(arbol);

    return (int)!sucess;
}

const char* Interprete::SimboloInicial = "<Programa>";

AnalizadorSintactico::TAS Interprete::tas = {
    //    Variable          	Token
    //    Produccion
    {{"<Programa>", Complex::Var},
     {"var", "<Variables>", "{", "<Cuerpo>", "}"}},
    {{"<Variables>", Complex::Id}, {"id", "<IdVar>"}},

    {{"<IdVar>", Complex::LlavesA}, {"epsilon"}},
    {{"<IdVar>", Complex::Coma}, {",", "id", "<IdVar>"}},
    {{"<IdVar>", Complex::ParentesisC}, {"epsilon"}},

    {{"<Cuerpo>", Complex::LlavesC}, {"epsilon"}},
    {{"<Cuerpo>", Complex::Id}, {"<Sent>", "<Cuerpo>"}},
    {{"<Cuerpo>", Complex::Leer}, {"<Sent>", "<Cuerpo>"}},
    {{"<Cuerpo>", Complex::Escribir}, {"<Sent>", "<Cuerpo>"}},
    {{"<Cuerpo>", Complex::Si}, {"<Sent>", "<Cuerpo>"}},
    {{"<Cuerpo>", Complex::Mientras}, {"<Sent>", "<Cuerpo>"}},

    {{"<Sent>", Complex::Id}, {"id", "=", "<OpAritmeticas>"}},
    {{"<Sent>", Complex::Leer}, {"leer", "(", "cadena", ",", "id", ")"}},
    {{"<Sent>", Complex::Escribir},
     {"escribir", "(", "cadena", ",", "<OpAritmeticas>", ")"}},
    {{"<Sent>", Complex::Si},
     {"si", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}", "<Sino>"}},
    {{"<Sent>", Complex::Mientras},
     {"mientras", "(", "<Condiciones>", ")", "{", "<Cuerpo>", "}"}},

    {{"<Condiciones>", Complex::Menos}, {"<Cond3>", "<B>", "<A>"}},
    {{"<Condiciones>", Complex::RaizCuadrada}, {"<Cond3>", "<B>", "<A>"}},
    {{"<Condiciones>", Complex::Id}, {"<Cond3>", "<B>", "<A>"}},
    {{"<Condiciones>", Complex::Constante}, {"<Cond3>", "<B>", "<A>"}},
    {{"<Condiciones>", Complex::ParentesisA}, {"<Cond3>", "<B>", "<A>"}},
    {{"<Condiciones>", Complex::CorcheteA}, {"<Cond3>", "<B>", "<A>"}},
    {{"<Condiciones>", Complex::Not}, {"<Cond3>", "<B>", "<A>"}},

    //{ 	{"<A>",               Complex::And},
    //{"and", "<Condiciones>"} },
    {{"<A>", Complex::Or}, {"or", "<Condiciones>"}},
    {{"<A>", Complex::ParentesisC}, {"epsilon"}},
    {{"<A>", Complex::CorcheteC}, {"epsilon"}},

    {{"<B>", Complex::And}, {"and", "<Cond3>", "<B>"}},
    {{"<B>", Complex::Or}, {"epsilon"}},
    {{"<B>", Complex::ParentesisC}, {"epsilon"}},
    {{"<B>", Complex::CorcheteC}, {"epsilon"}},

    {{"<Cond3>", Complex::Menos},
     {"<OpAritmeticas>", "opRel", "<OpAritmeticas>"}},
    {{"<Cond3>", Complex::RaizCuadrada},
     {"<OpAritmeticas>", "opRel", "<OpAritmeticas>"}},
    {{"<Cond3>", Complex::Id}, {"<OpAritmeticas>", "opRel", "<OpAritmeticas>"}},
    {{"<Cond3>", Complex::Constante},
     {"<OpAritmeticas>", "opRel", "<OpAritmeticas>"}},
    {{"<Cond3>", Complex::ParentesisA},
     {"<OpAritmeticas>", "opRel", "<OpAritmeticas>"}},
    {{"<Cond3>", Complex::CorcheteA}, {"[", "<Condiciones>", "]"}},

    {{"<Sino>", Complex::LlavesC}, {"epsilon"}},
    {{"<Sino>", Complex::Id}, {"epsilon"}},
    {{"<Sino>", Complex::Leer}, {"epsilon"}},
    {{"<Sino>", Complex::Escribir}, {"epsilon"}},
    {{"<Sino>", Complex::Sino}, {"sino", "{", "<Cuerpo>", "}"}},
    {{"<Sino>", Complex::Si}, {"epsilon"}},
    {{"<Sino>", Complex::Mientras}, {"epsilon"}},

    {{"<OpAritmeticas>", Complex::Menos}, {"<T>", "<W>"}},
    {{"<OpAritmeticas>", Complex::RaizCuadrada}, {"<T>", "<W>"}},
    {{"<OpAritmeticas>", Complex::Id}, {"<T>", "<W>"}},
    {{"<OpAritmeticas>", Complex::Constante}, {"<T>", "<W>"}},
    {{"<OpAritmeticas>", Complex::ParentesisA}, {"<T>", "<W>"}},

    {{"<W>", Complex::Mas}, {"+", "<T>", "<W>"}},
    {{"<W>", Complex::Menos}, {"-", "<T>", "<W>"}},
    {{"<W>", Complex::LlavesC}, {"epsilon"}},
    {{"<W>", Complex::And}, {"epsilon"}},
    {{"<W>", Complex::Or}, {"epsilon"}},
    {{"<W>", Complex::Id}, {"epsilon"}},
    {{"<W>", Complex::OpRel}, {"epsilon"}},
    {{"<W>", Complex::Leer}, {"epsilon"}},
    {{"<W>", Complex::Escribir}, {"epsilon"}},
    {{"<W>", Complex::Si}, {"epsilon"}},
    {{"<W>", Complex::Mientras}, {"epsilon"}},
    {{"<W>", Complex::ParentesisC}, {"epsilon"}},
    {{"<W>", Complex::CorcheteC}, {"epsilon"}},

    {{"<T>", Complex::Menos}, {"<F>", "<Z>"}},
    {{"<T>", Complex::RaizCuadrada}, {"<F>", "<Z>"}},
    {{"<T>", Complex::Id}, {"<F>", "<Z>"}},
    {{"<T>", Complex::Constante}, {"<F>", "<Z>"}},
    {{"<T>", Complex::ParentesisA}, {"<F>", "<Z>"}},

    {{"<Z>", Complex::Mas}, {"epsilon"}},
    {{"<Z>", Complex::Menos}, {"epsilon"}},
    {{"<Z>", Complex::Division}, {"/", "<F>", "<Z>"}},
    {{"<Z>", Complex::Multiplicacion}, {"*", "<F>", "<Z>"}},
    {{"<Z>", Complex::LlavesC}, {"epsilon"}},
    {{"<Z>", Complex::And}, {"epsilon"}},
    {{"<Z>", Complex::Or}, {"epsilon"}},
    {{"<Z>", Complex::Id}, {"epsilon"}},
    {{"<Z>", Complex::OpRel}, {"epsilon"}},
    {{"<Z>", Complex::Leer}, {"epsilon"}},
    {{"<Z>", Complex::Escribir}, {"epsilon"}},
    {{"<Z>", Complex::Si}, {"epsilon"}},
    {{"<Z>", Complex::Mientras}, {"epsilon"}},
    {{"<Z>", Complex::ParentesisC}, {"epsilon"}},
    {{"<Z>", Complex::CorcheteC}, {"epsilon"}},

    {{"<F>", Complex::Menos}, {"<R>", "<X>"}},
    {{"<F>", Complex::RaizCuadrada},
     {"rcd", "(", "<OpAritmeticas>", ")", "<X>"}},
    {{"<F>", Complex::Id}, {"<R>", "<X>"}},
    {{"<F>", Complex::Constante}, {"<R>", "<X>"}},
    {{"<F>", Complex::ParentesisA}, {"<R>", "<X>"}},

    {{"<X>", Complex::Mas}, {"epsilon"}},
    {{"<X>", Complex::Menos}, {"epsilon"}},
    {{"<X>", Complex::Division}, {"epsilon"}},
    {{"<X>", Complex::Multiplicacion}, {"epsilon"}},
    {{"<X>", Complex::LlavesC}, {"epsilon"}},
    {{"<X>", Complex::Potencia}, {"^", "<R>", "<X>"}},
    {{"<X>", Complex::And}, {"epsilon"}},
    {{"<X>", Complex::Or}, {"epsilon"}},
    {{"<X>", Complex::Id}, {"epsilon"}},
    {{"<X>", Complex::OpRel}, {"epsilon"}},
    {{"<X>", Complex::Leer}, {"epsilon"}},
    {{"<X>", Complex::Escribir}, {"epsilon"}},
    {{"<X>", Complex::Si}, {"epsilon"}},
    {{"<X>", Complex::Mientras}, {"epsilon"}},
    {{"<X>", Complex::ParentesisC}, {"epsilon"}},
    {{"<X>", Complex::CorcheteC}, {"epsilon"}},
    {{"<X>", Complex::Modulo}, {"%", "<R>", "<X>"}},

    {{"<R>", Complex::Menos}, {"-", "<R>"}},
    {{"<R>", Complex::Id}, {"id"}},
    {{"<R>", Complex::Constante}, {"constante"}},
    {{"<R>", Complex::ParentesisA}, {"(", "<OpAritmeticas>", ")"}},
};

AnalizadorLexico::TablaSimbolos Interprete::ts = {
    {Complex::Si, "si", true},
    {Complex::Or, "or", true},
    {Complex::Var, "var", true},
    {Complex::And, "and", true},
    {Complex::Sino, "sino", true},
    {Complex::Leer, "leer", true},
    {Complex::RaizCuadrada, "rcd", true},
    {Complex::Escribir, "escribir", true},
    {Complex::Mientras, "mientras", true},
    {Complex::Not, "not", true}};

#ifdef USE_EMSCRIPTEN
EMSCRIPTEN_BINDINGS(interprete) {
    class_<Interprete>("Interprete")
        //.constructor<std::string, intptr_t, intptr_t>()
        .class_function("Interpretar", &Interprete::Interpretar);
}
#endif

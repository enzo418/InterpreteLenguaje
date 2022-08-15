#include "utiles.hpp"

#include <string.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "AnalizadorSintactico/tipos.hpp"

bool AbrirArchivo(std::ifstream& fuente, std::string archivo){
    // Abrimos el archivo con permisos de lectura
    fuente.open(archivo);

    if(!fuente.good()){ // si no se pudo abrir
        return false;         
    }
    
    return true;
}

void LeerArgumentos(int cant_args, char* args[], std::string& archivoFuente, bool& volcar){
	archivoFuente = "entrada.txt";

	for (size_t i = 0; i < cant_args; i++) {
		if(strcmp(args[i], "-fuente") == 0 && cant_args >= i+1){
			archivoFuente = args[i+1];
		} else if(strcmp(args[i], "-volcar") == 0){
			volcar = true;
		}
	}

}

void RaizAString(AnalizadorSintactico::Nodo* raiz, std::string& texto) {
    std::ostringstream dirraiz;
    dirraiz << (void const*)raiz;

    texto += dirraiz.str() + "_" + raiz->contenido + ":";

    // agregar todos los hijos a la cadena separados por $
    size_t sz = raiz->hijos.size();
    // apilar todos los simbolos (de derecha a izquierda) y crear sus nodos
    for (int i = 0; i < sz; i++) {
        std::ostringstream dirhijo;
        dirhijo << (void const*)raiz->hijos[i];
        texto += "|" + dirhijo.str() + " " + raiz->hijos[i]->contenido + " " +
                 raiz->hijos[i]->lexema + "|";
    }

    if(sz > 0)
        // remplezar el ultimo $ con \n
        texto += '\n';
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

void ManejarErrorYSalir(const Error& error, ulong controlMasCercano,
                        bool shouldThrow) {
    Error err = error;

    if (error.linea == -1 || error.columna == -1) {
        std::istringstream fuente(_CodigoFuente.c_str());

        auto [linea, columna] =
            ObtenerLineaColumnaDeControl(fuente, controlMasCercano);

        err = Error(linea, columna - error.longitud, error.longitud,
                    error.mensaje);
    }

#ifdef USE_EMSCRIPTEN
    val interprete = val::global("interprete");
    interprete.call<val>("addErrorMarker", err.linea, err.columna, err.longitud,
                         err.mensaje);
#else
    std::cout << "Error!"
              << "\nLinea: " << err.linea << "\nColumna: " << err.columna
              << "\nLongitud: " << err.longitud << "\nMensaje: " << err.mensaje
              << std::endl;
#endif

    if (shouldThrow) throw 1;
}

void VolverHastaNuevaLinea(std::ifstream& archivo){
	char sig = archivo.peek();
	while (archivo.peek() <= 32 && archivo.good()) {
		archivo.unget();
	}

	while (archivo.tellg() != 0 && archivo.good())
	{
		sig = archivo.peek();
		if(sig == '\r' || sig == '\n'){
			archivo.get();		
			break;	
		}else archivo.unget();
	}
}

std::pair<ulong, ulong> ObtenerLineaColumnaDeControl(std::istream& fuente,
                                                     ulong position) {
    fuente.clear();
    ulong current = fuente.tellg();
    fuente.seekg(0);

    ulong line = 1;
    ulong column = 1;
    while (fuente.tellg() < position && !fuente.eof()) {
        if (fuente.get() == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
    }

    fuente.seekg(position);

    return std::make_pair(line, column);
}
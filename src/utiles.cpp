#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>

#include "utiles.hpp"

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


void RaizAString(AnalizadorSintactico::Nodo* raiz, std::string& texto){
	std::ostringstream dirraiz;
	dirraiz << (void const *)raiz;

	texto += dirraiz.str() + "_" + raiz->contenido + ":";

	// agregar todos los hijos a la cadena separados por $
	size_t sz = raiz->hijos.size(); 
    // apilar todos los simbolos (de derecha a izquierda) y crear sus nodos
    for(int i = 0; i < sz; i++) {
        std::ostringstream dirhijo;
	    dirhijo << (void const *)raiz->hijos[i];
		texto += "¿" + dirhijo.str() +"_"+ raiz->hijos[i]->contenido + "?$";
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


void ManejarErrorYSalir(std::string mensaje, ulong* controlMasCercano){
	std::cout << mensaje << std::endl;

	if(controlMasCercano){
		std::ifstream archivo;
		AbrirArchivo(archivo, _ArchivoFuente);

		archivo.seekg(*controlMasCercano - 1);

		VolverHastaNuevaLinea(archivo);
		
		std::string linea;
		std::getline(archivo, linea);

		// Quitar los tabs
		linea.erase(std::remove( linea.begin(), linea.end(), '\t' ),linea.end());

		std::cout << "\n" << _ArchivoFuente << ":" << *controlMasCercano << " \"" << linea << "\"" << std::endl;
	}
	
	std::exit(EXIT_FAILURE);
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
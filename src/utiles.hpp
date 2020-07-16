#include <iostream>
#include <fstream>

bool AbrirArchivo(std::ifstream& fuente, const char* archivo){
    // Abrimos el archivo con permisos de lectura
    std::ifstream fuente(archivo);

    if(!fuente.good()){ // si no se pudo abrir
        return false;         
    }
    
    return true;
}
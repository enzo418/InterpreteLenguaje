#pragma once

#include <iostream>
#include <fstream>

#include "AnalizadorSintactico/tipos.hpp"

bool AbrirArchivo(std::ifstream& fuente, std::string archivo);

void LeerArgumentos(int cant_args, char* args[], std::string& archivoFuente);

void RaizAString(AnalizadorSintactico::Nodo* raiz, std::string& texto);

void ArbolAArchivo(AnalizadorSintactico::Nodo* arbol);
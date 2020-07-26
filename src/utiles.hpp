#pragma once

#include <iostream>
#include <fstream>

#include "AnalizadorSintactico/tipos.hpp"

extern std::string _ArchivoFuente;

bool AbrirArchivo(std::ifstream& fuente, std::string archivo);

void LeerArgumentos(int cant_args, char* args[], std::string& archivoFuente, bool& volcar);

void RaizAString(AnalizadorSintactico::Nodo* raiz, std::string& texto);

void ArbolAArchivo(AnalizadorSintactico::Nodo* arbol);

void ManejarErrorYSalir(std::string mensaje, ulong* controlMasCercano = nullptr);

void VolverHastaNuevaLinea(std::ifstream& archivo);
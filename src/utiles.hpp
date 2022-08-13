#pragma once

#include <fstream>
#include <iostream>

#include "AnalizadorSintactico/tipos.hpp"
#include "Error.hpp"

extern std::string _CodigoFuente;

bool AbrirArchivo(std::ifstream& fuente, std::string archivo);

void LeerArgumentos(int cant_args, char* args[], std::string& archivoFuente, bool& volcar);

void RaizAString(AnalizadorSintactico::Nodo* raiz, std::string& texto);

void ArbolAArchivo(AnalizadorSintactico::Nodo* arbol);

// Toma un error y un control, si el error le falta linea (== -1) y columna se
// utiliza el parametro controlMasCercano para calcularlas
void ManejarErrorYSalir(const Error& error, ulong* controlMasCercano = nullptr);

void VolverHastaNuevaLinea(std::ifstream& archivo);

std::pair<ulong, ulong> ObtenerLineaColumnaDeControl(std::istream& fuente,
                                                     ulong control);
#pragma once
#include <iostream>
#include <vector>

#include "../AnalizadorLexico/AnalizadorLexico.hpp"
#include "tipos.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;
#include "reglas.hpp"

#include <math.h> 
#include <algorithm> // std::reverse
#include <iterator> // std::advance

#include "../AnalizadorLexico/utiles.hpp"

#include "tipos.hpp"
#include "utiles.hpp"

#include "operaciones_aritmeticas.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void CopiarValorDeId(std::string identificador, double* destino, AnalizadorLexico::TablaSimbolos& ts);

void CopiarValorDeHijo(double* destino, double* fuente);

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void AgregarParentesisExtremosYCopiarLista(Sintesis::ListaOperadoresOperando* listaOpa, Sintesis::ListaOperadoresOperando* destino);

void CambiarValorVariable(std::string& lexema, Sintesis::ListaOperadoresOperando* lista, AnalizadorLexico::TablaSimbolos& ts);

void ResolverListaYCalcularRaizCuadrada(Sintesis::ListaOperadoresOperando& lista, double* destino);

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts);

void GuardarValorYCopiarListaIdConstyT(double& valor, Sintesis::ListaOperadoresOperando* listaT, 
										Sintesis::ListaOperadoresOperando* listaIdConst,
										Sintesis::ListaOperadoresOperando* listaOpA);

void GuardarOperadorYCopiarListaOpA(Complex& operador, Sintesis::ListaOperadoresOperando* listaOpA, Sintesis::ListaOperadoresOperando* listaT);

bool ResolverCondicional(Sintesis::ListaOperadoresOperando* listaOpAi, Complex& operador, Sintesis::ListaOperadoresOperando* listaOpAd);

void Escribir(std::string& cadena, Sintesis::ListaOperadoresOperando* lista);

void RaizCuadrada(double* fuente, double* destino);
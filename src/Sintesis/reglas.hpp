#pragma once
#include <iostream>
#include <vector>

#include "../AnalizadorLexico/AnalizadorLexico.hpp"
#include "tipos.hpp"

using LOD = Sintesis::ListaOperadorDoble;
using Complex=AnalizadorLexico::ComponenteLexico;

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void CambiarValorVariable(std::string& lexema, Sintesis::ListaOperadorDoble* lista, AnalizadorLexico::TablaSimbolos& ts);

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts);

void GuardarValorYCopiarListaT(double& valor, LOD* listaT, LOD* listaOpA);

void GuardarOperadorYCopiarListaOpA(Complex& operador, LOD* listaOpA, LOD* listaT);

void ResolverCondicional(LOD* listaOpAi, Complex& operador, LOD* listaOpAd, bool& res);

void ResolverLista(LOD* lista, double* res);

//void CalcularOperacion(Complex operador, std::pair<double, double>* operandos, double* val);

void Escribir(std::string& cadena, Sintesis::ListaOperadorDoble* lista);

void SumarLista(Sintesis::ListaOperadorDoble* lista, double* res);

void RestarLista(Sintesis::ListaOperadorDoble* lista, double* res);

void MultiplicarLista(Sintesis::ListaOperadorDoble* lista, double* res);

void DividirLista(Sintesis::ListaOperadorDoble* lista, bool invertida, double* res);

void PotenciaLista(Sintesis::ListaOperadorDoble* lista, double* res);

void RaizCuadrada(double& a, double& res);
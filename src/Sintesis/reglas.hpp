#pragma once
#include <iostream>
#include <vector>

#include "../AnalizadorLexico/AnalizadorLexico.hpp"
#include "tipos.hpp"

using LOD = Sintesis::ListaOperadorDoble;

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void CambiarValorVariable(std::string& lexema, double valor, AnalizadorLexico::TablaSimbolos& ts);

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts);

void GuardarValorYCopiarListaT(double& valor, LOD* listaT, LOD* listaOpA);

void GuardarOperadorYCopiarListaOpA(AnalizadorLexico::ComponenteLexico& operador, LOD* listaOpA, LOD* listaT);

void ResolverCondicional(LOD* listaOpA1, AnalizadorLexico::ComponenteLexico& operador, LOD* listaOpA2);

void ResolverLista(LOD* lista, double& res);

//void CalcularOperacion(AnalizadorLexico::ComponenteLexico operador, std::pair<double, double>* operandos, double* val);

void Escribir(std::string& cadena, double& val);

void Suma(double& a, double &b, double& res);

void Resta(double& a, double &b, double& res);

void Multiplicacion(double& a, double &b, double& res);

void Division(double& a, double &b, double& res);

void Potencia(double& a, double &b, double& res);

void RaizCuadrada(double& a, double& res);
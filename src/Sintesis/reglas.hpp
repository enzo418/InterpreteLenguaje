#pragma once
#include "../AnalizadorLexico/AnalizadorLexico.hpp"

void AsignarReal(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void CopiarVariable(std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);

void CambiarValorVariable(std::string& lexema, double valor, AnalizadorLexico::TablaSimbolos& ts);

void Leer(std::string& cadena, std::string& var, AnalizadorLexico::TablaSimbolos& ts);

void Escribir(std::string& cadena, double& val);

void Suma(double& a, double &b, double& res);

void Resta(double& a, double &b, double& res);

void Multiplicacion(double& a, double &b, double& res);

void Division(double& a, double &b, double& res);

void Potencia(double& a, double &b, double& res);

void RaizCuadrada(double& a, double& res);
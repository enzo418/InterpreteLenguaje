#pragma once

#include "../AnalizadorSintactico/tipos.hpp"
#include "../Definiciones.hpp"
#include "ettd.hpp"
#include "tipos.hpp"

#ifdef USE_EMSCRIPTEN
#include <emscripten/val.h>
using namespace emscripten;
#endif

using Nodo=AnalizadorSintactico::Nodo;
using Variables=Sintesis::Variables;
using Complex=AnalizadorLexico::ComponenteLexico;

void EvaluarPrograma(Nodo* arbol);

void EvaluarVariables(Nodo* arbol, Variables& variables);

void EvaluarIdVar(Nodo* IdVar, Variables& variables);

void EvaluarCuerpo(Nodo* Cuerpo, Variables& variables);

void EvaluarSent(Nodo* Sent, Variables& variables);

void EvaluarAsignacion(Nodo* OperacionAritmetica, Nodo* id,
                       Variables& variables);

void EvaluarLeer(Nodo* cadena, Nodo* id, Variables& variables,
                 ulong* controlMasCercano);

void EvaluarEscribir(std::string cadena, Nodo* OperacionAritmetica, Variables& variables);


void EvaluarMientras(Nodo* Condiciones, Nodo* Cuerpo, Variables& variables);


void EvaluarSi(Nodo* Condiciones, Nodo* Cuerpo, Nodo* Sino, Variables& variables);


bool EvaluarCondiciones(Nodo* Condiciones, Variables& variables);

bool EvaluarA(Nodo* A, Variables& variables);

bool EvaluarB(Nodo* B, Variables& variables);

bool EvaluarCond3(Nodo* Cond3, Variables& variables);

void EvaluarSino(Nodo* Sino, Variables& variables);

void EvaluarOpAritmeticas(Nodo* OpAritmeticas, Variables& variables, double& res);

void EvaluarW(Nodo* W, Variables& variables, double& izq, double& res);

void EvaluarT(Nodo* T, Variables& variables, double& res);

void EvaluarZ(Nodo* Z, Variables& variables, double& izq, double& res);

void EvaluarF(Nodo* F, Variables& variables, double& res);

void EvaluarX(Nodo* X, Variables& variables, double& base, double& res);

void EvaluarR(Nodo* R, Variables& variables, double& res);
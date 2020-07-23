#pragma once
#include "tipos.hpp"
#include "../AnalizadorLexico/tipos.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

Sintesis::uchar PrecedenciaComplex(Complex& complex);

bool ExisteMasDeUnOperador(Sintesis::ListaOperadores* lista);

size_t ObtenerPosicionMayorPrecedencia(Sintesis::ListaOperadores* lista, Complex& operador);

size_t EncontrarPosicionParentesisC(Sintesis::ListaOperadores& lista, size_t& posA, unsigned int& profundidad);

double CalcularValorLista(Sintesis::ListaOperadores& operadores, Sintesis::ListaOperandos& operandos);
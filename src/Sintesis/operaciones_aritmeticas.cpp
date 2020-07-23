#include "tipos.hpp"
#include "operaciones_aritmeticas.hpp"
#include "../AnalizadorLexico/tipos.hpp"
#include <math.h>

#include <algorithm>

using Complex=AnalizadorLexico::ComponenteLexico;

Sintesis::uchar PrecedenciaComplex(Complex& complex) {
	Sintesis::uchar imp = 10;
	switch (complex) {
	case Complex::Mas:
		imp = 4;
		break;
	case Complex::Menos:
		imp = 3;
		break;
	case Complex::Multiplicacion:
		imp = 2;
		break;
	case Complex::Division:
		imp = 2;
		break;
	case Complex::ParentesisA:
		imp = 1;
		break;
	}

	return imp;
}

bool ExisteMasDeUnOperador(Sintesis::ListaOperadores* lista) {
	Complex* ultimoOperador = nullptr;

	for (auto it = lista->begin(); it != lista->end(); it++) {
		if (!ultimoOperador)
			ultimoOperador = &(*it);
		else if (*ultimoOperador != *it)
			return true;
	}

	return false;
}

size_t ObtenerPosicionMayorPrecedencia(Sintesis::ListaOperadores* lista, Complex& operador) {
	size_t pos = 0;
	Sintesis::uchar precenciaAct = 255;
	size_t i = 0;
	for (auto it = lista->begin(); it != lista->end(); it++) {
		Sintesis::uchar prec = PrecedenciaComplex(*it);
		if (prec < precenciaAct) {
			pos = i;
			precenciaAct = prec;
			operador = *it;
		}
		i++;
	}

	return pos;
}

size_t EncontrarPosicionParentesisC(Sintesis::ListaOperadores& lista, size_t& posA, unsigned int& profundidad) {
	size_t sz = lista.size();
	profundidad = 0;
	unsigned int maxp = 0;
	for (size_t i = posA + 1; i < sz; i++) {
		if (lista[i] == Complex::ParentesisA) {
			profundidad++;
			maxp++;
		}
		else if (lista[i] == Complex::ParentesisC) {
			if (profundidad == 0) {
				profundidad = maxp;
				return i;
			}
			else profundidad--;
		}
	}
    
    return 0;
}

double CalcularValorLista(Sintesis::ListaOperadores& operadores, Sintesis::ListaOperandos& operandos) {
	/* Nota:
		para hacer esta funcion mas eficiente se podria verificar que exista mas de un operador,
		si es asi realizar el siguiente codigo, sino solo aplicar la operacion sobre sus elementos.	
	*/

	// ya que la gramatica se deriva por derecha los primeros son los ultimos por los que damos vuelta las listas.
	std::reverse(operadores.begin(), operadores.end());
	std::reverse(operandos.begin(), operandos.end());

	while (operadores.size() > 0) {
		Complex operador;
		size_t pos = ObtenerPosicionMayorPrecedencia(&operadores, operador);
		switch (operador) 
		{
			case Complex::Mas:
				operandos[pos] = operandos[pos] + operandos[pos + 1];
				break;
			case Complex::Menos:
				operandos[pos] = operandos[pos] - operandos[pos + 1];
				break;
			case Complex::Multiplicacion:
				operandos[pos] = operandos[pos] * operandos[pos + 1];
				break;
			case Complex::Division:
				operandos[pos] = operandos[pos] / operandos[pos + 1];
				break;
			case Complex::Potencia:
				operandos[pos] = pow(operandos[pos], operandos[pos + 1]);
				break;
		};

		if (operador == Complex::ParentesisA) {
			// {3,2,10} {(,+,),*}
			
			// Guardarmos la profundidad, que es la cantidad de parentesis que abren que se encontraron dentro
			// del actual.
			unsigned int profundidad = 0;
			size_t pos2 = EncontrarPosicionParentesisC(operadores, pos, profundidad);
			Sintesis::ListaOperadores operadores2(operadores.begin() + (pos + 1), operadores.begin() + pos2);
			
			// borramos hasta pos2 - (profundidad * 2) ya que cada par de parentesis que abre tiene su parentesis
			// que cierra, por lo que agrega 2 operandos.
			Sintesis::ListaOperandos operandos2(operandos.begin() + pos, operandos.begin() + (pos2 - profundidad * 2));

			double val = CalcularValorLista(operadores2, operandos2);

			operadores.erase(operadores.begin() + pos, operadores.begin() + (pos2 + 1));
			operandos[pos] = val;
			operandos.erase(operandos.begin() + (pos + 1), operandos.begin() + (pos2 - profundidad * 2));
		}
		else {
			operandos.erase(operandos.begin() + pos + 1);
			operadores.erase(operadores.begin() + pos);
		}
	}
	return operandos[0];
}
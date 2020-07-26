#include <iostream>		// para std -> std::cout << "hola " << numero
#include <fstream>		// para archivos
#include <vector> 		// std::vector
#include <map> 			// std::map
#include <algorithm> 	// std::find
#include "tipos.hpp"
#include "automatas.hpp"

#define ExisteEn(vector,encontrar) std::find(std::begin(vector), std::end(vector), encontrar) != std::end(vector)

using namespace AnalizadorLexico;

/// <summary>Template Automata verifica si a continuacion de control existe una cadena que pertenezca al componente lexico (automata) dado.
/// </summary>
/// <param name='fuente'>stream del archivo</param>
/// <param name='control'>posicion del cursor en el archivo (stream buffer)</param>
/// <param name='lexema'>secuencia de caracteres validos encontrados (si se encontraron, sino vacia)</param>
/// <param name='CarASimbolo'>funcion para clasificar un caracter hacia un simbolo del alfabeto</param>
/// <param name='delta'>funcion transicion del automata</param>
/// <param name='finales'>conjunto de todos los estados finales del automata</param>
/// <param name='estadoInicial'>estado inicial del automata</param>
/// <param name='estadoMuerto'>estado muerto del automata</param>
/// <returns>Devuelve un boolean dependiendo si se encontro el token buscado.</returns>
template <typename F>
bool TemplateAutomata(std::ifstream& fuente, ulong& control, std::string& lexema, 
					  F CarASimbolo, Delta delta, std::vector<ushort> finales,
					  ushort estadoInicial, ushort estadoMuerto) {

	ushort q0 = estadoInicial;
	bool esValida = false;

	/// == Buscamos por un identificador
	ushort estadoActual = q0;
	ushort ultimoEstado = q0;

	lexema = "";

	char c = '\0';

	fuente.get(c);

	// -- Verificamos que el estado en el cual estamos no sea invalido y no sea el fin del archivo
	while (estadoActual != estadoMuerto && !fuente.eof()) {
		int simb = CarASimbolo(c);
		estadoActual = delta[{estadoActual, simb}];

		// -- Si no esta en un estado muerto el caracter es valido, por lo que lo agregamos
		if (estadoActual != estadoMuerto) {
			lexema += c; 
			ultimoEstado = estadoActual;
		}

		fuente.get(c);
	}

	// -- Si llegamos al final del archivo limpiar el bit de EOF, asi poder utilizar seekg si es necesario
	if (fuente.eof()) fuente.clear();

	// -- La cadena obtenida es valida si el ultimo estado que fue valido antes de que fallara es estado final
	if (ExisteEn(finales, ultimoEstado)) {
		control += lexema.size();
		fuente.seekg(control); // Cambiamos la posicion del cursor a la anterior a la actual (la que fallo el automata)
		esValida = true;
	} else { // -- Sino movemos el cursor a donde estaba
		fuente.seekg(control);
	}

	return esValida;    
}

bool EsIdentificador(std::ifstream& fuente, ulong& control, std::string& lexema) {
	// -- Definimos el alfabeto de entrada
	enum Sigma { Letra, Digito, Especial, Otro };

    // -- Funcion que en base a un caracter devuelve un elemento del alfabeto
	auto CarASimbolo = [](auto& c) -> Sigma {
		Sigma t = Otro;

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			t = Letra;
		}
		else if (c >= '0' && c <= '9') {
			t = Digito;
		}
		else if (c == '_') {
			t = Especial;
		}

		return t;
	};
		
	Delta delta = {
		//		 q	 x	simbolo	 ->	q
			{	{0,		Letra	},	1},
			{	{0,		Digito	},	2},
			{	{0,		Especial},	2},
			{	{0,		Otro	},	2},

			{	{1,		Letra	},	1},
			{	{1,		Digito	},	1},
			{	{1,		Especial},	1},
			{	{1,		Otro	},	2},

			{	{2,		Letra	},	2},
			{	{2,		Digito	},	2},
			{	{2,		Especial},	2},
			{	{2,		Otro	},	2},
	};

	// -- Definimos los estados finales, el estado muerto y el inicial
	std::vector<ushort> finales = { 1 };
	const ushort estadoMuerto = 2 ;
	const ushort q0 = 0;	
	
	bool esIdentificador = TemplateAutomata(fuente, control, lexema, CarASimbolo, delta, finales, q0, estadoMuerto);

	return esIdentificador;
}

bool EsConstanteReal(std::ifstream& fuente, ulong& control, std::string& lexema) {
	// -- Definimos el alfabeto de entrada, especial = _
	enum Sigma {
		Digito, Signo, Punto, Exponente, Otro
	};

	auto CarASimbolo = [](auto& c) -> Sigma {
		Sigma t = Sigma::Otro;

		if (c == 'e' || c == 'E') {
			t = Sigma::Exponente;
		} else if (c >= '0' && c <= '9') {
			t = Sigma::Digito;
		} else if (c == '-') {
			t = Sigma::Signo;
		} else if (c == '.') {
			t = Sigma::Punto;
		}

		return t;
	};

	Delta delta = {
		//		 q	 x	simbolo		->	q
			{	{0,		Exponente	},	7},
			{	{0,		Digito		},	2},
			{	{0,		Signo		},	1},
			{	{0,		Punto		},	7},
			{	{0,		Otro		},	7},

			{	{1,		Exponente	},	7},
			{	{1,		Digito		},	2},
			{	{1,		Signo		},	7},
			{	{1,		Punto		},	7},
			{	{1,		Otro		},	7},

			{	{2,		Exponente	},	5},
			{	{2,		Digito		},	2},
			{	{2,		Signo		},	7},
			{	{2,		Punto		},	3},
			{	{2,		Otro		},	7},

			{	{3,		Exponente	},	5},
			{	{3,		Digito		},	4},
			{	{3,		Signo		},	7},
			{	{3,		Punto		},	7},
			{	{3,		Otro		},	7},

			{	{4,		Exponente	},	5},
			{	{4,		Digito		},	4},
			{	{4,		Signo		},	7},
			{	{4,		Punto		},	7},
			{	{4,		Otro		},	7},

			{	{5,		Exponente	},	7},
			{	{5,		Digito		},  8},
			{	{5,		Signo		},	6},
			{	{5,		Punto		},	7},
			{	{5,		Otro		},	7},

			{	{6,		Exponente	},	7},
			{	{6,		Digito		},	8},
			{	{6,		Signo		},	7},
			{	{6,		Punto		},	7},
			{	{6,		Otro		},	7},

			{	{7,		Exponente	},	7},
			{	{7,		Digito		},	7},
			{	{7,		Signo		},	7},
			{	{7,		Punto		},	7},
			{	{7,		Otro		},	7},

			{	{8,		Exponente	},	7},
			{	{8,		Digito		},	8},
			{	{8,		Signo		},	7},
			{	{8,		Punto		},	7},
			{	{8,		Otro		},	7},
	};

	// -- Definimos los estados finales, el estado muerto y el inicial
	std::vector<ushort> finales = { 3,4,8 };
	const ushort estadoMuerto = 7;
	const ushort q0 = 0;
	bool esConstReal = TemplateAutomata(fuente, control, lexema, CarASimbolo, delta, finales, q0, estadoMuerto);

	return esConstReal;
}

bool EsConstanteEntera(std::ifstream& fuente, ulong& control, std::string& lexema) {
	// -- Definimos el alfabeto de entrada, especial = _
	enum Sigma {
		Digito, Signo, Otro
	};

	auto CarASimbolo = [](char& c) -> Sigma {
		Sigma t = Sigma::Otro;

		if (c == '-') {
			t = Sigma::Signo;
		} else if (c >= '0' && c <= '9') {
			t = Sigma::Digito;
		}

		return t;
	};

	Delta delta = {
		//		 q	 x	simbolo	 ->	q
			{	{0,		Signo	},	1},
			{	{0,		Digito	},	2},
			{	{0,		Otro	},	3},

			{	{1,		Signo	},	3},
			{	{1,		Digito	},	2},
			{	{1,		Otro	},	3},

			{	{2,		Signo	},	3},
			{	{2,		Digito	},	2},
			{	{2,		Otro	},	3},

			{	{3,		Signo	},	3},
			{	{3,		Digito	},	3},
			{	{3,		Otro	},	3},
	};
		
	// -- Definimos los estados finales, el estado muerto y el inicial
	std::vector<ushort> finales = { 2 };
	const ushort estadoMuerto = 3;
	ushort q0 = 0;	
	
	bool esConstEntera = TemplateAutomata(fuente, control, lexema, CarASimbolo, delta, finales, q0, estadoMuerto);

	return esConstEntera;
}

bool EsOperadorRelacional(std::ifstream& fuente, ulong& control, std::string& lexema) {
	// -- Definimos el alfabeto de entrada
	enum Sigma {
		Mayor, Menor, Igual, Otro
	};

	auto CarASimbolo = [](char& c) -> Sigma {
		Sigma t = Sigma::Otro;

		if (c == '>') {
			t = Sigma::Mayor;
		} else if (c == '<') {
			t = Sigma::Menor;
		} else if (c == '=') {
			t = Sigma::Igual;
		}

		return t;
	};

	Delta delta = {
		//		 q	 x	simbolo	 ->	q
			{	{0,		Menor	},	1},
			{	{0,		Mayor	},	4},
			{	{0,		Igual	},	3},
			{	{0,		Otro	},	5},

			{	{1,		Menor	},	5},
			{	{1,		Mayor	},	2},
			{	{1,		Igual	},	2},
			{	{1,		Otro	},	5},

			{	{2,		Menor	},	5},
			{	{2,		Mayor	},	5},
			{	{2,		Igual	},	5},
			{	{2,		Otro	},	5},

			{	{3,		Menor	},	5},
			{	{3,		Mayor	},	5},
			{	{3,		Igual	},	2},
			{	{3,		Otro	},	5},

			{	{4,		Menor	},	5},
			{	{4,		Mayor	},	5},
			{	{4,		Igual	},	2},
			{	{4,		Otro	},	5},

			{	{5,		Menor	},	5},
			{	{5,		Mayor	},	5},
			{	{5,		Igual	},	5},
			{	{5,		Otro	},	5}
	};

	// -- Definimos los estados finales, el estado muerto y el inicial
	std::vector<ushort> finales = { 1, 4, 2 };
	const ushort estadoMuerto = 5;
	ushort q0 = 0;

	bool esOperadorRelacional = TemplateAutomata(fuente, control, lexema, CarASimbolo, delta, finales, q0, estadoMuerto);

	return esOperadorRelacional;
}

bool EsCadena(std::ifstream& fuente, ulong& control, std::string& lexema){
	// -- Definimos el alfabeto de entrada
	enum Sigma {
		Comilla, Car, Otro
	};

	auto CarASimbolo = [](char& c) -> Sigma {
		Sigma t = Sigma::Otro;

		if (c == '"') {
			t = Sigma::Comilla;
		} else if (c >= 32) {
			t = Sigma::Car;
		}

		return t;
	};

	Delta delta = {
		//		 q	 x	simbolo	 ->	q
			{	{0,		Comilla	},	1},
			{	{0,		Car		},	3},
			{	{0,		Otro	},	3},

			{	{1,		Comilla	},	2},
			{	{1,		Car		},	1},
			{	{1,		Otro	},	3},

			{	{2,		Comilla	},	3},
			{	{2,		Car		},	3},
			{	{2,		Otro	},	3},

			{	{3,		Comilla	},	3},
			{	{3,		Car		},	3},
			{	{3,		Otro	},	3}
	};

	// -- Definimos los estados finales, el estado muerto y el inicial
	std::vector<ushort> finales = { 2 };
	const ushort estadoMuerto = 3;
	ushort q0 = 0;

	bool esCadena = TemplateAutomata(fuente, control, lexema, CarASimbolo, delta, finales, q0, estadoMuerto);

	return esCadena;
}

bool EsSimboloEspecial(std::ifstream& fuente, ulong& control, std::string& lexema, ComponenteLexico& complex) {
	char c = '\0';
	bool esSimbolo = true;
	fuente.get(c);
	ComponenteLexico cl = ComponenteLexico::ErrorLexico;
		
	switch (c) {
		case '(':
			cl = ComponenteLexico::ParentesisA;
			break;
		case ')':
			cl = ComponenteLexico::ParentesisC;
			break;
		case '=':
			cl = ComponenteLexico::Igual;
			break;
		case '+':
			cl = ComponenteLexico::Mas;
			break;
		case '-':
			cl = ComponenteLexico::Menos;
			break;
		case '/':
			cl = ComponenteLexico::Division;
			break;
		case '*':
			cl = ComponenteLexico::Multiplicacion;
			break;
		case '^':
			cl = ComponenteLexico::Potencia;
			break;
		case ',':
			cl = ComponenteLexico::Coma;
			break;
		case '{':	
			cl = ComponenteLexico::LlavesA;
			break;
		case '}':
			cl = ComponenteLexico::LlavesC;
			break;
		case '[':
			cl = ComponenteLexico::CorcheteA;
			break;
		case ']':
			cl = ComponenteLexico::CorcheteC;
			break;
		default:
			esSimbolo = false;
			break;
	}

	if (!esSimbolo)
		fuente.seekg(control); //// Si no es simbolo, volver el cursor a la pos de la cual obtuvimos el caracter
	else{
		lexema = c;
		complex = cl;
	}
	return esSimbolo;
}
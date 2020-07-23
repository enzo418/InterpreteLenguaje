#include "utiles.hpp"
#include "../AnalizadorLexico/tipos.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

/*
bool ExisteMasDeUnOperador(Sintesis::ListaOperadorDoble* lista){
	Complex* ultimoOperador = nullptr;

	// empezamos desde la posicion 1 y vamos mirando de a 2 elementos... {n, op,..., n}
	for (auto it = lista->begin()+1; it < lista->end(); std::advance(it, 2)) {
		// si el elemento es un operador
		if(*it->operador){
			// si todavia no se encontro un operador
			if(!ultimoOperador)
				ultimoOperador = it->operador;
			else if(*ultimoOperador != *it->operador)
				return true;			
		}

	}

	return false;
}*/
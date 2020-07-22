#pragma once
#include <iostream>

#include "tipos.hpp"
#include "../AnalizadorLexico/tipos.hpp"

using Complex=AnalizadorLexico::ComponenteLexico;

bool ExisteMasDeUnOperador(Sintesis::ListaOperadorDoble* lista);
#pragma once

#include "tipos.hpp"

bool ObtenerSiguienteComplex(std::ifstream& fuente, ulong& control, AnalizadorLexico::ComponenteLexico& complex, std::string& lexema, AnalizadorLexico::TablaSimbolos& ts);
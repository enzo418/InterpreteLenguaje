#pragma once

#include "tipos.hpp"

bool ObtenerSiguienteComplex(std::istream& fuente, ulong& control,
                             AnalizadorLexico::ComponenteLexico& complex,
                             std::string& lexema,
                             AnalizadorLexico::TablaSimbolos& ts);
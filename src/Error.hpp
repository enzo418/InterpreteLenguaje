#pragma once

#include <string>

class Error {
   public:
    Error() : linea(-1), columna(-1), longitud(-1), mensaje("") {}
    Error(int linea, int columna, int longitud, std::string mensaje)
        : linea(linea),
          columna(columna),
          longitud(longitud),
          mensaje(mensaje) {}

   public:
    int linea;
    int columna;
    int longitud;
    std::string mensaje;
};

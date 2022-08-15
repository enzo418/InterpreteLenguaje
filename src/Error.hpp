#pragma once

#include <string>

// No tiene lineainicio-fin ya que las cadenas no pueden tener caracteres < 32
// ascii, por lo tanto no pueden tener \n. Si se aceptara este caracter seria
// necesario modoficarlo.
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

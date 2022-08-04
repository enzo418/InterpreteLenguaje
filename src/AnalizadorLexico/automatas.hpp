#pragma once

#include <fstream>
#include <istream>
#include <map>
#include <vector>

#include "../tipos.hpp"
#include "tipos.hpp"

template <typename F>
bool TemplateAutomata(std::istream& fuente, ulong& control, std::string& lexema,
                      F CarASimbolo, AnalizadorLexico::Delta delta,
                      std::vector<ushort> finales, ushort estadoInicial,
                      ushort estadoMuerto);

bool EsIdentificador(std::istream& fuente, ulong& control, std::string& lexema);
bool EsConstanteReal(std::istream& fuente, ulong& control, std::string& lexema);
bool EsConstanteEntera(std::istream& fuente, ulong& control,
                       std::string& lexema);
bool EsOperadorRelacional(std::istream& fuente, ulong& control,
                          std::string& lexema);
bool EsSimboloEspecial(std::istream& fuente, ulong& control,
                       std::string& lexema,
                       AnalizadorLexico::ComponenteLexico& complex);
bool EsCadena(std::istream& fuente, ulong& control, std::string& lexema);
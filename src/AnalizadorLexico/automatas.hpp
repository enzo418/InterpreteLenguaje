#pragma once

#include <fstream>
#include <vector>
#include <map>
#include "../tipos.hpp"
#include "tipos.hpp"

template <typename F>
bool TemplateAutomata(std::ifstream& fuente, ulong& control, std::string& lexema,
                    F CarASimbolo, AnalizadorLexico::Delta delta, 
                    std::vector<ushort> finales, ushort estadoInicial, ushort estadoMuerto);

bool EsIdentificador(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsConstanteReal(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsConstanteEntera(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsOperadorRelacional(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsSimboloEspecial(std::ifstream& fuente, ulong& control, std::string& lexema, AnalizadorLexico::ComponenteLexico& complex);
bool EsCadena(std::ifstream& fuente, ulong& control, std::string& lexema);
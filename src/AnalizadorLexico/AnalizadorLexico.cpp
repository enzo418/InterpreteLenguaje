#include "AnalizadorLexico.hpp"
#include "automatas.hpp"
#include "utiles.hpp"

using namespace AnalizadorLexico;

bool ObtenerSiguienteComplex(std::ifstream& fuente, ulong& control, ComponenteLexico& complex, std::string& lexema, TablaSimbolos& ts){
    /** funcion  |  Utilidad
     * 
     *  peek()      Devuelve el caracter sobre el cual esta el cursor del archivo, sin removerlo del buffer.
     *  get()       Obtiene y devuelve el caracter sobre el cual esta el cursor del archivo.
     *  eof()       Verifica si es el final del archivo
     *  tellg()     Devuelve la posicion actual del puntero|control|cursor archivo.
    */        

    // -- Quitar los caracteres no necesarios	
	while (fuente.peek() <= 32 && !fuente.eof()) {
		fuente.get();
		control++;
	}
	 
	// Si se termino el archivo
	if (fuente.eof()){
		lexema = "$";
		complex = ComponenteLexico::FDA;
		return false;
	}

    // obtener posicion actual del control
	control = fuente.tellg();
	
	if (EsIdentificador(fuente, control, lexema)) {
		complex = ComponenteLexico::Id;
		
		if(!ExisteEnTS(ts, lexema, complex)){			
			AgregarEnTablaSimbolos(lexema, complex, ts);
		}
	} else if (EsConstanteReal(fuente, control, lexema)) {
		complex = ComponenteLexico::Constante;
	} else if (EsConstanteEntera(fuente, control, lexema)) {
		complex = ComponenteLexico::Constante;
	} else if (EsOperadorRelacional(fuente, control, lexema)) {
		complex = ComponenteLexico::OpRel;
	} else if (EsCadena(fuente, control, lexema)){
		complex = ComponenteLexico::Cadena;
	} else if (!EsSimboloEspecial(fuente, control, lexema, complex)) {
		complex = ComponenteLexico::ErrorLexico;
		lexema = "";
	}

	return true;
}
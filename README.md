# Que es?
Es in interprete de un lenguaje de programación que los integrantes llamamos "Factorial". Hay un solo tipo de dato, digitos. Aunque permita imprimir cadenas, estas no pueden ser asignadas a variables.

# Emscripten
Esta rama contiene el codigo necesario para poder ejectuar el interprete en la web. Esto se realizó y se puede probar en mi página persona.

Se puede mejorar el perfomance moviendo las llamadas a `val` de emscripten en ciertas funciones pero el punto de esto era probar que era posible llevar el interprete a la web sin muchos cambios.

## Build con Emscripten
1. Instalar [emscripten](https://emscripten.org/docs/getting_started/downloads.html)
	- Asegurarse de ejecutar el `source ./emsdk_env.sh` para tener los ejecutables.
2. Configurar y ejecutar make:
	- `mkdir build-em && cd build-em`
	- `emcmake cmake .. -D USE_EMSCRIPTEN=ON && emmake make -j4`
3. En ese directorio `build-em` se generaron dos archivos, `Interprete.js` y `Interprete.wasm`, el .js se encarga de cargar el .wasm y proporciona utilidades para efectuar la comunicacion con el assembly. Ya que estamos utilizando el interprete como una libreria, es importante evitar que se llame a main. Esto es porque emscripten detiene el runtime si se tira una excepcion o se llama a `exit`.
4. Es importante que el global de donde se este ejectutando el interprete tenga una propieda `interprete` que implemente los siguientes metodos y funciones que se llaman desde c++ compilado:
	- `writeMessageReadValue(cadena) -> Promise<double>`: Funcion que toma una cadena y devuelve un promise de doble. Deberia escribir una cadena en la terminal, lee un valor del usuario en respuesta a esa cadena y resuelve la promesa.
	- `writeMessage(cadena) -> void`: Metodo que toma una cadena. Deberia escribir un mensaje en la terminal.
	- `setSyntaxTree(cadena) -> void`: Metodo que toma una cadena. Desde c++ se llama a esta funcion que puede procesarla para obtener los nodos y aristas del arbol para luego representarlo de forma gráfica, mostrar errores o demas.
	- `addErrorMarker(linea, columna, longitud, mensaje) -> void`: Metodo que toma 3 enteros y una cadena. Cuando ocurre un error, ya sea en la etapa del analizador sintactico o runtime, se llama a esta funcion donde se detalla en que parte del input se produjo.
5. Ejecutando el interprete
	- Una vez que se cargo el assembly se puede llamar al interprete con, por ejemplo `globalThis.Module.Interprete.Interpretar(cadena)`. Esta llamada puede devolver un Promise si se ejecuta codigo de forma asincronica, como por ejemplo cuando se llama a `writeMessageReadValue` desde c++. Si esto no sucede la llamada devuelve un codigo o nada.
	- Dado que desde el inteprete si ocurre un error hacemos lanzamos un error, es necesario envolver la llamada anterior en un try-catch y al promise agregarle un catch. Se lanza una excepcion ya que si ocurre un error en runtime, al ser llamadas recursivas, no tenemos otra condicion de salida mas que se acabe de recorrer el arbol.

# Como usarlo?
1. Ir a [releases](https://github.com/enzo418/InterpreteLenguaje/releases) y descargarlo.
2. Escribir el codigo que debe interpretar en un archivo, para indicarle cual es el archivo se puede hacer de 2 formas:
 	- El interprete por defecto trata de leer un archivo "entrada.txt" en el mismo directorio que esta el ejecutable,
 	- o pasarle como argumento el archivo, ejemplo "./Interprete archivo.txt"
	
Este programa también reconoce un argumento opcional que se utiliza para obtener más información por la consola sobre lo que va realizando en la Fase de Análisis, ese argumento es -volcar. Ejemplo, ./Interprete.exe -volcar

# Ejemplos de programas en este lenguaje
A continuación algunos ejemplos para mostrar la sintaxis, en el siguiente título se detallan.

## Calcular el n-ésimo número de la sucesión de Fibonacci.
	var n, actual, ant1, ant2, i
	{
		n = 1200
		ant1 = 1
		ant2 = 1		
		
		si (n == 0 or n == 1) {
			actual = 1
		} sino {
			i = 2
			mientras(i <= n){
				actual = ant1 + ant2
				ant2 = ant1
				ant1 = actual

				i = i + 1
			}
		}

		escribir("Resultado: ", actual)
	}

## Calcular el mínimo común múltiplo entre dos números
	var n1, n2, ultimoDividendo, aux, resto, mcd, mcm
	{
		leer("Ingrese el primer numero: ", n1)
		leer("Ingrese el segundo numero: ", n2)

		resto = n1 % n2

		ultimoDividendo = n2

		mientras(resto <> 0){	
			aux = resto	

			resto = ultimoDividendo % resto

			ultimoDividendo = aux
		}

		mcd = ultimoDividendo

		mcm = (n1 * n2) / mcd

		escribir("MCM: ", mcm)
	}
# Definición formal de la sintaxis mediante una gramática en [notación Backus-Naur (BN)](https://es.wikipedia.org/wiki/Notaci%C3%B3n_de_Backus-Naur#Introducci%C3%B3n).
	<Programa> 	:== “var” <Variables> “{“ <Cuerpo> “}”
	<Variables> 	:== “id” <IdVar>
	<IdVar> 	:== “,” “id” <IdVar> | epsilon
	<Cuerpo>	:== <Sent> <Cuerpo> | epsilon
	<Sent>	:== “id”  “=” <OpAritmeticas>
		| “leer” “(“ “cadena” “,” “id” “)” | “escribir” “(“ “cadena” “,” <OpAritmeticas> “)”
		| “mientras” “(“ <Condiciones> “)” “{“ <Cuerpo> “}” | “si” “(“ <Condiciones> “)” “{“ <Cuerpo> “}” <Sino>
	<Condiciones> :== <Cond2> “or” <Condiciones> | <Cond2>
	<Cond2>  	:== <Cond3> “and” <Cond2> | <Cond3>
	<Cond3> 	:== “not” <Cond3> | “[“ <Condiciones> “]”  | <OpAritmeticas> “opRel” <OpAritmeticas>
	<Sino>	:== “sino” “{“ <Cuerpo> “}” | epsilon	
	<OpAritmeticas> :== <OpAritmeticas> “+” <T> | <OpAritmeticas>  “-” <T> | <T>
	<T> 		:== <T>  “*” <F> | <T>  “/” <F> |<F>
	<F> 		:== <F>  “^” <R> | “rcd” “(“ <OpAritmeticas> “)” | <R> | <F> “%” <R>
	<R> 		:== “id” | “constante” | “(“ <OpAritmeticas> “)” | “-” <R>


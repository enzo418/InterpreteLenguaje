# Que es?
Es in interprete de un lenguaje de programación que los integrantes llamamos "Factorial".

# Como usarlo?
1. Ir a [releases](https://github.com/enzo418/InterpreteLenguaje/releases) y descargarlo.
2. Escribir el codigo que debe interpretar en un archivo, para indicarle cual es el archivo se puede hacer de 2 formas:
 	- El interprete por defecto trata de leer un archivo "entrada.txt" en el mismo directorio que esta el ejecutable,
 	- o pasarle la flag -fuente seguido del nombre del arhivo 
	
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


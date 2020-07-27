# Ejemplos de programas en este lenguaje

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



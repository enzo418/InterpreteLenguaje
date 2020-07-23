## Errores conocidos pendien a arreglar:
- Cuando se reliza una Operacion Aritmetica que contiene un operador + o - seguido sin espacio de un numero, el analizador lexico lo toma como un real y produce un fallo en el analisador sintactico.

		Ej: i = j+5 fallaría
	**Solución:** Darle el contexto al analizador lexico, si es una asignacion o estamos calculando una operacion aritmetica.
/*5213903*/

#include "../include/info.h"
#include "../include/avl.h"
#include "../include/conjunto.h"
#include "../include/iterador.h"
#include <stddef.h>
struct repConjunto {
	TAvl arbol;
};

typedef struct repConjunto *TConjunto;

/*
  Devuelve un 'TConjunto' vacío (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TConjunto crearConjunto(){
	TConjunto nuevo = new repConjunto();
	nuevo->arbol = crearAvl();
	return nuevo;
}

/*
  Devuelve un 'TConjunto' cuyo único elemento es 'elem'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TConjunto singleton(nat elem){
	TConjunto larespu = crearConjunto();
	larespu->arbol = crearAvl();
	insertarEnAvl(elem, larespu->arbol);
	return larespu;
}


/*
  Devuelve un 'TConjunto' con los elementos que pertenecen a 'c1' o 'c2'.
  El 'TConjunto' resultado no comparte memoria ni con 'c1' no con 'c2'.
  El tiempo de ejecucion en el peor caso es O(n),
  siendo  'n' la cantidad de elementos del 'TConjunto' resultado.
 */
TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
	TConjunto solucion = crearConjunto();
	TIterador iterac1 = iteradorDeConjunto(c1);
	TIterador iterac2 = iteradorDeConjunto(c2);
	reiniciarIterador(iterac1);
	reiniciarIterador(iterac2);	
	if (estaVacioConjunto(c1)){
		while (estaDefinidaActual(iterac2)){	
		insertarEnAvl(actualEnIterador(iterac2), solucion->arbol);
		avanzarIterador(iterac2);
		}	
	}
	else if (estaVacioConjunto(c2)){
		while (estaDefinidaActual(iterac1)){	
		insertarEnAvl(actualEnIterador(iterac1), solucion->arbol);
		avanzarIterador(iterac1);
		}	
	}
	else{	
		
	while ((estaDefinidaActual(iterac1)) && (estaDefinidaActual(iterac2))){
			if (actualEnIterador(iterac1)<actualEnIterador(iterac2)){
				insertarEnAvl(actualEnIterador(iterac1), solucion->arbol);	
				avanzarIterador(iterac1);
			}
			else {
				if (actualEnIterador(iterac1)>actualEnIterador(iterac2)){
	
				insertarEnAvl(actualEnIterador(iterac2), solucion->arbol);
				avanzarIterador(iterac2);
			     } else	if (actualEnIterador(iterac1)==actualEnIterador(iterac2)){
				
				insertarEnAvl(actualEnIterador(iterac1), solucion->arbol);
				avanzarIterador(iterac2);
				avanzarIterador(iterac1);
				}
			}
		}
	while (estaDefinidaActual(iterac1)){
			
		insertarEnAvl(actualEnIterador(iterac1), solucion->arbol);
		avanzarIterador(iterac1);
	}	
	
	while (estaDefinidaActual(iterac2)){
			
		insertarEnAvl(actualEnIterador(iterac2), solucion->arbol);
		avanzarIterador(iterac2);
	}	
}
	liberarIterador(iterac1);
	liberarIterador(iterac2);
	return solucion;
}

/*
  Devuelve un 'TConjunto' con los elementos de 'c1' que no pertenecen a 'c2'.
  El 'TConjunto' resultado no comparte memoria ni con 'c1' no con 'c2'.
  El tiempo de ejecucion en el peor caso es O(n1 + n2),
  siendo 'n1' y 'n2' la cantidad de elementos de 'c1' y 'c2' respectivamente y
  'n' la del 'TConjunto' resultado.
 */
TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
	TConjunto solucion = crearConjunto();
	TIterador iterac1 = iteradorDeConjunto(c1);
	TIterador iterac2 = iteradorDeConjunto(c2);
	reiniciarIterador(iterac1);
	reiniciarIterador(iterac2);
	nat agregar;

	if (estaVacioConjunto(c1)){
	}
	else if (estaVacioConjunto(c2)){
		while (estaDefinidaActual(iterac1)){	
		agregar = actualEnIterador(iterac1);
		insertarEnAvl(agregar, solucion->arbol);
		avanzarIterador(iterac1);
		}	
	}
	else{	
		
	while ((estaDefinidaActual(iterac1)) && (estaDefinidaActual(iterac2))){
			if (actualEnIterador(iterac1)<actualEnIterador(iterac2)){
				agregar = actualEnIterador(iterac1);
				insertarEnAvl(agregar, solucion->arbol);	
				avanzarIterador(iterac1);
			}
			else {
				if (actualEnIterador(iterac1)>actualEnIterador(iterac2)){
				avanzarIterador(iterac2);
			     } else	if (actualEnIterador(iterac1)==actualEnIterador(iterac2)){
				avanzarIterador(iterac2);
				avanzarIterador(iterac1);
				}
			}
		}
	while (estaDefinidaActual(iterac1)){	
		agregar =actualEnIterador(iterac1);
		insertarEnAvl(agregar, solucion->arbol);
		avanzarIterador(iterac1);
	}	
	
}
	liberarIterador(iterac1);
	liberarIterador(iterac2);
	return solucion;
}
/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'c'.
  El tiempo de ejecución en el peor caso es O(log n), siendo 'n' la cantidad de
  elementos de 'c'.
 */
 
 //realinfo cuidado puede ser natInfo
bool perteneceAConjunto(nat elem, TConjunto c){
	bool esta = false;
	if (c != NULL){
		TAvl contiene = buscarEnAvl(elem, c->arbol);
		if (contiene != NULL)
			esta = elem == raizAvl(contiene);
	}
	return esta;
}

/*
  Devuelve 'true' si y solo si 'c' es vacío (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVacioConjunto(TConjunto c){
	return (c->arbol == NULL);
}

/*
  Devuelve la cantidad de elementos de 'c'.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cardinalidad(TConjunto c){
 //Implementar
 return 1;
}

/*
  Devuelve un 'TConjunto' con los 'n' elementos que están en en el rango
  [0 .. n - 1] del arreglo 'elems'.
  Precondiciones:
  - n > 0
  - Los elementos están ordenados de manera creciente estricto
  (creciente y sin repetidos).
  El tiempo de ejecución en el peor caso es O(n).
 */
TConjunto arregloAConjunto(nat *elems, nat n){
	TConjunto res = crearConjunto();
	res->arbol = arregloAAvl(elems, n);
	return res;
}

/*
  Devuelve un 'TIterador' de los elementos de 'c'.
  En la recorrida del iterador devuelto los elementos aparecerán en orden
  creciente.
  El 'TIterador' resultado no comparte memoria con 'c'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'c'.
 */
TIterador iteradorDeConjunto(TConjunto c){
	
	TIterador infos = enOrdenAvl(c->arbol);
	
	return infos;
}


/*
  Libera la memoria asignada a 'c' y la de todos sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'c'.
 */
void liberarConjunto(TConjunto c){
	liberarAvl(c->arbol);
	delete(c);
}
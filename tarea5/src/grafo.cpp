/*
  Módulo de definición de 'TGrafo'.

  Los elementos de tipo 'TGrafo' son grafos cuya cantidad de nodos se determina
  con un parámetro, N, y se identifican con naturales desde 1 hasta N.
  La cantidad de aristas está acotada por un parámetro, M, y tienen costo de
  tipo double.
  Los valores N y M son parámetros pasados al crear el grafo.
  El espacio ocupado para representar un grafo debe ser O(N + M).

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
 
 #include "../include/grafo.h"
#include "../include/utils.h"
#include "../include/info.h"
#include <stdio.h>  
#include "../include/pila.h"
#include "../include/colaAvls.h"
#include "../include/iterador.h"
#include "limits.h"



struct repGrafo{
	nat N;
	nat M;
};
/*
  Devuelve un 'TGrafo' con 'N' vértices identificados desde 1 hasta 'N'
  sin parejas de vecinos establecidos.
  Podŕa haber hasta 'M' parejas de vecinos.
  El tiempo de ejecución en peor caso es O(max{N,M}).
 */
TGrafo crearGrafo(nat N, nat M){
	TGrafo res=new repGrafo;
	return res;
}

/*
  Devuelve la cantidad de vértices de 'g'.
  El tiempo de ejecución en peor caso es O(1).
 */
nat cantidadVertices(TGrafo g){
	return 1;
}

/*
  Devuelve 'true' si y solo si en 'g' ya hay M parejas de vecinos,
  siendo M el segundo parámetro pasado en crearGrafo.
  El tiempo de ejecución en peor caso es O(1).
 */
bool hayMParejas(TGrafo g){
	return false;
}	
/*
  Establece que 'v1' y 'v2' son vecinos en 'g' y la distancia entre ambos es
  'd'.
  Precondición: 1 <= v1, v2 <= N.
  Precondición: v1 != v2
  Precondición: !sonVecinos(v1, v2, g).
  Precondición: !hayMParejas(g).
  Precondición: d >= 0.
  Devuelve 'g'.
  El tiempo de ejecución es en peor caso O(max{log n1, log n2}), siendo 'n1' y
  'n2' la cantidad de vecinos de 'v1' y 'v2' respectivamente.
 */
TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
	return g;
}
/*
  Devuelve 'true' si y solo si 'v1' y 'v2' son vecinos.
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */
bool sonVecinos(nat v1, nat v2, TGrafo g){
	return true;
}
/*
  Devuelve la distancia entre 'v1' y 'v2'.
  Precondición: sonVecinos(v1, v2, g).
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */
double distancia(nat v1, nat v2, TGrafo g){
	return 1.2;
}
/*
  Devuelve un 'TIterador' con los vecinos de 'v' ordenados de manera creciente.
  Precondición: 1 <= v <= N.
  El tiempo de ejecución en peor caso es O(n), siendo 'n' la cantidad de
  vecinos de 'v'.
 */
TIterador vecinos(nat v, TGrafo g){
	TIterador res=NULL;
	return res;
}
/*
  Libera la memoria asignada a 'g'.
  El tiempo de ejecuión en el peor caso en O(N*N + M), siende 'N' y 'M' los
  parámetros pasados en crearGrafo.
 */
void liberarGrafo(TGrafo g){
}

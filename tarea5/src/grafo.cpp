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
#include "../include/avl.h"
#include "../include/iterador.h"
#include "limits.h"
#include "../include/mapping.h"



struct repGrafo{
	nat M;
	nat N;
	//nat cantVertices;
	TMapping aristas;
	//bool *vertices;
	TAvl *vecinos;
};
/*
  Devuelve un 'TGrafo' con 'N' vértices identificados desde 1 hasta 'N'
  sin parejas de vecinos establecidos.
  Podŕa haber hasta 'M' parejas de vecinos.
  El tiempo de ejecución en peor caso es O(max{N,M}).
 */
TGrafo crearGrafo(nat N, nat M){
	TGrafo res=new repGrafo;
	res->aristas=crearMap(M);
	res->vecinos=new TAvl[M];
	for (nat iterador = 0; iterador < M; iterador++) {
        res->vecinos[iterador]= crearAvl();    
    }
    //res->vertices=new bool[N];
    //res->cantVertices=0;
    res->N=N;
    res->M=M;
	return res;
}

/*
  Devuelve la cantidad de vértices de 'g'.
  El tiempo de ejecución en peor caso es O(1).
 */
nat cantidadVertices(TGrafo g){
	return g->N;
}

/*
  Devuelve 'true' si y solo si en 'g' ya hay M parejas de vecinos,
  siendo M el segundo parámetro pasado en crearGrafo.
  El tiempo de ejecución en peor caso es O(1).
 */
bool hayMParejas(TGrafo g){
	return estaLlenoMap(g->aristas);
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
 static nat max(nat v1, nat v2){
	 return v1>v2? v1: v2;
 }
 
 static nat min(nat v1, nat v2){
	 return v2>v1? v1: v2;
 }
 
 
TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
	nat clave= (min(v1,v2)-1)*g->N+(max(v1,v2)-1);
    g->aristas=asociarEnMap(clave,d,g->aristas);
    g->vecinos[v1]=insertarEnAvl(v2,g->vecinos[v1]);
    g->vecinos[v2]=insertarEnAvl(v1,g->vecinos[v2]);
	return g;
}
/*
  Devuelve 'true' si y solo si 'v1' y 'v2' son vecinos.
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */
bool sonVecinos(nat v1, nat v2, TGrafo g){
	return existeAsociacionEnMap((min(v1,v2)-1)*g->N+(max(v1,v2)-1),g->aristas);
}
/*
  Devuelve la distancia entre 'v1' y 'v2'.
  Precondición: sonVecinos(v1, v2, g).
  Precondición: 1 <= v1, v2 <= N.
  El tiempo de ejecución es O(1) en promedio.
 */
double distancia(nat v1, nat v2, TGrafo g){
	return valorEnMap((min(v1,v2)-1)*g->N+(max(v1,v2)-1),g->aristas);
}
/*
  Devuelve un 'TIterador' con los vecinos de 'v' ordenados de manera creciente.
  Precondición: 1 <= v <= N.
  El tiempo de ejecución en peor caso es O(n), siendo 'n' la cantidad de
  vecinos de 'v'.
 */
TIterador vecinos(nat v, TGrafo g){
	return reiniciarIterador(enOrdenAvl(g->vecinos[v]));
}
/*
  Libera la memoria asignada a 'g'.
  El tiempo de ejecuión en el peor caso en O(N*N + M), siendo 'N' y 'M' los
  parámetros pasados en crearGrafo.
 */
void liberarGrafo(TGrafo g){
	for (nat iterador = 0; iterador < g->M; iterador++) {
        liberarAvl(g->vecinos[iterador]);    
    }
    liberarMap(g->aristas);
    delete[] g->vecinos;
    //delete[] g->vertices;
  
    delete g;
}

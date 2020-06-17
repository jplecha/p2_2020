//52139037
#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/info.h"
#include <stdio.h>  
#include "../include/pila.h"
#include "../include/colaAvls.h"
#include "../include/iterador.h"
#include "limits.h"

struct Nodo{
	TAvl arbol;
	Nodo *sig;
	Nodo *ant;
};

struct repColaAvls {
	Nodo *primero, *ultimo;
};
/*
  Devuelve una 'TColaAvls' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls crearColaAvls(){
	TColaAvls newElemento = new repColaAvls;
	newElemento->primero = newElemento->ultimo = NULL;
	return newElemento;
}

/*
  Encola 'avl' en 'c'.
  Devuelve 'c'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls encolar(TAvl avl, TColaAvls c){
	if (!estaVacioAvl(avl)) {
		
		Nodo *agregar = new Nodo;
		agregar->arbol = avl;
		agregar->ant = NULL;
		agregar->sig = c->primero;
		if (c->primero != NULL) c->primero->ant = agregar;
		else c->ultimo = agregar;
		c->primero = agregar;	
	}
	else{
		Nodo *agregar = new Nodo;
		agregar->arbol = NULL;
		agregar->ant = NULL;
		agregar->sig = c->primero;
		if (c->primero != NULL) c->primero->ant = agregar;
		else c->ultimo = agregar;
		c->primero = agregar;
	}
	return c;
}

/*
  Remueve de 'c' el elemento que está en el frente.
  Si estaVaciaColaAvls(c) no hace nada.
  Devuelve 'c'.
  NO libera la memoria del elemento removido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaAvls desencolar(TColaAvls c){
	if(c->ultimo != NULL){
		Nodo *borrar = c->ultimo;
		c->ultimo = c->ultimo->ant;
		if (c->ultimo != NULL) c->ultimo->sig = NULL;
		else
		c->primero = NULL;
		delete borrar;
	}
	return c;
}

/*
  Libera la memoria asignada a 'c', pero NO la de sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'c'.
 */
void liberarColaAvls(TColaAvls c){
	c->primero = NULL;
	Nodo *borrador = c->ultimo;
	while (borrador != NULL){
		c->ultimo = c->ultimo->ant;
		delete borrador;
		borrador = c->ultimo;
	}
	delete c;
}

/*
  Devuelve 'true' si y solo si 'c' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVaciaColaAvls(TColaAvls c){
	return (c->primero == NULL && c->ultimo == NULL);
}

/*
  Devuelve el elemento que está en el frente de 'c'.
  Precondición: ! estaVaciaColaAvls(c);
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl frente(TColaAvls c){
	return c->ultimo->arbol;
}

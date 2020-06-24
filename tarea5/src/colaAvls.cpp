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

TColaAvls crearColaAvls(){
	TColaAvls newElemento = new repColaAvls;
	newElemento->primero = newElemento->ultimo = NULL;
	return newElemento;
}


TColaAvls encolar(TAvl avl, TColaAvls c){
	if (estaVacioAvl(avl)) {
		
		Nodo *agregar = new Nodo;
		agregar->arbol = NULL;
		agregar->ant = NULL;
		agregar->sig = c->primero;
		if (c->primero != NULL) c->primero->ant = agregar;
		else c->ultimo = agregar;
		c->primero = agregar;
	}
	else{
		Nodo *agregar = new Nodo;
		agregar->arbol = avl;
		agregar->ant = NULL;
		agregar->sig = c->primero;
		if (c->primero != NULL) c->primero->ant = agregar;
		else c->ultimo = agregar;
		c->primero = agregar;	
		
	}
	return c;
}


TColaAvls desencolar(TColaAvls c){
	if(c->ultimo != NULL){
		Nodo *borrar = c->ultimo;
		c->ultimo = c->ultimo->ant;
		if (c->ultimo == NULL) c->primero = NULL;
		else c->ultimo->sig = NULL;
		
		delete borrar;
	}
	return c;
}

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


bool estaVaciaColaAvls(TColaAvls c){
	return (c->primero == NULL && c->ultimo == NULL);
}


TAvl frente(TColaAvls c){
	return c->ultimo->arbol;
}

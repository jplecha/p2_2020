#include "../include/colaInfo.h"
#include "../include/listaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>


struct Nodo{
  info_t info;
  Nodo *sig;
  Nodo *ant;
};

struct repCola{
  Nodo *pri,*ult;
};

TCola crearCola(){
  TCola nuevo = new repCola;
	nuevo->pri = nuevo->ult = NULL;
	return nuevo;
}


bool esVaciaCola(TCola cola){
  return (cola->pri == NULL && cola->ult == NULL);
}


TCola encolar(info_t nuevo, TCola cola){
  if (!esVaciaCola(cola)) {
		Nodo *agregar = new Nodo;
		agregar->info = nuevo;
		agregar->ant = NULL;
		agregar->sig = cola->pri;
		if (cola->pri != NULL) cola->pri->ant = agregar;
		else cola->ult = agregar;
		cola->pri = agregar;
	}
	else{
		Nodo *agregar = new Nodo;
		agregar->info = NULL;
		agregar->ant = NULL;
		agregar->sig = cola->pri;
		if (cola->pri != NULL) c->pri->ant = agregar;
		else cola->ult = agregar;
		cola->pri = agregar;
	}
}


info_t frente(TCola cola){
  return cola->ult->info;
}


TCola desencolar(TCola c){
  if(c->ult != NULL){
		Nodo *borrar = c->ult;
		c->ult = c->ult->ant;
		if (c->ult != NULL) c->ult->sig = NULL;
		else
		c->pri = NULL;
		delete borrar;
	}
  return c;
}

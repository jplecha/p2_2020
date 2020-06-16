//52139037

#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodoIt *PNodoIt;
struct nodoIt {
	nat elem;
	PNodoIt sig;
};

struct repIterador {
	PNodoIt inicio, fin, actual;
	bool bloqueado;
};

TIterador crearIterador(){
	TIterador res=new repIterador;
	res->actual = res->inicio=res->fin=NULL;
	res->bloqueado=false;
	return res;
}


TIterador agregarAIterador(nat elem, TIterador iter){
if(!iter->bloqueado){
	PNodoIt nodoNuevo=new nodoIt;
	nodoNuevo->elem=elem;
	nodoNuevo->sig=NULL;
	if(iter->fin!=NULL){
	iter->fin->sig=nodoNuevo;
	}else{
	iter->inicio=nodoNuevo;
	}
	iter->fin=nodoNuevo;
}

return iter;
}

TIterador reiniciarIterador(TIterador iter){

	if (iter->inicio != NULL){
		iter->actual = iter->inicio;
    }
    iter->bloqueado = false;
    
  return iter;  
}


TIterador avanzarIterador(TIterador iter){

if(estaDefinidaActual(iter)){
	iter->actual=iter->actual->sig;
}

return iter;
}


nat actualEnIterador(TIterador iter){
	return iter->actual->elem;
}

bool estaDefinidaActual(TIterador iter){
	return (iter->actual != NULL);
}

void liberarIterador(TIterador iter){
	iter->actual=iter->inicio;
	while(iter->actual!=NULL){
		PNodoIt aux;
		aux=iter->actual;
		iter->actual=iter->actual->sig;
		delete aux;
	}
	delete iter;
}

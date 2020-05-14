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


/*
  Agrega 'elem' al final de 'iter' si y solo si nunca se reinicio.
  Devuelve 'iter'.
  La posición actual sigue indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
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

/*
  Mueve la posición actual de 'iter' al primero si y solo si 'iter' tiene
  elementos.
  Devuelve 'iter'.
  No se podrán agregar más elementos (aunque no hubiera ninguno).
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador reiniciarIterador(TIterador iter){

	if(iter->fin!=NULL){
		iter->actual=iter->inicio;
		iter->bloqueado=true;
	}
	return iter;
}

/*
  Avanza la posición actual de 'iter' hacia el siguiente si y solo si'
  estaDefinidaActual(iter).
  Devuelve 'iter'.
  Si ! haySiguienteEnIter(iter) la posición actual queda indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador avanzarIterador(TIterador iter){

if(estaDefinidaActual(iter)){
	iter->actual=iter->actual->sig;
}

return iter;
}

/*
  Devuelve el elemento de la posición actual de 'iter'.
  Precondición: estaDefinidaActual(iter).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat actualEnIterador(TIterador iter){
	return iter->actual->elem;
}






/*
  Devuelve 'true' si y solo si la posición actual de 'iter' está definida.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaDefinidaActual(TIterador iter){
	return (iter->actual != NULL);
}


/*
  Libera la memoria asignada a 'iter'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'iter'.
 */
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
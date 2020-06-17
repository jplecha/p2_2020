//52139037
#include "../include/info.h"
#include "../include/avl.h"
#include "../include/conjunto.h"
#include "../include/iterador.h"
#include <stddef.h>
struct repConjunto {
	TAvl arbol;
	
};

typedef struct repConjunto *TConjunto;


TConjunto crearConjunto(){
	TConjunto newElemento = new repConjunto();
	newElemento->arbol = crearAvl();
	return newElemento;
}


TConjunto singleton(nat elem){
	TConjunto password = crearConjunto();
	password->arbol = crearAvl();
	password->arbol=insertarEnAvl(elem, password->arbol);
	
	return password;
}



TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
	TConjunto elResultadoSolucion = crearConjunto();
	TIterador iterac1 = iteradorDeConjunto(c1);
	TIterador iterac2 = iteradorDeConjunto(c2);
	reiniciarIterador(iterac1);
	reiniciarIterador(iterac2);	
	if (estaVacioConjunto(c1)){
		while (estaDefinidaActual(iterac2)){	
		elResultadoSolucion->arbol=insertarEnAvl(actualEnIterador(iterac2), elResultadoSolucion->arbol);
		avanzarIterador(iterac2);
		}	
	}
	else if (estaVacioConjunto(c2)){
		while (estaDefinidaActual(iterac1)){	
		elResultadoSolucion->arbol=insertarEnAvl(actualEnIterador(iterac1), elResultadoSolucion->arbol);
		avanzarIterador(iterac1);
		}	
	}
	else{	
		
	while ((estaDefinidaActual(iterac1)) && (estaDefinidaActual(iterac2))){
			if (actualEnIterador(iterac1)<actualEnIterador(iterac2)){
				elResultadoSolucion->arbol=insertarEnAvl(actualEnIterador(iterac1), elResultadoSolucion->arbol);	
				avanzarIterador(iterac1);
			}
			else {
				if (actualEnIterador(iterac1)>actualEnIterador(iterac2)){
	
				elResultadoSolucion->arbol=insertarEnAvl(actualEnIterador(iterac2), elResultadoSolucion->arbol);
				avanzarIterador(iterac2);
			     } else	if (actualEnIterador(iterac1)==actualEnIterador(iterac2)){
				
				elResultadoSolucion->arbol=insertarEnAvl(actualEnIterador(iterac1), elResultadoSolucion->arbol);
				avanzarIterador(iterac2);
				avanzarIterador(iterac1);
				}
			}
		}
	while (estaDefinidaActual(iterac1)){
			
		elResultadoSolucion->arbol=insertarEnAvl(actualEnIterador(iterac1), elResultadoSolucion->arbol);
		avanzarIterador(iterac1);
	}	
	
	while (estaDefinidaActual(iterac2)){
			
		elResultadoSolucion->arbol=insertarEnAvl(actualEnIterador(iterac2), elResultadoSolucion->arbol);
		avanzarIterador(iterac2);
	}	
}
	liberarIterador(iterac1);
	liberarIterador(iterac2);
	return elResultadoSolucion;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
	TConjunto elResultadoSolucion = crearConjunto();
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
		elResultadoSolucion->arbol=insertarEnAvl(agregar, elResultadoSolucion->arbol);
		avanzarIterador(iterac1);
		}	
	}
	else{	
		
	while ((estaDefinidaActual(iterac1)) && (estaDefinidaActual(iterac2))){
			if (actualEnIterador(iterac1)<actualEnIterador(iterac2)){
				agregar = actualEnIterador(iterac1);
				elResultadoSolucion->arbol=insertarEnAvl(agregar, elResultadoSolucion->arbol);	
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
		elResultadoSolucion->arbol=insertarEnAvl(agregar, elResultadoSolucion->arbol);
		avanzarIterador(iterac1);
	}	
	
}
	liberarIterador(iterac1);
	liberarIterador(iterac2);
	return elResultadoSolucion;
}

bool perteneceAConjunto(nat elem, TConjunto c){
	bool esta = false;
	if (c != NULL){
		TAvl contiene = buscarEnAvl(elem, c->arbol);
		if (contiene != NULL)
			esta = elem == raizAvl(contiene);
	}
	return esta;
}

bool estaVacioConjunto(TConjunto c){
	return (c->arbol == NULL);
}

nat cardinalidad(TConjunto c){
 return cantidadEnAvl(c->arbol);
}


TConjunto arregloAConjunto(nat *elems, nat n){
	TConjunto laPropiaSolucion = crearConjunto();
	laPropiaSolucion->arbol = arregloAAvl(elems, n);
	return laPropiaSolucion;
}


TIterador iteradorDeConjunto(TConjunto c){
	
	TIterador infos = enOrdenAvl(c->arbol);
	
	return infos;
}



void liberarConjunto(TConjunto c){
	liberarAvl(c->arbol);
	delete(c);
}

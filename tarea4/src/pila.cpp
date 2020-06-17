//52139037
#include "../include/pila.h"

struct repPila{
int *datos;
int tope;
int cota;
};

TPila crearPila(nat N){
	TPila p = new repPila ();
	p->datos = new int [N];   
    p->tope = 0;
    p->cota = N;
    return p; 
}


TPila apilar(nat num, TPila p){
	if (!estaLlenaPila(p)) {
          p->datos[p->tope] = num;
      p->tope++;
    }
	return p;
}

TPila desapilar(TPila p){
	if (!estaVaciaPila(p)) 
     p->tope--;
	return p;
}


void liberarPila(TPila p){
	delete[] p->datos;
	delete p;
}


bool estaVaciaPila(TPila p){
	return p->tope == 0;
}


bool estaLlenaPila(TPila p){
	return p->tope == p->cota;
}


nat cima(TPila p){
	return p->datos[p->tope-1];
}
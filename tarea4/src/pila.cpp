#include "../include/pila.h"

struct repPila{
int *datos;
int tope;
int cota;
};
/*
  Devuelve una 'TPila' vacía (sin elementos) que puede tener hasta 'N'
  elementos.
  Precondición: N > 0.
 */
TPila crearPila(nat N){
	TPila p = new repPila ();
	p->datos = new int [N];   
    p->tope = 0;
    p->cota = N;
    return p; 
}

/*
  Apila 'num' en 'p'.
  Devuelve 'p'.
  Si estaLenaPila(p) no hace nada.
  El tiempo de ejecución en el peor caso es O(1).
 */
TPila apilar(nat num, TPila p){
	if (!estaLlenaPila(p)) {
          p->datos[p->tope] = num;
      p->tope++;
    }
	return p;
}

/*
  Remueve de 'p' el elemento que está en la cima.
  Devuelve 'p'.
  Si estaVaciaPila(p) no hace nada.
  El tiempo de ejecución en el peor caso es O(1).
 */
TPila desapilar(TPila p){
	if (!estaVaciaPila(p)) 
     p->tope--;
	return p;
}

/*
  Libera la memoria asignada a 'p'.
 */
void liberarPila(TPila p){
	delete[] p->datos;
	delete p;
}

/*
  Devuelve 'true' si y solo si 'p' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVaciaPila(TPila p){
	return p->tope == 0;
}

/*
  Devuelve 'true' si y solo si la cantidad de elementos en 'p' es 'N'
  (siendo 'N' el valor del parámetro con que fue creada 'p').
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaLlenaPila(TPila p){
	return p->tope == p->cota;
}

/*
  Devuelve el elemento que está en la cima de 'p'.
  Precondición: ! estaVaciaPila(p);
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cima(TPila p){
	return p->datos[p->tope-1];
}
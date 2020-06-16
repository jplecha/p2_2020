/*5213903*/
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/avl.h"
#include "../include/conjunto.h"
#include "../include/iterador.h"
#include <stddef.h>
#include "../include/colaDePrioridad.h"

struct repCP {
    nat cant;
    nat N;
    TCadena *colaPrioridad;
};

/*
  Devuelve una 'TColaDePrioridad' vacía (sin elementos). Podrá contener
  elementos entre 1 y N.
  El tiempo de ejecución en el peor caso es O(N).
 */
TColaDePrioridad crearCP(nat N){
	nat iterador;
    if (N < 1)
        return NULL;
    TColaDePrioridad cp = new repCP;
    cp->colaPrioridad = new TCadena[N];
    for (iterador = 0; iterador < N; iterador++) {
        cp->colaPrioridad[iterador]= crearCadena();
    }
    cp->cant = 0;
    cp->N = N;
    return cp;
}


/*
  Devuelve el valor máximo que puede tener un elemento de 'cp', que es el
  parámetro de crearCP.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat rangoCP(TColaDePrioridad cp){
	return cp->N;
}

/*
  Inserta 'elem' en 'cp'. La prioridad asociada a 'elem' es 'valor'.
  Precondición 1 <= elem <= rangoCP(cp).
  Precondición: !estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
	nat paraje = elem % cp->N;
    TInfo cooperador=crearInfo(elem,valor);
    cp->colaPrioridad[paraje]=insertarAlFinal(cooperador,cp->colaPrioridad[paraje]);
    cp->cant++;
	return cp;
}

/*
  Devuelve 'true' si y solo si en 'cp' no hay elementos.
  El tiempo de ejecución en el peor casos es O(1).
 */
bool estaVaciaCP(TColaDePrioridad cp){
	return cp->cant==0;
}

/*
  Devuelve el elemento prioritario de 'cp'.
  Precondición: !estaVacioCP(cp).
  El tiempo de ejecución en el peor casos es O(1).
 */
nat prioritario(TColaDePrioridad cp){
return 1;
}

/*
  Elimina de 'cp' el elemento prioritario.
  Precondición: !estaVacioCP(cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
return cp;
}


/*
  Devuelve 'true' si y solo si 'elem' es un elemento de 'cp'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnCP(nat elem, TColaDePrioridad cp){
	int paraje = elem % cp->N;
    TLocalizador elValorDeRetorno=siguienteClave(elem,inicioCadena(cp->colaPrioridad[paraje]),cp->colaPrioridad[paraje]);
    return (elValorDeRetorno!=NULL);
}

/*
  Devuelve el valor de prioridad asociado a 'elem'.
  Precondición: estaEnCp(elem, cp).
  El tiempo de ejecución en el peor caso es O(1).
 */

double prioridad(nat elem, TColaDePrioridad cp){
	int paraje = elem % cp->N;
    TLocalizador gps= finalCadena(cp->colaPrioridad[paraje]);
    gps= anteriorClave(elem, gps, cp->colaPrioridad[paraje]);
    return realInfo(infoCadena(gps,cp->colaPrioridad[paraje]));
}

/*
  Modifica el valor de la propiedad asociada a 'elem'; pasa a ser 'valor'.
  Precondición: estaEnCp(elem, cp).
  Devuelve 'cp'.
  El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
  pasado en crearCP.
 */
TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
	int paraje = elem % cp->N;
	TInfo cooperador=crearInfo(elem,valor);
	cp->colaPrioridad[paraje]=insertarAlFinal(cooperador,cp->colaPrioridad[paraje]);
	return cp;
}

/*
  Libera la menoria asignada a 'cp'.
  El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
  pasado en crearCP.
 */
void liberarCP(TColaDePrioridad cp){
	for (nat i= 0; i < (cp->N); i++) {
            liberarCadena(cp->colaPrioridad[i]);
    }
    delete[] cp->colaPrioridad;
    delete cp;
}
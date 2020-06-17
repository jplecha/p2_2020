//52139037
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/avl.h"
#include "../include/conjunto.h"
#include "../include/iterador.h"
#include <stddef.h>
#include "../include/colaDePrioridad.h"
#include "../include/mapping.h"
#include "../include/utils.h"

struct repMap{
  TCadena *cadena;
  nat M;
  nat cant;
};
/*
  Crea un 'TMapping' vacío (sin elementos) de asociaciones nat -> double.
  Podrá haber hasta M asociaciones.
  El tiempo de ejecución en el peor caso es O(M).
 */
TMapping crearMap(nat M){
	nat iterador;
    if (M < 1)
        return NULL;
    TMapping map = new repMap;
    map->cadena = new TCadena[M];
    for (iterador = 0; iterador < M; iterador++) {
        map->cadena[iterador]= crearCadena();
    }
    map->cant = 0;
    map->M = M;
    return map;
}

/*
  Inserta en 'map' la asociación entre 'clave' y 'valor'.
  Precondición: !estaLlenoMap(map) y !existeAsociacionEnMap(clave, map).
  Devuelve 'map'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TMapping asociarEnMap(nat clave, double valor, TMapping map){
	
	TInfo newElemento=crearInfo(clave,valor);
	nat pos= clave % map->M;
	map->cadena[pos]=insertarAlFinal(newElemento, map->cadena[pos]);
    map->cant++;
    return map;
}

/*
  Elimina de 'map' la asociación correspondiente a 'clave' y libera la
  menoria  asignada a mantener esa asociación.
  Precondición: existeAsociacionenMap(clave, h).
  Devuelve 'map'.
  El 'TMapping' resultado comparte memoria con el parámetro'.
  El tiempo de ejecución es O(1) en promedio.
 */
TMapping desasociarEnMap(nat clave, TMapping map){
  nat pos=clave % map->M;
  TLocalizador loc=inicioCadena(map->cadena[pos]);
  while (natInfo(infoCadena(loc, map->cadena[pos]))!=clave){
      loc=siguiente(loc, map->cadena[pos]);
  }
  map->cadena[pos]=removerDeCadena(loc,map->cadena[pos]);
  map->cant--;
  return map;
}

/*
  Devuelve 'true' si y solo si en 'map' hay una asociación correspondiente
  a 'clave'.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existeAsociacionEnMap(nat clave, TMapping map){
	nat pos=clave % map->M;
	TLocalizador loc=inicioCadena(map->cadena[pos]);
	while (esLocalizador(loc) && natInfo(infoCadena(loc, map->cadena[pos]))!=clave){
      loc=siguiente(loc, map->cadena[pos]);
	}
	
	return esLocalizador(loc);
}

/*
  Devuelve el valor correspondiente a la asociacion de 'clave' en 'h'.
  Precondición: existeAsociacionenMap(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
double valorEnMap(nat clave, TMapping map){
  nat pos=clave % map->M;
	TLocalizador loc=inicioCadena(map->cadena[pos]);
	while (natInfo(infoCadena(loc, map->cadena[pos]))!=clave){
      loc=siguiente(loc, map->cadena[pos]);
	}
	
	return realInfo(infoCadena(loc, map->cadena[pos]));
}

/*
  Devuelve 'true' si y solo si 'map' tiene 'M' elementos, siendo 'M' el
  parámetro pasado en crearMap.
  El tiempo de ejecución es O(1).
 */
bool estaLlenoMap(TMapping map){
	return map->M==map->cant;
}

/*
  Libera la memoria asignada a 'map' y todos sus elementos.
  El tiempo de ejecución en el peor caso es O(M), siendo 'M' el parámetro
  pasado en crearMap.
 */
void liberarMap(TMapping map){
	for (nat i= 0; i < (map->M); i++) {
            liberarCadena(map->cadena[i]);
    }
    delete[] map->cadena;
    delete map;
}
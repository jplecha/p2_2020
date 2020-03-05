
#include "../include/mapping.h"
#include "../include/listaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>
// Representación de 'TMapping'.
// Se debe definir en mappingInfo.cpp.
// struct repMap;
// Declaración del tipo 'TMapping'.
struct repMap{
 int a;
}

/*  Operaciones de TMapping */

/*
  Devuelve un elemento de tipo 'TMapping' vacío (sin elementos).
 */
TMapping crearMapping(){
  return NULL;
}

/*
  Si en 'map' hay menos de MAX (definido en utils.h) asociaciones y 'clave'
  no tiene un valor asociado en 'map' agrega en 'map' la asociación
  (clave,valor)
  Devuelve 'map'.
 */
TMapping asociar(nat clave, double valor, TMapping map){
  return NULL;
}

/*
  Devuelve 'true' si y solo si 'clave' tiene un valor asociado en 'map'.
 */
bool esClave(nat clave, TMapping map){
  return NULL;
}

/*
  Devuelve el valor que en 'map' está asociado a 'clave'.
  Precondición: esClave(clave, map)
 */
double valor(nat clave, TMapping map){
  return NULL;
}

/*
  Si 'clave' tiene un valor asociado en 'map' remueve de `map' la asociación de
  'clave'.
  Devuelve 'map'.
 */
TMapping desasociar(nat clave, TMapping map){
  return NULL;
}

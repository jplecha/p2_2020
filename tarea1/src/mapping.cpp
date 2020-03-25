//52139037 - Jose Lecha
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
  TLista lista;
};

/*  Operaciones de TMapping */

/*
  Devuelve un elemento de tipo 'TMapping' vacío (sin elementos).
 */
TMapping crearMapping(){
  TMapping map=new repMap;
  map->lista=crearLista();
  return map;
}

/*
  Si en 'map' hay menos de MAX (definido en utils.h) asociaciones y 'clave'
  no tiene un valor asociado en 'map' agrega en 'map' la asociación
  (clave,valor)
  Devuelve 'map'.
 */
TMapping asociar(nat clave, double valor, TMapping map){
    if(longitud(map->lista)<MAX && !esClave(clave,map)){
      info_t nuevo;
      nuevo.natural=clave;
      nuevo.real=valor;
      map->lista=insertar(longitud(map->lista)+1,nuevo,map->lista);
    }
    return map;
}

/*
  Devuelve 'true' si y solo si 'clave' tiene un valor asociado en 'map'.
 */
bool esClave(nat clave, TMapping map){
  return posNat(clave,map->lista);
}

/*
  Devuelve el valor que en 'map' está asociado a 'clave'.
  Precondición: esClave(clave, map)
 */
double valor(nat clave, TMapping map){
  info_t aux;
  nat pos=posNat(clave, map->lista);
  aux=infoLista(pos,map->lista);
  return aux.real;
}

/*
  Si 'clave' tiene un valor asociado en 'map' remueve de `map' la asociación de
  'clave'.
  Devuelve 'map'.
 */
TMapping desasociar(nat clave, TMapping map){
  if(esClave(clave,map)){
      map->lista=remover(posNat(clave,map->lista),map->lista);
  }

  return map;
}

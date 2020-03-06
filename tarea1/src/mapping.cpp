
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
 info_t *elem;
 repMap *sig;
 int cant;
};

/*  Operaciones de TMapping */

/*
  Devuelve un elemento de tipo 'TMapping' vacío (sin elementos).
 */
TMapping crearMapping(){
  TMapping map=new repMap;
  map->elem=NULL;
  map->sig=NULL;
  map->cant=0;
  return map;
}

/*
  Si en 'map' hay menos de MAX (definido en utils.h) asociaciones y 'clave'
  no tiene un valor asociado en 'map' agrega en 'map' la asociación
  (clave,valor)
  Devuelve 'map'.
 */
TMapping asociar(nat clave, double valor, TMapping map){
    if(map->cant<MAX && !esClave(clave,map)){
      TMapping aux=crearMapping();
      info_t *nuevo=new info_t;
      nuevo->natural=clave;
      nuevo->real=valor;
      aux->elem=nuevo;
      aux->sig=map;
      aux->cant=map->cant+1;
      return aux;
    }
    else{
      return map;
    }
}

/*
  Devuelve 'true' si y solo si 'clave' tiene un valor asociado en 'map'.
 */
bool esClave(nat clave, TMapping map){
  while(map->elem!=NULL && map->elem->natural!=clave) map=map->sig;
  return (map->elem!=NULL);
}

/*
  Devuelve el valor que en 'map' está asociado a 'clave'.
  Precondición: esClave(clave, map)
 */
double valor(nat clave, TMapping map){
  while(map->elem!=NULL && map->elem->natural!=clave) map=map->sig;
  return map->elem->real;
}

/*
  Si 'clave' tiene un valor asociado en 'map' remueve de `map' la asociación de
  'clave'.
  Devuelve 'map'.
 */
TMapping desasociar(nat clave, TMapping map){
  TMapping inicio=map;
  if(esClave(clave,map)){
    if(map->cant==1){
      map->elem=NULL;
    }else{
      if(map->elem->natural==clave){
        map=map->sig;
      }else{
        while(map->sig->elem->natural!=clave){
          map=map->sig;
        }
        map->sig=map->sig->sig;
      }


    }
  }
  inicio->cant--;

  return inicio;
}

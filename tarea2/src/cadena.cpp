#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo{
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct repCadena{
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) {
  return loc!=NULL;
}

TCadena crearCadena(){
  TCadena res = new repCadena;
  res->inicio=res->final=NULLM
  return res;
}

void liberarCadena(TCadena cad){
  TLocalizador a_borrar;
  while (cad->inicio != NULL){
    a_borrar = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberarInfo(a_borrar->dato);
    delete a_borrar;
  }
  delete cad;
}

bool esVaciaCadena(TCadena cad){
  assert(((cad->inicio==NULL) && (cad->final == NULL)) || ((cad->inicio!=NULL) && (cad->final != NULL)));
  return (cad->inicio==NULL);
}

TLocalizador inicioCadena(TCadena cad){
  TLocalizador res;
  if (esVaciaCadena(cad)){
    res=NULL;
  }else{
    res=cad->inicio;
  }
  return res;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad){
  assert(esLocalizadorEnCadena(loc, cad));
  TLocalizador res;
  if(esFinalCadena(loc, cad)){
    res=NULL;
  } else{
    res= loc->siguiente;
  }
  return res;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad){
  TLocalizador cursor = inicioCadena(cad);
  while(esLocalizador(cursor) && (cursor != loc)){
    cursor=siguiente(cursor,cad);
  }
  reurn esLocalizador(cursor);
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad){
  bool res;
  res = localizadorEnCadena(loc1, cad);
  if(res){
    TLocalizador cursor = loc1;
    while (esLocalizador(cursor) && (cursor != loc2)){
      cursor = siguiente(cursor, cad);
    }
    res=esLocalizador(cursor);
    assert(!res || localizadorEnCadena(loc2,cad));
  }
  return res;
}

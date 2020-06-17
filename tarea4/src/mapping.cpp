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

TMapping asociarEnMap(nat clave, double valor, TMapping map){
	
	TInfo newElemento=crearInfo(clave,valor);
	nat pos= clave % map->M;
	map->cadena[pos]=insertarAlFinal(newElemento, map->cadena[pos]);
    map->cant++;
    return map;
}

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


bool existeAsociacionEnMap(nat clave, TMapping map){
	nat pos=clave % map->M;
	TLocalizador loc=inicioCadena(map->cadena[pos]);
	while (esLocalizador(loc) && natInfo(infoCadena(loc, map->cadena[pos]))!=clave){
      loc=siguiente(loc, map->cadena[pos]);
	}
	
	return esLocalizador(loc);
}


double valorEnMap(nat clave, TMapping map){
  nat pos=clave % map->M;
	TLocalizador loc=inicioCadena(map->cadena[pos]);
	while (natInfo(infoCadena(loc, map->cadena[pos]))!=clave){
      loc=siguiente(loc, map->cadena[pos]);
	}
	
	return realInfo(infoCadena(loc, map->cadena[pos]));
}


bool estaLlenoMap(TMapping map){
	return map->M==map->cant;
}


void liberarMap(TMapping map){
	nat i=0;
	while (i<map->M){
		liberarCadena(map->cadena[i]);
		i++;
	}
	
    delete[] map->cadena;
    delete map;
}
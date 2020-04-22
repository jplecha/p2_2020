//52139037
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
  res->inicio=res->final=NULL;
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

TLocalizador finalCadena(TCadena cad){
  TLocalizador res;
  if (esVaciaCadena(cad)){
    res=NULL;
  }else{
    res=cad->final;
  }
  return res;
}

/*
  Devuelve el elemento de 'cad' al que se accede con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TInfo infoCadena(TLocalizador loc, TCadena cad){
	return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad){
  assert(localizadorEnCadena(loc, cad));
  TLocalizador res;
  if(esFinalCadena(loc, cad)){
    res=NULL;
  } else{
    res= loc->siguiente;
  }
  return res;
}

TLocalizador anterior(TLocalizador loc, TCadena cad){
  assert(localizadorEnCadena(loc, cad));
  TLocalizador res;
  if(esInicioCadena(loc, cad)){
    res=NULL;
  } else{
    res= loc->anterior;
  }
  return res;
}



bool localizadorEnCadena(TLocalizador loc, TCadena cad){
  TLocalizador cursor = inicioCadena(cad);
  while(esLocalizador(cursor) && (cursor != loc)){
    cursor=siguiente(cursor,cad);
  }
  return esLocalizador(cursor);
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al último elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esFinalCadena(TLocalizador loc, TCadena cad){
	bool res;
	if(esVaciaCadena(cad)){
		res=false;
	}else{
		res=(loc==cad->final);
	}
	return res;
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al primer elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
*/
bool esInicioCadena(TLocalizador loc, TCadena cad){
	bool res;
	if(esVaciaCadena(cad)){
		res=false;
	}else{
		res=(loc==cad->inicio);
	}
	return res;
}
/*
  Se inserta 'i' como último elemento de 'cad'.
  Devuelve 'cad'.
  Si esVaciaVadena (cad) 'i' se inserta como único elemento de 'cad'.
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena insertarAlFinal(TInfo i, TCadena cad){
	nodo *aIns=new nodo;
	aIns->dato=i;
	aIns->siguiente=NULL;
	aIns->anterior=cad->final;
	if(cad->final==NULL){
		cad->inicio=aIns;
	}else{
		cad->final->siguiente=aIns;
	}
	cad->final=aIns;
	return cad;
}

/*
  Se inserta 'i' como un nuevo elemento inmediatamente antes de 'loc'.
  Devuelve 'cad'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad){
	nodo *nuevo=new nodo;
	nuevo->dato=i;
	nuevo->anterior=loc->anterior;
	nuevo->siguiente=loc;
	if(loc->anterior==NULL){
		cad->inicio=nuevo;
	}else{
		loc->anterior->siguiente=nuevo;
	}
	loc->anterior=nuevo;
	return cad;
}

/*
  Se remueve el elemento al que se accede desde 'loc' y se libera la memoria
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve 'cad'.
  El valor de 'loc' queda indeterminado.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena removerDeCadena(TLocalizador loc, TCadena cad){
	if(loc->anterior!=NULL){
		loc->anterior->siguiente=loc->siguiente;
	}else{
		cad->inicio=loc->siguiente;
	}
	if(loc->siguiente!=NULL){
		loc->siguiente->anterior=loc->anterior;
	}else{
		cad->final=loc->anterior;
	}
	liberarInfo(loc->dato);
	delete loc;
	return cad;
}
/*
  Imprime los elementos de 'cad' de la siguiente forma:
  (n de pos1,r de pos1)(n de pos2,r de pos2) ...
  donce 'n` es el componente natural y 'r' es el componente real.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVaciaCadena(cad) sólo se imprime el fin de línea.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
  
  Falta implementar
*/
void imprimirCadena(TCadena cad){
	if(!esVaciaCadena(cad)){
		TLocalizador aux=cad->inicio;
		while(esLocalizador(aux)){
			printf("(%d,%.2f)",natInfo(infoCadena(aux,cad)),realInfo(infoCadena(aux,cad)));
			aux=siguiente(aux,cad);
		}
	}
	printf("\n");
	
}
/*
  Devuelve el 'TLocalizador' con el que se accede al k-esimo elemento de 'cad'.
  Si 'k' es 0 o mayor a la cantidad de elementos de 'cad' devuelve un
  localizdor  no válido.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador kesimo(nat k, TCadena cad){
	TLocalizador res=inicioCadena(cad);
	if(k!=0){
		nat cont=1;
		while((res!=NULL) && (cont!=k)){
			res=siguiente(res,cad);
			cont++;
		}
	}else{
		res=NULL;
	}
	return res;
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
//revisar
/*
  Se inserta en 'cad' la 'TCadena' 'sgm' inmediatamente después de 'loc',
  manteniendo los elementos originales y el orden relativo entre ellos.
  Devuelve 'cad'.
  No se debe obtener memoria (los nodos de 'sgm' pasan a ser parte de 'cad').
  Se libera la memoria asignada al resto de las estructuras de 'sgm'.
  El valor de 'sgm' queda indeterminado.
  Si esVaciaCadena(cad) 'loc' es ignorado y el segmento queda insertado.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad){
	if(esVaciaCadena(cad)){
		cad->inicio=sgm->inicio;
		cad->final=sgm->final;
	}else{
		if(!esVaciaCadena(sgm)){
			sgm->inicio->anterior=loc;
			sgm->final->siguiente=loc->siguiente;
			if(esFinalCadena(loc,cad)){
				cad->final=sgm->final;
			}else{
				loc->siguiente->anterior=sgm->final;
			}
			loc->siguiente=sgm->inicio;
		}
	}
	sgm->inicio=sgm->final=NULL;
	delete(sgm);
	return cad;
}

/*
  Devuelve una 'TCadena' con los elementos de 'cad' que se encuentran entre
  'desde' y 'hasta', incluidos.
  La 'TCadena' resultado no comparte memoria con 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacia.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
*/
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
	TCadena res=crearCadena();
	if(!esVaciaCadena(cad)){
		TLocalizador loc=desde;
		while(loc!=siguiente(hasta,cad)){
			TInfo inf=copiaInfo(loc->dato);
			insertarAlFinal(inf,res);
			loc=siguiente(loc, cad);
		}
	}
	return res;
}
/*
  Remueve de 'cad' los elementos que se encuentran  entre 'desde' y 'hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacía.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
*/
TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
	if(!esVaciaCadena(cad)){
		if(desde==hasta){
			removerDeCadena(desde,cad);
		}else if(desde==cad->inicio && hasta==cad->final){
			liberarCadena(cad);
			cad=crearCadena();
		}else{
			TCadena aux=crearCadena();
			aux->inicio=desde;
			aux->final=hasta;
			if(esLocalizador(siguiente(hasta,cad))&& esLocalizador(anterior(desde,cad))){
				hasta->siguiente->anterior=anterior(desde,cad);
				desde->anterior->siguiente=siguiente(hasta,cad);
			}else if(esLocalizador(siguiente(hasta,cad))){
				cad->inicio=siguiente(hasta,cad);
				hasta->siguiente->anterior=NULL;
			}else if(esLocalizador(anterior(desde,cad))){
				cad->final=anterior(desde,cad);
				desde->anterior->siguiente=NULL;
			}
			hasta->siguiente=NULL;
			desde->anterior=NULL;
			liberarCadena(aux);
		}
	}
	return cad;
}

/*
  Sustituye con 'i' el elemento de 'cad' al que se accede con 'loc'.
  Devuelve 'cad'.
  No destruye el elemento al que antes se accedía con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 
*/
TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad){
	loc->dato=i;
	return cad;
}
/*
  Intercambia los elementos a los que se accede con 'loc1' y 'loc2'.
  'loc1' y 'loc2' mantienen su relación de precedencia.
  Devuelve 'cad'.
  Precondición:
  localizadorEnCadena (loc1, cad)
  y localizadorEnCadena (loc2, cad).
  El tiempo de ejecución en el peor caso es O(1).
*/
TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad){
	TInfo aux= copiaInfo(loc1->dato);
	liberarInfo(loc1->dato);
	loc1->dato=loc2->dato;
	loc2->dato=aux;
	return cad;
}
/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el final de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 
*/
TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad){
	TLocalizador aux=loc;
	if(esVaciaCadena(cad)){
		aux=NULL;
	}else{
		while(esLocalizador(aux)&&natInfo(infoCadena(aux,cad))!=clave){
			aux=siguiente(aux,cad);
		}
	}
	return aux;
}
/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el inicio de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
  
*/
TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad){
	TLocalizador aux=loc;
	if(esVaciaCadena(cad)){
		aux=NULL;
	}else{
		while(esLocalizador(aux)&&natInfo(infoCadena(aux,cad))!=clave){
			aux=anterior(aux,cad);
		}
	}
	return aux;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento cuyo componente
  natural es el menor en el segmento que va desde 'loc' hasta finalCadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
*/
TLocalizador menorEnCadena(TLocalizador loc, TCadena cad){
	TLocalizador res=loc;
	while(esLocalizador(siguiente(loc,cad))){
		loc=siguiente(loc,cad);
		if(natInfo(infoCadena(loc,cad))<natInfo(infoCadena(res,cad))){
			res=loc;
		}
	}
	return res;
}





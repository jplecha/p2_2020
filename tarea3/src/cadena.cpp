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

bool esFinalCadena(TLocalizador loc, TCadena cad){
	bool res;
	if(esVaciaCadena(cad)){
		res=false;
	}else{
		res=(loc==cad->final);
	}
	return res;
}


bool esInicioCadena(TLocalizador loc, TCadena cad){
	bool res;
	if(esVaciaCadena(cad)){
		res=false;
	}else{
		res=(loc==cad->inicio);
	}
	return res;
}

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

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad){
	loc->dato=i;
	return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad){
	TInfo aux= copiaInfo(loc1->dato);
	liberarInfo(loc1->dato);
	loc1->dato=loc2->dato;
	loc2->dato=aux;
	return cad;
}

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





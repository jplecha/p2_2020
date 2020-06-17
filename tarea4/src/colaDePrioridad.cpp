/*5213903*/
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/avl.h"
#include "../include/conjunto.h"
#include "../include/iterador.h"
#include <stddef.h>
#include "../include/colaDePrioridad.h"

struct repCP {
    TInfo *array;
	nat tope;
	nat N;
	nat *posiciones;
};


TColaDePrioridad crearCP(nat N){
	
	TColaDePrioridad coso = new repCP;
	coso->tope = 1;
	coso->N = N;
	coso->array = new TInfo[N+1];
	coso->posiciones = new nat[N + 1];
	for(nat i = 1; i<N+1;i++)
		coso->array[i] = NULL;
	for(nat i = 0; i<N+1;i++)
	coso->posiciones[i] = 0;
	return coso;
}



nat rangoCP(TColaDePrioridad cp){
	return cp->N;
}


 static nat filtradoAscendente(TColaDePrioridad &h, nat pos){
  nat valorRetornado = 0;
  TInfo cambiar = h->array[pos];
  while ((pos>1) && (realInfo(h->array[pos/2])> realInfo(cambiar))){
    h->array[pos] = h->array[pos/2];
    h->posiciones[natInfo(h->array[pos/2])] = pos;
    pos = pos/2;
  }
  h->array[pos] = cambiar;
  valorRetornado = pos;
  return valorRetornado;
}


static void filtrado_descendente(TColaDePrioridad &h, nat n, nat pos){
  bool salir = false;
  TInfo cambiar = h->array[h->tope-1];
  while(!salir && 2*pos<= n){
    nat hijo = 2*pos;
    if ((hijo+1 <= n) && (realInfo(h->array[hijo+1]) < realInfo(h->array[hijo]))){
      hijo = hijo+1;
    }
    if (realInfo(h->array[hijo]) < realInfo(cambiar)){
      h->array[pos] = h->array[hijo];
      h->posiciones[natInfo(h->array[pos])] = pos;
      pos = hijo;
    }
    else salir = true;	
  }
  h->array[pos] = cambiar;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
	cp->tope = cp->tope+1;
	TInfo i=crearInfo(elem,valor);
	cp->array[cp->tope-1] = i;
	nat pos = filtradoAscendente(cp , cp->tope-1 );
	int agrega = natInfo(i);
	cp->posiciones[agrega] = pos;
	return cp;
}


bool estaVaciaCP(TColaDePrioridad cp){
	return (cp->tope ==1);
}


nat prioritario(TColaDePrioridad cp){
return natInfo(cp->array[1]);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
  nat agrega = natInfo(cp->array[1]);
  liberarInfo(cp->array[1]);
  cp->posiciones[agrega] = 0;
  filtrado_descendente(cp, cp->tope-1, 1);
  cp->tope = cp->tope-1;
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp){
	return cp->posiciones[elem] != 0;
}


double prioridad(nat elem, TColaDePrioridad cp){
	return realInfo(cp->array[cp->posiciones[elem]]);
}

 //modificar
 static void filtradoAscendente2(TColaDePrioridad &c, nat pos){
  if((pos > 1) && (realInfo(c->array[pos/2]) > realInfo(c->array[pos]))){
    c->posiciones[natInfo(c->array[pos/2])]= pos;
    c->posiciones[natInfo(c->array[pos])]= pos/2;
    TInfo aux = c->array[pos/2];
    c->array[pos/2] = c->array[pos];
    c->array[pos]= aux;
    filtradoAscendente2(c,pos/2);
  }
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
 
  int i = cp->posiciones[elem];
  liberarInfo(cp->array[i]);
  TInfo nuevo = crearInfo(elem,valor);
  cp->array[i] = nuevo;
  if( i == 1){
    filtrado_descendente(cp,i,cp->tope);
  }else if(realInfo(cp->array[i]) < realInfo(cp->array[cp->posiciones[i/2]])){
    filtradoAscendente2(cp,i);
  }else filtrado_descendente(cp,i,cp->tope);
  return cp;
}


void liberarCP(TColaDePrioridad cp){
	 if (cp != NULL){
    if (cp->tope >1)
      for(nat i = 1; i< cp->tope; i++)
        liberarInfo(cp->array[i]);
    delete [] cp->array;
    delete [] cp->posiciones;
  }
  delete cp;
}

//52139037
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
	int *posiciones;
};


TColaDePrioridad crearCP(nat N){
	
	TColaDePrioridad coso = new repCP;
	coso->tope = 1;
	coso->N = N;
	coso->array = new TInfo[N+1];
	coso->posiciones = new int[N + 1];
	for(nat i = 1; i<N+1;i++)
		coso->array[i] = NULL;
	for(nat i = 0; i<N+1;i++)
	coso->posiciones[i] = -1;
	return coso;
}



nat rangoCP(TColaDePrioridad cp){
	return cp->N;
}


 static nat funcionAuxiliarFiltradoAscendente1(TColaDePrioridad &alturita, nat pos){
  nat valorRetornado = 0;
  TInfo cambiar = alturita->array[pos];
  while ((pos>1) && (realInfo(alturita->array[pos/2])> realInfo(cambiar))){
    alturita->array[pos] = alturita->array[pos/2];
    alturita->posiciones[natInfo(alturita->array[pos/2])] = pos;
    pos = pos/2;
  }
  alturita->array[pos] = cambiar;
  valorRetornado = pos;
  return valorRetornado;
}


static void funcionAuxiliarFiltradoDescendente(TColaDePrioridad &alturita, nat n, nat pos){
  bool salir = false;
  TInfo cambiar = alturita->array[alturita->tope-1];
  while(!salir && 2*pos<= n){
    nat hijo = 2*pos;
    if ((hijo+1 <= n) && (realInfo(alturita->array[hijo+1]) < realInfo(alturita->array[hijo]))){
      hijo = hijo+1;
    }
    if (realInfo(alturita->array[hijo]) < realInfo(cambiar)){
      alturita->array[pos] = alturita->array[hijo];
      alturita->posiciones[natInfo(alturita->array[pos])] = pos;
      pos = hijo;
    }
    else salir = true;	
  }
  alturita->array[pos] = cambiar;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
	cp->tope = cp->tope+1;
	TInfo i=crearInfo(elem,valor);
	cp->array[cp->tope-1] = i;
	nat pos = funcionAuxiliarFiltradoAscendente1(cp , cp->tope-1 );
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
  cp->posiciones[agrega] = -1;
  funcionAuxiliarFiltradoDescendente(cp, cp->tope-1, 1);
  cp->tope = cp->tope-1;
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp){
	return cp->posiciones[elem] != -1;
}


double prioridad(nat elem, TColaDePrioridad cp){
	return realInfo(cp->array[cp->posiciones[elem]]);
}


TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
  nat i = cp->posiciones[elem];
  if( i != 1){
	  liberarInfo(cp->array[i]);
	  cp->array[i] = crearInfo(elem,valor);
		  if(valor < realInfo(cp->array[i/2])){
			nat res;
			res=funcionAuxiliarFiltradoAscendente1(cp,i);
			cp->posiciones[elem]=res;
		  }else{
			funcionAuxiliarFiltradoDescendente(cp,i,cp->tope-1);
		  }	  
  }else {
	  cp=eliminarPrioritario(cp);	  
	  cp=insertarEnCP(elem,valor,cp);
  }
  
  return cp;
}


void liberarCP(TColaDePrioridad cp){
	if (cp != NULL){
		if (cp->tope >1){
			nat i=1;
			while(i<cp->tope){
				liberarInfo(cp->array[i]);
				i++;
			}
		}
		
		delete [] cp->posiciones;
		delete [] cp->array;
	}
  delete cp;
}

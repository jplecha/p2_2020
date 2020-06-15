//52139037
#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


struct repBinario{
	TInfo dato;
	TBinario izq;
	TBinario der;
};

TBinario crearBinario(){
	return NULL;
}

static nat maximo(nat n1, nat n2){
	return (n1 >= n2) ? n1 : n2;
}

static void auxInsertar(TInfo i, TBinario &b){
  if (b!=NULL){
    if (natInfo(b->dato)>natInfo(i)){
     auxInsertar(i, b->izq);
    }
    else {
     auxInsertar(i, b->der);
   }
  }else {
    b = new repBinario;
    b->dato = i;
    b->der = b->izq= NULL;
      
  }
  
}

TBinario insertarEnBinario(TInfo i, TBinario b){
  auxInsertar(i,b);
  return b;	
}

TInfo mayor(TBinario b){
	TInfo res;
	if(derecho(b)!=NULL){
		res=mayor(b->der);
	}else{
		res=b->dato;
	}
	return res; 	
}

TBinario removerMayor(TBinario b){
	if (b->der == NULL){
		TBinario izq = b->izq;
		delete(b);
		b= izq;
	}else{
		b->der = removerMayor(b->der);
	}
	return b;
}

static void auxiliarDeRemBinario(nat elem, TBinario &b){
  
    if(natInfo(b->dato)<elem){
      auxiliarDeRemBinario(elem, b->der);
    }else if(natInfo(b->dato)>elem){
      auxiliarDeRemBinario(elem,b->izq);
    }else{
      TBinario aBorrar=b;
      if(b->izq==NULL){
        b=b->der;
      }else if(b->der==NULL){
        b=b->izq;
	  }else{
        TBinario ultimo=crearBinario();
        ultimo=insertarEnBinario(mayor(b->izq),ultimo);
        ultimo->izq=removerMayor(b->izq);
        ultimo->der=b->der;
        b=ultimo;
      }
      aBorrar->der=aBorrar->izq=NULL;
      liberarBinario(aBorrar);
      
    }
  
}  

TBinario removerDeBinario(nat elem, TBinario b){
  auxiliarDeRemBinario(elem,b);
  return b;
}

static TBinario liberarBin(TBinario &b){
	if(b!=NULL){
		b->izq = liberarBin(b->izq);
		b->der= liberarBin(b->der);
		liberarInfo(b->dato);
		delete b;
		b= NULL;
	}
	return b;
}

void liberarBinario(TBinario b){
	liberarBin(b);
	delete(b);
}

bool esVacioBinario(TBinario b){
		return b==NULL;
}

static bool cont(TBinario b, int *altura) {
 int ramaIzquierdaA=0,ramaDerechaA=0;
 int izquierdita=0,derechita=0;
 if(b==NULL){
    *altura=0;
    return 1;
 }

 izquierdita = cont(b->izq, &ramaIzquierdaA);
 derechita = cont(b->der, &ramaDerechaA);

 *altura= (ramaIzquierdaA > ramaDerechaA? ramaIzquierdaA: ramaDerechaA)+1;

 if ((ramaIzquierdaA-ramaDerechaA)>1 || (ramaDerechaA-ramaIzquierdaA)>1) return 0;
 else return (izquierdita && derechita);
} 	     

bool esAvl(TBinario b){
	int altura=0;
	return cont(b, &altura);
	
}

TInfo raiz(TBinario b){
	return b->dato;
}

TBinario izquierdo(TBinario b){
	
return b->izq;	
}

TBinario derecho(TBinario b){
	
return b->der;	
}

TBinario buscarSubarbol(nat elem, TBinario b){
	
	TBinario res;
	if (esVacioBinario(b))
		res = crearBinario();
	else {
		
		if(elem<natInfo(raiz(b)))
			res = buscarSubarbol(elem, izquierdo(b));
		else if(elem>natInfo(raiz(b)))
			res = buscarSubarbol(elem,derecho(b));
		else
			res=b;
	}
	return res;	
}

nat alturaBinario(TBinario b){
	if(esVacioBinario(b)) return 0;
	else return 1 + maximo(alturaBinario(b->der), alturaBinario(b->izq));	
}

nat cantidadBinario(TBinario b){
	if(!esVacioBinario(b)) return 1+ cantidadBinario(b->izq) + cantidadBinario(b->der);
	else return 0; 
}

double suma_ultimos_positivos_aux(nat &i, TBinario b){
  double suma;
  if(!esVacioBinario(b) && i>0){
    suma=suma_ultimos_positivos_aux(i, b->der);
    if(realInfo(b->dato) > 0 && i>0){
      suma=suma+realInfo(b->dato);
      i--;
    }
    suma=suma+suma_ultimos_positivos_aux(i, b->izq);
    
    return suma;
  }else
  return 0;
}

double sumaUltimosPositivos(nat i, TBinario b){
   return suma_ultimos_positivos_aux(i,b);
}

static TCadena linealization(TBinario b, TCadena res){
	if(b){
		res=linealization(b->izq,res);
		TInfo copia=copiaInfo(b->dato);
		res=insertarAlFinal(copia,res);
		res=linealization(b->der,res);
	}
	return res;
}

TCadena linealizacion(TBinario b){
	TCadena res = crearCadena();
	return linealization(b,res);
}

 static bool existe(TBinario b, int cota){
	bool valor = false;
	if (!esVacioBinario(b)){
		if (realInfo(b->dato) < cota) valor = true;
		else valor = existe(b->izq,cota) || existe(b->der,cota); 
	}
	return valor;
}

TBinario menores(double cota, TBinario b){
	if (!esVacioBinario(b)){
                if (esVacioBinario(b->izq) && esVacioBinario(b->der)){
                        if (realInfo(b->dato) < cota) {
                                TBinario arrowsito = new repBinario;
                                arrowsito->dato = copiaInfo(b->dato);
                                arrowsito->izq = arrowsito->der = NULL;
                                return arrowsito;
                        }else return NULL;
                }else if (realInfo(b->dato) < cota){
                        TBinario arrowsito = new repBinario;
                        arrowsito->dato = copiaInfo(b->dato);
                        arrowsito->izq = menores(cota, b->izq);
                        arrowsito->der = menores(cota, b->der);
                        return arrowsito;
                }else if (!existe(b->der,cota)){
                        TBinario arrowsito = menores(cota, b->izq);
                        return arrowsito;
                }
				else if (!existe(b->izq,cota)){
                        TBinario arrowsito = menores(cota, b->der);
                        return arrowsito;
                }else {
                        TBinario arrowsito = new repBinario;
                        arrowsito->izq=menores(cota,b->izq);
                        arrowsito->dato=mayor(arrowsito->izq);
                        arrowsito->izq=removerMayor(arrowsito->izq);
                        arrowsito->der=menores(cota, b->der);
                        return arrowsito;

                }
        }else return NULL;	
} 
 
 static void auxImp(TBinario z, int level){
	if(!esVacioBinario(z)){
		auxImp(z->der, level + 1);
		int i=0;
		while (i<level){
			printf("-");
			i++;
		}
		char* linternaverde = infoATexto(z->dato);
		printf("%s\n", linternaverde);
		delete[] linternaverde;
		auxImp(z->izq, level+1);
	}
}

void imprimirBinario(TBinario b){
	printf("\n");
	auxImp(b, 0);
}

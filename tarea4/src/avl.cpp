//52139037
#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/info.h"
#include <stdio.h>  
#include "../include/pila.h"
#include "../include/colaAvls.h"
#include "../include/iterador.h"
#include "limits.h"

struct repAvl{
	nat dato;
	nat altura;
	nat cantidad;
	TAvl izq, der;
};

struct avlUltimo{
	TAvl avl;
	int ultimo;
};

TAvl crearAvl(){ return NULL; }

bool estaVacioAvl(TAvl avl){ return avl == NULL; }

void liberarAvl(TAvl avl) {
	if (avl!=NULL){
		liberarAvl(avl->izq);
		liberarAvl(avl->der);
		delete avl;
	}
}

nat raizAvl(TAvl avl) {
	return avl->dato;
}

static int elMayorDe(int a, int b){
	return (a>b)? a: b;
}
static void giroHaciaLaDerecha(TAvl &avl){
	//terminada
    
	TAvl I = avl->izq;
    TAvl D = I->der;
    
    avl->izq = D;
    I->der = avl;
    avl->cantidad =(cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der))+1;
    I->cantidad = (cantidadEnAvl(I->izq) + cantidadEnAvl(I->der))+1;
    avl->altura = elMayorDe(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
    I->altura = elMayorDe(alturaDeAvl(I->izq),alturaDeAvl(I->der))+1;
    avl = I;
}

static void giroHaciaLaIzquierda(TAvl &avl){
	//terminada
    TAvl I =avl->der;
	TAvl D = I->izq;
    avl->der = D;
    
    I->izq = avl;
    avl->cantidad =(cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der))+1;
    I->cantidad = (cantidadEnAvl(I->izq) + cantidadEnAvl(I->der))+1;
    avl->altura = elMayorDe(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
    I->altura = elMayorDe(alturaDeAvl(I->izq),alturaDeAvl(I->der))+1;
    avl = I;
    }

TAvl insertarEnAvl(nat elem, TAvl avl){
	//terminada
	if (avl != NULL){
		if (elem >= avl->dato){
            avl->der = insertarEnAvl(elem ,avl->der);
            avl->altura = elMayorDe(alturaDeAvl(izqAvl(avl)),alturaDeAvl(derAvl(avl)))+1;
            avl->cantidad = avl->cantidad +1;

            int aux = (alturaDeAvl(izqAvl(avl)) - alturaDeAvl(derAvl(avl)));
            if (aux<-1){
                if (alturaDeAvl(avl->der->der) <= alturaDeAvl(avl->der->izq)){
                    giroHaciaLaDerecha(avl->der);
                    giroHaciaLaIzquierda(avl);
                }else{               
					giroHaciaLaIzquierda(avl);
                    }
            }
        }else{
			avl->izq = insertarEnAvl(elem ,avl->izq);
            avl->altura = elMayorDe(alturaDeAvl(derAvl(avl)),alturaDeAvl(izqAvl(avl)))+1;
            avl->cantidad = avl->cantidad +1;
            int aux =(alturaDeAvl(izqAvl(avl)) - alturaDeAvl(derAvl(avl)));
            if (aux > 1){
                if (alturaDeAvl(avl->izq->izq) > alturaDeAvl(avl->izq->der)){
                    giroHaciaLaDerecha(avl);
                }else{
                    giroHaciaLaIzquierda(avl->izq);
                    giroHaciaLaDerecha(avl);
                    }
                }
        }
        
    }else{
        avl = new repAvl;
        avl->dato = elem ;
        avl->izq = avl->der = NULL;
        avl->altura = 1;
        avl->cantidad = 1;
    }
    return avl ;
}

TAvl buscarEnAvl(nat elem, TAvl avl){
	//terminada
	TAvl password;
	if (!estaVacioAvl(avl)){
		if(elem <raizAvl(avl))
			password = buscarEnAvl(elem, izqAvl(avl));
		else if(elem > raizAvl(avl))
			password = buscarEnAvl(elem, derAvl(avl));
		else
			password=avl;
	}
		
	else {
		password = crearAvl();
	}
	return password;
}

TAvl izqAvl(TAvl avl){
	return avl->izq;
}


TAvl derAvl(TAvl avl){
	return avl->der;
}


nat cantidadEnAvl(TAvl avl){
	if(avl == NULL) return 0;
	else
		return avl->cantidad;
}


nat alturaDeAvl(TAvl avl){
	if(avl == NULL) return 0;
	else
		return avl->altura;
}


static void funcionAuxiliarParaEnOrdenAvl(TAvl &avl,TIterador laPropiaSolucion){
	//terminada
  if(avl!= NULL){
    funcionAuxiliarParaEnOrdenAvl(avl->izq,laPropiaSolucion);
    laPropiaSolucion = agregarAIterador(avl->dato,laPropiaSolucion);
    funcionAuxiliarParaEnOrdenAvl(avl->der,laPropiaSolucion);
  }
}

TIterador enOrdenAvl(TAvl avl){
	//terminada
    TIterador laPropiaSolucion;
    laPropiaSolucion= crearIterador();
    funcionAuxiliarParaEnOrdenAvl(avl,laPropiaSolucion);
  return laPropiaSolucion;
}

 static TAvl funcionAuxiliarAvlRec(nat *infos, int sup, int inf){
	 //terminada
	TAvl password;
	if (inf <= sup){
		nat medio = (inf+sup)/2;
		password = new repAvl;
		password->dato = infos[medio];
		password->izq = funcionAuxiliarAvlRec(infos, medio - 1, inf);
		password->der = funcionAuxiliarAvlRec(infos, sup, medio + 1);
		password->cantidad = cantidadEnAvl(izqAvl(password)) + cantidadEnAvl(derAvl(password)) + 1;
		password->altura = 1 + elMayorDe(alturaDeAvl(izqAvl(password)), alturaDeAvl(derAvl(password)) );
	}else{
		password = NULL;
		
	}
	return password;
}

TAvl arregloAAvl(nat *elems, nat n){
	nat fin=n-1;
	return funcionAuxiliarAvlRec(elems, fin, 0);
}

static avlUltimo funcionAuxiliarAvlMinAux(nat primero, nat alturita){
	//terminada
  avlUltimo laPropiaSolucion;
  if (alturita ==0){
    laPropiaSolucion.avl = NULL;
    laPropiaSolucion.ultimo = primero - 1;
  }else  if (alturita== 1){
	laPropiaSolucion.avl = new repAvl;
    
    laPropiaSolucion.avl->altura = 1;
	laPropiaSolucion.avl->cantidad = 1;
	laPropiaSolucion.avl -> dato = primero;
    laPropiaSolucion.avl->izq = NULL;
	laPropiaSolucion.avl->der = NULL;
    laPropiaSolucion.ultimo = primero;   
  }else{
    laPropiaSolucion.avl = new repAvl;
    avlUltimo izq = funcionAuxiliarAvlMinAux(primero,alturita-1);
    laPropiaSolucion.avl->dato =izq.ultimo +1;
    laPropiaSolucion.avl->izq = izq.avl;
    avlUltimo der = funcionAuxiliarAvlMinAux(izq.ultimo+2,alturita-2);
    laPropiaSolucion.avl->der= der.avl;
    laPropiaSolucion.ultimo = der.ultimo;
   
    laPropiaSolucion.avl->cantidad = cantidadEnAvl(izqAvl(laPropiaSolucion.avl)) + cantidadEnAvl(derAvl(laPropiaSolucion.avl)) + 1;
	 laPropiaSolucion.avl->altura = elMayorDe(alturaDeAvl(laPropiaSolucion.avl->izq), alturaDeAvl(laPropiaSolucion.avl->der)) + 1;
  }
  return laPropiaSolucion;
}


TAvl avlMin(nat alturita){
	//terminada
  avlUltimo  laPropiaSolucion = funcionAuxiliarAvlMinAux(1,alturita);
  return laPropiaSolucion.avl;
}

void imprimirAvl(TAvl avl){
	//terminada
	if (avl != NULL){
		TColaAvls bombom = crearColaAvls();
		encolar(avl, bombom);
		encolar(NULL, bombom);
		TPila pilacincovolts=crearPila(cantidadEnAvl(avl)+alturaDeAvl(avl));
		bool terminar=false;
		while (!terminar && !estaVaciaColaAvls(bombom)){
			TAvl arbol = frente(bombom);
			if (arbol == NULL){
				
				encolar(NULL, bombom);
				apilar(INT_MAX, pilacincovolts);
				desencolar(bombom);
				if(frente(bombom)==NULL){
				terminar=true;
				}
			}else{
				apilar(raizAvl(arbol),pilacincovolts);
				if (arbol->der != NULL)
					encolar(arbol->der, bombom);
				if (arbol->izq != NULL)
					encolar(arbol->izq, bombom);
					
				desencolar(bombom);
			}
		}
		desapilar(pilacincovolts);
		while(!estaVaciaPila(pilacincovolts)){
				
                	if(cima(pilacincovolts)!=INT_MAX){
						printf("%d ", cima(pilacincovolts));
					}else{   
							printf("\n");
                        	
                    }
            
                        desapilar(pilacincovolts);
		}
		printf("\n");
		liberarColaAvls(bombom);
		liberarPila(pilacincovolts);
		
	}
}



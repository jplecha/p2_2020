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


static void funcionAuxiliarParaEnOrdenAvl(TAvl &avl,TIterador res){
	//terminada
  if(avl!= NULL){
    funcionAuxiliarParaEnOrdenAvl(avl->izq,res);
    res = agregarAIterador(avl->dato,res);
    funcionAuxiliarParaEnOrdenAvl(avl->der,res);
  }
}

TIterador enOrdenAvl(TAvl avl){
	//terminada
    TIterador res;
    res= crearIterador();
    funcionAuxiliarParaEnOrdenAvl(avl,res);
  return res;
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

static avlUltimo funcionAuxiliarAvlMinAux(nat primero, nat h){
	//terminada
  avlUltimo res;
  if (h ==0){
    res.avl = NULL;
    res.ultimo = primero - 1;
  }else  if (h== 1){
	res.avl = new repAvl;
    
    res.avl->altura = 1;
	res.avl->cantidad = 1;
	res.avl -> dato = primero;
    res.avl->izq = NULL;
	res.avl->der = NULL;
    res.ultimo = primero;   
  }else{
    res.avl = new repAvl;
    avlUltimo izq = funcionAuxiliarAvlMinAux(primero,h-1);
    res.avl->dato =izq.ultimo +1;
    res.avl->izq = izq.avl;
    avlUltimo der = funcionAuxiliarAvlMinAux(izq.ultimo+2,h-2);
    res.avl->der= der.avl;
    res.ultimo = der.ultimo;
   
    res.avl->cantidad = cantidadEnAvl(izqAvl(res.avl)) + cantidadEnAvl(derAvl(res.avl)) + 1;
	 res.avl->altura = elMayorDe(alturaDeAvl(res.avl->izq), alturaDeAvl(res.avl->der)) + 1;
  }
  return res;
}


TAvl avlMin(nat h){
	//terminada
  avlUltimo  res = funcionAuxiliarAvlMinAux(1,h);
  return res.avl;
}

void imprimirAvl(TAvl avl){
	//terminada
	if (avl != NULL){
		TColaAvls trasero = crearColaAvls();
		encolar(avl, trasero);
		encolar(NULL, trasero);
		TPila alcalina=crearPila(cantidadEnAvl(avl)+alturaDeAvl(avl));
		bool terminar=false;
		while (!terminar && !estaVaciaColaAvls(trasero)){
			TAvl arbol = frente(trasero);
			if (arbol == NULL){
				
				encolar(NULL, trasero);
				apilar(INT_MAX, alcalina);
				desencolar(trasero);
				if(frente(trasero)==NULL){
				terminar=true;
				}
			}else{
				apilar(raizAvl(arbol),alcalina);
				if (arbol->der != NULL)
					encolar(arbol->der, trasero);
				if (arbol->izq != NULL)
					encolar(arbol->izq, trasero);
					
				desencolar(trasero);
			}
		}
		desapilar(alcalina);
		while(!estaVaciaPila(alcalina)){
				
                	if(cima(alcalina)!=INT_MAX){
						printf("%d ", cima(alcalina));
					}else{   
							printf("\n");
                        	
                    }
            
                        desapilar(alcalina);
		}
		printf("\n");
		liberarColaAvls(trasero);
		liberarPila(alcalina);
		
	}
}



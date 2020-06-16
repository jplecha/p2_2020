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

static int maximo(int a, int b){
	return (a>b)? a: b;
}
static void rotacionD(TAvl &avl){
    TAvl I = avl->izq;
    TAvl D = I->der;
    I->der = avl;
    avl->izq = D;
    
    avl->cantidad =(cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der))+1;
    I->cantidad = (cantidadEnAvl(I->izq) + cantidadEnAvl(I->der))+1;
    avl->altura = maximo(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
    I->altura = maximo(alturaDeAvl(I->izq),alturaDeAvl(I->der))+1;
    avl = I;
}

static void rotacionI(TAvl &avl){
    TAvl I =avl->der;
    TAvl D = I->izq;
    I->izq = avl;
    avl->der = D;
    
    avl->cantidad =(cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der))+1;
    I->cantidad = (cantidadEnAvl(I->izq) + cantidadEnAvl(I->der))+1;
    avl->altura = maximo(alturaDeAvl(avl->izq),alturaDeAvl(avl->der))+1;
    I->altura = maximo(alturaDeAvl(I->izq),alturaDeAvl(I->der))+1;
    avl = I;
    }

TAvl insertarEnAvl(nat elem, TAvl avl){
	if (avl == NULL){
        avl = new repAvl;
        avl->dato = elem ;
        avl->izq = avl->der = NULL;
        avl->altura = 1;
        avl->cantidad = 1;
    }else{
        if (elem < avl->dato){
            avl->izq = insertarEnAvl(elem ,avl->izq);
            avl->altura = maximo(alturaDeAvl(izqAvl(avl)),alturaDeAvl(derAvl(avl)))+1;
            avl->cantidad = avl->cantidad +1;
            int aux =(alturaDeAvl(izqAvl(avl)) - alturaDeAvl(derAvl(avl)));
            if (aux > 1){
                if (alturaDeAvl(avl->izq->izq) > alturaDeAvl(avl->izq->der)){
                    rotacionD(avl);
                }else{
                    rotacionI(avl->izq);
                    rotacionD(avl);
                    }
                }
        }else{
            avl->der = insertarEnAvl(elem ,avl->der);
            avl->altura = maximo(alturaDeAvl(izqAvl(avl)),alturaDeAvl(derAvl(avl)))+1;
            avl->cantidad = avl->cantidad +1;

            int aux = (alturaDeAvl(izqAvl(avl)) - alturaDeAvl(derAvl(avl)));
            if (aux<-1){
                if (alturaDeAvl(avl->der->der) > alturaDeAvl(avl->der->izq)){
                    rotacionI(avl);
                }else{
                    rotacionD(avl->der);
                    rotacionI(avl);

                    }
            }
        }
    }
    return avl ;
    //modificar
}

/*
  Devuelve el subárbol cuya raíz es 'elem'.
  Si ningún nodo cumple esa condición devuelve el árbol vacío.
  El 'TAvl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(log n), siendo 'n' la cantidad
  de elementos de 'avl'.
 */
TAvl buscarEnAvl(nat elem, TAvl avl){
	TAvl larespu;
	if (estaVacioAvl(avl))
		larespu = crearAvl();
	else {
		if(elem <raizAvl(avl))
			larespu = buscarEnAvl(elem, izqAvl(avl));
		else if(elem > raizAvl(avl))
			larespu = buscarEnAvl(elem, derAvl(avl));
		else
			larespu=avl;
	}
	return larespu;
}

/*
  Devuelve el subárbol izquierdo de 'avl'.
  Precondición: ! estaVacioAvl(TAvl).
  El 'TAvl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl izqAvl(TAvl avl){
	return avl->izq;
}

/*
  Devuelve el subárbol derecho de 'avl'.
  Precondición: ! estaVacioAvl(TAvl).
  El 'TAvl' resultado comparte memoria con el parámetro.
  El tiempo de ejecución en el peor caso es O(1).
 */
TAvl derAvl(TAvl avl){
	return avl->der;
}

/*
  Devuelve la cantidad de elementos en 'avl'.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat cantidadEnAvl(TAvl avl){
	if(avl == NULL) return 0;
	else
		return avl->cantidad;
}

/*
  Devuelve la altura de 'avl'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución en el peor caso es O(1).
 */
nat alturaDeAvl(TAvl avl){
	if(avl == NULL) return 0;
	else
		return avl->altura;
}

/*
  Devuelve un 'TIterador' de los elementos de 'c'.
  En la recorrida del iterador devuelto los elementos aparecerán en orden
  creciente.
  El 'TIterador' resultado no comparte memoria con 'avl'.
  El tiempo de ejecución en el peor caso es O(n) siendo 'n' la cantidad de
  elementos de 'avl'.
 */
static void enOrdenAvlAux(TIterador res, TAvl &avl){
  if(avl!= NULL){
    enOrdenAvlAux(res,avl->izq);
    res = agregarAIterador(avl->dato,res);
    enOrdenAvlAux(res, avl->der);
  }
 
}

TIterador enOrdenAvl(TAvl avl){
    TIterador res;
    res= crearIterador();
    enOrdenAvlAux(res,avl);
  return res;
}

/*
  Devuelve un 'TAvl' con los 'n' elementos que están en el rango [0 .. n - 1]
  del arreglo 'elems'.
  Precondiciones:
  - n > 0
  - Los elementos están ordenados de manera creciente estricto
  (creciente y sin  repetidos).
  En cada nodo del árbol resultado la cantidad de elementos de su subárbol
  izquierdo es igual a, o 1 menos que, la cantidad de elementos de su subárbol
  derecho.
  El tiempo de ejecución en el peor caso es O(n).
 */
 static TAvl a2avl_rec(nat *infos, int inf, int sup){
	TAvl larespu;
	if (inf > sup)
		larespu = NULL;
	else{
		nat medio = (inf+sup)/2;
		larespu = new repAvl;
		larespu->dato = infos[medio];
		larespu->izq = a2avl_rec(infos, inf, medio - 1);
		larespu->der = a2avl_rec(infos, medio + 1, sup);
		larespu->cantidad = cantidadEnAvl(izqAvl(larespu)) + cantidadEnAvl(derAvl(larespu)) + 1;
		larespu->altura = 1 + maximo(alturaDeAvl(izqAvl(larespu)), alturaDeAvl(derAvl(larespu)) );
	}
	return larespu;
}

TAvl arregloAAvl(nat *elems, nat n){
	return a2avl_rec(elems, 0, n - 1);
}

/*
  Devuelve un 'TAvl' de altura 'h' con 'n' nodos, siendo 'n' la mínima cantidad
  de elementos que puede tener un 'TAvl' de altura 'h'.
  Los elementos van desde 1 hasta 'n'.
  En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el
  subárbol izquierdo.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución en el peor caso es O(n).
  Ver ejemplos en la letra.
 */
struct ultimoAvl{
	TAvl avl;
	int ultimo;
};

//modificar
static ultimoAvl avlMinAux(nat h, nat primero){
  ultimoAvl res;
  if (h ==1){
    res.avl = new repAvl;
    res.avl -> dato = primero;
    res.avl->cantidad = 1;
    res.avl->altura = 1;
    res.avl->der = NULL;
    res.avl->izq = NULL;
    res.ultimo = primero;
  }else  if (h== 0){
    res.avl = NULL;
    res.ultimo = primero - 1;
  }else{
    res.avl = new repAvl;
    ultimoAvl izq = avlMinAux(h-1,primero);
    res.avl->dato =izq.ultimo +1;
    res.avl->izq = izq.avl;
    ultimoAvl der = avlMinAux(h-2,izq.ultimo+2);
    res.avl->der= der.avl;
    res.ultimo = der.ultimo;
    res.avl->altura = maximo(alturaDeAvl(res.avl->izq), alturaDeAvl(res.avl->der)) + 1;
    res.avl->cantidad = cantidadEnAvl(izqAvl(res.avl)) + cantidadEnAvl(derAvl(res.avl)) + 1;
  }
  return res;
}

//modificar
TAvl avlMin(nat h){
  ultimoAvl  res = avlMinAux(h,1);
  return res.avl;
}
/*
  Imprime los elementos de cada nivel de 'avl'.
  Imprime una línea por nivel, primero el más profundo y al final el que
  corresponde a la raíz.
  Cada nivel se imprime en orden creciente. Se debe dejar un espacio en
  blanco después de cada número.
  Se puede asumir que 0 no es ningún elemento.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'TAvl'.
  Ver ejemplos en la letra.
 */
void imprimirAvl(TAvl avl){
	if (avl != NULL){
		TColaAvls trasero = crearColaAvls();
		encolar(avl, trasero);
		encolar(NULL, trasero);
		bool terminar=false;
		TPila alcalina=crearPila(cantidadEnAvl(avl)+alturaDeAvl(avl));
		while (!estaVaciaColaAvls(trasero) && !terminar){
			TAvl arbol = frente(trasero);
			if (arbol != NULL){
				apilar(raizAvl(arbol),alcalina);
				if (arbol->der != NULL)
					encolar(arbol->der, trasero);
				if (arbol->izq != NULL)
					encolar(arbol->izq, trasero);
					
				desencolar(trasero);
			}else{
				encolar(NULL, trasero);
				apilar(INT_MAX, alcalina);
				desencolar(trasero);
				if(frente(trasero)==NULL){
				terminar=true;
				}
			}
		}
		desapilar(alcalina);
		while(!estaVaciaPila(alcalina)){
				
                	if(cima(alcalina)==INT_MAX){
				printf("\n");
			}else{      
                        	printf("%d ", cima(alcalina));
                        }
            
                        desapilar(alcalina);
		}
		printf("\n");
		liberarPila(alcalina);
		liberarColaAvls(trasero);
	}
}



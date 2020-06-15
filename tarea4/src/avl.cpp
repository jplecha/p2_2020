//52139037
#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/info.h"
#include <stdio.h>  
#include "../include/pila.h"
#include "../include/colaAvls.h"
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

static int max(int a, int b){
	return (a>b)? a: b;
}
static void rotarDer(TAvl &avl){
	TAvl unaesquina = avl->izq;
	TAvl zanahoria = unaesquina->der;
	unaesquina->der = avl;
	avl->izq = zanahoria;
	avl->altura = max(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
	avl->cantidad = cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der) + 1;
	unaesquina->altura = max(alturaDeAvl(unaesquina->izq), alturaDeAvl(unaesquina->der)) + 1;
	unaesquina->cantidad = cantidadEnAvl(unaesquina->izq) + cantidadEnAvl(unaesquina->der) + 1;	
	avl = unaesquina;	
}
static void rotarIzq(TAvl &avl){
	TAvl unaesquina = avl->der;
	TAvl zanahoria = unaesquina->izq;
	unaesquina->izq = avl;
	avl->der = zanahoria;
	avl->altura = max(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
	avl->cantidad = cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der) + 1;	
	unaesquina->altura = max(alturaDeAvl(unaesquina->izq), alturaDeAvl(unaesquina->der)) + 1;
	unaesquina->cantidad = cantidadEnAvl(unaesquina->izq) + cantidadEnAvl(unaesquina->der) + 1;	
	avl = unaesquina;
}

TAvl insertarEnAvl(nat elem, TAvl avl){
	TAvl res;
	if(avl==NULL){
		res=new repAvl;
		res->dato=elem;
		res->izq=avl->der=NULL;
		res->altura=1;
		res->cantidad=1;
	}else if(elem<raizAvl(avl)){
			res=insertarEnAvl(elem, avl->izq);
			avl->altura = max(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
			avl->cantidad = cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der) + 1;
			int num = alturaDeAvl(avl->izq) - alturaDeAvl(avl->der);
			if (num>1){
				if(alturaDeAvl(avl->izq->der)> alturaDeAvl(avl->izq->izq)){
					rotarIzq(avl->izq);
					rotarDer(avl); 
				}
				else {
					rotarDer(avl);		
				}		
			}	
    }
    else{
		res=insertarEnAvl(elem, avl->der);
		avl->altura = max(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) + 1;
		avl->cantidad = cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der) + 1;
		int num = alturaDeAvl(avl->der) - alturaDeAvl(avl->izq);
		if (num>1){
			if(alturaDeAvl(avl->der->izq)> alturaDeAvl(avl->der->der)){
				rotarDer(avl->der);
				rotarIzq(avl);		
			}
			else {
				rotarIzq(avl);
			}
		}		
    }
	return res;
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
 
 static TIterador *en_orden_rec(TIterador *res, nat &tope, TAvl avl){
	if (!estaVacioAvl(avl)){
		res = en_orden_rec(res, tope, izqAvl(avl));
		res[tope] = raizAvl(avl);
		tope++;
		res = en_orden_rec(res, tope, derAvl(avl));
	}
	return res;
}

TIterador enOrdenAvl(TAvl avl){
	TIterador *larespu;
	if (estaVacioAvl(avl))
		larespu = NULL;
	else{
		larespu = new TInfo[cantidadEnAvl(avl)];
		nat tope = 0;
		larespu = en_orden_rec(larespu, tope, avl);
	}
	return larespu;
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
 static TAvl a2avl_rec(TInfo *infos, int inf, int sup){
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
		larespu->altura = 1 + max(alturaDeAvl(izqAvl(larespu)), alturaDeAvl(derAvl(larespu)) );
	}
	return larespu;
}

TAvl arregloAAvl(nat *elems, nat n){
	return a2avl_rec(infos, 0, n - 1);
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
 static avlUltimo avl_min_rec(nat h, nat primero){
        avlUltimo larespu;
        if (h == 0){
                larespu.avl = NULL;
                larespu.ultimo = primero - 1;
        }
        else if (h == 1){
                larespu.ultimo = primero;
                char *real = new char[1];
                real[0] = '\0';
                TInfo agrego = crearInfo(primero, real);
                larespu.avl = new repAvl;
                larespu.avl->dato = agrego;
                larespu.avl->altura = 1;
                larespu.avl->cantidad = 1;
                larespu.avl->izq = larespu.avl->der = NULL;
        }
        else{
                int num;
                avlUltimo avlpri=avl_min_rec(h-1,primero);
                avlUltimo avlseg=avl_min_rec(h-2,1);
                larespu.ultimo = cantidadEnAvl(avlpri.avl) + cantidadEnAvl(avlseg.avl) + primero;
				liberar_avl(avlseg.avl);
                if (h==2)
                        num = natInfo(raizAvl(avlpri.avl)) + 1;
                else
                        num = avlpri.ultimo + 1;
                char *poner = new char[1];
                poner[0] = '\0';
                TInfo agrego = crearInfo(num, poner);
                larespu.avl = new repAvl;
                larespu.avl->dato = agrego;
                larespu.avl->izq = avlpri.avl;
                larespu.avl->der = avl_min_rec(h-2,natInfo(raizAvl(larespu.avl))+1).avl;
                larespu.avl->altura = max(alturaDeAvl(larespu.avl->izq), alturaDeAvl(larespu.avl->der)) + 1;
                larespu.avl->cantidad = cantidadEnAvl(larespu.avl->izq) + cantidadEnAvl(larespu.avl->der) + 1;
        }


        return larespu;
}

TAvl avlMin(nat h){
	avlUltimo larespu = avl_min_rec(h, 1);
	return larespu.avl;
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
		while (!estaVaciaPila(trasero) && !terminar){
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



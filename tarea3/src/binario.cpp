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

/*
  Inserta 'i' en 'b' respetando la propiedad de orden definida.
  Devuelve 'b'.
  Precondición: esVacioBinario(buscarSubarbol(natInfo(i), b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
 
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

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TInfo mayor(TBinario b){
	TInfo res;
	if(derecho(b)!=NULL){
		res=mayor(b->der);
	}else{
		res=b->dato;
	}
	return res; 	
}
/*
  Remueve el nodo en el que se localiza el elemento mayor de 'b'
  (libera la memoria  asignada al nodo, pero no la del elemento).
  Devuelve 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
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
/*
  Remueve de 'b' el nodo en el que el componente natural de su elemento es
  'elem'.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Devuelve 'b'.
  Precondición: !esVacioBinario(buscarSubarbol(elem, b).
  Libera la memoria del nodo y del elemento.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
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
/*
  Libera la memoria asociada a 'b' y todos sus elementos.
  El tiempo de ejecución es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
void liberarBinario(TBinario b){
	liberarBin(b);
	delete(b);
}
/*
  Devuelve 'true' si y solo si 'b' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool esVacioBinario(TBinario b){
		return b==NULL;
}
/*
  Devuelve 'true' si y solo si cada nodo de 'b' cumple la condición de balanceo
  AVL. El árbol vacío cumple la condición.
  Un nodo cumple la condición de balanceo AVL si el valor absoluto de la
  diferencia de las alturas de sus subárboles izquierdo y derecho en menor o
  igual a 1.
  Cada nodo se puede visitar una sola vez.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
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

/*
  Devuelve el elemento asociado a la raíz de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TInfo raiz(TBinario b){
	return b->dato;
}
/*
  Devuelve el subárbol izquierdo de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TBinario izquierdo(TBinario b){
	
return b->izq;	
}

/*
  Devuelve el subárbol derecho de 'b'.
  Precondición: ! esVacioBinario(b).
  El tiempo de ejecución es O(1).
 */
TBinario derecho(TBinario b){
	
return b->der;	
}

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo
  componente natural es 'elem'.
  Si 'elem' no pertenece a 'b', devuelve el árbol vacío.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
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

/*
  Devuelve la altura de 'b'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
nat alturaBinario(TBinario b){
	if(esVacioBinario(b)) return 0;
	else return 1 + maximo(alturaBinario(b->der), alturaBinario(b->izq));	
}

/*
  Devuelve la cantidad de elementos de 'b'.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
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

/*
  Devuelve la suma de los componentes reales de los últimos 'i' elementos
  (considerados según la propiedad de orden de los árboles TBinario)
  de 'b' cuyos componentes reales sean mayores que 0.
  Si en 'b' hay menos de 'i' elementos que cumplan esa condición devuelve la
  suma de los componenetes reales de ellos.
  No se deben crear estructuras auxiliares.
  No se deben visitar nuevos nodos después que se hayan encontrado los
  'i' elementos.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
double sumaUltimosPositivos(nat i, TBinario b){
   return suma_ultimos_positivos_aux(i,b);
}

/*
  Devuelve una 'TCadena' con los elementos de 'b' en orden lexicográfico
  creciente según sus componentes naturales.
  La 'TCadena' devuelta no comparte memoria con 'b'.
  El tiempo de ejecución es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
static TCadena linealization(TCadena res,TBinario b){
	if(b){
		res=linealization(res,b->izq);
		TInfo copia=copiaInfo(b->dato);
		res=insertarAlFinal(copia,res);
		res=linealization(res,b->der);
	}
	return res;
}

TCadena linealizacion(TBinario b){
	TCadena res = crearCadena();
	return linealization(res,b);
}

/*
  Devuelve un árbol con copias de los elementos de 'b' que cumplen la condición
  "realInfo(elemento) < cota".
  La estructura del árbol resultado debe ser análoga a la de 'b'. Esto
  significa que dados dos nodos 'U' y 'V' de 'b' en los que se cumple la
  condición y tal que 'U' es ancestro de 'V', en el árbol resultado la copia de
  'U' debe ser ancestro de la copia de 'V' cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
  en el caso en el que en un nodo 'V' no se cumple la condición y en sus dos
  subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (según la propiedad de orden definida) de los que
  cumplen la condición en el subárbol izquierdo de 'V' deberá ser ancestro de
  las copias de todos los descendientes de 'V' que cumplen la condición.
  Ver ejemplos en la letra.
  El árbol resultado no comparte memoria con 'b'. *)
  El tiempo de ejecución es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
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
                                TBinario larespu = new repBinario;
                                larespu->dato = copiaInfo(b->dato);
                                larespu->izq = larespu->der = NULL;
                                return larespu;
                        }else return NULL;
                }else if (realInfo(b->dato) < cota){
                        TBinario larespu = new repBinario;
                        larespu->dato = copiaInfo(b->dato);
                        larespu->izq = menores(cota, b->izq);
                        larespu->der = menores(cota, b->der);
                        return larespu;
                }else if (!existe(b->der,cota)){
                        TBinario larespu = menores(cota, b->izq);
                        return larespu;
                }
				else if (!existe(b->izq,cota)){
                        TBinario larespu = menores(cota, b->der);
                        return larespu;
                }else {
                        TBinario larespu = new repBinario;
                        larespu->izq=menores(cota,b->izq);
                        larespu->dato=mayor(larespu->izq);
                        larespu->izq=removerMayor(larespu->izq);
                        larespu->der=menores(cota, b->der);
                        return larespu;

                }
        }else return NULL;	
}

/*
  Imprime los elementos de 'b', uno por línea, en orden descendente de la
  propiedad de orden de los árboles 'TBinario'.
  Antes del elemento imprime una cantidad de guiones igual a su profundidad.
  El elemento se imprime según la especificación dada en 'infoATexto'.
  La profundidad de la raíz es 0.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVacioBinario(b) solo se imprime el fin de línea.
  El tiempo de ejecución es O(n . log n) en promedio, siendo 'n' la cantidad
  de elementos de 'b'.
 */
 
 
 static void auxiliar_imprimir_binario(TBinario z, int estante){
	if(!esVacioBinario(z)){
		auxiliar_imprimir_binario(z->der, estante + 1);
		int i=0;
		while (i<estante){
			printf("-");
			i++;
		}
		char* superman = infoATexto(z->dato);
		printf("%s\n", superman);
		delete[] superman;
		auxiliar_imprimir_binario(z->izq, estante+1);
	}
}

void imprimirBinario(TBinario b){
	printf("\n");
	auxiliar_imprimir_binario(b, 0);
}

//52139037
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"
#include "../include/colaDePrioridad.h"
#include "../include/avl.h"
#include "../include/float.h"
#include <stdio.h>

static TCadena funcionAuxiliarUno(nat l, nat final, TBinario b, TCadena cadena){
  if(!esVacioBinario(b)){
    funcionAuxiliarUno(l+1,final, izquierdo(b),cadena); 
    if(l==final){
      cadena=insertarAlFinal(copiaInfo(raiz(b)),cadena);
    }
    funcionAuxiliarUno(l+1,final,derecho(b),cadena);
  }
  return cadena;
}

TCadena nivelEnBinario(nat l, TBinario b){
  TCadena cadena=crearCadena();
  funcionAuxiliarUno(1,l,b,cadena);
  
  return cadena;
}

nat longitud(TCadena cad){
	TLocalizador loc1=inicioCadena(cad);
	nat i=0;
	while(esLocalizador(loc1)) {
		i++;
		loc1=siguiente(loc1,cad);
	}
	return i;
}

 /*
  Devuelve un arreglo que indica a cuales vértices se puede llegar desde 'v'.
  El arreglo devuelto tiene tamaño N+1. La coordenada 0 no se tiene en cuenta.
  La coordenada 'i' (1 <= i <= N) es 'true' si y solo si el vértice 'i' es
  accesible desde 'v'.
  Precondición: 1 <= v <= N.

  Seudocódigo:
   - Inicializar cada coordenada del arreglo a devolver con 'false'
     (se considera cada vértice no accesible).
   - Pasar 'v' como parámetro a una función auxiliar. Esta función
     -- marca el parámetro como accesible desde 'v'.
     -- para cada vécino de su parámetro que todavía sea no accesible
        desde 'v' hace una llamada recursiva.
   - Devolver el arreglo.
 */
static void auxiliarAccesibles(ArregloBools &res, nat v, TGrafo g){
	TIterador aux=vecinos(v,g);
	res[v]=true;
	while(estaDefinidaActual(aux)){
		 if(res[actualEnIterador(aux)]==false)
			auxiliarAccesibles(res,actualEnIterador(aux),g);
		 aux=avanzarIterador(aux);
			
	}		
	
	liberarIterador(aux);
}
ArregloBools accesibles(nat v, TGrafo g){
	ArregloBools res=new bool[cantidadVertices(g)+1];
	for (nat i=0;i<cantidadVertices(g)+1;i++){
		res[i]=false;
	}
	
	auxiliarAccesibles(res,v,g);
	
		
	return res;
	
}

// nueva

/*
  Devuelve un arreglo con las longitudes de los caminos más cortos desde 'v'
  hasta cada vértice del grafo.
  El arreglo devuelto tiene tamaño N+1. La coordenada 0 no se tiene en cuenta.
  En la coordenada 'i' (1 <= i <= N) se devuelve la longitud del camino más
  corto desde 'v' hasta 'i'. Si 'i' no es accesible desde 'v' el valor de esa
  coordenada es DBL_MAX (definido en float.h)
  Precondición: 1 <= v <= N.

  Seudocódigo:
   - Crear colecciones 'C' y 'S', inicialmente vacías, de pares (u,du)
     donde 'u' representa un vértice y 'du' es la longitud del camino más
     corto desde 'v' hasta 'u'. El valor de 'du' en 'C' es provisorio
     mientras que en 'S' es definitivo.
   - Insertar (v,0) en 'C'.
   . Mientras 'C' no es vacía:
     -- se obtiene y remueve de 'C' el par (u, du) tal que 'du' es mínimo
        entre todos los pares de 'C'.
     -- se inserta ese par en 'S'.
     -- para cada vecino 'w' de 'u' que no está en S sea dw' = du + d(u,w),
        donde d(u,v) es la distancia entre 'u' y 'w'.
        Si 'w' no está en 'C' se inserta (w,dw') en 'C'.
        Si 'w' está en 'C' en el par (w,dw) y dw' < dw entoces se actualiza
        'C' con el par con (w,dw') en lugar de (w,dw).
   - Para cada vétice 'u' que no pertenece a 'S' se inserta en 'S' el par
     (u, infinito).
   - Devolver 'S'.

 */
ArregloDoubles longitudesCaminosMasCortos(nat v, TGrafo g){
	TColaDePrioridad C=crearCP(cantidadVertices(g)), S=crearCP(cantidadVertices(g));
	C = insertarEnCP(v,0,C);
	while(!estaVaciaCP(C)){
		nat u=prioritario(C);
		double du= prioridad(u,C);
		C=eliminarPrioritario(C);
		S=insertarEnCP(u,du,S);
		
		TIterador vec=vecinos(u,g);
		while(estaDefinidaActual(vec)){
			 nat w=actualEnIterador(vec);
			 nat dw=du+distancia(u,w,g);
			 if(!estaEnCP(w,C)) insertarEnCP(w,dw,C);
			 else if(!estaEnCP(w,C) && dw < prioridad(w,C)) C=actualizarEnCP(w,dw,C);
			 vec=avanzarIterador(vec);
		}		
	
		liberarIterador(vec);
	}
	ArregloDoubles res=new double[cantidadVertices(g)+1];
	for(nat i=1;i<=cantidadVertices(g);i++){
		if(!estaVaciaCP(C)){
			res[i]=prioridad(prioritario(C),C);
			C=eliminarPrioritario(C);
		}else{
			res[i]=DBL_MAX;
		}
	}
	return res ;
}

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2){
	//terminada
  if(!estaVacioConjunto(c2) && !estaVacioConjunto(c1)){
			int a, b, c;
			a=1; b=2;
			c=3;
			a=c+b+a;
			TConjunto conjuntounito = unionDeConjuntos(c1,c2);
			TConjunto conjuntodosito = diferenciaDeConjuntos(c1,c2);
			TConjunto conjuntotercito = diferenciaDeConjuntos(c2,c1);
			TConjunto conjuntocuartito = unionDeConjuntos(conjuntodosito,conjuntotercito);
			TConjunto resultadito = diferenciaDeConjuntos(conjuntounito,conjuntocuartito);			
			liberarConjunto(conjuntounito);
			liberarConjunto(conjuntotercito);
			liberarConjunto(conjuntocuartito);
			liberarConjunto(conjuntodosito);
			a++;
			b++;
			c++;
			//las variables estan al pedo? Revisar
			return resultadito;
  }else return crearConjunto();
}

bool esCamino(TCadena c, TBinario b){
	//terminada
	TLocalizador varAux=inicioCadena(c);
	while(b && varAux && natInfo(infoCadena(varAux,c)) == natInfo(raiz(b))){
		varAux=siguiente(varAux,c);
		if(varAux){
			natInfo(infoCadena(varAux,c))<=natInfo(raiz(b)) ? b=izquierdo(b) : b=derecho(b);
		}
	}
	return !varAux && !izquierdo(b) && !derecho(b);
}


bool pertenece(nat elem, TCadena cad){
	//terminada
	TLocalizador loc1=inicioCadena(cad);
	while(esLocalizador(loc1) && (natInfo(infoCadena(loc1,cad))!=elem)) {
		loc1=siguiente(loc1,cad);
	}
	return esLocalizador(loc1);
}


bool estaOrdenadaPorNaturales(TCadena cad){
	TLocalizador loc1=inicioCadena(cad);
	bool laPropiaSolucion=true;
	nat max=0;
	if(!esVaciaCadena(cad)) {
		while(esLocalizador(loc1) && laPropiaSolucion){
			if(natInfo(infoCadena(loc1,cad))<max){
				laPropiaSolucion=false;
			}else{
				max=natInfo(infoCadena(loc1,cad));
				loc1=siguiente(loc1,cad);
			}
		}
			
	}
	return laPropiaSolucion;
}


bool hayNatsRepetidos(TCadena cad){
	bool encontrado=false;
	if (longitud(cad)>1){
		TLocalizador loc1=inicioCadena(cad);
		TCadena cad2=crearCadena();
		TLocalizador loc2;
		nat n;
		insertarAlFinal(copiaInfo(infoCadena(loc1,cad)),cad2);
		loc1=siguiente(loc1,cad);
		
	while(esLocalizador(loc1) && !encontrado){
			n=natInfo(infoCadena(loc1,cad));
			loc2=inicioCadena(cad2);
			while(esLocalizador(loc2) && !encontrado){
				if(n==natInfo(infoCadena(loc2,cad2))){
					encontrado=true;
				}else{
					if(esFinalCadena(loc2,cad2)){
						insertarAlFinal(copiaInfo(infoCadena(loc1,cad)),cad2);
						loc2=NULL;
					}else{
					loc2=siguiente(loc2,cad2);
					}
				}
			}
			loc1=siguiente(loc1,cad);
	}
	liberarCadena(cad2);
	loc2=loc1=NULL;
	}
	return encontrado;
}

bool sonIgualesCadena(TCadena c1, TCadena c2){
	TLocalizador loc1=inicioCadena(c1), loc2=inicioCadena(c2);
	bool laPropiaSolucion=true;
	TInfo info1,info2;
	while(esLocalizador(loc1) && esLocalizador(loc2) && laPropiaSolucion){
		info1=infoCadena(loc1,c1), info2=infoCadena(loc2,c2);
		if((natInfo(info1)==natInfo(info2)) && (realInfo(info1)==realInfo(info2))){
			loc1=siguiente(loc1,c1);
			loc2=siguiente(loc2,c2);
		}else{
			laPropiaSolucion=false;
		}
	}
	return laPropiaSolucion && !esLocalizador(loc1) && !esLocalizador(loc2);
}

TCadena concatenar(TCadena c1, TCadena c2){
	TCadena priCad;
	if(!esVaciaCadena(c1) && !esVaciaCadena(c2)){
		priCad=copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
		insertarSegmentoDespues(copiarSegmento(inicioCadena(c2),finalCadena(c2),c2),finalCadena(priCad),priCad);
	}else if(esVaciaCadena(c2)){
		priCad=copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
	}else if(esVaciaCadena(c1)){
		priCad=copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
	}else{
		priCad=crearCadena();
	}
	
	return priCad;
}

TCadena ordenar(TCadena cad){
	TLocalizador inicioCad = inicioCadena(cad);
	while(esLocalizador(inicioCad)){
		TLocalizador varAux=inicioCad;
		while(esLocalizador(anterior(varAux,cad)) && natInfo(infoCadena(varAux,cad))<natInfo(infoCadena(anterior(varAux,cad),cad))){
			intercambiar(varAux,anterior(varAux,cad),cad);
			varAux=anterior(varAux,cad);
		}
		inicioCad=siguiente(inicioCad,cad);
	}
	return cad;
}

TCadena cambiarTodos(nat original, nat newElemento, TCadena cad){
	TLocalizador varAux = inicioCadena(cad);
	while(esLocalizador(varAux)){
		if(natInfo(infoCadena(varAux,cad))==original){
			TInfo nuev=crearInfo(newElemento,realInfo(infoCadena(varAux,cad)));
			TInfo infoVieja=infoCadena(varAux,cad);
			cambiarEnCadena(nuev,varAux,cad);
			liberarInfo(infoVieja);
		}
		varAux=siguiente(varAux,cad);
	}
	return cad;
}


TCadena subCadena(nat menor, nat mayor, TCadena cad){
	TCadena laPropiaSolucion=crearCadena();
	TLocalizador loc=inicioCadena(cad);
	if(longitud(cad)==1) {
		insertarAlFinal(copiaInfo(infoCadena(loc,cad)),laPropiaSolucion);
	}else{
		
	while(esLocalizador(loc) && natInfo(infoCadena(loc,cad))<=mayor){
		if(natInfo(infoCadena(loc,cad))>=menor){
			insertarAlFinal(copiaInfo(infoCadena(loc,cad)),laPropiaSolucion);
		}
		loc=siguiente(loc,cad);
	}
	}
	return laPropiaSolucion;
}

















































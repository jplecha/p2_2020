//52139037
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"
#include "../include/binario.h"
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

















































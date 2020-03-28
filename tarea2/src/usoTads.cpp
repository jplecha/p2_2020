#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"

/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
bool pertenece(nat elem, TCadena cad){
	TLocalizador loc1=inicioCadena(cad);
	while(esLocalizador(loc1) && (natInfo(infoCadena(loc1,cad))!=elem)) {
		loc1=siguiente(loc1,cad);
	}
	return esLocalizador(loc1);
}

/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
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
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
bool estaOrdenadaPorNaturales(TCadena cad){
	TLocalizador loc1=inicioCadena(cad);
	bool res=true;
	nat max=0;
	if(!esVaciaCadena(cad)) {
		while(esLocalizador(loc1) && res){
			if(natInfo(infoCadena(loc1,cad))<max){
				res=false;
			}else{
				max=natInfo(infoCadena(loc1,cad));
				loc1=siguiente(loc1,cad);
			}
		}
			
	}
	return res;
}

/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de 
  elementos de 'cad' son iguales.

	Falta implementar
*/
bool hayNatsRepetidos(TCadena cad){
	return true;
}

/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
*/
bool sonIgualesCadena(TCadena c1, TCadena c2){
	TLocalizador loc1=inicioCadena(c1), loc2=inicioCadena(c2);
	bool res;
	while(esLocalizador(loc1) && esLocalizador(loc2) && res){
		TInfo info1=infoCadena(loc1,c1), info2=infoCadena(loc2,c2);
		if((natInfo(info1)==natInfo(info2)) && (realInfo(info1)==realInfo(info2))){
			loc1=siguiente(loc1,c1);
			loc2=siguiente(loc2,c2);
		}else{
			res=false;
		}
	}
	return res;
}
/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
*/
TCadena concatenar(TCadena c1, TCadena c2){
	TCadena priCad, segCad;
	if(!esVaciaCadena(c1) && !esVaciaCadena(c2)){
		priCad=copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
		segCad=copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
		insertarSegmentoDespues(segCad,finalCadena(priCad),priCad);
		liberarCadena(segCad);
	}else if(esVaciaCadena(c2)){
		priCad=copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
	}else if(esVaciaCadena(c1)){
		priCad=copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
	}else{
		priCad=crearCadena();
	}
	
	return priCad;
}
/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
TCadena ordenar(TCadena cad){
	TLocalizador inicioCad = inicioCadena(cad);
	while(esLocalizador(inicioCad)){
		TLocalizador aux=inicioCad;
		while(esLocalizador(anterior(aux,cad)) && realInfo(infoCadena(aux,cad))<realInfo(infoCadena(anterior(aux,cad),cad))){
			intercambiar(aux,anterior(aux,cad),cad);
			aux=anterior(aux,cad);
		}
		inicioCad=siguiente(inicioCad,cad);
	}
	return cad;
}
/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
*/
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){
	TLocalizador aux = inicioCadena(cad);
	while(esLocalizador(aux)){
		if(natInfo(infoCadena(aux,cad))==original){
			TInfo nuev=crearInfo(nuevo,realInfo(infoCadena(aux,cad)));
			TInfo infoVieja=infoCadena(aux,cad);
			cambiarEnCadena(nuev,aux,cad);
			liberarInfo(infoVieja);
		}
		aux=siguiente(aux,cad);
	}
	return cad;
}

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
  
  Falta implementar
*/
TCadena subCadena(nat menor, nat mayor, TCadena cad){
	return cad;
}

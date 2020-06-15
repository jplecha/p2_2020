#include "../include/mapping.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

struct repMap{
  TCadena cadena;
  nat M;
  nat cant;
};
/*
  Crea un 'TMapping' vacío (sin elementos) de asociaciones nat -> double.
  Podrá haber hasta M asociaciones.
  El tiempo de ejecución en el peor caso es O(M).
 */
TMapping crearMap(nat M){
	TMapping map=new repMap;
	map->cadena=crearCadena();
	map->M=M;
	return map;
}

/*
  Inserta en 'map' la asociación entre 'clave' y 'valor'.
  Precondición: !estaLlenoMap(map) y !existeAsociacionEnMap(clave, map).
  Devuelve 'map'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TMapping asociarEnMap(nat clave, double valor, TMapping map){
	
	TInfo nuevo;
	nuevo.natural=clave;
	nuevo.real=valor;
	map->cadena=insertarAlFinal(nuevo,map->cadena);
    map->M--;
    return map;
}

/*
  Elimina de 'map' la asociación correspondiente a 'clave' y libera la
  menoria  asignada a mantener esa asociación.
  Precondición: existeAsociacionenMap(clave, h).
  Devuelve 'map'.
  El 'TMapping' resultado comparte memoria con el parámetro'.
  El tiempo de ejecución es O(1) en promedio.
 */
TMapping desasociarEnMap(nat clave, TMapping map){
  if(esClave(clave,map)){
      map->cadena=removerDeCadena(posNat(clave,map->cadena),map->cadena);
  }
  map->M++;
  return map;
}

/*
  Devuelve 'true' si y solo si en 'map' hay una asociación correspondiente
  a 'clave'.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existeAsociacionEnMap(nat clave, TMapping map){
	return posNat(clave,map->cadena);
}

/*
  Devuelve el valor correspondiente a la asociacion de 'clave' en 'h'.
  Precondición: existeAsociacionenMap(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
double valorEnMap(nat clave, TMapping map){
  TInfo aux;
  nat pos=posNat(clave, map->cadena);
  aux=infoLista(pos,map->cadena);
  return aux.real;
}

/*
  Devuelve 'true' si y solo si 'map' tiene 'M' elementos, siendo 'M' el
  parámetro pasado en crearMap.
  El tiempo de ejecución es O(1).
 */
bool estaLlenoMap(TMapping map){
	return M==0;
}

/*
  Libera la memoria asignada a 'map' y todos sus elementos.
  El tiempo de ejecución en el peor caso es O(M), siendo 'M' el parámetro
  pasado en crearMap.
 */
void liberarMap(TMapping map){

}
#!/bin/bash


opcion=$((1+RANDOM % 33))
case $opcion in
	1)  echo  "esLocalizador"
	;;
	2)  echo  "esVaciaCadena"
	;;
	3)  echo  "inicioCadena"
	;;
	4)  echo  "finalCadena"
	;; 
	5)  echo  "infoCadena"
	;;
	6)  echo  "esFinalCadena"
	;;
	7)  echo  "esInicioCadena"
	;;
	8)  echo  "siguiente"
	;;
	9)  echo  "anterior"
	;;
	10) echo  "insertarAlFinal ("
	;; 
	11) echo  "insertarAntes"
	;;
	12) echo  "removerDeCadena"
	;;
	13) echo  "imprimirCadena"
	;;
	14) echo  "kesimo"
	;;
	15) echo  "localizadorEnCadena"
	;;
	16) echo  "precedeEnCadena"
	;;
	17) echo  "insertarSegmentoDespues "
	;;
	18) echo  "copiarSegmento "
	;;  
	19) echo  "borrarSegmento"
	;;
	20) echo  "cambiarEnCadena"
	;;
	21) echo  "intercambiar"
	;;
	22) echo  "siguienteClave"
	;;
	23) echo  "anteriorClave"
	;;
	24) echo  "menorEnCadena"
	;;
	25) echo  "pertenece"
	;;
	26) echo  "estaOrdenadaPorNaturales"
	;;
	27) echo  "hayNatsRepetidos"
	;;
	28) echo  "sonIgualesCadena"
	;;
	29) echo  "concatenar"
	;;
	30) echo  "ordenar"
	;;
	31) echo  "cambiarTodos"
	;;
	32) echo  "subCadena"
	;;
	33) echo  "reiniciar"
	;;
	*) echo "Error"
	;;

esac

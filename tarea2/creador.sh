#!/bin/bash


cantElementos=0
locValido=0
posLoc=0
for i in {1..25}
do
if [ $posLoc -lt $cantElementos ] && [ $posLoc -ge 1 ]
then
	locValido=1
else
	locValido=0
fi
if [ $i -le 9 ]
then
   		a=$((1+RANDOM % 9))
                b=$((1 +RANDOM % 9))
                c=$((1 +RANDOM % 9))
                echo  "insertarAlFinal ($a,$b.$c)"
else
opcion=$((1+RANDOM % 33))
case $opcion in
	1)  echo  "esLocalizador"
	;;
	2)  echo  "esVaciaCadena"
	;;
	3)
		if [ $cantElementos -gt 0 ]
                then
                        echo  "inicioCadena"
                        posLoc=1
			locValido=1
                else
                        echo "esLocalizador"
                        locValido=0
                fi

	;;
	4)
		
                if [ $cantElementos -gt 0 ]
                then
                        echo  "finalCadena"
                        posLoc=$cantElementos
                        locValido=1
                else
                        echo "esLocalizador"
                        locValido=0
                fi
 
	;; 
	5)  
		if [ $locValido -gt 0 ]
                then
                        echo  "infoCadena"
                else
                        echo "finalCadena"
                        posLoc=$cantElementos
                        locValido=1
                fi
	;;
	6)  echo  "esFinalCadena"
	;;
	7)  echo  "esInicioCadena"
	;;
	8)  
		if [ $locValido -gt 0 ]
                then
                        echo  "siguiente"
                        ((posLoc=posLoc+1))
                else
                        echo "finalCadena"
                        posLoc=$cantElementos
                        locValido=1
                fi

	;;
	9)  
		if [ $locValido -gt 0 ]
                then
                        echo  "anterior"
                        ((posLoc=posLoc-1))
                else
                        echo "finalCadena"
                        posLoc=$cantElementos
                        locValido=1
                fi

	;;
	10) 
		a=$((1+RANDOM % 9))
                b=$((1 +RANDOM % 9))
                c=$((1 +RANDOM % 9))
		((cantElementos=cantElementos+1))
		echo  "insertarAlFinal ($a,$b.$c)"
	;; 
	11) 
		a=$((1+RANDOM % 9))
                b=$((1 +RANDOM % 9))
                c=$((1 +RANDOM % 9))
		((cantElementos=cantElementos+1))
		echo  "insertarAntes ($a,$b.$c)"
	;;
	12) 
		if [ $locValido -gt 0 ]
		then 
			echo  "removerDeCadena"
			locValido=0

		else
			echo "inicioCadena"
			
		fi
	;;
	13) echo  "imprimirCadena"
	;;
	14) 
                k=$((1 +RANDOM % 9))
		echo  "kesimo $k"
	;;
	15)
		if [ $locValido -eq 0 ]
                then
                        echo  "localizadorEnCadena"
                else
                        echo "inicioCadena"
                fi
	;;
	16) 
		if [ $cantElementos -gt 0 ]
		then
		k=$((RANDOM % $cantElementos))
		if [ $locValido -eq 0 ]
                then
                        echo  "precedeEnCadena"
                else
                        echo "esLocalizador"
                fi
		else
			echo "inicioCadena"
		fi
	;;
	17) 
		a=$((1+RANDOM % 9))
                b=$((1 +RANDOM % 9))
                c=$((1 +RANDOM % 9))
		z=$((1 +RANDOM % 9))
		aAgregar="($a,$b.$z)"
		i=1;
		while [ $i -le $c ]
		do
			 a=$((1+RANDOM % 9))
	                 b=$((1 +RANDOM % 9))
                	 z=$((1 +RANDOM % 9))
			((i=i+1))
			((cantElementos=cantElementos+1))
			 aAgregar+=" ($a,$b.$z)"	
		done

		echo  "insertarSegmentoDespues $aAgregar"
	;;
	18) 
		if [ $cantElementos -gt 0 ]
		then
		  a=$((1+RANDOM % $cantElementos))
		  c=$cantElementos
                b=$(($a +RANDOM % $c))
		echo  "copiarSegmento $a $c"
		fi
	;;  
        19) 
		if [ $cantElementos -gt 0 ]
                then
                  a=$((1+RANDOM % $cantElementos))
                  c=$((cantElementos - 1))
		  totalBorrados=$((c-a))
		  cantElementos=$((cantElmentos-totalBorrados))
		  echo  "borrarSegmento $a $c"
		fi
	;;
#	20) echo  "cambiarEnCadena"
#	;;
#	21) echo  "intercambiar"
#	;;
#	22) 
#		 if [ $locValido -eq 0 ]
 #               then
 #                      echo  "siguienteClave"
#			((posLoc=posLoc+1))
 #               else
  #                      echo "finalCadena"
#			posLoc=$cantElementos
#			locValido=1
 #               fi
#	;;
#	23) echo  "anteriorClave"
#	;;
	24) echo  "menorEnCadena"
	;;
#	25) echo  "pertenece"
#	;;
	26) echo  "estaOrdenadaPorNaturales"
	;;
#	27) echo  "hayNatsRepetidos"
#	;;
#	28) echo  "sonIgualesCadena"
#	;;
#	29) echo  "concatenar"
#	;;
	30) echo  "ordenar"
	;;
	31) echo  "cambiarTodos"
	;;
#	32) echo  "subCadena"
#	;;
#	33) echo  "reiniciar"
#	;;
	*) echo "finalCadena"
	;;
	
esac
fi
done

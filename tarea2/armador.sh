#!/bin/bash

make -f Makefile clean
for i in {300..310}
do
sh creador.sh > test/$i.in
echo "" > test/$i.out
sed -i "/CASOS =/ s/$/ $i/" Makefile

done
echo 'agregarTests: all $(DIFFS)' >> Makefile

make -f Makefile agregarTests

for i in {300..310}
do
	mv test/$i.sal test/$i.out
done

make -f Makefile clean

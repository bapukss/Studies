#!/bin/bash

#wczytuje n
echo "Podaj liczbę naturalną n: "
read N
#jesli n<=0 konczy dzialanie
if [ $N -le 0 ]; then
    echo "Błędna wartość!"
    exit 1
fi
#tworzy n plikow
for ((i=1; i<=N; i++)); do
    touch "plik$i.txt"
done

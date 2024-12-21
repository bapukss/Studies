#!/bin/bash

#wczytuje N
echo "Podaj liczbę naturalną n:"
read N

if [ $N -le 0 ]; then
    #jesli n <= 0 komunikuje o blednej wartosci i konczy dzialanie
    echo "Błędna wartość n!"
    exit 1
fi

#wypisuje n razy fraze "warto sie uczyc"
for ((i=0; i<N; i++)); do
    echo "Warto się uczyć"
done
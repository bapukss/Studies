#!/bin/bash

#wczytuje liczbe
echo "Podaj liczbę naturalną n: "
read N

#jesli liczba nie jest naturalna tzn <= 0 to wyswietla komunikat i konczy dzialanie
if [ $N -le 0 ]; then
    echo "Błędna wartość n!"
    exit 1
fi
#wyswietla n gwiazdek w jednej lini poprzez parametr -n (bez nowej lini)
for ((i=0; i<N; i++)); do
    echo -n "*"
done
# wypisuje nowa linie
echo

#!/bin/bash

SUMA=0

#infinity loop
while true; do
    #wczytuje liczbe
    echo "Podaj liczbę (0 kończy): "
    read LICZBA
    #jesli liczba == 0 konczy
    if [ $LICZBA -eq 0 ]; then
        break
    fi
    #dodaje liczbe do obecnej sumy
    SUMA=$((SUMA + LICZBA))
done
#wypisuje sume
echo "Suma: $SUMA"
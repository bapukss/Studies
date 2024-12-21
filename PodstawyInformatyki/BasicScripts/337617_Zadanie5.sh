#!/bin/bash

#wczytuje liczbe
echo "Podaj liczbę: "
read LICZBA

#jesli liczbe <= 1 to nie jest pierwsza
if [ $LICZBA -le 1 ]; then
    echo "Liczba nie jest pierwsza"
    exit 1
fi

#sprawdza wszystie potencjalne dzielniki do sqrt(n)
for((i=2;i*i<=LICZBA;i++)); do
    if [ $((LICZBA % i)) -eq 0 ]; then
        #jesli reszta z dzielenia liczby przez i jest rowne 0 to 
        #znaczy ze jest ona dzielnikiem tej liczby
        #z czego wynika ze nie jest pierwsza
        echo "Liczba nie jest pierwsza"
        exit 1
    fi
done

echo "Liczba jest pierwsza"

#!/bin/bash

#wczytuje nazwe pliku
echo "Podaj nazwę pliku: "
read NAZWA

if [ ! -e $NAZWA ]; then
    #jesli plik nie istnieje to tworzy go i wczytuje do niego napis "nowy plik"
    echo "Nowy plik" > $NAZWA
    echo "Utworzono plik: $NAZWA"
    #wypisuje zawartosc pliku tylko w wypadku gdy utworzylismy nowy plik
    # ponieawaz jesli istnieje moze byc on katalogiem co zakonczy dzialanie komunikatem
    # cat: $NAZWA: Is a directory
    cat $NAZWA
fi


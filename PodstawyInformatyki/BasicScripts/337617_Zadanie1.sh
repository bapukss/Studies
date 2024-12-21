#!/bin/bash

HASLO=abc #przechowuje poprawny kod
PROBY=0 #liczy proby uzytkownika

while [ $PROBY -lt 3 ]; do #wykonuj dopoki liczba prob < 3 (0,1,2 proba)
    #wczytuje kod
    echo "Podaj kod dostępu: "
    read KOD
    # sprawdza czy wczytany kod == haslo
    if [ $KOD = $HASLO ]; then
        # jesli tak wyswietl zawartosc pliku
        echo "Zawartość pliku tajne.txt: "
        cat tajne.txt
        exit 0
    else
        #jesli nie to poinformuj o tym uzytkownika i zwieksz licznik prob
        echo "Niepoprawne hasło."
        ((PROBY++))
    fi
done
#!/bin/bash

#tworzy lista.txt
touch lista.txt

#petla po 10 nazwisk
for ((i=0; i<10; i++)); do
    echo "Podaj nazwisko: "
    read NAZWISKO
    #zapisuje wczytane nazwisko w pliku
    echo $NAZWISKO >> lista.txt
done
#wyswietla posortowane nazwiska
echo "Nazwiska w porządku alfabetycznym:"
sort lista.txt

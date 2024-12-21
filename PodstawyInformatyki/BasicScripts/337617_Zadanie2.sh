#!/bin/bash

#wczytaj wiek
echo "Podaj swój wiek: "
read WIEK

if [ "$WIEK" -lt 0 ]; then
    #jesli liczba ujemna to bledna wartosc
    echo "Błędnie podana wartość!"
    exit 1
elif [ "$WIEK" -ge 18 ]; then
    #jesli wiek >= 18 to pelnoletni
    echo "Jesteś pełnoletni."
else
    #w innym przypadku nie jest pelnoletni
    echo "Nie jesteś pełnoletni."
fi
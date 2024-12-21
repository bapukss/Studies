#!/bin/bash

#sprawdza czy liczba wejsciowych argumentow == 2
if [ $# -ne 2 ]; then
    echo "Podano złą ilość argumentów na wejściu"
    exit 1
fi

#przekazuje argumenty wywolania do odpowienich parametrow
SLOWO=$1
PLIK=$2

#sprawdza czy plik istnieje
if [ ! -f "$PLIK" ]; then
    echo "Plik nie istnieje!"
    exit 1
fi

# grep przeszukuje plik szukajac wzorca
# -w zapewnia ze grep nie dopasuje podciagow tzn nie znajdzie recznik w podrecznik
# -i ignoruje wielkosc liter
# -o zapewnia ze wzorzec zapisany n razy w tej samej lini zostanie policzony n razy
# wc = word count, liczy wystapienia slowa w pliku
# liczy tylko linie co w polaczeniu z grepem zlicza ile razy wrzoec pojawia sie w tekscie
grep -o -w -i "\b$SLOWO\b" "$PLIK" | wc -l

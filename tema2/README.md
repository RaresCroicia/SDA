# Prelucrarea imaginilor

## Cuvant inainte
Probabil se poate vedea istoricul de incercari pe vmchecker, deoarece am sursele in folder-ul src/ , for some unknown reason,
fisierele out si ref nu se creau, asa ca le-am creat eu manual.

Imi cer mii de scuze pentru *probabil* nervii pe care i-am creat pe forum/teams, insa imi placea prea mult subiectul temei pentru 
a o abandona asa usor.

## Implementare

### utils.h
Biblioteca **utils.h** contine niste functii ajutatoare de care vom avea nevoie mai incolo. (Practic micunealta secreta)
Utilizarea functiilor este mai bine definita in comentariile codului.

### rgb.h
Biblioteca **rgb.h** contine structura de pixel cu cele 3 culori (RGB), insa si o structura de tip BIG_RGB, unde culorile pot atinge 
valori de tip long long, pentru a-mi calcula culoarea medie (va exista acel overflow cand adunam culorile)
Utilizarea functiilor este mai bine definita in comentariile codului.

### tree.h
Biblioteca de baza in care definim structura nodului de arbore, arborele cuaternar in sine si structura de coada + instructiunile 
aferente acestora. Am avut nevoie de coada pentru a folosi BFS pentru indexarea nodurilor, pentru inserarea in vector.
Utilizarea functiilor este mai bine definita in comentariile codului.

### main
In functia main ne vom folosi de argumentele primite in linia de comanda si vom apela functiile de care avem nevoie. Nimic special,
vedem ce am primit si in functie de acesti parametri, rezolvam ce ni se cere.

## Timp de implementare
Dupa cum le-am spus si colegilor cand m-au intrebat "Da' cat a durat sa faci?", au existat 5 faze in "rezolvarea" temei.

- Prep-urile initiale (research + implementarea structurilor/functiilor) -> aproximativ **3-4 zile** de lucru neconstant (adica fie 1 ora, fie 12 in ziua respectiva)
- Task 1 -> aproximativ **1 zi** pentru a fi sigur ca am comprimat cum trebuie
- Task 2 -> aproximativ **2 ore** pentru ca este practic inversul comprimarii, a fost nevoie de definirea a una/doua functii noi care se bazau pe cele vechi
- Task 3 -> aproximativ **o ora**, deoarece a fost rapid sa imi dau seama cum trebuie rotite imaginile, facandu-mi un mic desen
    **1 2  ---> 2 1**
    **4 3  ---> 3 4**  care este un proces recursiv (exemplul pentru orizontala)
- Beautify al codului + realizarea README -> cam **1 zi** pentru ca era destul de "necomentat" codul.

# Tema 3 SDA - Grafuri

## Cuvant inainte

As dori sa precizez ca tema fost foarte interesanta si m-a ajutat sa inteleg mai bine unii algoritmi de cost minim.
Plus, a fost foarte bine detaliata, exemplele clare, ceea ce m-a bucurat, venind dupa niste experiente mai neplacute.

## Timp de implementare

Pentru fiecare task mi-am luat cam aproximativ o zi/doua, insa pentru djikstra a fost nevoie de 4 zile deoarece nu vedeam  
ca nu dealocam toata memoria folosita.

Mai pe scurt, tema mi-a luat cam o saptamana de implementat *cu unele pauze*

## Despre task-uri si implementarea lor

Am detaliat si in comentariile codului ce se intampla mai exact

### Task 1

Algoritm folosit: 

- Floyd-Warshall O(n^3)

Algoritmul este destul de usor, va cauta pentru fiecare pereche (i,j) drumul cel mai scurt, verificand daca se poate scrie drumul
direct ca (i,j) sau ca o suma de (i,k) + (k,j) s.a.m.d.

### Task 2

Algoritm folosit:

Nu cred ca are un nume specific, insa se bazeaza pe faptul ca se verifica pentru fiecare nod daca are drum catre altele care au drum 
catre el (putin cam ambiguu spus, stiu, nu stiu cum altcumva sa ma exprim)

M-am folosit de DFS atat intern, cat si extern pentru a verifica fiecare componenta tare conexa

### Task 3

Algoritm folosit:

- Djikstra (pe masti)

Mastile ne ajuta pentru a retine starea traseului pana la momentul respectiv (de exemplu starea 1001 ne spune ca am trecut prin nodul 0 si nodul 3)

In rest, este algoritmul clasic Djikstra, care se foloseste de coada pentru a cauta drumul minim, mereu adaugand vecinii la care avem drum. 

Pentru a ignora situatii pe care le-am analizat deja, am folosit o lista unde retin fiecare stare in care m-am aflat cautand drumurile

# Tema 1 - Remedierea problemelor prezente in seturi de date folosind liste dublu inlantuite

Pentru rularea executabilului, se vor executa urmatoarele:

**make build** - pentru crearea executabilului

**./tema1** --argumente - pentru executarea propriu zisa

**make clean** - pentru curatarea fisierelor de tip obiect si a executabilului

## Implementare

### Lista

Pentru a memora lista cu perechile (timestamp, value) am folosit o structura de tip **lista dublu inlantuita**, care contine nodurile cap si coada ale listei si lungimea acesteia.

**Nodurile** acesteia sunt definite prin timestamp si value, precum si nodul precedent si cel urmator.

In header-ul **liste.h** am declarat urmatoarele functii:

```c#
    init_list(); //Functia de initiere a unei liste in memorie
    init_node(timestamp, value); //Functia de initiere a unui nod in memorie
    destroy_list(list); //Functia de distrugere a unei liste
    destroy_node(node); //Functia de distrugere a unui nod
    print_list(list); //Afiseaza lista
```

```c#
    add_to_list(list, position, timestamp, value); //Functie de adaugare in lista la o pozitie data
    remove_from_list(list, position); //Functie care elimina din lista un nod de la pozitia data
    priority_insert_value(list, timestamp, value); //Functie care introduce in ordine un nod in functie de value
    priority_insert_timestamp(list, timestamp, value); //Functie care introduce in ordine un nod in functie de timestamp
```

### Rezolvarea sarcinilor de lucru

#### Eliminare de exceptii folosind metode statistice

Pentru abordarea acestei probleme, am creat o noua lista care va contine *doar* nodurile care respecta intervalul dat.

Pentru calculul **mediei valorilor** si **deviatiei standard** si pentru verificarea apartanentei in interval, am implementat functiile:

In **utils.h**
```c#
    window_average(middle); //calculul mediei
    standard_deviation(middle); //calculul deviatiei
    is_in_bounds(element, lower_bound, upper_bound); //verificarea lower <= element <= upper
```

Pentru rezolvarea propriu-zisa, am implementat functia:

In **work.h**
```c#
    remove_exceptions_statistically(list); //Returneaza lista dupa ce s-au eliminat exceptiile
```

#### Eliminare de zgomot folosind filtre

##### Filtrare mediana

Pentru abordarea acestei probleme, am creat **subliste** de cate 5 elemente, in care elementele au fost introduse in ordine crescatoare pentru a lua direct elementul din mijloc (care stim ca este si element **median**), dupa aceea vom introduce elementele mediane in lista noua.

Pentru calculul medianei, am implementat functia:

In **utils.h**
```c#
    median(middle); //Calculeaza mediana ferestrei din jurul nodului middle
```

Pentru rezolvarea propriu-zisa, am implementat functia:

In **work.h**
```c#
    median_filtered(list); //Returneaza lista dupa ce s-a filtrat
```

##### Filtrare folosind media aritmetica

Pentru abordarea acestei probleme, am creat **subliste** de cate 5 elemente, dupa am calculat **media aritmetica** pentru fiecare sublista si am introdus-o in lista noua.


Pentru calculul mediei aritmetice, am folosit functia definita mai sus:

```c#
    window_average(middle); 
```

Pentru rezolvarea propriu-zisa, am implementat functia:

In **work.h**
```c#
    average_filtered(list); //Returneaza lista dupa ce s-a filtrat
```

####  Uniformizarea frecventei in timp a datelor

Pentru abordarea acestei probleme, vom verifica **diferenta de timestampuri** dintre fiecare 2 noduri, reducand intervalul in cazul in care diferenta este mai mare de o secunda.


Pentru verificarea apartenentei in interval, am implementat functia:

In **utils.h**
```c#
    is_in_bounds_uint(element, lower, upper);  //verificarea lower <= element <= upper
```

Pentru rezolvarea propriu-zisa, am implementat functia:

In **work.h**
```c#
    frequency_uniform(list); //uniformizeaza lista
```

####  Completarea datelor

Pentru abordarea acestei probleme, verificam **diferenta de timestampuri** intre noduri consecutive si adaugam, conform formulelor, nodurile suplimentare, construind cele doua liste de vecini (**left** si **right**)


Pentru calculele de rigoare si crearea listelor left si right, am implementat urmatoarele functii:

In **utils.h**
```c#
    get_left_list(middle); //creeaza lista vecinilor din stanga a lui middle
    get_right_list(middle); //creeaza lista vecinilor din dreapta a lui middle
    scaling_factor(timestamp, left_list, right_list); //returneaza factorul de scalare C
    w(i, k); //calculeaza functia w(i,k)
    value_calculation(left_list, right_list, timestamp, C, k); //calculeaza valoarea nodului la timestamp-ul respectiv in functie de C
```

Pentru rezolvarea propriu-zisa, am implementat functia:

In **work.h**
```c#
    data_completion(list) //completeaza lista cu valorile necesare in cazul gap-urilor mari
```


####  Statistici

Pentru abordarea acestei probleme, vom crea a noua lista care va contine toate elementele listei originale, insa in **ordine crescatoare**. Dupa aceea vom vedea pe fiecare interval, incepand cu intervalul **[min_list, min_list+frequency]** cate elemente exista.


Pentru rezolvarea propriu-zisa, am implementat functia:

In **work.h**
```c#
    print_statistics(list, frequency)
```

### Mod de rulare

Fisierul *source.c* contine main-ul executabilului, in care *citim* de la **tastatura** elementele listei si primim din **linia de comanda** comenzile pe care le vom executa.

Pentru a vedea ce comanda am primit, am creat functia
```c#
    check_command(choice)
```
pentru a putea codifica fiecare comanda cu un numar.

Codificarile sunt urmatoarele:

--e1 = 1

--e2 = 2

--e3 = 3

--u = 4

--c = 5

--st = 6

Cand primim comanda **--st**, ne vom folosi de functia
```c#
    extract_number(string); //Functia returneaza numarul de dupa --st
```
pentru a vedea ce frecventa ni se da ca parametru

La final, afisam **pe ecran** lista finala, dupa modificarile aduse.

### Timp de implementare

*Sometimes the hardest thing in the process of doing is understanding*

Procesul de implementare a durat:

-aproximativ **6 ore** pentru intelegerea pe deplin a cerintelor

-aproximativ **4 ore** pentru implementare

-aproximativ **1 ora** pentru *curatare* (procesul de beautify al codului, adaugarea comentariilor, etc.)

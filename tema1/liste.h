#ifndef _liste_
#define _liste_

typedef unsigned int uint;
typedef double real;

//Structura unui nod
typedef struct node{
    uint timestamp;
    real value;
    struct node *prev, *next;
}TNod;

//Structura unei liste
typedef struct lista{
    uint length;
    TNod *head, *tail;
}TList;

//Structura pentru perechea de elemente a unui nod
typedef struct pair{
    uint timestamp;
    real value;
}TPair;


//Functia de initiere a unei liste in memorie
TList* init_list();
//Functia de initiere a unui nod in memorie
TNod* init_node(uint ts, real val);
//Functia de distrugere a unei liste
void destroy_list(TList* list);
//Functia de distrugere a unui nod
void destroy_node(TNod* node);

//Functia de adaugare in lista
TList* add_to_list(TList* list, uint position, uint ts, real vl);
//Functia de stergere a unui element din lista
TList* remove_from_list(TList* list, uint position);
//Va insera in ordine crescatoare in functie de value
TList* priority_insert_value(TList* list, uint ts, real value);
//Va insera in ordine crescatoare in functie de timestamp
TList* priority_insert_timestamp(TList* list, uint timestamp, real value);
//Functie de afisare a elementelor din lista
void print_list(TList* list); 


#endif


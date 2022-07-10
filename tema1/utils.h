#ifndef _utils_
#define _utils_
#include "liste.h"

#define TRUE 1
#define FALSE 0

#define e1 1
#define e2 2
#define e3 3
#define u 4
#define c 5
#define st 6
#define ERROR -1


//Functia de calcul a mediei valorilor din fereastra
real window_average(TNod* middle);

//Functia de calcul a deviatiei standard
real standard_deviation(TNod* middle);

//Functia pentru apartenenta intr-un interval
int is_in_bounds(real value, real lower_bound, real upper_bound);

//Functia pentru apartenenta intr-un interval (pentru uint)
int is_in_bounds_uint(uint value, uint lower_bound, uint upper_bound);

//Functie care returneaza ce comanda a fost primita in linia de comanda
int check_command(char *choice);

//Calculul medianei in fereastra de k = 5 din jurul lui middle
TPair median(TNod* middle);

//Extragerea unui numar din sir de caractere
int extract_number(char* string);

//Extragerea vecinilor din stanga
TList* get_left_list(TNod* middle);

//Extragerea vecinilor din dreapta
TList* get_right_list(TNod* middle);

//Calculcul factorului de scalare C
real scaling_factor(uint timestamp, TList* left, TList* right);

//Calculul functiei w
real w(uint i, uint k);

//Calculul valorii ce trebuie adaugata la timestamp-ul dat
real value_calculation(TList* left, TList* right, uint timestamp, real C, uint k);

#endif
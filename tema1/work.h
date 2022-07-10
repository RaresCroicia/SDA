#ifndef _work_
#define _work_
#include "liste.h"

//Eliminare de exceptii folosind metode statistice
TList* remove_exceptions_statistically(TList* list);

//Eliminare de zgomot folosind filtrare mediana
TList* median_filtered(TList* list);

//Eliminare de zgomot folosind filtrare pe baza mediei aritmetice
TList* average_filtered(TList* list);

//Uniformizarea frecventei in timp a datelor
TList* frequency_uniform(TList* list);

//Completarea datelor
TList* data_completion(TList* list);

//Afisarea statisticii
void print_statistics(TList* list, int frequency);

#endif
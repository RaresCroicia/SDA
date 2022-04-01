/**
 *  @author Florin Dumitrescu
 *
 *  Header pentru lab05.c
 *  Contine semnaturile functiilor pentru exercitiile 3 si 4
  */

#ifndef SD_LABS_LAB05_H
#define SD_LABS_LAB05_H

/**
 * Verifica daca fiecare paranteza deschisa este ulterior inchisa (parantezele sunt echilibrate).
 * Tipuri de perechi de paranteze:
 *      - ()
 *      - []
 *      - {}
 *
 * Pentru simplitate, se vor numi:
 *      - '(', '[', '{' = opening brackets (deschidere paranteza)
 *      - ')', ']', '}' = closing brackets (inchidere paranteza)
 *
 * Exemplu de expresie cu paranteze echilibrate:    '([{[]()}])'
 * Exemplu de expresie cu paranteze neechilibrate:  '(([)])'
 *
 * Explicatie:
 * In exemplul incorect, desi fiecare opening bracket are corespondent un closing bracket,
 * oridinea in care acestea se inchid este incorecta: '(' de pe pozitia 1 se inchide cu ')' de pe pozitia 3,
 * inainte ca '[' de pe pozitia 2 sa fie inchisa
 *
 * Se considera ca indexul incepe de la pozitia 0.
 *
 * Orice alte caractere in afara de parantezele definite mai sus vor fi ignorate.
 *
 * Implementarea se va face folosind o stiva:
 *      - Daca la pozitia curenta se afla un opening bracket, acesta se introduce in stiva
 *      - Daca la pozitia curenta se afla un closing bracket, se verifica daca in varful stivei se afla
 *      opening bracket-ul corespunzator. In caz afirmativ, se elimina din stiva si se trece la urmatorul caracter.
 *      Altfel, se returneaza valoarea 0 pentru a indica faptul ca expresia nu are paranteze balansate.
 *
 * @param exp Expresia ce trebuie evaluata
 * @return
 *      - 1 daca parantezele sunt balansate
 *      - 0 altfel
 */
int checkBalancedBrackets(char *exp);

/**
 * Sorteaza crescator vectorul primit la intrare folosind algoritmul Radix Sort. Sortarea se va face in-place folosind
 * 10 cozi, cate o coada pentru fiecare numar de la 0 la 9.
 *
 * De exemplu, dat fiind vectorul v = [15, 23, 6], se vor face urmatorii pasi:
 *      - Se obtine ultimul digit al fiecarui numar
 *      - Se adauga fiecare numar in coada corespunzatoare:
 *          - q0 = []
 *          - q1 = []
 *          - q2 = []
 *          - q3 = [23]
 *          - q4 = []
 *          - q5 = [15]
 *          - q6 = [6]
 *          - q7 = []
 *          - q8 = []
 *          - q9 = []
 *      - Se itereaza prin cozi incepand cu q0 pana la q9 si se adauga toate elementele inapoi in vector
 *          - v = [23, 15, 6]
 *          - Vectorul v este acum sortat dupa ultimul digit
 *      - Se repeta procesul pentru ceilalti digiti. Daca un numar are mai putini digiti decat ceilalti, se va folosi
 *      valoarea 0 pentru acesta. De exemplu, 6 devine 06.
 *
 * @param v vectorul ce trebuie sortat
 * @param n numarul de elemente din vector
 */
void radixSort(int *v, int n);

#endif //SD_LABS_LAB05_H

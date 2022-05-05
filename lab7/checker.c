#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

#define RED_TEXT()      \
    printf("\033[0;31m");

#define GREEN_TEXT()    \
    printf("\033[0;32m");

#define CYAN_TEXT()    \
    printf("\033[0;36m");

#define RESET_TEXT()    \
    printf("\033[0m");

#define HEADER_TEXT()     \
    printf("\033[1;33m");

#define PRINT_CONTAINS(root, word) \
    printf("Arborele %s contine cuvantul \033[0;36m%s\033[0m\n", \
            trieContainsWord(root, word) ? "\b" : "\033[0;31mNU\033[0m", \
            word);

int main() {
    trieNode_t *rootTrie = NULL;

    HEADER_TEXT()
    printf("Se insereaza cuvinte in trie\n");
    RESET_TEXT()

    // Inserare de cuvinte
    trieInsertWord(&rootTrie, "ana");
    trieInsertWord(&rootTrie, "mar");
    trieInsertWord(&rootTrie, "analogic");
    trieInsertWord(&rootTrie, "margine");
    trieInsertWord(&rootTrie, "margini");
    trieInsertWord(&rootTrie, "martiimatii");
    trieInsertWord(&rootTrie, "analogim");
    //printNodeCharacters(rootTrie->children[CHAR_TO_IDX('a')]);

    // Verificare ca toate cuvintele au fost inserate
    PRINT_CONTAINS(rootTrie, "ana")
    PRINT_CONTAINS(rootTrie, "mar")
    PRINT_CONTAINS(rootTrie, "analogie")
    PRINT_CONTAINS(rootTrie, "analogic")
    PRINT_CONTAINS(rootTrie, "margine")

    printf("\n");

    HEADER_TEXT()
    printf("Se sterg cuvinte din trie\n");
    RESET_TEXT()

    // Stergere de cuvinte (existente sau nu)
    //trieDeleteWord(&rootTrie, "ana");
    trieDeleteWord(&rootTrie, "abfsa");
    trieDeleteWord(&rootTrie, "mar");

    // Verificare ca doar cuvantul "ana" a fost sters
    PRINT_CONTAINS(rootTrie, "ana")
    PRINT_CONTAINS(rootTrie, "analogic")
    PRINT_CONTAINS(rootTrie, "mar")
    PRINT_CONTAINS(rootTrie, "margine")
    printf("\n");

    HEADER_TEXT()
    printf("Se afiseaza toate cuvintele care au un anumit prefix\n");
    RESET_TEXT()
    // Afisare toate cuvintele care au prefixul "ana"
    triePrefixMatching(rootTrie, "mar");

    trieDestroy(&rootTrie);

    return 0;
}
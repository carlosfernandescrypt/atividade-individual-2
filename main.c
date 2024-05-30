#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nó da lista circular duplamente encadeada
typedef struct No {
    char artista[100];
    char musica[100];
    struct No *anterior;
    struct No *proximo;
} No;
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

// Função para criar um novo nó
No* criarNo(char *artista, char *musica) {
    No *novoNo = (No*)malloc(sizeof(No));
    strcpy(novoNo->artista, artista);
    strcpy(novoNo->musica, musica);
    novoNo->anterior = novoNo->proximo = novoNo;
    return novoNo;
}

// Função para inserir um nó na lista
void inserirNo(No **head, char *artista, char *musica) {
    No *novoNo = criarNo(artista, musica);
    if (*head == NULL) {
        *head = novoNo;
    } else {
        No *ultimo = (*head)->anterior;
        novoNo->proximo = *head;
        (*head)->anterior = novoNo;
        novoNo->anterior = ultimo;
        ultimo->proximo = novoNo;
    }
}

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

// Função para ler o arquivo e preencher a lista
void lerArquivoEInserirNaLista(No **head) {
    FILE *arquivo = fopen("musicas.txt", "r");
    char linha[200];
    char *artista, *musica;

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }
    // Lê cada linha do arquivo e insere na lista
    while (fgets(linha, sizeof(linha), arquivo)) {
        artista = strtok(linha, ";");
        musica = strtok(NULL, "\n");
        if (artista && musica) {
            inserirNo(head, artista, musica);
        }
    }

    fclose(arquivo);
}

// Função para exibir a playlist
void exibirPlaylist(No *head) {
    if (head == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }
    No *atual = head;
    do {
        printf("Artista: %s - Música: %s\n", atual->artista, atual->musica);
        atual = atual->proximo;
    } while (atual != head);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

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

// Função auxiliar para trocar dois nós
void trocarNos(No *a, No *b) {
    char artistaTemp[100];
    char musicaTemp[100];
    strcpy(artistaTemp, a->artista);
    strcpy(musicaTemp, a->musica);
    strcpy(a->artista, b->artista);
    strcpy(a->musica, b->musica);
    strcpy(b->artista, artistaTemp);
    strcpy(b->musica, musicaTemp);
}

// Função para ordenar a playlist pelo nome da música
void inserirMusicaUsuario(No **head) {
    char artista[100];
    char musica[100];

    printf("Digite o nome do artista: ");
    fgets(artista, 100, stdin);
    artista[strcspn(artista, "\n")] = 0; // Remove a nova linha lida pelo fgets

    printf("Digite o nome da música: ");
    fgets(musica, 100, stdin);
    musica[strcspn(musica, "\n")] = 0; // Remove a nova linha lida pelo fgets

    inserirNo(head, artista, musica);
    printf("Música '%s' de '%s' adicionada com sucesso!\n", musica, artista);
}

void exibirPlaylistOrdenada(No *head) {
    if (head == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }

    // Conta o número de músicas na playlist
    int numMusicas = 0;
    No *atual = head;
    do {
        numMusicas++;
        atual = atual->proximo;
    } while (atual != head);

    // Cria um array para armazenar as músicas
    No **array = malloc(numMusicas * sizeof(No*));

    // Copia as músicas para o array
    atual = head;
    for (int i = 0; i < numMusicas; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }

    // Ordena o array
    for (int i = 0; i < numMusicas - 1; i++) {
        for (int j = 0; j < numMusicas - i - 1; j++) {
            if (strcmp(array[j]->musica, array[j + 1]->musica) > 0) {
                No *temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    // Cria uma nova lista a partir do array ordenado
    No *novaHead = NULL;
    for (int i = 0; i < numMusicas; i++) {
        inserirNo(&novaHead, array[i]->artista, array[i]->musica);
    }

    // Exibe a nova lista
    exibirPlaylist(novaHead);

    // Libera a memória do array
    free(array);
}

// Função para remover uma música específica da playlist
void removerMusica(No **head, char *musicaParaRemover) {
    if (*head == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }

    No *atual = *head;
    No *anterior = atual->anterior;
    int encontrou = 0;

    // Procura pela música na lista
    do {
        if (strcmp(atual->musica, musicaParaRemover) == 0) {
            encontrou = 1;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    } while (atual != *head);

    // Se encontrou a música, remove-a da lista
    if (encontrou) {
        if (atual == *head && atual->proximo == *head) { // Único nó na lista
            *head = NULL;
        } else {
            if (atual == *head) { // Removendo o nó cabeça
                *head = atual->proximo;
            }
            anterior->proximo = atual->proximo;
            atual->proximo->anterior = anterior;
        }
        free(atual);
        printf("Música '%s' removida com sucesso!\n", musicaParaRemover);
    } else {
        printf("Música '%s' não encontrada na playlist.\n", musicaParaRemover);
    }
}

void liberarMemoriaLista(No **head) {
    if (*head == NULL) return;

    No *atual = *head;
    No *temp;

    do {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    } while (atual != *head);

    *head = NULL;
}

// Função para solicitar ao usuário a música a ser removida
void removerMusicaUsuario(No **head) {
    char musicaParaRemover[100];

    printf("Digite o nome da música que deseja remover: ");
    fgets(musicaParaRemover, 100, stdin);
    musicaParaRemover[strcspn(musicaParaRemover, "\n")] = 0; // Remove a nova linha lida pelo fgets

    removerMusica(head, musicaParaRemover);
}

// Função para buscar uma música específica na playlist
void buscarMusica(No *head, char *musicaParaBuscar) {
    if (head == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }

    No *atual = head;
    int encontrou = 0;

    // Procura pela música na lista
    do {
        if (strcmp(atual->musica, musicaParaBuscar) == 0) {
            printf("Música encontrada: '%s' de '%s'\n", atual->musica, atual->artista);
            encontrou = 1;
            break;
        }
        atual = atual->proximo;
    } while (atual != head);

    if (!encontrou) {
        printf("Música '%s' não encontrada na playlist.\n", musicaParaBuscar);
    }
}

// Função para solicitar ao usuário a música a ser buscada
void buscarMusicaUsuario(No *head) {
    char musicaParaBuscar[100];

    printf("Digite o nome da música que deseja buscar: ");
    fgets(musicaParaBuscar, 100, stdin);
    musicaParaBuscar[strcspn(musicaParaBuscar, "\n")] = 0; // Remove a nova linha lida pelo fgets

    buscarMusica(head, musicaParaBuscar);
}

// Função para avançar para a próxima música na playlist
void avancarMusica(No **musicaAtual) {
    if (*musicaAtual == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }

    *musicaAtual = (*musicaAtual)->proximo;
    printf("\nTocando agora: '%s' de '%s'\n", (*musicaAtual)->musica, (*musicaAtual)->artista);
}


// Função para retornar à música anterior na playlist
void retornarMusica(No **musicaAtual) {
    if (*musicaAtual == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }

    *musicaAtual = (*musicaAtual)->anterior;
    printf("\nTocando agora: '%s' de '%s'\n", (*musicaAtual)->musica, (*musicaAtual)->artista);
}

// Função para atualizar a lista de músicas no arquivo txt. É chamada sempre que houver uma atualização nas músicas.
void atualizarLista(No *head) {
    FILE *file = fopen("musicas.txt", "w");
    No *atual = head;

    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    do {
        fprintf(file, "%s;%s\n", atual->artista, atual->musica);
        atual = atual->proximo;
    } while (atual != head);

    fclose(file);

    printf("Lista de músicas atualizada.\n");
}

// Função para limpar o arquivo de músicas toda vez que a opção 8 (sair do programa) do menu for chamada.
void limparArquivo() {
    FILE *file = fopen("musicas.txt", "w");

    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    fclose(file);
    printf("Limpando a lista de músicas...\n");
    printf("Dados do arquivo 'musicas.txt' foram apagados.\n");
}

void exibirMusicaAtual(No **musicaAtual) {
    if (*musicaAtual != NULL) {
        printf("\nTocando agora: '%s' de '%s'\n", (*musicaAtual)->musica, (*musicaAtual)->artista);
    } else {
        printf("Nenhuma música está tocando no momento.\n");
    }
}

int exibirMenu() {
    int escolha;

  printf("\nMenu da Playlist:\n");
  printf("1. Exibir a playlist pela ordem de cadastro\n");
  printf("2. Exibir a playlist ordenada pelo nome das músicas\n");
  printf("3. Inserir novas músicas\n");
  printf("4. Remover uma música\n");
  printf("5. Buscar por uma música\n");
  printf("6. Avançar para próxima música\n");
  printf("7. Retornar a música anterior\n");
  printf("8. Sair\n");
  printf("Escolha uma opção: ");
  scanf("%d", &escolha);
  while ((getchar()) != '\n'); // Limpa o buffer do stdin

  return escolha;
}

int main() {
  No *head = NULL;
  No *musicaAtual = NULL;
  lerArquivoEInserirNaLista(&head);
  musicaAtual = head; // Inicializa com a primeira música da playlist
  exibirMusicaAtual(&musicaAtual);
  int escolha;
  do {
      escolha = exibirMenu();

      switch (escolha) {
          case 1:
              exibirPlaylist(head);
              break;
          case 2:
              exibirPlaylistOrdenada(head);
              break;
          case 3:
              inserirMusicaUsuario(&head);
              atualizarLista(head);
              break;
          case 4:
              removerMusicaUsuario(&head);
              atualizarLista(head);
              break;
          case 5:
              buscarMusicaUsuario(head);
              break;
          case 6:
              avancarMusica(&musicaAtual);
              break;
          case 7:
              retornarMusica(&musicaAtual);
              break;
          case 8:
              printf("Você deseja limpar o arquivo de músicas? (S/N): ");
              char resposta;
              scanf(" %c", &resposta);
              while ((getchar()) != '\n'); // Limpa o buffer do stdin
              if (resposta == 'S' || resposta == 's') {
                  limparArquivo();
              }
              printf("Saindo do programa...\n");
              break;
          default:
              printf("Opção inválida. Por favor, tente novamente.\n");
      }
  } while (escolha != 8);

  liberarMemoriaLista(&head); // Libera a memória alocada para a lista antes de sair

  return 0;
}

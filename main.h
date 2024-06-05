#ifndef MAIN_H
#define MAIN_H

// Estrutura para representar um nó da lista circular duplamente encadeada
typedef struct No {
    char artista[100];
    char musica[100];
    struct No *anterior;
    struct No *proximo;
} No;

// Declarações das funções utilizadas no sistema de playlist
No* criarNo(char *artista, char *musica);
void inserirNo(No **cabeca, char *artista, char *musica);
void lerArquivoEInserirNaLista(No **cabeca);
void exibirPlaylist(No *cabeca);
void exibirPlaylistOrdenada(No *cabeca);
void inserirMusicaUsuario(No **cabeca);
void removerMusica(No **cabeca, char *musicaParaRemover);
void removerMusicaUsuario(No **cabeca);
void buscarMusica(No *cabeca, char *musicaParaBuscar);
void buscarMusicaUsuario(No *cabeca);
void avancarMusica(No **musicaAtual);
void retornarMusica(No **musicaAtual);
void atualizarLista(No *head);
void limparArquivo();

#endif

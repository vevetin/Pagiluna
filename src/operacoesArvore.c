#include <stdlib.h>
#include "operacoesArvore.h"

/* Cria novo nó com filhos especificados */
NoBST *novoNo(Livro novoLivro, NoBST *esquerda, NoBST *direita) {
    NoBST *no = malloc(sizeof(NoBST));
    no->esquerda = esquerda;
    no->direita = direita;
    no->item = novoLivro;
    return no;
}

/* Inserção na árvore (ordenada por chave) */
NoBST *inserirNo(NoBST *raiz, NoBST *novo) {
    if (raiz == NULL) return novo;
    if (raiz->item.chave > novo->item.chave)
        raiz->esquerda = inserirNo(raiz->esquerda, novo);
    else
        raiz->direita = inserirNo(raiz->direita, novo);
    return raiz;
}

/* Busca por chave (exata) */
NoBST *buscarBST(NoBST *raiz, tipoT busca) {
    if(raiz == NULL || igual(busca, chave(raiz->item))) 
        return raiz;   
    
    if(menor(busca, chave(raiz->item))) return buscarBST(raiz->esquerda, busca);
    else return buscarBST(raiz->direita, busca);
}

// funcao auxiliar para encontrar o menor no da subarvore
NoBST *encontrarMinimo(NoBST *no) {
    while (no->esquerda != NULL) 
        no = no->esquerda;
    return no;
}

NoBST *excluirNo(NoBST *raiz, tipoT excluir) {
    if(raiz == NULL) return NULL; // se a arvore estiver vazia, nao ha o que excluir 
    if(menor(excluir, chave(raiz->item))) 
        raiz->esquerda = excluirNo(raiz->esquerda, excluir);
    else if(menor(chave(raiz->item), excluir)) 
        raiz->direita = excluirNo(raiz->direita, excluir);
    else {
        // caso o no tenha apenas um ou nenhum filho
        if(raiz->esquerda == NULL) {
            NoBST *temp = raiz->direita;
            free(raiz);
            return temp;
        } 
        
        else if(raiz->direita == NULL) {
            NoBST *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        
        // caso o no tenha dois filhos
        NoBST *temp = encontrarMinimo(raiz->direita);
        raiz->item = temp->item;
        raiz->direita = excluirNo(raiz->direita, chave(temp->item));
    }
    return raiz;
}

/* Edição do conteúdo de um nó com a mesma chave */
NoBST *editarNo(NoBST *raiz, Livro livroAtualizado) {
    NoBST *no = buscarBST(raiz, livroAtualizado.chave);
    if(no != NULL) no->item = livroAtualizado;
    return raiz;
}

/* Liberação da memória da árvore */
void liberarArvore(NoBST *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}
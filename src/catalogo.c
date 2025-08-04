#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"
#include "operacoesArvore.h"

/*Funcoes Auxiliares*/
void exibirLivro(Livro livro) {
    printf("Chave: %d\n", livro.chave);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Genero: %s\n", livro.genero);
    printf("Editora: %s\n", livro.editora);
    printf("Ano de Publicacao: %s\n", livro.anoPublicacao);
    printf("Notas Pessoais: %s\n", livro.notasPessoais);
    printf("\n");
}

/*Funcoes de Criacao e Insercao*/
Livro criarLivro() {
    static int quantidade = 0; // variavel estatica para gerar chaves unicas
    Livro novoLivro; 

    printf("\nDigite o titulo do livro: ");
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = 0;

    printf("Digite o autor do livro: ");
    fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = 0;

    printf("Digite o genero do livro: ");
    fgets(novoLivro.genero, sizeof(novoLivro.genero), stdin);
    novoLivro.genero[strcspn(novoLivro.genero, "\n")] = 0;

    printf("Digite a editora do livro: ");
    fgets(novoLivro.editora, sizeof(novoLivro.editora), stdin);
    novoLivro.editora[strcspn(novoLivro.editora, "\n")] = 0;

    printf("Digite o ano de publicacao do livro: ");
    fgets(novoLivro.anoPublicacao, sizeof(novoLivro.anoPublicacao), stdin);
    novoLivro.anoPublicacao[strcspn(novoLivro.anoPublicacao, "\n")] = 0;

    getchar();
    printf("Pode adicionar notas pessoais sobre o livro, se desejar: ");
    fgets(novoLivro.notasPessoais, sizeof(novoLivro.notasPessoais), stdin);
    novoLivro.notasPessoais[strcspn(novoLivro.notasPessoais, "\n")] = 0;

    novoLivro.chave = quantidade++;
    return novoLivro;
}

/*Funcoes de Busca*/
void buscarPorNome(NoBST *raiz, const char *nome, NoBST **resultados, int *total, int *capacidade) {
    if (raiz == NULL) return;
    if (strstr(raiz->item.titulo, nome) != NULL) {
        if (*total >= *capacidade) {
            *capacidade *= 2; 
            resultados = realloc(resultados, *capacidade * sizeof(NoBST));
            if (resultados == NULL) {
                fprintf(stderr, "Erro ao realocar memoria\n");
                return;
            }
        }
        (*resultados)[*total] = *raiz;
        (*total)++;
    }

    buscarPorNome(raiz->esquerda, nome, resultados, total, capacidade);
    buscarPorNome(raiz->direita, nome, resultados, total, capacidade);
}

void buscarLivro(NoBST *catalogo) {
    int capacidade = 5, total = 0, escolha, opcao;
    char nomeBusca[100];
    printf("Digite o titulo (ou parte dele) do livro a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    NoBST *resultados = malloc(capacidade * sizeof(NoBST));
    if (resultados == NULL) {
        fprintf(stderr, "Erro ao alocar memoria\n");
        return;
    }

    buscarPorNome(catalogo, nomeBusca, &resultados, &total, &capacidade);

    if (total > 0) {
        for (int i = 0; i < total; i++)
            exibirLivro(resultados[i].item);
        
        printf("Deseja editar ou excluir algum livro? (1-Sim / 0-Nao): ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("Digite a chave do livro que deseja editar ou excluir: ");
            scanf("%d", &escolha);
            getchar();

            NoBST *no = buscarBST(catalogo, escolha);
            if (no == NULL) {
                printf("Livro nao encontrado\n");
                free(resultados);
                return;
            }

            printf("1. Editar Livro\n");
            printf("2. Excluir Livro\n");
            printf("0. Voltar ao menu principal\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            getchar(); 
            switch (opcao) {
                case 1: {
                    Livro livroAtualizado = criarLivro();
                    livroAtualizado.chave = escolha;  
                    catalogo = editarNo(catalogo, livroAtualizado);
                    printf("Livro atualizado com sucesso!\n");
                    break;
                }
                case 2: {
                    catalogo = excluirNo(catalogo, escolha);
                    printf("Livro excluido com sucesso!\n");
                    break;
                }
                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        } 

        else printf("Voltando ao menu principal sem alterações.\n");
    }
     
    else printf("Nenhum livro encontrado\n");
    free(resultados); 
}

/*Funcao de Impressao*/
void imprimirCatalogo(NoBST *raiz) {
    if(raiz != NULL) {
        imprimirCatalogo(raiz->esquerda);
        exibirLivro(raiz->item);
        imprimirCatalogo(raiz->direita);
    }
}

void imprimirCatalogoCompleto(NoBST *raiz) {
   if (raiz == NULL) {
        printf("catalogo vazio\n");
        return;
    }
    imprimirCatalogo(raiz);
}
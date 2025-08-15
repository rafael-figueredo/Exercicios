#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarv{
    char info;
    struct Tarv *esq, *dir;
} Tarv;

typedef Tarv* Parv;

Parv CREATE(char info){
    Parv novo;
    novo = malloc(sizeof(Tarv));
    novo->info = info;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int POSICAO(char vetor[], int inicio, int fim, char valor){
    int i;
    for(i = inicio; i <= fim; i++){
        if(vetor[i] == valor){
            return i;
        }
    }
    return -1;
}

Parv MONTAR(char prefixo[], char infixo[], int inicio, int fim, int *pre_indice){
    Parv novo;
    int posicao;

    if(inicio > fim){
        return NULL;
    }

    novo = CREATE(prefixo[*pre_indice]);
    (*pre_indice)++;

    if(inicio == fim){
        return novo;
    }

    posicao = POSICAO(infixo, inicio, fim, novo->info);

    novo->esq = MONTAR(prefixo, infixo, inicio, posicao-1, pre_indice);
    novo->dir = MONTAR(prefixo, infixo, posicao+1, fim, pre_indice);

    return novo;
}

void POSFIXA(Parv a){
    if(a == NULL){
        return;
    }

    POSFIXA(a->esq);
    POSFIXA(a->dir);
    printf("%c", a->info);
}

void LIBERA(Parv a){
    if(a == NULL){
        return;
    }

    LIBERA(a->esq);
    LIBERA(a->dir);
    free(a);
}

int main(){
    int n, pre_indice;
    char prefixo[100], infixo[100];
    Parv raiz;

    while( scanf("%d", &n) != EOF ){
        if(n != 0){
            scanf("%s %s", prefixo, infixo);

            pre_indice = 0;
            raiz = MONTAR(prefixo, infixo, 0, n-1, &pre_indice);
            POSFIXA(raiz);
            printf("\n");
            LIBERA(raiz);
        }
    }

    return 0;
}

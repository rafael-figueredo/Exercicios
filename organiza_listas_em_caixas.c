#include <stdio.h>

/* Estrutura de um noh da lista encadeada */
typedef struct no {
    int info; // valor armazenado no noh
    struct no *prox; // ponteiro para o proximo noh
    }No;
    /* Estrutura das caixas */

typedef struct cx {
    No **caixa; // ponteiro para as caixas
    int N; // numero de caixas
    }Caixa;

No* inicializa (){
    return NULL;
}    

int h (int k , int N){
    return k%N;
}

void insere (No* caixa , int k){
    No *item = malloc(sizeof(No));

    if (caixa==NULL){
        caixa = item;
        item->info = k;
        item->prox = inicializa();
    }

    else {
        while (caixa->prox != NULL){
            caixa = caixa->prox;
        }
        caixa->prox = item;
        item->info = k;
        item->prox = NULL;
    }

    return;
}

No* retira (No*caixa , int k){
    No *p;
    if (caixa != NULL){
        while (caixa->prox->info != k || caixa ->prox != NULL){
            caixa = caixa->prox;
        }
        p = caixa->prox;
        caixa->prox = caixa->prox->prox;
        
    }
    return p;
}

Caixa* aloca_caixas(int N){
    Caixa *estrutura = malloc(sizeof(Caixa));
    estrutura->N = N;
    estrutura->caixa = malloc(N*sizeof(No*));
    for (int i=0 ; i<N ; i++){
        estrutura->caixa[i] = inicializa();
    }
    return estrutura;
}

void desaloca_lista(No*caixa) {
    No *p = caixa;
    while (caixa!=NULL){
        caixa = caixa->prox;
        free(p);
        p = caixa;
        
        
    }
    return;
}
int main(){






return 0;
}


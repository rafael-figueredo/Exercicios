#include <stdio.h>
#include <stdlib.h>
typedef struct no No;

typedef struct cx Caixa;

struct no {
    int info;
    struct no *prox;
};

struct cx {
    No **caixa;
    int N;
};

No* inicializa(){
    return NULL;
}


Caixa* aloca_caixas (int N){
    Caixa* bloco = malloc(sizeof(Caixa));
    bloco->caixa = malloc(N*sizeof(No*));
    bloco -> N = N;

    for(int i = 0 ; i < N ; i++){
        bloco ->caixa[i] = inicializa();

    }


    return bloco;
}
int h(int k , int N){
    return k % N;

}

void insere(int k , Caixa* bloco){
    No* novo = malloc(sizeof(No));
    novo->info = k;
    novo->prox = NULL;
    int p = h(k , bloco->N);

    novo -> prox = bloco -> caixa [p];
    bloco -> caixa [p] = novo;
    return;
}

No* retira (int x , Caixa* bloco){
    int p;
    No *atual , *ant;
    p = h(x , bloco -> N);
    ant = NULL;

    for(atual = bloco->caixa[p]; atual != NULL && atual->info!= x ; ){
        ant = atual;
        atual= atual->prox;
    }

    if(atual == NULL)return NULL;

    if(ant==NULL){
        bloco -> caixa[p] = bloco -> caixa[p] ->prox;
    } else{
        ant->prox = atual ->prox;
    }
    return atual;
}

void desaloca_lista (No*lista){
    No* ant = NULL , *atual;
    for(atual = lista ; atual != NULL ; ){
        ant = atual;
        atual = atual -> prox;
        free (ant);
}
    return;
}

void desaloca_caixas(Caixa *bloco){
     int N = bloco -> N;
     for (int i = 0 ; i<N ; i++){
        desaloca_lista(bloco -> caixa[i]);
     }
     free(bloco->caixa);
     free(bloco);
     return;
}



int main (){


    int N, m, i, k, x;
    No* lixo;

    Caixa *bloco;

    scanf ("%d" , &N);

    bloco = aloca_caixas(N);

    scanf ("%d" , &m);
    for  (i=0 ; i<m ; i++){
        scanf("%d" , &k);
        insere(k , bloco);
    }
    scanf("%d", &x);
    lixo = retira(x , bloco);

    if (lixo != NULL){
        printf("%d\n",lixo->info);
    }
    else {
        printf("-1\n");
    }
    free(lixo);

    for (int i = 0; i < bloco->N; i++) {
        for (No *aux = bloco->caixa[i]; aux != NULL; aux = aux->prox) {
            printf("%d ", aux->info);
        }
        printf("\n");
    }
    desaloca_caixas(bloco);
    return 0;
}

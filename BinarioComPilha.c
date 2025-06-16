#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int erro = 0;

typedef struct pilha {
    int info;
    struct pilha* prox;
} pilha;

typedef pilha* ppilha;

// adiciona um elemento no topo da pilha
ppilha PUSH(ppilha p, int* info) {
    ppilha novo = (ppilha) malloc(sizeof(pilha));
    novo->info = *info;
    novo->prox = p;
    return novo;
}

// remove o topo da pilha e coloca o valor na variável 'info'
ppilha POP(ppilha p, int* info) {
    if (p == NULL) {
        printf("Erro: Pilha vazia!\n");
        erro = 1;
        return p;
    }
    ppilha exc = p;
    *info = p->info;
    p = p->prox;
    free(exc);
    return p;
}
void ConverteBinario (int N){
    int i;
    ppilha p = malloc(sizeof(pilha));
    ppilha aux = p;
    p->prox = NULL;
    for (int i = N ; i>0 ; i = i/2){
        PUSH(aux , i%2);
        aux = aux->prox;
    }
    for (p ; p != NULL ; p = p->prox){
        p = POP(p, &i);
        printf("%d", i);
    }
}


int main(){
    int N;
    scanf("%d", &N);
    ConverteBinario(N);
    return 0;
}
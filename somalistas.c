#include <stdio.h>
#include <stdlib.h>

typedef struct pilha {
    int info;
    struct pilha*prox;
}pilha;

typedef pilha* ppilha;


ppilha PUSH(ppilha p, int* info) {
    ppilha novo = (ppilha) malloc(sizeof(pilha));
    novo->info = *info;
    novo->prox = p;
    return novo;
}

ppilha POP(ppilha p, int* info) {
    if (p == NULL) {
        printf("Erro: Pilha vazia!\n");
        return p;
    }
    ppilha exc = p;
    *info = p->info;
    p = p->prox;
    free(exc);
    return p;
}

ppilha somalista(ppilha l1, ppilha l2){
    int soma , somaprox = 0, vlrl1, vlrl2;
    ppilha l3 = NULL;
    while (l1 != NULL && l2 != NULL){
        l1 = POP(l1, &vlrl1);
        l2 = POP(l2, &vlrl2);
        soma = vlrl1 + vlrl2 + somaprox;
        somaprox = 0;
        if(soma > 9){
            soma = soma%10;
            somaprox = 1;
        }
        l3 = PUSH(l3, &soma);
    }

    while (l1 != NULL){
        l1 = POP(l1, &vlrl1);
        if (somaprox == 1){
            somaprox = 0;
            vlrl1 += 1;
        }
        if (vlrl1 > 9){
            somaprox = 1;
            vlrl1 = vlrl1%10;
        }
        l3 = PUSH(l3, &vlrl1);
    }

    while (l2 != NULL){
        l2 = POP(l2, &vlrl2);
        if (somaprox == 1){
            somaprox = 0;
            vlrl2 += 1;
        }
        if (vlrl2 > 9){
            somaprox = 1;
            vlrl2 = vlrl2%10;
        }
        l3 = PUSH(l3, &vlrl2);
    }

    if (somaprox == 1){
        l3 = PUSH(l3, &somaprox);
    }

    return l3;
}
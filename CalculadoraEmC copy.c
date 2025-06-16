#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int erro = 0;

typedef struct pilha {
    int info;
    struct pilha* prox;
} pilha;

typedef pilha* ppilha;

ppilha PUSH(ppilha p, int* info) {
    ppilha novo = (ppilha) malloc(sizeof(pilha));
    novo->info = *info;
    novo->prox = p;
    return novo;
}

ppilha POP(ppilha p, int* info) {
    if (p == NULL) {
        printf("Erro: pilha vazia!");
        erro = 1;
        return p;
    }
    ppilha exc = p;
    *info = p->info;
    p = p->prox;
    free(exc);
    return p;
}

ppilha ADD(ppilha p) {
    int a, b;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: pilha vazia!");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    int res = b + a;
    p = PUSH(p, &res);
    return p;
}

ppilha SUB(ppilha p) {
    int a, b;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: pilha vazia!");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    int res = b - a;
    p = PUSH(p, &res);
    return p;
}

ppilha MUL(ppilha p) {
    int a, b;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: pilha vazia!");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    int res = b * a;
    p = PUSH(p, &res);
    return p;
}

ppilha DIV(ppilha p) {
    int a, b;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: pilha vazia!");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    if (a == 0) {
        printf("Erro: divisao por zero!");
        erro = 1;
        return p;
    }
    p = POP(p, &b);
    int res = b / a;
    p = PUSH(p, &res);
    return p;
}

ppilha DUP(ppilha p) {
    int a;
    if (p == NULL) {
        printf("Erro: pilha vazia!");
        erro = 1;
        return p;
    }
    a = p->info;
    p = PUSH(p, &a);
    return p;
}

ppilha SWAP(ppilha p) {
    int a, b;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: pilha vazia!");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    p = PUSH(p, &a);
    p = PUSH(p, &b);
    return p;
}

ppilha ROLL(ppilha p, int N) {
    if (N <= 0) {
        printf("Erro: posicao invalida!");
        erro = 1;
        return p;
    }

    int tam = 0;
    ppilha temp = p;
    while (temp) {
        tam++;
        temp = temp->prox;
    }

    if (N > tam) {
        printf("Erro: posicao invalida!");
        erro = 1;
        return p;
    }

    ppilha aux = NULL;
    int val, i;
    for (i = 0; i < N - 1; i++) {
        p = POP(p, &val);
        aux = PUSH(aux, &val);
    }

    p = POP(p, &val);

    while (aux) {
        aux = POP(aux, &i);
        p = PUSH(p, &i);
    }

    p = PUSH(p, &val);
    return p;
}

ppilha CLEAR(ppilha p) {
    int a;
    while (p != NULL) {
        p = POP(p, &a);
    }
    return NULL;
}

void PRINT(ppilha p) {
    ppilha temp = p;
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->prox;
    }
    printf("!");
}

int main() {
    ppilha p = NULL;
    int N = 0, qntprints = 0;
    scanf("%d", &N);
    char comando[20];
    int valor;

    for (int i = 0; i < N; i++) {
        scanf("%s", comando);

        if (strcmp(comando, "PUSH") == 0) {
            scanf("%d", &valor);
            p = PUSH(p, &valor);
        } else if (strcmp(comando, "POP") == 0) {
            p = POP(p, &valor);
        } else if (strcmp(comando, "ADD") == 0) {
            p = ADD(p);
        } else if (strcmp(comando, "SUB") == 0) {
            p = SUB(p);
        } else if (strcmp(comando, "MUL") == 0) {
            p = MUL(p);
        } else if (strcmp(comando, "DIV") == 0) {
            p = DIV(p);
        } else if (strcmp(comando, "DUP") == 0) {
            p = DUP(p);
        } else if (strcmp(comando, "SWAP") == 0) {
            p = SWAP(p);
        } else if (strcmp(comando, "ROLL") == 0) {
            scanf("%d", &valor);
            p = ROLL(p, valor);
        } else if (strcmp(comando, "CLEAR") == 0) {
            p = CLEAR(p);
        } else if (strcmp(comando, "PRINT") == 0) {
            PRINT(p);
            qntprints++;
        }

        if (erro == 1) {
            break;
        }
    }

    if (qntprints == 0 && erro == 0) {
        PRINT(p);
    }

    CLEAR(p);
    return 0;
}

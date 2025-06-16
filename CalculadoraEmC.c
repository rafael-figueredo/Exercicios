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

// soma os dois primeiros elementos da pilha
ppilha ADD(ppilha p) {
    int a, b, soma;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: Elementos insuficientes para operacao\n!");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    soma = b + a;
    p = PUSH(p, &soma);
    return p;
}

// subtrai o topo da pilha do segundo elemento
ppilha SUB(ppilha p) {
    int a, b, sub;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: Elementos insuficientes para operacao\n!");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    sub = b - a;
    p = PUSH(p, &sub);
    return p;
}

// multiplica os dois primeiros elementos da pilha
ppilha MUL(ppilha p) {
    int a, b, mul;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: Elementos insuficientes para operacao\n");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    mul = b * a;
    p = PUSH(p, &mul);
    return p;
}

// divide o segundo elemento pelo topo da pilha
ppilha DIV(ppilha p) {
    int a, b, div;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: Elementos insuficientes para operacao\n");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    if (a == 0) {
        printf("Erro: Divisao por zero!\n");
        erro = 1;
        return p;
    }
    p = POP(p, &b);
    div = b / a;
    p = PUSH(p, &div);
    return p;
}

// duplica o topo da pilha
ppilha DUP(ppilha p) {
    int a;
    if (p == NULL) {
        printf("Erro: Pilha vazia para DUP!\n");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = PUSH(p, &a);
    p = PUSH(p, &a);
    return p;
}

// troca os dois primeiros elementos da pilha
ppilha SWAP(ppilha p) {
    int a, b;
    if (p == NULL || p->prox == NULL) {
        printf("Erro: Pilha vazia para SWAP!\n");
        erro = 1;
        return p;
    }
    p = POP(p, &a);
    p = POP(p, &b);
    p = PUSH(p, &a);
    p = PUSH(p, &b);
    return p;
}

// move o N-ésimo elemento para o topo da pilha
ppilha ROLL(ppilha p, int N) {
    ppilha aux = NULL;
    int i, val, tam = 0;
    ppilha temp = p;

    // calcula o tamanho da pilha
    while (temp != NULL) {
        tam++;
        temp = temp->prox;
    }

    // checa se o N é válido
    if (N <= 0 || N > tam) {
        printf("Erro: Posicao invalida!\n");
        erro = 1;
        return p;
    }

    // remove os elementos antes de N e os coloca na pilha auxiliar
    for (i = 0; i < N-1 ; i++) {
        p = POP(p, &val);
        if (erro == 1) return p; 
        aux = PUSH(aux, &val);
    }

    // remove o N-ésimo elemento
    p = POP(p, &val);
    if (erro == 1) return p; 

    // coloca os elementos de aux de volta na pilha
    while (aux != NULL) {
        aux = POP(aux, &i);
        if (erro == 1) return p; 
        p = PUSH(p, &i);
    }

    // coloca o N-ésimo elemento no topo
    p = PUSH(p, &val);
    return p;
}

// limpa toda a pilha
ppilha CLEAR(ppilha p) {
    int a;
    while (p != NULL) {
        p = POP(p, &a);
    }
    return NULL;
}

// imprime a pilha
void PRINT(ppilha p) {
    while (p != NULL) {
        printf("%d ", p->info);
        p = p->prox;
    }
    printf("\n");
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
    // se não houve nenhum PRINT, imprime o estado final da pilha
    if (qntprints == 0 && erro == 0){
        PRINT(p);
    }

    CLEAR(p);

    return 0;
}

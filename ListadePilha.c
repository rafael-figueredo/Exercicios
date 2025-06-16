#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int info;
    struct No *prox;
} Tno;

typedef Tno* Pno;

typedef struct lista {
    char nome[50];
    Pno pilha;
    struct lista *prox;
} Tlista;

typedef Tlista* Plista;

int erro = 0;

void INIT(Plista lista, char nome[]) {
    Plista novo = (Plista)malloc(sizeof(Tlista));
    strcpy(novo->nome, nome);
    novo->pilha = NULL;
    novo->prox = lista->prox;
    lista->prox = novo;
}

void PUSH(Plista lista, char nome[], int *v) {
    lista = lista->prox;
    while (lista != NULL && strcmp(nome, lista->nome) != 0) {
        lista = lista->prox;
    }
    if (lista == NULL) {
        printf("Pilha %s nao encontrada!\n", nome);
        erro = 1;
        return;
    }
    Pno novo = (Pno)malloc(sizeof(Tno));
    novo->info = *v;
    novo->prox = lista->pilha;
    lista->pilha = novo;
}

void POP(Plista lista, char nome[], int *v) {
    Plista ant = lista;
    Plista l = lista->prox;
    while (l != NULL && strcmp(nome, l->nome) != 0) {
        ant = l;
        l = l->prox;
    }
    if (l == NULL) {
        printf("Pilha %s nao encontrada!\n", nome);
        erro = 1;
        return;
    }
    if (l->pilha == NULL) {
        printf("Pilha %s vazia!\n", nome);
        erro = 1;
        return;
    }
    Pno p = l->pilha;
    *v = p->info;
    l->pilha = p->prox;
    free(p);
    if (l->pilha == NULL) {
        ant->prox = l->prox;
        free(l);
    }
}

void TOP(Plista lista, char nome[]) {
    lista = lista->prox;
    while (lista != NULL && strcmp(nome, lista->nome) != 0) {
        lista = lista->prox;
    }
    if (lista == NULL) {
        printf("Pilha %s nao encontrada!\n", nome);
        erro = 1;
        return;
    }
    if (lista->pilha == NULL) {
        printf("Pilha %s vazia!\n", nome);
        erro = 1;
        return;
    }
    printf("%d\n", lista->pilha->info);
}

void PRINT(Plista lista, char nome[]) {
    lista = lista->prox;
    while (lista != NULL && strcmp(nome, lista->nome) != 0) {
        lista = lista->prox;
    }
    if (lista == NULL) {
        printf("Pilha %s nao encontrada!\n", nome);
        erro = 1;
        return;
    }
    printf("[");
    Pno p = lista->pilha;
    while (p != NULL) {
        printf("%d", p->info);
        if (p->prox != NULL) printf(", ");
        p = p->prox;
    }
    printf("]\n");
}

void MERGE(Plista lista, char nomeA[], char nomeB[]) {
    Plista a = lista->prox, b = lista->prox, antB = lista;

    while (a != NULL && strcmp(nomeA, a->nome) != 0) {
        a = a->prox;
    }
    while (b != NULL && strcmp(nomeB, b->nome) != 0) {
        antB = b;
        b = b->prox;
    }

    if (a == NULL || b == NULL) {
        printf("Erro: pilhas nao encontradas!\n");
        erro = 1;
        return;
    }

    if (b->pilha != NULL) {
        Pno fim = b->pilha;
        while (fim->prox != NULL) {
            fim = fim->prox;
        }
        fim->prox = a->pilha;
        a->pilha = b->pilha;
    }

    antB->prox = b->prox;
    free(b);
}

void SPLIT(Plista lista, char nome[], char novoNome[], int k) {
    Plista p = lista->prox, ant = lista;
    while (p != NULL && strcmp(nome, p->nome) != 0) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        printf("Pilha %s nao encontrada!\n", nome);
        erro = 1;
        return;
    }

    Plista novo = (Plista)malloc(sizeof(Tlista));
    strcpy(novo->nome, novoNome);
    novo->pilha = NULL;
    novo->prox = NULL;

    Pno atual = p->pilha;
    Pno fim = atual;

    if (k < 0) {
        fim = NULL;
    } else {
        for (int i = 1; i < k && fim != NULL; i++) {
            fim = fim->prox;
        }
    }

    if (fim != NULL) {
        novo->pilha = atual;
        p->pilha = fim->prox;
        fim->prox = NULL;
    } else {
        novo->pilha = atual;
        p->pilha = NULL;
    }

    if (p->pilha == NULL) {
        ant->prox = p->prox;
        free(p);
    }

    novo->prox = lista->prox;
    lista->prox = novo;
}

void SHOW(Plista lista) {
    Plista p = lista->prox;
    int listasimpressas = 0;  // flag para saber se imprimiu alguma pilha

    while (p != NULL) {
        if (p->pilha != NULL) {
            printf("%s: [", p->nome);
            Pno no = p->pilha;
            while (no != NULL) {
                printf("%d", no->info);
                if (no->prox != NULL) printf(", ");
                no = no->prox;
            }
            printf("]\n");
            listasimpressas = 1;
        }
        p = p->prox;
    }

    if (!listasimpressas) {
        printf("\n");  // imprime só uma quebra de linha se não imprimiu pilhas
    }
}


void LIBERAR(Plista lista) {
    Plista p = lista->prox, auxL;
    Pno no, auxN;
    while (p != NULL) {
        no = p->pilha;
        while (no != NULL) {
            auxN = no;
            no = no->prox;
            free(auxN);
        }
        auxL = p;
        p = p->prox;
        free(auxL);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // consumir \n

    Tlista cabeca;
    cabeca.prox = NULL;
    Plista lista = &cabeca;

    for (int i = 0; i < N; i++) {
        if (erro == 1) {
            LIBERAR(lista);
            return 0;
        }

        char comando[100];
        scanf("%s", comando);

        if (strstr(comando, ":INIT")) {
            comando[strlen(comando) - 5] = '\0'; // remove ":INIT"
            INIT(lista, comando);
        }
        else if (strstr(comando, ":PUSH")) {
            int val;
            comando[strlen(comando) - 5] = '\0';
            scanf("%d", &val);
            PUSH(lista, comando, &val);
        }
        else if (strstr(comando, ":POP")) {
            comando[strlen(comando) - 4] = '\0';
            int lixo;
            POP(lista, comando, &lixo);
        }
        else if (strstr(comando, ":TOP")) {
            comando[strlen(comando) - 4] = '\0';
            TOP(lista, comando);
        }
        else if (strstr(comando, ":PRINT")) {
            comando[strlen(comando) - 6] = '\0';
            PRINT(lista, comando);
        }
        else if (strcmp(comando, "MERGE") == 0) {
            char nomeA[50], nomeB[50];
            scanf("%s %s", nomeA, nomeB);
            MERGE(lista, nomeA, nomeB);
        }
        else if (strcmp(comando, "SPLIT") == 0) {
            char nome[50], novoNome[50];
            int k;
            scanf("%s %s %d", nome, novoNome, &k);
            SPLIT(lista, nome, novoNome, k);
        }
        else if (strcmp(comando, "SHOW") == 0) {
            SHOW(lista);
        }

        getchar(); // consumir \n
    }

    LIBERAR(lista);
    return 0;
}

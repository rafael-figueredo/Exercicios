#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50

typedef struct No {
    int valor;
    struct No* proximo;
} No;

typedef struct Pilha {
    char nome[TAM_NOME];
    No* topo;
    struct Pilha* proxima;
} Pilha;

Pilha* pilhas = NULL;

// Funções auxiliares
Pilha* encontrar_pilha(const char* nome) {
    Pilha* atual = pilhas;
    while (atual) {
        if (strcmp(atual->nome, nome) == 0)
            return atual;
        atual = atual->proxima;
    }
    return NULL;
}

void remover_pilha(const char* nome) {
    Pilha** atual = &pilhas;
    while (*atual) {
        if (strcmp((*atual)->nome, nome) == 0) {
            Pilha* temp = *atual;
            *atual = (*atual)->proxima;

            No* no = temp->topo;
            while (no) {
                No* aux = no;
                no = no->proximo;
                free(aux);
            }
            free(temp);
            return;
        }
        atual = &((*atual)->proxima);
    }
}

void liberar_tudo() {
    while (pilhas) {
        remover_pilha(pilhas->nome);
    }
}

void create_stack(const char* nome) {
    Pilha* nova = (Pilha*)malloc(sizeof(Pilha));
    strcpy(nova->nome, nome);
    nova->topo = NULL;
    nova->proxima = pilhas;
    pilhas = nova;
}

void push(const char* nome, int valor) {
    Pilha* p = encontrar_pilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        liberar_tudo();
        exit(0);
    }
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = p->topo;
    p->topo = novo;
}

void pop(const char* nome) {
    Pilha* p = encontrar_pilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        liberar_tudo();
        exit(0);
    }
    if (!p->topo) {
        printf("Pilha %s vazia!\n", nome);
        liberar_tudo();
        exit(0);
    }
    No* temp = p->topo;
    p->topo = temp->proximo;
    free(temp);

    if (!p->topo)
        remover_pilha(nome);
}

void top(const char* nome) {
    Pilha* p = encontrar_pilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        liberar_tudo();
        exit(0);
    }
    if (!p->topo) {
        printf("Pilha %s vazia!\n", nome);
        liberar_tudo();
        exit(0);
    }
    printf("%d\n", p->topo->valor);
}

void print_stack(const char* nome) {
    Pilha* p = encontrar_pilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        liberar_tudo();
        exit(0);
    }
    printf("[");
    No* atual = p->topo;
    while (atual) {
        printf("%d", atual->valor);
        if (atual->proximo) printf(", ");
        atual = atual->proximo;
    }
    printf("]\n");
}

void show_all() {
    Pilha* atual = pilhas;
    while (atual) {
        printf("%s: ", atual->nome);
        print_stack(atual->nome);
        atual = atual->proxima;
    }
}

void merge(const char* nomeA, const char* nomeB) {
    Pilha* a = encontrar_pilha(nomeA);
    Pilha* b = encontrar_pilha(nomeB);
    if (!a || !b) {
        printf("Erro: pilhas nao encontradas!\n");
        liberar_tudo();
        exit(0);
    }
    if (!b->topo) {
        remover_pilha(nomeB);
        return;
    }

    // Inverter pilha B
    No* invertida = NULL;
    No* atual = b->topo;
    while (atual) {
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = atual->valor;
        novo->proximo = invertida;
        invertida = novo;
        atual = atual->proximo;
    }

    // Inserir na pilha A
    while (invertida) {
        No* temp = invertida;
        invertida = invertida->proximo;
        temp->proximo = a->topo;
        a->topo = temp;
    }

    remover_pilha(nomeB);
}

void split(const char* nome, const char* novoNome, int k) {
    Pilha* origem = encontrar_pilha(nome);
    if (!origem) {
        printf("Pilha %s nao encontrada!\n", nome);
        liberar_tudo();
        exit(0);
    }

    create_stack(novoNome);
    Pilha* destino = encontrar_pilha(novoNome);

    for (int i = 0; i < k; i++) {
        if (!origem->topo) break;
        No* temp = origem->topo;
        origem->topo = temp->proximo;

        temp->proximo = destino->topo;
        destino->topo = temp;
    }

    if (!origem->topo) {
        remover_pilha(nome);
    }
}

int main() {
    int N;
    scanf("%d\n", &N);
    char linha[100];
    for (int i = 0; i < N; i++) {
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = 0;

        if (strstr(linha, ":INIT")) {
            char nome[TAM_NOME];
            sscanf(linha, "%[^:]:INIT", nome);
            create_stack(nome);
        } else if (strstr(linha, ":PUSH")) {
            char nome[TAM_NOME];
            int valor;
            sscanf(linha, "%[^:]:PUSH %d", nome, &valor);
            push(nome, valor);
        } else if (strstr(linha, ":POP")) {
            char nome[TAM_NOME];
            sscanf(linha, "%[^:]:POP", nome);
            pop(nome);
        } else if (strstr(linha, ":TOP")) {
            char nome[TAM_NOME];
            sscanf(linha, "%[^:]:TOP", nome);
            top(nome);
        } else if (strstr(linha, ":PRINT")) {
            char nome[TAM_NOME];
            sscanf(linha, "%[^:]:PRINT", nome);
            print_stack(nome);
        } else if (strncmp(linha, "MERGE", 5) == 0) {
            char a[TAM_NOME], b[TAM_NOME];
            sscanf(linha, "MERGE %s %s", a, b);
            merge(a, b);
        } else if (strncmp(linha, "SPLIT", 5) == 0) {
            char origem[TAM_NOME], novoNome[TAM_NOME];
            int k;
            sscanf(linha, "SPLIT %s %s %d", origem, novoNome, &k);
            split(origem, novoNome, k);
        } else if (strcmp(linha, "SHOW") == 0) {
            show_all();
        }
    }

    liberar_tudo();
    return 0;
}

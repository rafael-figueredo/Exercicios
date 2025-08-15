#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarv{
    char nome[51], numero[12];
    struct Tarv *esq, *dir;
} Tarv;

typedef Tarv* Parv;

Parv ADD (Parv a, char nome[], char numero[]){
    Parv novo;
    if(a == NULL){
        novo = malloc(sizeof(Tarv));
        strcpy(novo->nome, nome);
        strcpy(novo->numero, numero);
        novo->dir = NULL;
        novo->esq = NULL;
        return novo;
    }

    if(strcmp(nome, a->nome) == 0){
        printf("Contato ja existe\n");
        return a;
    }

    if(strcmp(nome, a->nome) < 0){
        a->esq = ADD(a->esq, nome, numero);
        return a;
    }

    else {
        a->dir = ADD(a->dir, nome, numero);
        return a;
    }

}

void SEARCH (Parv a, char nome[]){
    if(a == NULL){
        printf("Contato nao encontrado\n");
        return;
    }

    if(strcmp(nome, a->nome) == 0){
        printf("%s\n", a->numero);
        return;
    }

    if (strcmp(nome, a->nome) > 0){
        SEARCH(a->dir, nome);
        return;
    }

    if (strcmp(nome, a->nome) < 0){
        SEARCH(a->esq, nome);
        return;
    }

}

void LIST(Parv a){
    if(a == NULL){
        return;
    }

    LIST(a->esq);
    printf("Nome: %s - Telefone: %s\n", a->nome, a->numero);
    LIST(a->dir);
}

void libera(Parv a){
    if(a == NULL){
        return;
    }
    libera(a->esq);
    libera(a->dir);
    free(a);
}

int main(){
    int N;
    do{
        scanf("%d", &N);
    }while(N > 100 || N < 0);
    
    char linha[100], comando[10], nome[51], numero[12];
    Parv raiz = NULL;

    getchar(); // tira o \n

    for(int i = 0; i < N; i++){
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%s", comando);

        if(strcmp(comando, "ADD") == 0){
            if(sscanf(linha, "%*s %s %s", nome, numero) == 2){
                raiz = ADD(raiz, nome, numero);
            }
        }

        else if(strcmp(comando, "SEARCH") == 0){
            if(sscanf(linha, "%*s %s", nome) == 1){
                SEARCH(raiz, nome);
            }
        }

        else if(strcmp(comando, "LIST") == 0){
            if(raiz == NULL){
                printf("Agenda vazia\n");
            } else {
                LIST(raiz);
            }
        }
    }

    libera(raiz);
    return 0;
}

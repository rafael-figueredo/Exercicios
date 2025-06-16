#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
    int codigo;
    char descricao[50];
    struct lista*prox;
    struct lista*ant;
}Tlista;

typedef Tlista* Plista;

Plista SEARCH (Plista lista , int codigo){
    Plista p = lista;
    if (lista == NULL){
        return NULL;
    }

    do{
        p = p->prox;
    } while(p != lista && p->codigo != codigo);

    if (p->codigo == codigo){
        return p;
    }

    else {
        return NULL;
    }
}

Plista ADD (Plista lista , int codigo , char descricao[50]){
    Plista p;
    p = SEARCH(lista, codigo);
    if(p != NULL){
        printf("Codigo ja existente!\n");
        return lista;
    }

     Plista novo = (Plista)(malloc(sizeof(Tlista)));

    if(lista == NULL){
        novo->prox = novo;
        novo->ant = novo;
    }
    
    else{
        novo->prox = lista->prox;
        novo->ant = lista;
        lista->prox->ant = novo;
        lista->prox = novo;

    }

    novo->codigo = codigo;
    strcpy(novo->descricao , descricao);
    return novo;
}

Plista REMOVE(Plista lista , int codigo){
    Plista p = SEARCH(lista , codigo);
    if (p == NULL){     
        printf("Codigo nao encontrado!\n");
        return lista;
    }

    if(p->prox == p){
        free(p);
        return NULL;
    }

    else{
        p->ant->prox = p->prox;
        p->prox->ant = p->ant;
        if(lista == p){
            lista = lista->ant;
        }
        free(p);
        return lista;
    }
}

void PRINT_FORWARD(Plista lista){
    Plista p = lista;
    if(lista == NULL){
        printf("Lista vazia!\n");
        return;
    }

    do{
        p = p->prox;
        printf("Codigo: %d - %s\n", p->codigo , p->descricao);
    } while (p != lista);

}

void PRINT_REVERSE(Plista lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    Plista p = lista;

    // se houver so um elemento
    if (lista->ant == lista) {
        printf("Codigo: %d - %s\n", p->codigo, p->descricao);
        return;
    }

    do {
        printf("Codigo: %d - %s\n", p->codigo, p->descricao);
        p = p->ant;
    } while (p != lista);
}


void liberar(Plista lista) {
    if (lista == NULL) return;

    Plista atual = lista->prox;
    while (atual != lista) {
        Plista temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

int main() {
    int N, i;
    char linha[100];
    char comando[20], descricao[50];
    Plista lista = NULL;
    Plista p;
    int comandos_executados = 0;
    int entrada_valida = 1;

    if (scanf("%d", &N) != 1 || N < 0 || N > 100) {
        printf("N nao e valido!\n");
        return 0;
    }

    getchar(); // consumir '\n' depois de N

    while (comandos_executados < N && entrada_valida == 1) {
    if (fgets(linha, sizeof(linha), stdin) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; // remove \n

        if (sscanf(linha, "%s", comando) == 1) {

            if (strcmp(comando, "ADD") == 0) {
                if (sscanf(linha, "%*s %d %[^\n]", &i, descricao) == 2) {
                    lista = ADD(lista, i, descricao);
                    comandos_executados++;
                } else {
                    entrada_valida = 0;
                }
            }

            else if (strcmp(comando, "REMOVE") == 0) {
                if (sscanf(linha, "%*s %d", &i) == 1) {
                    lista = REMOVE(lista, i);
                    comandos_executados++;
                } else {
                    entrada_valida = 0;
                }
            }

            else if (strcmp(comando, "SEARCH") == 0) {
                if (sscanf(linha, "%*s %d", &i) == 1) {
                    p = SEARCH(lista, i);
                    if (p != NULL)
                        printf("Codigo: %d - %s\n", p->codigo, p->descricao);
                    else
                        printf("Codigo nao encontrado!\n");
                    comandos_executados++;
                } else {
                    entrada_valida = 0;
                }
            }

            else if (strcmp(comando, "PRINT_FORWARD") == 0) {
                PRINT_FORWARD(lista);
                comandos_executados++;
            }

            else if (strcmp(comando, "PRINT_REVERSE") == 0) {
                PRINT_REVERSE(lista);
                comandos_executados++;
            }

            else {
                entrada_valida = 0;
            }

        } else {
            entrada_valida = 0;
        }

    } else {
        entrada_valida = 0;
    }
}

    if (comandos_executados < N) {
        printf("N superior ao numero de comandos!\n");
    }

    liberar(lista);
    return 0;
}

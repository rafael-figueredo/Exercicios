#include <stdio.h>
#include <stdlib.h>
#define MAX_LINHA 100
typedef struct no *pme;

struct no {
int col, val;
pme prox;
};

typedef pme matriz[MAX_LINHA];

void inicializa(matriz m, int lin){ 
    int i;
    for(i = 0 ; i < lin ; i++){
        m[i] = NULL;
    }
}

void insere(matriz m , int val, int lin, int col){
    pme p, novo, ant;
    novo = (pme)(malloc(sizeof(struct no)));
    novo->col = col;
    novo->val = val;
    novo->prox = NULL;
    if (m[lin] == NULL || m[lin]->col > col) {
        // insere no inicio da lista
        novo->prox = m[lin];
        m[lin] = novo;
    }
    
    else {
        ant = m[lin];
        p = ant->prox;
        while (p != NULL && p->col < col) {
            ant = p;
            p = p->prox;
        }

        ant->prox = novo;
        novo->prox = p;
    }
}


int busca (matriz m, int lin, int col){
    pme p = m[lin];
    while (p != NULL && p->col <= col){
        if (p->col == col){
            return p->val;
        }
        
        p = p->prox;
    }

    return 0;
}

void somamatriz(matriz m1, matriz m2, matriz m3, int tam){
    int val, i, j;
    inicializa(m3, tam);
    for(i = 0 ; i < tam ; i++){
        for(j = 0 ; j < tam ; j++){
            val = busca(m1, i, j) + busca(m2, i, j);
            if (val != 0){
                insere(m3, val, i, j);
           }
        }
    }   
}

void subtraimatriz(matriz m1, matriz m2, matriz m3, int tam){
    int val, i, j;
    inicializa(m3, tam);
    for(i = 0 ; i < tam ; i++){
        for(j = 0 ; j < tam ; j++){
            val = busca(m1, i, j) - busca(m2, i, j);
            if (val != 0){
                insere(m3, val, i, j);
            }
        }
    }
}

void multiplicamatriz(matriz m1, matriz m2, matriz m3, int tam){
    int i, j, k, soma, val1, val2;
    inicializa(m3, tam);
    for(i = 0 ; i < tam ; i++){
        for(j = 0 ; j < tam ; j++){
            soma = 0;
            for(k = 0 ; k < tam ; k++){
                val1 = busca(m1, i, k);
                val2 = busca(m2, k, j);
                soma = soma + (val1 * val2);
            }
            if (soma != 0){
                insere(m3, soma, i, j);
            }
        }
    }
}

void imprimematriz(matriz m, int tam){
    int i, j, val;
    for(i = 0 ; i < tam ; i++){
        for(j = 0 ; j < tam ; j++){
            val = busca(m, i, j);
            printf("%d", val);
            if (j < tam - 1){
                printf(" ");
            }
        }
        printf("\n");
    }
}

void libera(matriz m, int tam){
    int i;
    pme p, temp;
    for(i = 0 ; i < tam ; i++){
        p = m[i];
        while(p != NULL){
            temp = p;
            p = p->prox;
            free(temp);
        }
        m[i] = NULL;
    }
}

int main() {
    int acao, tam, i, j, val;
    matriz m1, m2, m3;

    scanf("%d", &acao);
    scanf("%d", &tam);

    inicializa(m1, tam);
    inicializa(m2, tam);

    for(i = 0 ; i < tam ; i++){
        for(j = 0 ; j < tam ; j++){
            scanf("%d", &val);
            if (val != 0){
                insere(m1, val, i, j);
            }
        }
    }

    for(i = 0 ; i < tam ; i++){
        for(j = 0 ; j < tam ; j++){
            scanf("%d", &val);
            if (val != 0){
                insere(m2, val, i, j);
            }
        }
    }

    if (acao == 1){
        somamatriz(m1, m2, m3, tam);
    } else if (acao == 2){
        subtraimatriz(m1, m2, m3, tam);
    } else if (acao == 3){
        multiplicamatriz(m1, m2, m3, tam);
    }

    imprimematriz(m3, tam);

    libera(m1, tam);
    libera(m2, tam);
    libera(m3, tam);

    return 0;
}

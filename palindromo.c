#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct pilha {
    char c;
    struct pilha*prox;
}Tpilha;
typedef Tpilha* Ppilha;

Ppilha PULL(Ppilha p, char c){
    Ppilha novo = (Ppilha)(malloc(sizeof(Tpilha)));
    novo->prox = p;
    novo->c = c;
    return novo;
}

Ppilha POP(Ppilha p,char *c){
    Ppilha temp;
    if (p == NULL){
        return NULL;
    }
    else {
        *c = p->c;
        temp = p;
        p = p->prox;
        free(temp);
        return p;
    }
}

int main(){
    Ppilha p = NULL;
    char c;
    char palavra[100];
    int tam, i, ehpalindromo = 1;
    fgets(palavra, 100, stdin);
    palavra[strcspn(palavra, "\n")] = '\0';
    tam = strlen(palavra);
    for(i = 0 ; i < tam ; i++){
        p = PULL(p, palavra[i]);
    }
    for(i = 0 ; i < tam ; i++){
        p = POP(p , &c);
        if(c != palavra[i]){
            ehpalindromo = 0;
        }
    }
    printf("%d\n", ehpalindromo);
    return 0;
}

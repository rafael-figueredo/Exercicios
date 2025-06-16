#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
  struct no* prox;
  int info;
} Tno;

typedef Tno* Pno;

typedef struct fila {
  Pno ini, fim;
} Tfila;

typedef Tfila* Pfila;

// inicia a fila
Pfila Cria_fila(Pfila fila) {
  fila = (Pfila)malloc(sizeof(Tfila));
  fila->ini = NULL;
  fila->fim = NULL;
  return fila;
}

// adiciona na fila
void AddFila(Pfila fila,int info){
Pno novo = (Pno)malloc(sizeof(Tno));
novo->info = info;
novo->prox = NULL;
  if (fila->ini == NULL){
    fila->ini = fila->fim = novo;
  }
  else {
    fila->fim->prox = novo;
    fila->fim = novo;
  }
  return;
}

void RmvFila(Pfila fila , int *v){
  if(fila->ini == NULL){
    printf("erro");
  }
  else if(fila->ini == fila->fim){
    *v = fila->ini->info;
    free(fila->ini);
    fila->ini = fila->fim = NULL;
  
  }
  else {
    Pfila p = fila->ini;
    fila->ini = fila->ini->prox;
    free(p);
  }
  return;
}

int main(){
  Pfila f = Cria_fila(f);
  Pfila f_pares = Cria_fila(f_pares);
  Pfila f_impares = Cria_fila(f_impares);
  int i;
  for (i ; i != -1;){
    scanf("%d", &i);
    AddFila(f,i);
  }
  while (f->ini != NULL){
    RmvFila(f,&i);
    if (i%2 == 0){
      AddFila(f_pares,i);
    }
    else {
      AddFila(f_impares,i);
    }
    printf("%d\n", i);
  
  }
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
typedef struct no {
  struct no* prox;
  int ID;
  char msg[50];
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
 
// adiciona no fim da fila
Pfila Enqueue(Pfila fila, int ID, char msg[]) {
  Pno novo = (Pno)malloc(sizeof(Tno));
  novo->prox = NULL;
  novo->ID = ID;
  strcpy(novo->msg, msg);
  if (fila->ini == NULL) {
    fila->ini = novo;
    fila->fim = novo;
  } else {
    fila->fim->prox = novo;
    fila->fim = novo;
  }
  return fila;
}
 
// remove do inicio da fila
Pfila Dequeue(Pfila fila, int *erro) {
  Pno p = fila->ini;
 
  if (fila->ini == fila->fim) {
    if (fila->ini == NULL) {
      printf("Fila vazia!\n");
      *erro = 1;
      return fila;
    } else {
      fila->ini = NULL;
      fila->fim = NULL;
    }
  } else {
    fila->ini = fila->ini->prox;
  }
 
  free(p);
  return fila;
}
 
// imprime a lista a partir do inicio
void Printfila(Pfila fila) {
  Pno p;
  if (fila->ini == NULL) {
    printf("\n");
    return;
  }
  for (p = fila->ini; p != NULL; p = p->prox) {
    printf("ID: %d - %s\n", p->ID, p->msg);
  }
}
 
// limpa a fila inteira
Pfila Clearfila(Pfila fila,int *erro) {
  while (fila->ini != NULL) {
    fila = Dequeue(fila,&erro);
  }
  return fila;
}
 
// função auxiliar para converter string para maiúscula
void maiuscula(char* s) {
  for (int i = 0; s[i]; i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      s[i] -= ('a' - 'A');
    }
  }
}
 
int main() {
  int erro = 0;
  int N;
  char str[50];
  do {scanf("%d", &N);} while (N>100 || N<=0);
  getchar();
  Pfila fila = Cria_fila(fila);
 
  for (int i = 0; i < N; i++) {
    scanf("%s", str);
    maiuscula(str);
 
    if (strcmp(str, "ENQUEUE") == 0) {
      int ID;
      char msg[50];
      scanf("%d", &ID);
      getchar(); // consome o espaço ou \n
      fgets(msg, 50, stdin);
      msg[strcspn(msg, "\n")] = '\0'; // remove o \n do final
      fila = Enqueue(fila, ID, msg);
 
    } else if (strcmp(str, "DEQUEUE") == 0) {
      fila = Dequeue(fila,&erro);
      if (erro == 1){
        free(fila);
        return 0;
      }
 
    } else if (strcmp(str, "PRINT") == 0) {
      Printfila(fila);
 
    } else if (strcmp(str, "CLEAR") == 0) {
      fila = Clearfila(fila,&erro);
    }
  }
 
  fila = Clearfila(fila,&erro);
  free(fila);
  return 0;
}
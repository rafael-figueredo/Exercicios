#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct Operacao {
        char tipo; // ’I’ para inserir, ’R’ para remover
        char caractere; // caractere inserido ou removido
        int posicao; // posicao no texto onde a operacao ocorreu
        struct Operacao *prox; // ponteiro para a proxima operacao na pilha
} Operacao;

    typedef struct Editor {
        char texto[1000];
        int tamanho;
        Operacao *desfazer;
        Operacao *refazer;
} Editor;

    Operacao* NovaOperacao(char tipo, char caractere, int posicao) {
        Operacao *op = (Operacao*)malloc(sizeof(Operacao));
        op->tipo = tipo;
        op->caractere = caractere;
        op->posicao = posicao;
        op->prox = NULL;
        return op;
}

    void empilhar(Operacao **pilha, Operacao *op) {
        op->prox = *pilha;
        *pilha = op;
}

    Operacao* desempilhar(Operacao **pilha) {
        if (*pilha == NULL) return NULL;
        Operacao *topo = *pilha;
        *pilha = topo->prox;
        return topo;
}

    Editor* inicializarEditor(int tam, char *txt) {
        Editor *ed = (Editor*)malloc(sizeof(Editor));
        strncpy(ed->texto, txt, tam);
        ed->texto[tam] = '\0';
        ed->tamanho = tam;
        ed->desfazer = NULL;
        ed->refazer = NULL;
        return ed;
}

    void inserir(Editor *ed, char c, int pos) {
        if (pos < 0 || pos > ed->tamanho || ed->tamanho >= 999) return;
        for (int i = ed->tamanho; i > pos; i--) {
            ed->texto[i] = ed->texto[i - 1];
        }
        ed->texto[pos] = c;
        ed->tamanho++;
        ed->texto[ed->tamanho] = '\0';
        empilhar(&ed->desfazer, NovaOperacao('I', c, pos));
        while (ed->refazer) free(desempilhar(&ed->refazer));
}

    void remover(Editor *ed, int pos) {
        if (pos < 0 || pos >= ed->tamanho) return;
        char c = ed->texto[pos];
        for (int i = pos; i < ed->tamanho - 1; i++) {
            ed->texto[i] = ed->texto[i + 1];
        }
        ed->tamanho--;
        ed->texto[ed->tamanho] = '\0';
        empilhar(&ed->desfazer, NovaOperacao('R', c, pos));
        while (ed->refazer) free(desempilhar(&ed->refazer));
}

    void desfazer(Editor *ed) {
        Operacao *op = desempilhar(&ed->desfazer);
        if (!op) return;

        if (op->tipo == 'I') {
            for (int i = op->posicao; i < ed->tamanho - 1; i++) {
                ed->texto[i] = ed->texto[i + 1];
            }
            ed->tamanho--;
            ed->texto[ed->tamanho] = '\0';
        } else if (op->tipo == 'R') {
            for (int i = ed->tamanho; i > op->posicao; i--) {
                ed->texto[i] = ed->texto[i - 1];
            }
            ed->texto[op->posicao] = op->caractere;
            ed->tamanho++;
            ed->texto[ed->tamanho] = '\0';
        }
        empilhar(&ed->refazer, op);
}

    void refazer(Editor *ed) {
        Operacao *op = desempilhar(&ed->refazer);
        if (!op) return;

        if (op->tipo == 'I') {
            for (int i = ed->tamanho; i > op->posicao; i--) {
                ed->texto[i] = ed->texto[i - 1];
            }
            ed->texto[op->posicao] = op->caractere;
            ed->tamanho++;
            ed->texto[ed->tamanho] = '\0';
        } else if (op->tipo == 'R') {
            for (int i = op->posicao; i < ed->tamanho - 1; i++) {
                ed->texto[i] = ed->texto[i + 1];
            }
            ed->tamanho--;
            ed->texto[ed->tamanho] = '\0';
        }
        empilhar(&ed->desfazer, op);
}

    void liberar(Editor *ed) {
        while (ed->desfazer) free(desempilhar(&ed->desfazer));
        while (ed->refazer) free(desempilhar(&ed->refazer));
        free(ed);
}

    int main() {
        int n, m;
        char txt[1000];
        scanf("%d", &n);
        scanf("%s", txt);
        Editor *ed = inicializarEditor(n, txt);

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            char op, c;
            int pos;
            scanf(" %c", &op);
            if (op == 'I') {
                scanf(" %c %d", &c, &pos);
                inserir(ed, c, pos);
            } else if (op == 'R') {
                scanf("%d", &pos);
                remover(ed, pos);
            } else if (op == 'U') {
                desfazer(ed);
            } else if (op == 'E') {
                refazer(ed);
            }
            printf("%s\n", ed->texto);
        }

    liberar(ed);
    return 0;
}

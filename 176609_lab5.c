#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    // estrutura da tarefa
    typedef struct Tarefa {
        int tarefaID;
        int tarefaPaginas;
        char tarefaPrioridade;
        struct Tarefa* proximaTarefa;
        struct Tarefa* anteriorTarefa;
    } Tarefa;

    // estrutura da fila
    typedef struct {
        Tarefa* primeiraTarefa;
        Tarefa* ultimaTarefa;
        int totalTarefas;
    } FilaTarefas;

    // definicao das funcoes
    FilaTarefas* criarFilaTarefas() {
        FilaTarefas* fila = (FilaTarefas*)malloc(sizeof(FilaTarefas));
        fila->primeiraTarefa = NULL;
        fila->ultimaTarefa = NULL;
        fila->totalTarefas = 0;
        return fila;
    }

    void apagarFilaTarefas(FilaTarefas* fila) {
        while (fila->primeiraTarefa != NULL) {
            Tarefa* tempTarefa = fila->primeiraTarefa;
            fila->primeiraTarefa = fila->primeiraTarefa->proximaTarefa;
            free(tempTarefa);
        }
        free(fila);
    }

    void adicionarTarefa(FilaTarefas* fila, int tarefaID, int tarefaPaginas, char tarefaPrioridade) {
        Tarefa* novaTarefa = (Tarefa*)malloc(sizeof(Tarefa));
        novaTarefa->tarefaID = tarefaID;
        novaTarefa->tarefaPaginas = tarefaPaginas;
        novaTarefa->tarefaPrioridade = tarefaPrioridade;
        novaTarefa->proximaTarefa = NULL;
        novaTarefa->anteriorTarefa = NULL;

        if (fila->primeiraTarefa == NULL || tarefaPrioridade == 'U') { // adiciona no inicio se for urgente
            novaTarefa->proximaTarefa = fila->primeiraTarefa;
            fila->primeiraTarefa = novaTarefa;
            if (fila->ultimaTarefa == NULL) {
                fila->ultimaTarefa = novaTarefa;
            }
        } else { // adiciona no fim se a prioridade for normal
            fila->ultimaTarefa->proximaTarefa = novaTarefa;
            novaTarefa -> anteriorTarefa = fila->ultimaTarefa;
            fila->ultimaTarefa = novaTarefa;
        }
        fila->totalTarefas++;
    }

    Tarefa* processarTarefa(FilaTarefas* fila) {
        if (fila->primeiraTarefa == NULL) {
            return NULL;
        }
        Tarefa* tarefaAtual = fila->primeiraTarefa;
        fila->primeiraTarefa = fila->primeiraTarefa->proximaTarefa;
        fila -> primeiraTarefa -> anteriorTarefa = NULL;
        if (fila->primeiraTarefa == NULL) {
            fila->ultimaTarefa = NULL;
        }
        fila->totalTarefas--;
        return tarefaAtual;
}

    Tarefa* cancelarTarefa(FilaTarefas* fila, int tarefaID) {
        Tarefa* tarefaAtual = fila->primeiraTarefa;
        Tarefa* tarefaAnterior = NULL;

        while (tarefaAtual != NULL) {
            if (tarefaAtual->tarefaID == tarefaID) {
                if (tarefaAnterior == NULL) {
                    fila->primeiraTarefa = tarefaAtual->proximaTarefa;
                    fila -> primeiraTarefa -> anteriorTarefa = NULL;
                } else {
                    tarefaAnterior->proximaTarefa = tarefaAtual->proximaTarefa;
                    tarefaAnterior->proximaTarefa->anteriorTarefa = tarefaAnterior;
                }
                if (fila->ultimaTarefa == tarefaAtual) {
                    fila->ultimaTarefa = tarefaAnterior;
                    fila->ultimaTarefa->proximaTarefa=NULL;
                }
                fila->totalTarefas--;
                return tarefaAtual;
            }
            tarefaAnterior = tarefaAtual;
            tarefaAtual = tarefaAtual->proximaTarefa;
        }
        return NULL;
    }

    void exibirTarefas(FilaTarefas* fila, int ordemReversa) {
        if (fila->totalTarefas == 0) {
            printf("\n");
            return;
        }

        Tarefa* tarefaAtualultima;
        Tarefa* tarefaAtual = fila->primeiraTarefa;
        int i = 0;
        if (ordemReversa == -1) {
            for ( tarefaAtualultima  = fila->ultimaTarefa ; tarefaAtualultima != NULL ; tarefaAtualultima = tarefaAtualultima->anteriorTarefa) {
                printf("%d %d %c\n", tarefaAtualultima->tarefaID , tarefaAtualultima->tarefaPaginas, tarefaAtualultima->tarefaPrioridade);
            }
        } else  {
            for ( tarefaAtual  = fila->ultimaTarefa ; tarefaAtual != NULL ; tarefaAtual = tarefaAtual->proximaTarefa) {
                printf("%d %d %c\n", tarefaAtual->tarefaID , tarefaAtual->tarefaPaginas, tarefaAtual->tarefaPrioridade);
            }
        }
}

    // funcao main
    int main() {
        int numeroOperacoes;
        scanf("%d", &numeroOperacoes);

        FilaTarefas* fila = criarFilaTarefas();

        for (int i = 0; i < numeroOperacoes; i++) {
            char operacao;
            scanf(" %c", &operacao);

            if (operacao == 'A') { // adiciona a tarefa
                int tarefaID, tarefaPaginas;
                char tarefaPrioridade;
                scanf("%d %d %c", &tarefaID, &tarefaPaginas, &tarefaPrioridade);
                adicionarTarefa(fila, tarefaID, tarefaPaginas, tarefaPrioridade);

            } else if (operacao == 'P') { // processa a tarefa
                Tarefa* tarefaProcessada = processarTarefa(fila);
                if (tarefaProcessada != NULL) {
                    printf("%d %d %c\n", tarefaProcessada->tarefaID, tarefaProcessada->tarefaPaginas, tarefaProcessada->tarefaPrioridade);
                    free(tarefaProcessada);
                } else {
                    printf("\n");
            }

        }   else if (operacao == 'C') { // remove a tarefa
                int tarefaID;
                scanf("%d", &tarefaID);
                Tarefa* tarefaCancelada = cancelarTarefa(fila, tarefaID);
                if (tarefaCancelada != NULL) {
                    printf("%d %d %c\n", tarefaCancelada->tarefaID, tarefaCancelada->tarefaPaginas, tarefaCancelada->tarefaPrioridade);
                    free(tarefaCancelada);
            }   else {
                    printf("\n");
            }

        }   else if (operacao == 'E') { // exibe todas as tarefas
                int ordemReversa;
                scanf("%d", &ordemReversa);
                exibirTarefas(fila, ordemReversa);
        }
    }

        apagarFilaTarefas(fila);






    return 0;
}

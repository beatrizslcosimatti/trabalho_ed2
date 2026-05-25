#include <stdio.h>
#include <time.h>
#include "algoritmos.h"

void bubble_sort(int *vetor, int n, Metricas *m){
    //inicialização das métricas
    m->comparacoes = 0; //qtd de comparações entre os valores do vetor
    m->trocas = 0; //qtd de trocas realizadas

    //inicia a contagem do tempo de execução
    clock_t inicio = clock();

    for (int i = 0; i < n-1; i++){
        int houveTroca = 0;

        for(int j = 0; j < n-i-1; j++){
            m->comparacoes++; //incrementa contador de comparações 

            if(vetor[j] > vetor[j+1]){
                int temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;

                m->trocas++; //incrementa contador de trocas
                houveTroca = 1;
            }
        }

        if (houveTroca == 0){ //se não houve troca, já está ordenado
            break;
        }
    }

    //finaliza a contagem do tempo de execução
    clock_t fim = clock();
    m->tempoExecucao = (double)(fim - inicio)/CLOCKS_PER_SEC;

}
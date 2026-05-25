#include <stdio.h>
#include <time.h>
#include "algoritmos.h"

void insertion_sort(int *vetor, int n, Metricas *m){
    //inicialização das métricas
    m->comparacoes = 0; //qtd de comparações entre os valores do vetor
    m->trocas = 0; //qtd de trocas realizadas

    //inicia a contagem do tempo de execução
    clock_t inicio = clock();

    for (int i = 1; i < n; i++) {
        int chave = vetor[i]; 
        int j = i - 1;

        while (j >= 0) {
            m->comparacoes++; //incrementa contador de comparações 

            if (vetor[j] > chave) {
                vetor[j + 1] = vetor[j]; //desloca o elemento para a direita
                m->trocas++; //incrementa contador de trocas
                j--;
            } else {
                break; 
            }
        }
        
        //coloca a chave na posição correta
        vetor[j + 1] = chave;
    }

    //finaliza a contagem do tempo de execução
    clock_t fim = clock();
    m->tempoExecucao = (double)(fim - inicio)/CLOCKS_PER_SEC;
}
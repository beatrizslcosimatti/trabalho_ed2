#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"

void troca(int *a, int *b, Metricas *m)
{
    int temp = *a;

    *a = *b;
    *b = temp;

    m->trocas++;
    m->operacoes += 3;
}

// MEDIANA DE TRÊS
// O método da Mediana de Três é utilizado para determinar o pivô utilizado para o Quick Sort
// Consiste-se em determinar a mediana entre o elemento inicial, central e final do vetor
// Desse modo, o método ordena esses elementos em ordem crescente e retorna o elemento central, 
// que é a mediana entre três elementos

int medianaDeTres(int *vetor, int inicio, int fim, Metricas *m)
{
    int meio = inicio + (fim - inicio) / 2; // calcula o índice central do vetor

    m->comparacoes++;
    m->operacoes++; // operação de comparação
    if (vetor[inicio] > vetor[meio])
    {
        // troca entre os valores: 
        troca(&vetor[inicio], &vetor[meio], m);
    }

    m->comparacoes++;
    m->operacoes++; // operação de comparação
    if (vetor[inicio] > vetor[fim])
    {
        // troca entre os valores: 
        troca(&vetor[inicio], &vetor[fim], m);
    }

    m->comparacoes++;
    m->operacoes++; // operação de comparação
    if (vetor[meio] > vetor[fim])
    {
        // troca entre os valores: 
        troca(&vetor[meio], &vetor[fim], m);
    }

    // após a ordenação: vetor[inicio] <= vetor[meio] <= vetor[fim]

    return vetor[meio];
}

// PARTICIONAMENTO DE HOARE

int particionamento(int *vetor, int inicio, int fim, Metricas *m)
{
    int pivo = medianaDeTres(vetor, inicio, fim, m);

    int i = inicio - 1;
    int j = fim + 1;

    while (1)
    {
        do
        {
            i++;
            m->operacoes++;
            m->comparacoes++;
        }
        while (vetor[i] < pivo);

        do
        {
            j--;
            m->operacoes++;
            m->comparacoes++;
        }
        while (vetor[j] > pivo);

        m->comparacoes++;
        if (i >= j)
            return j;

        troca(&vetor[i], &vetor[j], m);
    }
}

void quick_sort_rec(int *vetor, int inicio, int fim, Metricas *m, int profundidade_atual)
{
    profundidade_atual++;
    m->chamadas_recursivas++;

    if (profundidade_atual > m->profundidade_maxima)
    {
        m->profundidade_maxima = profundidade_atual;
    }
    
    m->comparacoes++;
    if (inicio < fim)
    {
        int p = particionamento(vetor, inicio, fim, m);

        quick_sort_rec(vetor, inicio, p, m, profundidade_atual);
        quick_sort_rec(vetor, p + 1, fim, m, profundidade_atual);
    }
}

void quick_sort (int *vetor, int n, Metricas *m)
{
    //inicialização das métricas
    m->tempoExecucao = 0;
    m->trocas = 0;
    m->chamadas_recursivas = 0;
    m->comparacoes = 0;
    m->operacoes = 0;
    m->memoria_extra_bytes = 0;
    m->profundidade_maxima = 0;
    int profundidade_atual = 0;

    // inicia a contagem do tempo de execução
    clock_t inicio = clock();

    quick_sort_rec(vetor, 0, n - 1, m, profundidade_atual);

    // finaliza a contagem do tempo de execução
    clock_t fim = clock();

    // armazena a diferença entre ambas as contagens
    m->tempoExecucao = (double)(fim - inicio)/CLOCKS_PER_SEC;

    // determinação da memória extra utilizada
    int frame_size = sizeof(int*) + 3*sizeof(int);
    m->memoria_extra_bytes = m->profundidade_maxima * frame_size;
}
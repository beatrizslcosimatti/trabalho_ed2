#ifndef ALGORITMOS_H
#define ALGORITMOS_H

typedef struct {
    double tempoExecucao;
    long long comparacoes;
    long long trocas;
    unsigned long long memoria_extra_bytes;
    unsigned long long operacoes;
    unsigned long long copias;
} Metricas;

void bubble_sort(int *vetor, int n, Metricas *m);
void insertion_sort(int *vetor, int n, Metricas *m);

#endif
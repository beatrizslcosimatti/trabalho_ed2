#ifndef ALGORITMOS_H
#define ALGORITMOS_H

typedef struct {
    double tempoExecucao;
    long long comparacoes;
    long long trocas;
} Metricas;

void bubble_sort(int *vetor, int n, Metricas *m);

#endif
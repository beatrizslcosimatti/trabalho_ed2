#ifndef ALGORITMOS_H
#define ALGORITMOS_H
//typedef unsigned long long int int_grande;

typedef struct {
    unsigned long long int comparacoes;
    unsigned long long int trocas;
    unsigned long long int memoria_extra_bytes;
    unsigned long long int operacoes;
    unsigned long long int copias;
    unsigned long long int chamadas_recursivas;
    unsigned long long int profundidade_maxima;
} Metricas;

void bubble_sort (int *vetor, int n, Metricas *m);
void insertion_sort (int *vetor, int n, Metricas *m);
void radix_sort (int* vetor, int n, Metricas* m);
void heap_sort (int* vetor, int n, Metricas*m);
void quick_sort (int* vetor, int n, Metricas* m);

#endif 
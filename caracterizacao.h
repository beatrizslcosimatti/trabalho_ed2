#ifndef CARACTERIZACAO_H
#define CARACTERIZACAO_H

#include <stdio.h>

//funções das metricas
float calcular_desordem(int *v, int n);
int contar_repetidos(int *v, int n);
int faixa_valores(int *v, int n);
double desvio_padrao(int *v, int n);
void max_e_min(int *v, int n, int *max, int *min);

//arvore de decisao dos algoritmos
void decidir_algoritmo(int n, float desordem, int repetidos, int range, double desvio, int min);

#endif // CARACTERIZACAO_H
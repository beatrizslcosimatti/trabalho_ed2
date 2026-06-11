#include "caracterizacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//funcao da desordem:
float calcular_desordem(int *v, int n) {
    if (n <= 1) {
        return 0.0;
    }

    int quantidade_inversoes = 0;

    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            quantidade_inversoes++;
        }
    }

    float desordem = ((float)quantidade_inversoes / (n - 1)) * 100.0;
    return desordem;
}



//funcao que conta a quantidade total de elementos repetidos (copias extras)
int contar_repetidos(int *v, int n) {
    int unico = 0;

    for (int i = 0; i < n; i++) {
        int repetido = 0;

        //olha para tras para ver se o numero já apareceu
        for (int j = 0; j < i; j++) {
            if (v[i] == v[j]) {
                repetido = 1;
                break;
            }
        }

        if (!repetido)
            unico++;
    }

    return n - unico;
}


//funcao que calcula a faixa de valores:
int faixa_valores (int *v, int n){
    int max = v[0];
    int min = v[0];

    for (int i = 1; i < n; i++) {
        if (v[i] > max)
            max = v[i];

        if (v[i] < min)
            min = v[i];
    }

    int range = max - min;
    return range;
}


//funcao pra medir quao espalhados estao os valores:
double desvio_padrao(int *v, int n) {
    //se o vetor for 1 ou vazio, nao tem dispersao
    if(n<=1) return 0.0;

    double media = 0;

    for (int i = 0; i < n; i++)
        media = media + v[i];

    media = media / n;

    double soma = 0;

    for (int i = 0; i < n; i++) {
        soma = soma + pow(v[i] - media, 2);
    }

    double desvio = sqrt(soma / n);
    return desvio;
}


//funcao para achar o maximo e o minimo:
void max_e_min(int *v, int n, int *max, int *min){
    *max = v[0];
    *min = v[0];

    for (int i = 1; i < n; i++) {
        if (v[i] > *max)
            *max = v[i];

        if (v[i] < *min)
            *min = v[i];
    }
}


//decidir qual algoritmo
void decidir_algoritmo(int n, float desordem, int repetidos, int range, double desvio, int min) {
    //INSERTION
    if (n < 50 || desordem < 5.0) {
        printf("Algoritmo Escolhido: INSERTION SORT\n");
    }

    //RADIX
    else if (range <= (2 * n) && min >= 0) {
        printf("Algoritmo Escolhido: RADIX SORT\n");
    }

    //HEAP
    else if (desordem>90) {
        printf("Algoritmo Escolhido: HEAP SORT\n");
    }

    //QUICK
    else {
        printf("Algoritmo Escolhido: QUICK SORT\n");
    }
}
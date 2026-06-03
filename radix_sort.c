#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"

// Usar a lógica bit a bit para números grandes 
// ou apenas para executar de forma direta
//CASOS DE DEGRADAÇÂO:
//1.VALORES MUITO MAIORES QUE OS OUTROS. EX: [1,2,3,40000000,5]
//2.VETORES MUITO GRANDES, DEVIDO O RADIX REALIZAR COPÍAS
//3.VETORES QUASE ORDENADOS, MELHOR USAR O INSERTION O RADIX NÃO VERIFICA

void counting_sort_radix(int* arr, int n, int algarismo, int* B, Metricas* m) {
    int C[10] = {0};
    
    // Registra o espaço gasto na Stack pelo vetor de frequências (10 inteiros)
    m->memoria_extra_bytes += sizeof(C); 

    for (int i = 0; i < n; i++) {
        // Esforço da CPU para calcular o dígito (divisão/módulo) e atualizar o contador
        m->operacoes++; 
        int digito = (arr[i] / algarismo) % 10;
        C[digito]++;
    }

    for (int i = 1; i < 10; i++) {
        // Esforço da CPU para acessar as posições de memória e fazer a soma cumulativa
        m->operacoes++; 
        C[i] = C[i] + C[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        // Tráfego de memória (cópia exata de 1 elemento do vetor original para o auxiliar B)
        m->copias++; 
        // Esforço da CPU na iteração (cálculo do dígito, leitura do array e subtração da vaga)
        m->operacoes++; 
        
        int digito = (arr[i] / algarismo) % 10; 
        B[C[digito] - 1] = arr[i];       
        C[digito]--;                     
    }

    for (int i = 0; i < n; i++) {
        arr[i] = B[i];
        
        // Esforço da CPU para avançar o laço de repetição
        m->operacoes++; 
        // Tráfego de memória (cópia de volta de 1 elemento do vetor auxiliar B para o original)
        m->copias++; 
    }
}

void Radix_sort(int* arr, int n, Metricas* m) {
    if (n <= 1) return;
    
    int *B = (int *)malloc(n * sizeof(int));
    if (B == NULL) return; 

    // Registra a alocação de memória dinâmica no Heap (tamanho do array original)
    m->memoria_extra_bytes += (n * sizeof(int)); 

    int max = arr[0];
    for (int i = 1; i < n; i++) {
        // Conta o teste lógico "if" exigido para encontrar o maior valor do array
        m->comparacoes++; 
        if (arr[i] > max) max = arr[i];
    }

    for(int algarismo = 1; max / algarismo > 0; algarismo *= 10) {
        counting_sort_radix(arr, n, algarismo, B, m);
    }

    free(B); 
}
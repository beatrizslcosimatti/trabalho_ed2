#include <stdio.h>
#include <stdlib.h>
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

void radix_sort(int* arr, int n, Metricas* m) {
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

void heapify(int* arr, int n, int i, Metricas* m) {
    m->operacoes += 3; // Atribuições iniciais
    int aux = 0;
    int esquerda = 2 * i + 1; 
    int direita = 2 * i + 2;

    // Registra o esforço da CPU para comparar o pai com os filhos no IF abaixo
    m->comparacoes += 2; 

    if ( (esquerda < n && arr[i] < arr[esquerda]) || (direita < n && arr[i] < arr[direita]) ) {
        
        m->comparacoes++; // Comparação do IF interno (filho contra filho)
        if (direita >= n || arr[esquerda] > arr[direita]) {
            
            // Troca o pai com o filho da ESQUERDA
            aux = arr[i];
            arr[i] = arr[esquerda];
            arr[esquerda] = aux;
            
            m->trocas++;       // Registrou a troca
            m->operacoes += 3; // Operações de atribuição da troca
            
            m->chamadas_recursivas++; // Registra o salto de recursão
            heapify(arr, n, esquerda, m); 
            
        } else {
            
            // Troca o pai com o filho da DIREITA
            aux = arr[i];
            arr[i] = arr[direita];
            arr[direita] = aux;
            
            m->trocas++;       // Registrou a troca
            m->operacoes += 3; // Operações de atribuição da troca
            
            m->chamadas_recursivas++; // Registra o salto de recursão
            heapify(arr, n, direita, m);
        }
    }
}

void heap_sort(int* arr, int n, Metricas* m) {
    
    // PRIMEIRO FOR: Constroi o Heap (DEVE ir até >= 0)
    for(int i = (n/2 - 1); i >= 0; i--) {
        m->operacoes++; // Conta o giro do laço
        heapify(arr, n, i, m);
    }

    // SEGUNDO FOR: Extrai os maiores (Pode parar em > 0)
    for(int i = (n - 1); i > 0; i--) {
        m->operacoes++; // Conta o giro do laço
        
        // Troca a raiz (maior) com o último elemento
        int aux = 0;
        aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;
        
        m->trocas++; // Registrou a troca final
        m->operacoes += 3;
        
        // O Heapify não é chamado de forma recursiva pela raiz aqui, 
        // mas sim como uma chamada direta do laço.
        heapify(arr, i, 0, m);
    }
}



void quick_sort(int* veotor,int n,Metricas* m){}
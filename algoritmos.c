#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"

// FUNÇÃO DE TROCA ENTRE DOIS ELEMENTOS

void troca(int *a, int *b, Metricas *m)
{
    int temp = *a;

    *a = *b;
    *b = temp;

    m->trocas++;
    m->operacoes += 3;
}

// ================================================================================
// BUBBLE SORT - ALGORITMO O(n^2)
// ================================================================================

void bubble_sort(int *vetor, int n, Metricas *m){
    //inicialização das métricas
    m->comparacoes = 0; //qtd de comparações entre os valores do vetor
    m->trocas = 0; //qtd de trocas realizadas
    //m->operacoes = 0;

    //inicia a contagem do tempo de execução
    clock_t inicio = clock();
    m->operacoes++;

    m->operacoes++; //int i=0
    for (int i = 0; i < n-1; i++){
        int houveTroca = 0;
        m->operacoes+=3;

        m->operacoes++; //int j=0        
        for(int j = 0; j < n-i-1; j++){
            m->operacoes+=2;
            m->comparacoes++; //incrementa contador de comparações 

            m->operacoes++; //comparação do if
            if(vetor[j] > vetor[j+1]){
                //troca entre os valores
                troca(&vetor[j], &vetor[j+1], m);
                houveTroca = 1;
                m->operacoes++;
            }
        }

        m->operacoes++; //comparação do if
        if (houveTroca == 0){ //se não houve troca, já está ordenado
            break;
        }
    }

    //finaliza a contagem do tempo de execução
    clock_t fim = clock();
    m->tempoExecucao = (double)(fim - inicio)/CLOCKS_PER_SEC;

}

// ================================================================================
// INSERTION SORT - ALGORITMO O(n^2)
// ================================================================================

void insertion_sort(int *vetor, int n, Metricas *m){
    //inicialização das métricas
    m->comparacoes = 0; //qtd de comparações entre os valores do vetor
    m->trocas = 0; //qtd de trocas realizadas
    //m->operacoes = 0;

    //inicia a contagem do tempo de execução
    clock_t inicio = clock();

    m->operacoes++;
    for (int i = 1; i < n; i++) {
        m->operacoes+=2;

        int chave = vetor[i]; 
        int j = i - 1;
        m->operacoes+=2;

        while (j >= 0) {
            m->operacoes++;

            m->comparacoes++; //incrementa contador de comparações 

            m->operacoes++; //comparação do if
            if (vetor[j] > chave) {
                vetor[j + 1] = vetor[j]; //desloca o elemento para a direita
                m->trocas++; //incrementa contador de trocas
                j--;

                m->operacoes+=2;
            } else {
                break; 
            }
        }
        
        //coloca a chave na posição correta
        vetor[j + 1] = chave;
        m->operacoes++;
    }

    //finaliza a contagem do tempo de execução
    clock_t fim = clock();
    m->tempoExecucao = (double)(fim - inicio)/CLOCKS_PER_SEC;
}

// ================================================================================
// HEAP SORT - ALGORITMO O(n log n)
// ================================================================================

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
            troca(&arr[i], &arr[esquerda], m);
            
            m->chamadas_recursivas++; // Registra o salto de recursão
            heapify(arr, n, esquerda, m); 
            
        } else {
            
            // Troca o pai com o filho da DIREITA
            troca(&arr[i], &arr[direita], m);
            
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
        troca(&arr[0], &arr[i], m);
        
        // O Heapify não é chamado de forma recursiva pela raiz aqui, 
        // mas sim como uma chamada direta do laço.
        heapify(arr, i, 0, m);
    }
}

// ================================================================================
// QUICK SORT - ALGORITMO O(n log n)
// ================================================================================

// MEDIANA DE TRÊS

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

        // m->comparacoes++; - comparação entre elementos fora da ordenação
        if (i >= j)
            return j;

        troca(&vetor[i], &vetor[j], m);
    }
}

void quick_sort_rec(int *vetor, int inicio, int fim, Metricas *m, int profundidade_atual)
{
    profundidade_atual++;
    m->chamadas_recursivas++;

    // m->comparacoes++; - comparação entre elementos fora da ordenação 
    if (profundidade_atual > m->profundidade_maxima)
    {
        m->profundidade_maxima = profundidade_atual;
    }
    
    // m->comparacoes++; - comparação entre elementos fora da ordenação 
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

// ================================================================================
// RADIX SORT - ALGORITMO ALTERNATIVO
// ================================================================================

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
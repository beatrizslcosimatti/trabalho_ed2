#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"

//O heap não tem casos de degradação temporam devido a entradas especificas, apenas problemas em casos especificos.
//1.Problema com o cache
//2.Vetores Ordenados (Não muda nada, se tiver algum que verifica isso e faz mais rapido, usar ele)
//3.Vetores Inversamente ordenados (Não muda nada, se tiver algum que verifica isso e faz mais rapido, usar ele)
//4.Vetores com muitos elementos repetidos
    
void Heapify(int* arr, int n, int i, Metricas* m) {
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
            Heapify(arr, n, esquerda, m); 
            
        } else {
            
            // Troca o pai com o filho da DIREITA
            aux = arr[i];
            arr[i] = arr[direita];
            arr[direita] = aux;
            
            m->trocas++;       // Registrou a troca
            m->operacoes += 3; // Operações de atribuição da troca
            
            m->chamadas_recursivas++; // Registra o salto de recursão
            Heapify(arr, n, direita, m);
        }
    }
}

void Heap_sort(int* arr, int n, Metricas* m) {
    
    // PRIMEIRO FOR: Constroi o Heap (DEVE ir até >= 0)
    for(int i = (n/2 - 1); i >= 0; i--) {
        m->operacoes++; // Conta o giro do laço
        Heapify(arr, n, i, m);
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
        Heapify(arr, i, 0, m);
    }
}
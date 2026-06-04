#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmos.h"

//Pode ser problematico para o Heap, caso o
void vetor_aletorio(int*arr, int tamanho, int tamanho_elementos){
    srand(time(NULL));
    for(int i = 0; i<tamanho; i++){
        arr[i]=rand()%tamanho_elementos;
    }

}

void gera_vetor_quase_ordenado(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1; // Fica: 1, 2, 3, 4, 5...
    }
    int qtd_trocas = n * 0.05; 
    
    for (int i = 0; i < qtd_trocas; i++) {
        int pos1 = rand() % n;
        int pos2 = rand() % n;
        
        int temp = arr[pos1];
        arr[pos1] = arr[pos2];
        arr[pos2] = temp;
    }
}

void gera_vetor_discrepante(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    int qtd_outliers = (n > 100) ? n / 100 : 1;

    for (int i = 0; i < qtd_outliers; i++) {
        int posicao_aleatoria = rand() % n;
        
        // Injeta o valor 1 Bilhão (10 dígitos)
        arr[posicao_aleatoria] = 1000000000; 
    }
}

void gera_vetor_crescente(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

void gera_vetor_decrescente(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i; 
    }
}

int main(int argc, int** argv){
/* ANTES DE ESCOLHER O VETOR fazer coisas como:
    achar tamanho de entrada n
    percentual estimado de desordem
    quantidade de valores repetidos
    amplitude dos valores
    densidade de duplicatas
    presença de padrões
    entrada quase ordenada
    distribuição dos dados
*/
    char* algoritmo = "não informado";
    int tamanho = 0;
    char* arquivo_input=NULL;
    char* modo="padrao";
    return 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--algoritmo") == 0 && i + 1 < argc) {
            algoritmo = argv[i + 1];
            i++;
        } 
        else if (strcmp(argv[i], "--tamanho") == 0 && i + 1 < argc) {
            tamanho = atoi(argv[i + 1]);
            i++;
        } 
        else if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
            arquivo_input = argv[i + 1];
            i++;
        } 
        else if (strcmp(argv[i], "--modo") == 0 && i + 1 < argc) {
            modo = argv[i + 1];
            i++;
        }
    }

    if (arquivo_input != NULL) {
        printf("Modo: Lendo do arquivo %s...\n", arquivo_input);
    } 
    else if (tamanho > 0) {
        printf("Modo: Gerando %d dados dinamicamente para o algoritmo %s...\n", tamanho, algoritmo);
    } 
    else {
        printf("Uso incorreto. Exemplo: ./programa --algoritmo quick --tamanho 10000\n");
        return 1;
    }

    return 0;
}
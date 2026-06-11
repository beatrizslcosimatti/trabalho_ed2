#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "algoritmos.h"

//Pode ser problematico para o Heap, caso o
void vetor_aletorio(int*arr, int tamanho, int tamanho_elementos){
    for(int i = 0;i<tamanho;i++){
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

int* ler_vetor_arquivo(const char* nome_arquivo, int* n) {
    // Tenta abrir o arquivo no modo leitura ("r" = read)
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    // Proteção de segurança caso o professor digite o nome do arquivo errado
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo '%s'. Verifique se ele existe.\n", nome_arquivo);
        return NULL;
    }

    int contador = 0;
    int lixo_temporario;

    // 1ª PASSADA: Apenas conta quantos números inteiros existem no arquivo
    // O fscanf retorna 1 sempre que consegue ler um número com sucesso
    while (fscanf(arquivo, "%d", &lixo_temporario) == 1) {
        contador++;
    }

    // Se o arquivo estiver vazio
    if (contador == 0) {
        printf("ERRO: O arquivo '%s' esta vazio ou nao contem numeros validos.\n", nome_arquivo);
        fclose(arquivo);
        return NULL;
    }

    // Agora que sabemos o tamanho, alocamos o vetor gigante no Heap!
    int* arr = (int*)malloc(contador * sizeof(int));
    if (arr == NULL) {
        printf("ERRO: Falta de memoria (Memoria RAM insuficiente).\n");
        fclose(arquivo);
        return NULL;
    }

    // 2ª PASSADA: "Rebobina" o arquivo de volta para a primeira linha
    rewind(arquivo);

    // Lê os números de verdade e guarda no vetor recém-criado
    for (int i = 0; i < contador; i++) {
        fscanf(arquivo, "%d", &arr[i]);
    }

    // Fecha o arquivo para liberar o uso para o sistema operacional
    fclose(arquivo);

    // Atualiza a variável 'n' do main com o tamanho que acabamos de descobrir
    *n = contador; 

    return arr;
}

int main(int argc, char** argv){

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
    srand(time(NULL));

    char* algoritmo = "não informado";
    int tamanho = 0;
    char* arquivo_input=NULL;
    char* modo="padrao";
    char* tipo_distribuicao = "aleatorio";

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
        else if (strcmp(argv[i], "--distribuicao") == 0 && i + 1 < argc) {
            tipo_distribuicao = argv[i + 1];
            i++;
        }
    }
    int* arr=NULL;
    int n=0;
    if (arquivo_input != NULL) {
        
        printf("Modo: Lendo dados do arquivo '%s'...\n", arquivo_input);
        
        // Chama a nossa nova função! Passamos o &n para que a função preencha o tamanho real.
        arr = ler_vetor_arquivo(arquivo_input, &n);
        
        if (arr == NULL) {
            return 1; // Encerra o programa se deu erro na leitura
        }
        
        printf("Sucesso! %d numeros foram carregados na memoria.\n", n);

    }
    else if (tamanho > 0) {
        printf("Modo: Gerando %d dados dinamicamente para o algoritmo %s...\n", tamanho, algoritmo);
        n = tamanho;
        arr = (int*)malloc(n * sizeof(int));
        
        if (arr == NULL) {
            printf("ERRO: Falha ao alocar memoria para %d inteiros.\n", n);
            return 1;
        }

        if (strcmp(tipo_distribuicao, "aleatorio") == 0) {
            vetor_aletorio(arr, n, 100000); 
        } else if (strcmp(tipo_distribuicao, "crescente") == 0) {
            gera_vetor_crescente(arr, n);
        } else if (strcmp(tipo_distribuicao, "decrescente") == 0) {
            gera_vetor_decrescente(arr, n);
        } else if (strcmp(tipo_distribuicao, "quase_ordenado") == 0) {
            gera_vetor_quase_ordenado(arr, n);
        } else if (strcmp(tipo_distribuicao, "discrepante") == 0) {
            gera_vetor_discrepante(arr, n);
        }

        Metricas m;
        m.comparacoes = 0;
        m.trocas = 0;
        m.operacoes = 0;
        m.copias = 0;
        m.chamadas_recursivas = 0;
        m.memoria_extra_bytes = 0;

        clock_t inicio = clock();

        if (strcmp(algoritmo, "heap") == 0) {
            heap_sort(arr, n, &m);
        }else if (strcmp(algoritmo, "radix") == 0) {
            radix_sort(arr, n, &m);
        }else if (strcmp(algoritmo, "bubble") == 0){
            bubble_sort(arr,n,&m);
        }else if (strcmp(algoritmo,"insertion") == 0){
            insertion_sort(arr,n,&m);
        }else if (strcmp(algoritmo, "quick")==0){
            quick_sort(arr,n,&m);
        }else {
            printf("ERRO: Algoritmo '%s' desconhecido!\n", algoritmo);
            free(arr);
            return 1;
        }

        clock_t fim = clock();
        double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("Algoritmo: %s, \nTamanho: %d, \nTipo de distribuicao: %s, \nTempo de execucao: %.12f s, \nNumero de comparacoes: %llu, \nNumero de copias: %llu, \nNumero de operacoes: %llu, \nNumero de chamadas recursivas: %llu, \nMemoria extra utilizada: %llu bytes\n", 
                algoritmo, 
                n, 
                tipo_distribuicao, 
                tempo_execucao, 
                m.comparacoes, 
                m.copias, 
                m.operacoes,
                m.chamadas_recursivas,
                m.memoria_extra_bytes);

        free(arr);
    } 
    else {
        printf("Uso incorreto. Exemplo: ./programa --algoritmo quick --tamanho 10000\n");
        return 1;
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "algoritmos.h"
#include "caracterizacao.h"

void vetor_aletorio(int*arr, int tamanho, int tamanho_elementos){
    for(int i = 0;i<tamanho;i++){
        arr[i]=rand()%tamanho_elementos;
    }

}

void gera_vetor_quase_ordenado(int* arr, int n, double percentual) { //adicionei o double percentual aqui
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1; // Fica: 1, 2, 3, 4, 5...
    }
    //int qtd_trocas = n * 0.05; 
    int qtd_trocas = n * percentual / 100.0;
    
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

// pior caso do quick sort com mediana de 3
void gera_vetor_organ_pipe(int* arr, int n) {
    int meio = (n + 1) / 2;

    for (int i = 0; i < meio; i++) {
        arr[i] = i + 1;
    }

    for (int i = meio; i < n; i++) {
        arr[i] = n - i;
    }
}

// pior caso do quick sort com mediana de 3
void gera_vetor_intercalado(int* arr, int n) {
    int menor = 1;
    int maior = n;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            arr[i] = menor++;
        } else {
            arr[i] = maior--;
        }
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

    const char* algoritmo = "auto";
    int tamanho = 0;
    char* arquivo_input=NULL;
    char* modo="padrao";
    char* tipo_distribuicao = "aleatorio";

    //adicionando aqui p/ testar
    double percentual_desordem = 5.0;

    int* arr = NULL; 
    int n = 0;       
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
        }else if (strcmp(argv[i], "--array") == 0) {
            int count = 0;
            int j = i + 1;
            while (j < argc && argv[j][0] != '-') {
                count++;
                j++;
            }

            if (count > 0) {
                n = count;
                arr = (int*)malloc(n * sizeof(int));
                
                for (int k = 0; k < n; k++) {
                    arr[k] = atoi(argv[i + 1 + k]);
                }
                
                i = j - 1; 
            } else {
                printf("ERRO: Nenhum numero fornecido apos a flag --array.\n");
                return 1; 
            }
        }


        //adicionando aqui p/ testar
        else if (strcmp(argv[i], "--desordem") == 0 && i + 1 < argc) {
            percentual_desordem = atof(argv[i + 1]);
            i++;
        }
        
    }

    // =================================================================
    // ETAPA 1: OBTENÇÃO DO VETOR (Independente da Origem)
    // =================================================================
    if (arr != NULL && n > 0) {
        tipo_distribuicao = "terminal_manual";
        printf("Modo: Utilizando %d dados passados diretamente via terminal...\n", n);
        
    } else if (arquivo_input != NULL) {
        printf("Modo: Lendo dados do arquivo '%s'...\n", arquivo_input);
        
        arr = ler_vetor_arquivo(arquivo_input, &n);
        if (arr == NULL) {
            return 1; 
        }

    } else if (tamanho > 0) {
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
            gera_vetor_quase_ordenado(arr, n, percentual_desordem); //adicionando o percentual aqui p/ testar tbm
        } else if (strcmp(tipo_distribuicao, "discrepante") == 0) {
            gera_vetor_discrepante(arr, n);
        } else if (strcmp(tipo_distribuicao, "organ_pipe") == 0) {
            gera_vetor_organ_pipe(arr, n);
        } else if (strcmp(tipo_distribuicao, "intercalado") == 0) {
            gera_vetor_intercalado(arr, n);
        } else {
            printf("Uso incorreto. Forneca --tamanho, --input ou --array.\n");
            return 1;
        }
    }

    Metricas m;
    m.comparacoes = 0;
    m.trocas = 0;
    m.operacoes = 0;
    m.copias = 0;
    m.chamadas_recursivas = 0;
    m.memoria_extra_bytes = 0;
    m.profundidade_maxima = 0;

    if (strcmp(algoritmo, "auto") == 0) {
        //Chama funções de caracterização do array
        
        float desordem = calcular_desordem(arr, n);
        printf("[Metrica 2] Grau de desordem: %.2f\n", desordem);
        
        int repetidos = contar_repetidos(arr, n);
        printf("[Metrica 3] Quantos repetidos: %d\n", repetidos);

        int range = faixa_valores (arr, n);
        printf("[Metrica 4] Range maximo: %d\n", range);

        double desvio = desvio_padrao(arr, n);
        printf("[Metrica 5] Desvio padrao: %.2f%%\n", desvio);

        int meu_max = 0, meu_min = 0;
        max_e_min(arr, n, &meu_max, &meu_min);
        printf("[Metrica 6] Amplitude: \nMaximo = %d\nMinimo = %d\n", meu_max, meu_min);

        algoritmo = decidir_algoritmo(n, desordem, repetidos, range, desvio, meu_min);

    }

    clock_t inicio = clock();

    if (strcmp(algoritmo, "heap") == 0) {
        heap_sort(arr, n, &m);
    } 
    else if (strcmp(algoritmo, "radix") == 0) {
        radix_sort(arr, n, &m);
    } 
    else if (strcmp(algoritmo, "bubble") == 0) {
        bubble_sort(arr, n, &m);
    } 
    else if (strcmp(algoritmo, "insertion") == 0) {
        insertion_sort(arr, n, &m);
    } 
    else if (strcmp(algoritmo, "quick") == 0) {
        quick_sort(arr, n, &m); 
    } 
    else {
        printf("ERRO: Algoritmo '%s' desconhecido!\n", algoritmo);
        if (arr != NULL) free(arr);
        return 1;
    }

    clock_t fim = clock();

    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    const char* caminho_csv = "output/dados.csv";

    FILE *check_arquivo = fopen(caminho_csv, "r");
    int precisa_cabecalho = 0;
    
    if (check_arquivo == NULL) {
        precisa_cabecalho = 1; 
    } else {
        fclose(check_arquivo);
    }

    FILE *arquivo_csv = fopen(caminho_csv, "a");
    if (arquivo_csv != NULL) {
        
        if (precisa_cabecalho) {
            fprintf(arquivo_csv, "Algoritmo,Tamanho,Distribuicao,Tempo (s),Comparacoes,Trocas,Copias,Memoria Extra (bytes),Chamadas recursivas,Profundidade maxima,Operacoes\n");
        } 
        
        fprintf(arquivo_csv, "%s,%d,%s,%.6f,%llu,%llu,%llu,%llu, %llu, %llu, %llu\n", 
                algoritmo, 
                n, 
                tipo_distribuicao, 
                tempo_execucao, 
                m.comparacoes, 
                m.trocas,
                m.copias,
                m.memoria_extra_bytes,
                m.chamadas_recursivas,
                m.profundidade_maxima, 
                m.operacoes);
        
        fclose(arquivo_csv);

        printf("Teste finalizado! Dados salvos com sucesso em '%s'.\n", caminho_csv);

        printf("\n");

        // tabela para imprimir os dados no terminal

        printf("+==============================================================================+\n");
        printf("|                            RESULTADOS DA EXECUCAO                            |\n");
        printf("+----------------------+-------------------------------------------------------+\n");
        printf("| %-20s | %-53s |\n", "Algoritmo", algoritmo);
        printf("| %-20s | %-53d |\n", "Tamanho do vetor", n);
        printf("| %-20s | %-53s |\n", "Distribuicao", tipo_distribuicao);
        printf("| %-20s | %-53.9f |\n", "Tempo de execucao", tempo_execucao);
        printf("| %-20s | %-53llu |\n", "Comparacoes", m.comparacoes);
        printf("| %-20s | %-53llu |\n", "Trocas", m.trocas);
        printf("| %-20s | %-53llu |\n", "Memoria extra", m.memoria_extra_bytes);
        printf("| %-20s | %-53llu |\n", "Chamadas recursivas", m.chamadas_recursivas);
        printf("| %-20s | %-53llu |\n", "Profundidade maxima", m.profundidade_maxima);
        printf("| %-20s | %-53llu |\n", "Copias", m.copias);
        printf("| %-20s | %-53llu |\n", "Operacoes", m.operacoes);
        printf("+==============================================================================+\n");

        printf("\n");

    } else {
        printf("ERRO: Nao foi possivel criar o arquivo em '%s'. Certifique-se de que a pasta 'output' existe.\n", caminho_csv);
    }

    if (arr != NULL) {
        free(arr);
    }

    return 0;
}

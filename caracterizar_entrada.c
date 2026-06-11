#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//funcao que le os números da linha e joga no vetor (alocando memoria conforme precisa)
int* extrair_dados(const char *linha, int *vetor, int *qtd, int *cap) {
    int numero;
    int caracteres_lidos;
    int deslocamento = 0;

    while (sscanf(linha + deslocamento, "%d%n", &numero, &caracteres_lidos) == 1) {
        if (*qtd >= *cap) {
            *cap *= 2;
            vetor = (int*) realloc(vetor, (*cap) * sizeof(int));
        }
        vetor[*qtd] = numero;
        (*qtd)++;
        deslocamento += caracteres_lidos;
    }
    return vetor;
}


//funcao que determina se o vetor vai vir do terminal ou de um arquivo.txt
//tambem determina o tamanho do vetor
int* como_ler_entrada(FILE *fluxo, int terminal, int *tamanho_saida) {
    int capacidade = 10;
    int quantidade = 0;
    int *vetor = (int*) malloc(capacidade * sizeof(int));

    if (terminal) {
        char buffer[65536]; 
        printf("Digite os numeros na mesma linha e aperte ENTER:\n");
        if (fgets(buffer, sizeof(buffer), fluxo) != NULL) {
            vetor = extrair_dados(buffer, vetor, &quantidade, &capacidade);
        }
    } else {
        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), fluxo) != NULL) {
            vetor = extrair_dados(buffer, vetor, &quantidade, &capacidade);
        }
    }

    //ajusta a memoria para o tamanho exato de números lidos 
    if (quantidade > 0) {
        vetor = (int*) realloc(vetor, quantidade * sizeof(int));
    } else {
        free(vetor);
        vetor = NULL;
    }

    //guarda a quantidade direto na variável lá do main
    *tamanho_saida = quantidade; 

    return vetor;
}



//funcao que calcula a porcentagem de desordem:
//recebe o vetor e o tamanho do vetor (que vao ser determinados antes com as funcoes de cima)
float calcular_desordem(int *v, int n) {
    // Se o vetor tiver 0 ou 1 elemento, ele já está ordenado (0% de desordem)
    if (n <= 1) {
        return 0.0;
    }

    int quantidade_inversoes = 0;

    // O loop vai até (n - 2) para que v[i+1] acesse o último elemento com segurança
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            quantidade_inversoes++;
        }
    }

    // (float) converte "quantidade_inversoes" para float antes de dividir, 
    // garantindo que o resultado tenha casas decimais. 
    // Multiplicamos por 100.0 para dar o resultado em porcentagem (ex: 45.5%)
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

    //quantidade total de elementos repetidos e o tamanho total menos os unicos!
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





int main(int argc, char *argv[]) {
    FILE *fluxo = stdin;
    int fechar_arquivo = 0;
    int terminal = 1;

    //confere se foi passado o arquivo por linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--input") == 0 && (i + 1) < argc) {
            fluxo = fopen(argv[i + 1], "r");
            if (fluxo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return 1;
            }
            fechar_arquivo = 1;
            terminal = 0;
            break;
        }
    }

    //cria-se a variável para guardar o tamanho
    int tamanho_do_vetor = 0;

    //passamos o endereço dela para a função preencher
    int *meu_vetor = como_ler_entrada(fluxo, terminal, &tamanho_do_vetor);

    if (fechar_arquivo) {
        fclose(fluxo);
    }

    if (meu_vetor != NULL) {
        printf("Vetor lido com sucesso!\n");
        printf("[Metrica 1] Tamanho detectado: %d elementos\n", tamanho_do_vetor);

        printf("Elementos do vetor: ");
        for (int i = 0; i < tamanho_do_vetor; i++) {

            printf("%d ", meu_vetor[i]);

        }
        printf("\n");
       

        //imprimir o grau de desordem:
        float desordem = calcular_desordem(meu_vetor, tamanho_do_vetor);
        printf("[Metrica 2] Grau de desordem: %.2f%%\n", desordem);


        //quantos valores repetidos:
        int repetidos = contar_repetidos(meu_vetor, tamanho_do_vetor);
        printf("[Metrica 3] Quantos repetidos: %d\n", repetidos);


        //faixa de valores:
        int range = faixa_valores (meu_vetor, tamanho_do_vetor);
        printf("[Metrica 4] Range maximo: %d\n", range);


        //desvio padrao:
        double desvio = desvio_padrao(meu_vetor, tamanho_do_vetor);
        printf("[Metrica 5] Desvio padrao: %.2f\n", desvio);

        //max e min:
        int meu_max = 0, meu_min = 0;
        max_e_min(meu_vetor, tamanho_do_vetor, &meu_max, &meu_min);
        printf("[Metrica 6] Amplitude: \nMaximo = %d\nMinimo = %d\n", meu_max, meu_min);



        free(meu_vetor);
    }




    return 0;
}
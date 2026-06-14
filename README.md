# Sistema Adaptativo de Ordenação

Projeto desenvolvido para a disciplina **SCC0606 - Estruturas de Dados II**.

**Docente:** Prof. Renato Moraes Silva  
**Instituição:** Instituto de Ciências Matemáticas e de Computação (ICMC) - Universidade de São Paulo (USP)

---

## Integrantes

| Nome | Nº USP |
|--------|---------|
| Beatriz São Leandro Cosimatti | 17024130 |
| João Victor Bozola Bosi | 5979703 |
| João Vitor Vasconcelos Jacob | 16987258 |
| Laís Antunes Cayres Quintão | 16880392 |

---

## Objetivo

Desenvolver um sistema capaz de caracterizar automaticamente vetores de entrada e selecionar o algoritmo de ordenação mais adequado para cada situação, com base em métricas extraídas dos dados e em heurísticas validadas experimentalmente.


## Algoritmos Aplicados

O sistema adaptativo foi desenvolvido utilizando cinco algoritmos de ordenação clássicos. Cada um deles apresenta características distintas, tornando-se mais adequado para determinados tipos de entrada.

### Bubble Sort

Algoritmo simples baseado em comparações e trocas entre elementos adjacentes.

**Características:**
- Complexidade média: O(n²)
- Melhor caso: O(n), quando já está ordenado
- Não utiliza memória auxiliar significativa
- Útil como algoritmo de referência, mas pouco eficiente para entradas grandes

### Insertion Sort

O Insertion Sort constrói gradualmente um vetor ordenado inserindo cada elemento em sua posição correta.

**Características:**
- Complexidade média: O(n²)
- Complexidade no melhor caso: O(n)
- Não utiliza memória auxiliar significativa
- Excelente desempenho para vetores pequenos ou quase ordenados

### Quick Sort

O Quick Sort utiliza a estratégia de divisão e conquista, particionando o vetor em torno de um pivô.

**Características:**
- Complexidade média: O(n log n)
- Complexidade no pior caso: O(n²)
- Baixo consumo de memória
- Excelente desempenho geral

Nesta implementação foi utilizada a estratégia da mediana de três para seleção do pivô, reduzindo a probabilidade de partições desbalanceadas.

### Heap Sort

O Heap Sort utiliza uma estrutura de heap binária para organizar os elementos antes da ordenação.

**Características:**
- Complexidade: O(n log n)
- Não depende da distribuição dos dados
- Utiliza memória auxiliar constante
- Desempenho estável independentemente da entrada

### Radix Sort

O Radix Sort ordena os elementos processando seus dígitos individualmente.

**Características:**
- Complexidade aproximada: O(d·n)
- Não realiza comparações entre elementos
- Excelente desempenho para grandes conjuntos de dados não negativos
- Requer memória auxiliar adicional

---

## Caracterização dos Dados

Antes de selecionar o algoritmo de ordenação, o sistema realiza uma análise do vetor de entrada. Essa etapa tem como objetivo identificar características capazes de influenciar o desempenho dos algoritmos implementados. 

Essas métricas não medem o desempenho dos algoritmos; elas são utilizadas exclusivamente para caracterizar o vetor de entrada e permitir a seleção automática do algoritmo mais adequado.

As seguintes métricas são calculadas:

### Grau de Desordem

Mede o percentual de inversões adjacentes presentes no vetor.

```text
Desordem = (Inversões Adjacentes / (n - 1)) × 100
```

Essa métrica é utilizada para identificar vetores quase ordenados, cenário favorável ao Insertion Sort.

### Quantidade de Elementos Repetidos

Corresponde ao número de cópias extras de valores já presentes no vetor.

Essa métrica é utilizada para caracterização dos dados e para análise experimental.

### Amplitude dos Valores (Range)

Calculada pela diferença entre o maior e o menor elemento:

```text
Range = Máximo - Mínimo
```

É utilizada para avaliar a adequação do vetor ao Radix Sort.

### Desvio Padrão

Mede a dispersão dos valores em relação à média.

Embora seja calculado pelo sistema, não foi incorporado à heurística final de seleção.

### Valores Máximo e Mínimo

Permitem determinar a amplitude dos dados e identificar a presença de números negativos.

---

## Heurísticas Adaptativas

Após a caracterização do vetor, o sistema utiliza uma árvore de decisão para selecionar automaticamente o algoritmo de ordenação.

### Regras Utilizadas

```c
if (n <= 1000 && desordem <= 5.0)
    return "insertion";

if (min < 0 && n >= 10000)
    return "heap";

if (min >= 0 && range <= 10 * n)
    return "radix";

return "quick";
```

### Interpretação

| Condição | Algoritmo |
|-----------|-----------|
| Vetor quase ordenado e pequeno | Insertion Sort |
| Vetor grande contendo valores negativos | Heap Sort |
| Vetor não negativo com range proporcional ao tamanho | Radix Sort |
| Demais casos | Quick Sort |

### Validação

As heurísticas foram definidas a partir de experimentos comparando o desempenho dos algoritmos em diferentes cenários, incluindo:

- Vetores pequenos aleatórios
- Vetores quase ordenados
- Vetores aleatórios médios e grandes
- Vetores discrepantes
- Vetores de grande porte

Algumas hipóteses iniciais foram descartadas após os testes, como a utilização obrigatória do Insertion Sort para vetores muito pequenos e a preferência pelo Heap Sort para vetores muito grandes (testes realizados com o tamanho de até 500000).


## Métricas de Desempenho

Durante a execução dos algoritmos de ordenação, o sistema coleta informações que permitem comparar seu desempenho.

| Métrica | Descrição |
|----------|----------|
| Tempo(s) | Tempo total de execução do algoritmo |
| Comparações | Número de comparações realizadas entre elementos |
| Cópias | Quantidade de movimentações/cópias de dados realizadas |
| Operações | Métrica agregada utilizada para estimar o trabalho total executado pelo algoritmo |

Essas informações são armazenadas automaticamente em arquivos CSV para posterior análise experimental.



---

## Compilação

Para compilar o projeto, utilize:

```bash
gcc main.c algoritmos.c caracterizacao.c -o main -lm
```

No Windows, o executável gerado será:

```bash
main.exe
```

---

## Como Executar

O programa pode ser executado de três formas principais:

1. Gerando um vetor automaticamente;
2. Informando um vetor manualmente pelo terminal;
3. Lendo os dados a partir de um arquivo de entrada.

Caso a flag `--algoritmo` seja omitida, o programa utiliza automaticamente o modo adaptativo, escolhendo o algoritmo considerado mais adequado para o vetor analisado.

### Execução com geração automática

```bash
.\main.exe --tamanho 50000 --distribuicao aleatorio --algoritmo quick
```

```bash
.\main.exe --tamanho 50000 --distribuicao quase_ordenado
```

No segundo exemplo, como o algoritmo não foi informado, o sistema utiliza o modo adaptativo.

### Execução com vetor manual

```bash
.\main.exe --array 42 15 8 99 4 23 104 2 --algoritmo bubble
```

```bash
.\main.exe --array 15 3 99 21 8
```

Quando o algoritmo é omitido, o sistema calcula as métricas do vetor e escolhe automaticamente o método de ordenação.

### Execução com arquivo de entrada

```bash
.\main.exe --input dados.txt --algoritmo bubble
```

```bash
.\main.exe --input dados.txt
```

---

## Distribuições Disponíveis

Ao gerar vetores automaticamente, é possível escolher diferentes distribuições de dados.

| Distribuição | Descrição |
|-------------|-----------|
| `aleatorio` | Gera valores aleatórios |
| `crescente` | Gera vetor em ordem crescente |
| `decrescente` | Gera vetor em ordem decrescente |
| `quase_ordenado` | Gera vetor quase ordenado |
| `discrepante` | Gera vetor com grande diferença entre valores |

Exemplo:

```bash
.\main.exe --tamanho 10000 --distribuicao discrepante
```

---

## Saída Gerada

Após a execução, o programa exibe no terminal as métricas coletadas e o resultado da ordenação.

Além disso, os dados de desempenho são salvos em:

```text
output/dados.csv
```

O arquivo CSV segue o formato:

```text
Algoritmo,Tamanho,Distribuicao,Tempo(s),Comparacoes,Copias,Operacoes
```

Esses dados foram utilizados para comparar o desempenho dos algoritmos e validar as heurísticas do sistema adaptativo.

---

## Relatório

O relatório completo do projeto está disponível em:

```text
Relatorio/relatorio.pdf
```

---

## Vídeo Demonstrativo

Link do vídeo demonstrativo:

```text
Adicionar link aqui
```










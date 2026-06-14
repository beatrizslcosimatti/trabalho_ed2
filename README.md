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













# trabalho_ed2
Trabalho de Estrutura de Dados


## Como Executar (Exemplos de Uso)

Aqui estão exemplos de como adicionar informações pelo terminal

Ao omitir a flag `--algoritmo`, o programa sempre ira usar as funções de verificação do melhor algoritmo para ordenar.


* **Exemplos de comando:**
  ```bash
  .\main.exe --tamanho 50000000 --distribuicao aleatorio --algoritmo quick
  .\main.exe --tamanho 50000 --distribuicao quase_ordenado

  .\main.exe --array 42 15 8 99 4 23 104 2 --algoritmo bubble
  .\main.exe --array 15 3 99 21 8

  .\main.exe --input dados.txt --algoritmo bubble
  .\main.exe --input dados.txt
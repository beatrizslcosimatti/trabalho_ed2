import os
import pandas as pd
import matplotlib.pyplot as plt

# 1. Configuração de Caminhos (O "GPS" automático)
diretorio_atual = os.path.dirname(os.path.abspath(__file__))
caminho_arquivo = os.path.join(diretorio_atual, 'output', 'dados.csv')

# Cria uma pasta específica para guardar os gráficos gerados
pasta_graficos = os.path.join(diretorio_atual, 'output', 'graficos_separados')
if not os.path.exists(pasta_graficos):
    os.makedirs(pasta_graficos)

# 2. Carrega os dados e faz a faxina do cabeçalho
df = pd.read_csv(caminho_arquivo)
df.columns = df.columns.str.strip()

# 3. Filtra apenas os testes da distribuição "aleatorio"
df_aleatorio = df[df['Distribuicao'] == 'aleatorio']

# Pega a lista de algoritmos que existem no CSV
algoritmos = df_aleatorio['Algoritmo'].unique()

print(f"Iniciando a geração de {len(algoritmos)} gráficos individuais...\n")

# 4. O Laço que cria e salva um gráfico por algoritmo
for alg in algoritmos:
    # Filtra os dados apenas do algoritmo atual do laço
    dados_alg = df_aleatorio[df_aleatorio['Algoritmo'] == alg]
    
    # Inicia uma NOVA figura em branco (Isso garante o eixo Y específico!)
    plt.figure(figsize=(10, 6))
    
    # Plota a linha
    plt.plot(dados_alg['Tamanho'], dados_alg['Tempo (s)'], marker='o', color='#1f77b4', linewidth=2)
    
    # Formatação visual
    plt.title(f'Desempenho: {alg.capitalize()} (Dist. Aleatória)', fontsize=15, fontweight='bold')
    plt.xlabel('Tamanho do Vetor (N)', fontsize=12)
    plt.ylabel('Tempo de Execução (Segundos)', fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    
    # Define o nome do arquivo dinamicamente (ex: grafico_radix.png)
    nome_arquivo = f'grafico_tempo_{alg}.png'
    caminho_salvar = os.path.join(pasta_graficos, nome_arquivo)
    
    # Ajusta as margens e SALVA o arquivo
    plt.tight_layout()
    plt.savefig(caminho_salvar, dpi=300)
    
    # FECHA a figura da memória (Crucial para o próximo laço não desenhar por cima)
    plt.close()
    
    print(f"[ OK ] Salvo: {nome_arquivo}")

print(f"\nSucesso! Todos os gráficos estão na pasta: {pasta_graficos}")
# ==========================================================
# GRÁFICOS COMPARATIVOS ESPECÍFICOS (A BATALHA DOS TITÃS)
# ==========================================================

print("\nGerando gráficos comparativos de alto nível...")

# --- Gráfico 6: Heap vs Quick ---
plt.figure(figsize=(10, 6))
# Lista específica dos dois que queremos comparar
for alg in ['heap', 'quick']: 
    if alg in algoritmos: # Verifica se existe no CSV para evitar erros
        dados_alg = df_aleatorio[df_aleatorio['Algoritmo'] == alg]
        plt.plot(dados_alg['Tamanho'], dados_alg['Tempo (s)'], marker='o', linewidth=2, label=alg.capitalize())

plt.title('Confronto de Arquitetura: Heap Sort vs Quick Sort', fontsize=15, fontweight='bold')
plt.xlabel('Tamanho do Vetor (N)', fontsize=12)
plt.ylabel('Tempo de Execução (Segundos)', fontsize=12)
plt.legend(fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()

caminho_grafico_6 = os.path.join(pasta_graficos, 'grafico_6_heap_vs_quick.png')
plt.savefig(caminho_grafico_6, dpi=300)
plt.close()
print("[ OK ] Salvo: grafico_6_heap_vs_quick.png")


# --- Gráfico 7: Quick vs Radix ---
plt.figure(figsize=(10, 6))
# Lista específica para a batalha final
for alg in ['quick', 'radix']:
    if alg in algoritmos:
        dados_alg = df_aleatorio[df_aleatorio['Algoritmo'] == alg]
        plt.plot(dados_alg['Tamanho'], dados_alg['Tempo (s)'], marker='o', linewidth=2, label=alg.capitalize())

plt.title('A Batalha Final: Quick Sort vs Radix Sort', fontsize=15, fontweight='bold')
plt.xlabel('Tamanho do Vetor (N)', fontsize=12)
plt.ylabel('Tempo de Execução (Segundos)', fontsize=12)
plt.legend(fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()

caminho_grafico_7 = os.path.join(pasta_graficos, 'grafico_7_quick_vs_radix.png')
plt.savefig(caminho_grafico_7, dpi=300)
plt.close()
print("[ OK ] Salvo: grafico_7_quick_vs_radix.png")
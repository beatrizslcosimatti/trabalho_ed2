Write-Host "==========================================" -ForegroundColor Cyan
Write-Host " FASE 1: LEVANTAMENTO DA CURVA BIG-O (20 PONTOS)" -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

# 1. Testes O(n^2) - Bubble e Insertion
# 20 pontos variando de 15.000 até 300.000 (saltos de 15.000)
$tamanhos_n2 = @(15000, 30000, 45000, 60000, 75000, 90000, 105000, 120000, 135000, 150000, 165000, 180000, 195000, 210000, 225000, 240000, 255000, 270000, 285000, 300000)
$algoritmos_n2 = @("insertion", "bubble")

foreach ($alg in $algoritmos_n2) {
    Write-Host "`n>> Levantando curva do $alg (20 pontos)..." -ForegroundColor Yellow
    foreach ($tam in $tamanhos_n2) {
        Write-Host "   -> Tamanho: $tam"
        .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo $alg
    }
}

# 2. Testes O(n log n) - Heap Sort
# 20 pontos variando de 15 Milhões até 300 Milhões (saltos de 15 Milhões)
$tamanhos_heap = @(15000000, 30000000, 45000000, 60000000, 75000000, 90000000, 105000000, 120000000, 135000000, 150000000, 165000000, 180000000, 195000000, 210000000, 225000000, 240000000, 255000000, 270000000, 285000000, 300000000)

Write-Host "`n>> Levantando curva do heap (20 pontos)..." -ForegroundColor Yellow
foreach ($tam in $tamanhos_heap) {
    Write-Host "   -> Tamanho: $tam"
    .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo heap
}

# 3. Testes Extremos - Radix e Quick Sort
# 20 pontos variando de 100 Milhões até 2 Bilhões (saltos de 100 Milhões)
$tamanhos_extremos = @(100000000, 200000000, 300000000, 400000000, 500000000, 600000000, 700000000, 800000000, 900000000, 1000000000, 1100000000, 1200000000, 1300000000, 1400000000, 1500000000, 1600000000, 1700000000, 1800000000, 1900000000, 2000000000)
$algoritmos_extremos = @("radix", "quick")

foreach ($alg in $algoritmos_extremos) {
    Write-Host "`n>> Levantando curva do $alg (20 pontos)..." -ForegroundColor Yellow
    foreach ($tam in $tamanhos_extremos) {
        Write-Host "   -> Tamanho: $tam"
        .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo $alg
    }
}

Write-Host "`n=========================================================" -ForegroundColor Cyan
Write-Host " FASE 2: O CONFRONTO DIRETO DA CACHE (100M a 550M)" -ForegroundColor Cyan
Write-Host "=========================================================" -ForegroundColor Cyan

# Array com 13 pontos (saltos de 50 Milhões)
$tamanhos_confronto = @(
    100000000, 150000000, 200000000, 250000000, 300000000, 
    350000000, 400000000, 450000000, 500000000, 550000000
)

$algoritmos_confronto = @("heap", "quick")

foreach ($alg in $algoritmos_confronto) {
    Write-Host "`n>> Levantando dados de estresse de Hardware para o $alg..." -ForegroundColor Yellow
    foreach ($tam in $tamanhos_confronto) {
        Write-Host "   -> Tamanho: $tam (Distribuicao Aleatoria)"
        .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo $alg
    }
}
Write-Host "`n[ OK ] Testes de confronto de Cache finalizados!" -ForegroundColor Green


# ==========================================================
# FASE 3: VALIDAÇÃO DA HEURÍSTICA DO ORÁCULO VS REALIDADE
# Comprova as decisões dos IFs implementados no código
# ==========================================================
Write-Host "`n=========================================================" -ForegroundColor Cyan
Write-Host " FASE 3: VALIDAÇÃO DA HEURÍSTICA DO ORÁCULO VS REALIDADE" -ForegroundColor Cyan
Write-Host "=========================================================" -ForegroundColor Cyan

# --- 3.1. VALIDAÇÃO DO INSERTION SORT ---
Write-Host "`n[3.1] Testando Condicao: n <= 1000 e Quase Ordenado..." -ForegroundColor Yellow
$tamanhos_pequenos = @(100, 500, 1000, 2000) # O 2000 quebra a regra propositalmente
$algoritmos_pequenos = @("insertion", "quick", "oraculo")

foreach ($tam in $tamanhos_pequenos) {
    foreach ($alg in $algoritmos_pequenos) {
        Write-Host "   -> Tamanho: $tam | Dist: quase_ordenado | Alg: $alg"
        .\main.exe --tamanho $tam --distribuicao quase_ordenado --algoritmo $alg
    }
}

# --- 3.2. VALIDAÇÃO DO RADIX SORT ---
Write-Host "`n[3.2] Testando Condicao: Range proporcional ao Tamanho (Sem Negativos)..." -ForegroundColor Yellow
$tamanhos_radix = @(500000, 1000000, 5000000)
$algoritmos_radix = @("radix", "quick", "oraculo")

foreach ($tam in $tamanhos_radix) {
    foreach ($alg in $algoritmos_radix) {
        Write-Host "   -> Tamanho: $tam | Dist: aleatorio | Alg: $alg"
        .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo $alg
    }
}

# --- 3.3. VALIDAÇÃO DO HEAP SORT (DECISÃO CONSERVADORA) ---
Write-Host "`n[3.3] Testando Condicao: Presenca de Valores Negativos..." -ForegroundColor Yellow
$tamanhos_negativos = @(10000, 50000, 100000)
$algoritmos_negativos = @("heap", "quick", "oraculo")

foreach ($tam in $tamanhos_negativos) {
    foreach ($alg in $algoritmos_negativos) {
        Write-Host "   -> Tamanho: $tam | Dist: aleatorio | Alg: $alg (Teórico para Negativos)"
        .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo $alg
    }
}
3
# --- 3.4. VALIDAÇÃO DO QUICK SORT (FALLBACK) ---
Write-Host "`n[3.4] Testando Condicao: O Caso Geral (Fallback para Quick Sort)..." -ForegroundColor Yellow
$tamanhos_geral = @(2000000, 4000000, 8000000)
$algoritmos_geral = @("quick", "radix", "oraculo")

foreach ($tam in $tamanhos_geral) {
    foreach ($alg in $algoritmos_geral) {
        Write-Host "   -> Tamanho: $tam | Dist: decrescente | Alg: $alg"
        .\main.exe --tamanho $tam --distribuicao decrescente --algoritmo $alg
    }
}

Write-Host "`n=========================================================" -ForegroundColor Magenta
Write-Host " SUCESSO: BATERIA COMPLETA DE TESTES FINALIZADA! " -ForegroundColor Magenta
Write-Host "=========================================================" -ForegroundColor Magenta
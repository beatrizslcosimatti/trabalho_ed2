Write-Host "=====================================================" -ForegroundColor Cyan
Write-Host " FASE DE VALIDAÇÃO: HEURÍSTICA DO ORÁCULO VS REALIDADE" -ForegroundColor Cyan
Write-Host "=====================================================" -ForegroundColor Cyan

# ==========================================================
# 1. VALIDAÇÃO DO INSERTION SORT
# Regra: if (n <= 1000 && desordem <= 5.0)
# ==========================================================
Write-Host "`n[1] Testando Condicao: n <= 1000 e Quase Ordenado..." -ForegroundColor Yellow
$tamanhos_pequenos = @(100, 500, 1000, 2000) # O 2000 serve para ver o Oraculo mudando de ideia!
$algoritmos_pequenos = @("insertion", "quick", "auto")

foreach ($tam in $tamanhos_pequenos) {
    foreach ($alg in $algoritmos_pequenos) {
        Write-Host "   -> Tamanho: $tam | Dist: quase_ordenado | Alg: $alg"
        .\main.exe --tamanho $tam --distribuicao quase_ordenado --algoritmo $alg
    }
}

# ==========================================================
# 2. VALIDAÇÃO DO RADIX SORT
# Regra: if (min >= 0 && range <= 10*n)
# ==========================================================
Write-Host "`n[2] Testando Condicao: Range proporcional ao Tamanho (Sem Negativos)..." -ForegroundColor Yellow
# Vamos usar tamanhos onde o Radix brilha contra o Quick
$tamanhos_radix = @(500000, 1000000, 5000000)
$algoritmos_radix = @("radix", "quick", "auto")

foreach ($tam in $tamanhos_radix) {
    foreach ($alg in $algoritmos_radix) {
        # Assumindo que a distribuição 'aleatorio' do seu C se encaixe nessa regra de range
        Write-Host "   -> Tamanho: $tam | Dist: aleatorio | Alg: $alg"
        .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo $alg
    }
}

# ==========================================================
# 3. VALIDAÇÃO DO HEAP SORT (A DECISÃO CONSERVADORA)
# Regra: if (min < 0 && n >= 10000)
# ==========================================================
Write-Host "`n[3] Testando Condicao: Presenca de Valores Negativos..." -ForegroundColor Yellow
# Como pontuado no seu texto, os testes originais não tinham negativos. 
# Se o seu C ainda NÃO gera negativos, esse teste pode ser ignorado ou falhará em acionar o Heap.
# Caso tenha implementado uma distribuição com negativos (ex: 'aleatorio_negativo'), altere abaixo:
$tamanhos_negativos = @(10000, 50000, 100000)
$algoritmos_negativos = @("heap", "quick", "auto")

foreach ($tam in $tamanhos_negativos) {
    foreach ($alg in $algoritmos_negativos) {
        # Troque 'aleatorio' para o nome da sua distribuição negativa, se existir
        Write-Host "   -> Tamanho: $tam | Dist: aleatorio | Alg: $alg (Teórico para Negativos)"
        .\main.exe --tamanho $tam --distribuicao aleatorio --algoritmo $alg
    }
}

# ==========================================================
# 4. VALIDAÇÃO DO QUICK SORT (O DEFAULT / FALLBACK)
# Regra: return "quick"; (Para todo o resto)
# ==========================================================
Write-Host "`n[4] Testando Condicao: O Caso Geral (Fallback para Quick Sort)..." -ForegroundColor Yellow
# Vetores grandes, totalmente desordenados e fora das regras anteriores
$tamanhos_geral = @(2000000, 4000000, 8000000)
$algoritmos_geral = @("quick", "radix", "auto")

foreach ($tam in $tamanhos_geral) {
    foreach ($alg in $algoritmos_geral) {
        Write-Host "   -> Tamanho: $tam | Dist: decrescente | Alg: $alg"
        .\main.exe --tamanho $tam --distribuicao decrescente --algoritmo $alg
    }
}

Write-Host "`n[ OK ] Bateria de testes da Heurística Finalizada!" -ForegroundColor Green
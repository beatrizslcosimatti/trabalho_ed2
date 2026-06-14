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
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para criar a matriz de habilidade em forma de cone
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cria um cone apontando para baixo
            if (j >= i && j < TAMANHO_HABILIDADE - i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cria uma cruz com o centro em (2,2)
            if (i == TAMANHO_HABILIDADE/2 || j == TAMANHO_HABILIDADE/2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de octaedro
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cria um losango (vista frontal do octaedro)
            int centro = TAMANHO_HABILIDADE/2;
            int distancia = abs(i - centro) + abs(j - centro);
            if (distancia <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                      int linha_origem, int coluna_origem) {
    int centro = TAMANHO_HABILIDADE/2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha_tabuleiro = linha_origem - centro + i;
            int coluna_tabuleiro = coluna_origem - centro + j;
            
            // Verifica se a posição está dentro do tabuleiro
            if (linha_tabuleiro >= 0 && linha_tabuleiro < TAMANHO_TABULEIRO &&
                coluna_tabuleiro >= 0 && coluna_tabuleiro < TAMANHO_TABULEIRO) {
                // Se a posição na matriz de habilidade for 1, marca no tabuleiro
                if (habilidade[i][j] == 1) {
                    tabuleiro[linha_tabuleiro][coluna_tabuleiro] = 5;
                }
            }
        }
    }
}

// Função para posicionar um navio horizontalmente
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe no tabuleiro
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Posição inválida
    }
    
    // Verifica se há sobreposição
    for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
        if (tabuleiro[linha][j] != 0) {
            return 0; // Há sobreposição
        }
    }
    
    // Posiciona o navio
    for (int j = coluna; j < coluna + TAMANHO_NAVIO; j++) {
        tabuleiro[linha][j] = 3;
    }
    
    return 1; // Navio posicionado com sucesso
}

// Função para posicionar um navio verticalmente
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe no tabuleiro
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Posição inválida
    }
    
    // Verifica se há sobreposição
    for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
        if (tabuleiro[i][coluna] != 0) {
            return 0; // Há sobreposição
        }
    }
    
    // Posiciona o navio
    for (int i = linha; i < linha + TAMANHO_NAVIO; i++) {
        tabuleiro[i][coluna] = 3;
    }
    
    return 1; // Navio posicionado com sucesso
}

// Função para posicionar um navio na diagonal principal (de cima para baixo)
int posicionarNavioDiagonalPrincipal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe no tabuleiro
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Posição inválida
    }
    
    // Verifica se há sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != 0) {
            return 0; // Há sobreposição
        }
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 3;
    }
    
    return 1; // Navio posicionado com sucesso
}

// Função para posicionar um navio na diagonal secundária (de baixo para cima)
int posicionarNavioDiagonalSecundaria(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe no tabuleiro
    if (linha - TAMANHO_NAVIO + 1 < 0 || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // Posição inválida
    }
    
    // Verifica se há sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha - i][coluna + i] != 0) {
            return 0; // Há sobreposição
        }
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha - i][coluna + i] = 3;
    }
    
    return 1; // Navio posicionado com sucesso
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    printf("Legenda:\n");
    printf("0 - Água\n");
    printf("3 - Navio\n");
    printf("5 - Área afetada por habilidade\n\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona os navios
    if (!posicionarNavioHorizontal(tabuleiro, 1, 1)) {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }
    
    if (!posicionarNavioVertical(tabuleiro, 1, 8)) {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }
    
    if (!posicionarNavioDiagonalPrincipal(tabuleiro, 6, 2)) {
        printf("Erro ao posicionar navio na diagonal principal!\n");
        return 1;
    }
    
    if (!posicionarNavioDiagonalSecundaria(tabuleiro, 6, 6)) {
        printf("Erro ao posicionar navio na diagonal secundária!\n");
        return 1;
    }
    
    // Cria as matrizes de habilidade
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    
    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 0, 0);    // Cone no canto superior esquerdo
    aplicarHabilidade(tabuleiro, habilidadeCruz, 4, 4);    // Cruz um pouco acima do centro
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 8, 8); // Octaedro no canto inferior direito
    
    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);
    
    return 0;
}

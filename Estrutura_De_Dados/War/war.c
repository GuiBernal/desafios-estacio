#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void cadastrarTerritorios(struct Territorio* mapa, int quantidade) {
    printf("=== Cadastro de Territorios ===\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("Territorio %d:\n", i + 1);
        
        printf("Nome: ");
        scanf("%29s", mapa[i].nome);
        
        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);
        
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");
    }
}

void exibirTerritorios(struct Territorio* mapa, int quantidade) {
    printf("=== Territorios Cadastrados ===\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("\n");
    }
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("=== Batalha ===\n");
    printf("Atacante: %s (%s) - Dado: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("Defensor: %s (%s) - Dado: %d\n", defensor->nome, defensor->cor, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("Vitoria do atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
        if (defensor->tropas == 0) {
            defensor->tropas = 1;
        }
        printf("O territorio %s agora pertence a %s com %d tropas.\n", 
               defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("Vitoria do defensor!\n");
        atacante->tropas--;
        if (atacante->tropas < 0) {
            atacante->tropas = 0;
        }
        printf("O atacante %s agora possui %d tropas.\n", 
               atacante->nome, atacante->tropas);
    }
    printf("\n");
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strncpy(destino, missoes[indice], 99);
    destino[99] = '\0';
}

void exibirMissao(char* missao) {
    printf("=== Sua Missao Estrategica ===\n");
    printf("%s\n\n", missao);
}

int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    if (strstr(missao, "Conquistar 3 territorios seguidos") != NULL) {
        int maxContagem = 0;
        for (int i = 0; i < tamanho; i++) {
            int contagem = 0;
            for (int j = 0; j < tamanho; j++) {
                if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                    contagem++;
                }
            }
            if (contagem > maxContagem) {
                maxContagem = contagem;
            }
        }
        return maxContagem >= 3;
    }
    
    if (strstr(missao, "Eliminar todas as tropas vermelhas") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 || 
                strcmp(mapa[i].cor, "vermelha") == 0) {
                return 0;
            }
        }
        return 1;
    }
    
    if (strstr(missao, "Eliminar todas as tropas azuis") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 || 
                strcmp(mapa[i].cor, "azuis") == 0) {
                return 0;
            }
        }
        return 1;
    }
    
    if (strstr(missao, "Conquistar metade dos territorios") != NULL) {
        int metade = tamanho / 2;
        if (tamanho % 2 == 1) {
            metade++;
        }
        int maxContagem = 0;
        for (int i = 0; i < tamanho; i++) {
            int contagem = 0;
            for (int j = 0; j < tamanho; j++) {
                if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                    contagem++;
                }
            }
            if (contagem > maxContagem) {
                maxContagem = contagem;
            }
        }
        return maxContagem >= metade;
    }
    
    if (strstr(missao, "Ter pelo menos 4 territorios") != NULL) {
        int maxContagem = 0;
        for (int i = 0; i < tamanho; i++) {
            int contagem = 0;
            for (int j = 0; j < tamanho; j++) {
                if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                    contagem++;
                }
            }
            if (contagem > maxContagem) {
                maxContagem = contagem;
            }
        }
        return maxContagem >= 4;
    }
    
    return 0;
}

void liberarMemoria(struct Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL));
    
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas vermelhas",
        "Eliminar todas as tropas azuis",
        "Conquistar metade dos territorios",
        "Ter pelo menos 4 territorios"
    };
    int totalMissoes = 5;
    
    int quantidade;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);
    
    if (quantidade <= 0) {
        printf("Quantidade invalida. Encerrando programa.\n");
        return 1;
    }
    
    struct Territorio* mapa = (struct Territorio*)calloc(quantidade, sizeof(struct Territorio));
    
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    
    char* missaoJogador = (char*)malloc(100);
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(mapa);
        return 1;
    }
    
    cadastrarTerritorios(mapa, quantidade);
    exibirTerritorios(mapa, quantidade);
    
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);
    
    int continuar = 1;
    int missaoCumprida = 0;
    
    while (continuar && !missaoCumprida) {
        printf("=== Sistema de Ataque ===\n");
        printf("Territorios disponiveis:\n");
        for (int i = 0; i < quantidade; i++) {
            printf("%d - %s (%s) - %d tropas\n", 
                   i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        
        int indiceAtacante, indiceDefensor;
        printf("\nEscolha o territorio atacante (1-%d): ", quantidade);
        scanf("%d", &indiceAtacante);
        indiceAtacante--;
        
        printf("Escolha o territorio defensor (1-%d): ", quantidade);
        scanf("%d", &indiceDefensor);
        indiceDefensor--;
        
        if (indiceAtacante < 0 || indiceAtacante >= quantidade || 
            indiceDefensor < 0 || indiceDefensor >= quantidade) {
            printf("Indices invalidos!\n\n");
            continue;
        }
        
        if (indiceAtacante == indiceDefensor) {
            printf("Um territorio nao pode atacar a si mesmo!\n\n");
            continue;
        }
        
        if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
            printf("Nao e possivel atacar um territorio da mesma cor!\n\n");
            continue;
        }
        
        if (mapa[indiceAtacante].tropas <= 0) {
            printf("O territorio atacante nao possui tropas suficientes!\n\n");
            continue;
        }
        
        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        exibirTerritorios(mapa, quantidade);
        
        missaoCumprida = verificarMissao(missaoJogador, mapa, quantidade);
        
        if (missaoCumprida) {
            printf("=== PARABENS! VOCE VENCEU! ===\n");
            printf("Missao cumprida: %s\n", missaoJogador);
            break;
        }
        
        printf("Deseja realizar outro ataque? (1-Sim, 0-Nao): ");
        scanf("%d", &continuar);
        printf("\n");
    }
    
    if (!missaoCumprida) {
        printf("Jogo encerrado. Missao nao foi cumprida.\n");
    }
    
    liberarMemoria(mapa, missaoJogador);
    return 0;
}


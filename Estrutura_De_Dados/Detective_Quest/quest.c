#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

typedef struct HashEntry {
    char pista[100];
    char suspeito[50];
    struct HashEntry* proximo;
} HashEntry;

#define TAMANHO_HASH 101

typedef struct {
    HashEntry* tabela[TAMANHO_HASH];
} TabelaHash;

Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    if (pista != NULL && strlen(pista) > 0) {
        strcpy(novaSala->pista, pista);
    } else {
        novaSala->pista[0] = '\0';
    }
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

int calcularHash(const char* chave) {
    int hash = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        hash = (hash * 31 + chave[i]) % TAMANHO_HASH;
    }
    return (hash < 0) ? hash + TAMANHO_HASH : hash;
}

TabelaHash* criarTabelaHash() {
    TabelaHash* hash = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (hash == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    for (int i = 0; i < TAMANHO_HASH; i++) {
        hash->tabela[i] = NULL;
    }
    return hash;
}

void inserirNaHash(TabelaHash* hash, const char* pista, const char* suspeito) {
    int indice = calcularHash(pista);
    HashEntry* novo = (HashEntry*)malloc(sizeof(HashEntry));
    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = hash->tabela[indice];
    hash->tabela[indice] = novo;
}

char* encontrarSuspeito(TabelaHash* hash, const char* pista) {
    int indice = calcularHash(pista);
    HashEntry* atual = hash->tabela[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        if (novo == NULL) {
            printf("Erro ao alocar memoria.\n");
            exit(1);
        }
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    int comparacao = strcmp(pista, raiz->pista);
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

PistaNode* explorarSalas(Sala* salaAtual, PistaNode* raizPistas, TabelaHash* hash) {
    if (salaAtual == NULL) {
        return raizPistas;
    }

    printf("\nVoce esta em: %s\n", salaAtual->nome);

    if (salaAtual->pista[0] != '\0') {
        printf("Pista encontrada: %s\n", salaAtual->pista);
        raizPistas = inserirPista(raizPistas, salaAtual->pista);
        
        char* suspeito = encontrarSuspeito(hash, salaAtual->pista);
        if (suspeito != NULL) {
            printf("Esta pista aponta para: %s\n", suspeito);
        }
    }

    printf("Escolha um caminho:\n");
    if (salaAtual->esquerda != NULL) {
        printf("  [e] Esquerda\n");
    }
    if (salaAtual->direita != NULL) {
        printf("  [d] Direita\n");
    }
    printf("  [s] Sair\n");
    printf("Opcao: ");

    char opcao;
    scanf(" %c", &opcao);

    switch (opcao) {
        case 'e':
        case 'E':
            if (salaAtual->esquerda != NULL) {
                raizPistas = explorarSalas(salaAtual->esquerda, raizPistas, hash);
            } else {
                printf("Nao ha caminho a esquerda.\n");
                raizPistas = explorarSalas(salaAtual, raizPistas, hash);
            }
            break;
        case 'd':
        case 'D':
            if (salaAtual->direita != NULL) {
                raizPistas = explorarSalas(salaAtual->direita, raizPistas, hash);
            } else {
                printf("Nao ha caminho a direita.\n");
                raizPistas = explorarSalas(salaAtual, raizPistas, hash);
            }
            break;
        case 's':
        case 'S':
            printf("Saindo da exploracao...\n");
            return raizPistas;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            raizPistas = explorarSalas(salaAtual, raizPistas, hash);
            break;
    }

    return raizPistas;
}

int contarPistasPorSuspeito(PistaNode* raiz, TabelaHash* hash, const char* suspeito) {
    if (raiz == NULL) {
        return 0;
    }
    int contador = 0;
    contador += contarPistasPorSuspeito(raiz->esquerda, hash, suspeito);
    
    char* suspeitoPista = encontrarSuspeito(hash, raiz->pista);
    if (suspeitoPista != NULL && strcmp(suspeitoPista, suspeito) == 0) {
        contador++;
    }
    
    contador += contarPistasPorSuspeito(raiz->direita, hash, suspeito);
    return contador;
}

void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    exibirPistas(raiz->esquerda);
    printf("  - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

void normalizarNome(char* nome) {
    if (nome[0] != '\0') {
        nome[0] = (nome[0] >= 'a' && nome[0] <= 'z') ? nome[0] - 32 : nome[0];
        for (int i = 1; nome[i] != '\0'; i++) {
            nome[i] = (nome[i] >= 'A' && nome[i] <= 'Z') ? nome[i] + 32 : nome[i];
        }
    }
}

void verificarSuspeitoFinal(PistaNode* raizPistas, TabelaHash* hash) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("\n=== FASE DE JULGAMENTO ===\n");
    printf("Suspeitos disponiveis:\n");
    printf("  1. Joao\n");
    printf("  2. Maria\n");
    printf("  3. Pedro\n");
    printf("  4. Ana\n");
    printf("\nQuem voce acusa? Digite o nome: ");
    
    char suspeitoAcusado[50];
    if (fgets(suspeitoAcusado, sizeof(suspeitoAcusado), stdin) == NULL) {
        printf("Erro ao ler entrada.\n");
        return;
    }
    
    size_t len = strlen(suspeitoAcusado);
    if (len > 0 && suspeitoAcusado[len - 1] == '\n') {
        suspeitoAcusado[len - 1] = '\0';
    }
    
    normalizarNome(suspeitoAcusado);
    
    int quantidadePistas = contarPistasPorSuspeito(raizPistas, hash, suspeitoAcusado);
    
    printf("\n=== RESULTADO DO JULGAMENTO ===\n");
    printf("Suspeito acusado: %s\n", suspeitoAcusado);
    printf("Pistas encontradas contra %s: %d\n", suspeitoAcusado, quantidadePistas);
    
    if (quantidadePistas >= 2) {
        printf("\n*** VEREDICTO: CULPADO! ***\n");
        printf("Voce coletou evidencia suficiente para sustentar a acusacao.\n");
        printf("Parabens, detetive! O caso foi resolvido.\n");
    } else {
        printf("\n*** VEREDICTO: INSUFICIENTE ***\n");
        printf("Nao ha pistas suficientes para sustentar a acusacao.\n");
        printf("E necessario pelo menos 2 pistas apontando para o suspeito.\n");
    }
}

void liberarHash(TabelaHash* hash) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashEntry* atual = hash->tabela[i];
        while (atual != NULL) {
            HashEntry* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(hash);
}

void liberarPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

int main() {
    Sala* hall = criarSala("Hall de Entrada", "Porta principal trancada por dentro");
    Sala* salaEstar = criarSala("Sala de Estar", "Copo de vinho sobre a mesa");
    Sala* cozinha = criarSala("Cozinha", "Faca manchada na pia");
    Sala* biblioteca = criarSala("Biblioteca", "Livro aberto na pagina 42");
    Sala* quarto = criarSala("Quarto", "Relogio parado as 23:45");
    Sala* jardim = criarSala("Jardim", "Pegadas na terra molhada");
    Sala* porao = criarSala("Porao", "Cofre aberto e vazio");
    Sala* escritorio = criarSala("Escritorio", "Carta rasgada no lixo");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = quarto;

    cozinha->esquerda = jardim;
    cozinha->direita = porao;

    biblioteca->esquerda = escritorio;

    TabelaHash* hash = criarTabelaHash();
    inserirNaHash(hash, "Porta principal trancada por dentro", "Joao");
    inserirNaHash(hash, "Copo de vinho sobre a mesa", "Maria");
    inserirNaHash(hash, "Faca manchada na pia", "Joao");
    inserirNaHash(hash, "Livro aberto na pagina 42", "Pedro");
    inserirNaHash(hash, "Relogio parado as 23:45", "Maria");
    inserirNaHash(hash, "Pegadas na terra molhada", "Ana");
    inserirNaHash(hash, "Cofre aberto e vazio", "Pedro");
    inserirNaHash(hash, "Carta rasgada no lixo", "Joao");

    printf("=== DETECTIVE QUEST ===\n");
    printf("Bem-vindo a mansao! Explore os comodos para encontrar pistas.\n");

    PistaNode* raizPistas = NULL;
    raizPistas = explorarSalas(hall, raizPistas, hash);

    printf("\n=== PISTAS COLETADAS (ORDEM ALFABETICA) ===\n");
    if (raizPistas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(raizPistas);
    }

    verificarSuspeitoFinal(raizPistas, hash);

    liberarPistas(raizPistas);
    liberarHash(hash);
    free(escritorio);
    free(biblioteca);
    free(quarto);
    free(jardim);
    free(porao);
    free(salaEstar);
    free(cozinha);
    free(hall);

    return 0;
}


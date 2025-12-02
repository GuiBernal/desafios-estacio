#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;
int vetorOrdenado = 0;

No* mochilaLista = NULL;
int totalItensLista = 0;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;
int ordenadoPorNome = 0;
int comparacoesOrdenacao = 0;

void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("Mochila cheia! Capacidade maxima: %d itens.\n", MAX_ITENS);
        return;
    }

    printf("\n=== Cadastrar Item (Vetor) ===\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", mochilaVetor[totalItensVetor].nome);

    printf("Tipo (ex: arma, municao, cura, ferramenta): ");
    scanf(" %[^\n]", mochilaVetor[totalItensVetor].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);

    if (mochilaVetor[totalItensVetor].quantidade <= 0) {
        printf("Quantidade invalida! Item nao cadastrado.\n");
        return;
    }

    totalItensVetor++;
    vetorOrdenado = 0;
    printf("Item cadastrado com sucesso!\n");
}

void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Remover Item (Vetor) ===\n");
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    int indice = -1;
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
        return;
    }

    for (int i = indice; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    totalItensVetor--;
    vetorOrdenado = 0;
    printf("Item '%s' removido com sucesso!\n", nomeBusca);
}

void listarItensVetor() {
    if (totalItensVetor == 0) {
        printf("\nMochila vazia! Nenhum item cadastrado.\n");
        return;
    }

    printf("\n=== Itens na Mochila (Vetor) ===\n");
    printf("%-30s %-20s %s\n", "Nome", "Tipo", "Quantidade");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < totalItensVetor; i++) {
        printf("%-30s %-20s %d\n", 
               mochilaVetor[i].nome, 
               mochilaVetor[i].tipo, 
               mochilaVetor[i].quantidade);
    }

    printf("\nTotal: %d item(ns)\n", totalItensVetor);
    if (vetorOrdenado) {
        printf("Status: Ordenado por nome\n");
    } else {
        printf("Status: Nao ordenado\n");
    }
}

void ordenarVetor() {
    if (totalItensVetor == 0) {
        printf("Mochila vazia! Nao ha itens para ordenar.\n");
        return;
    }

    if (vetorOrdenado) {
        printf("Vetor ja esta ordenado.\n");
        return;
    }

    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }

    vetorOrdenado = 1;
    printf("Vetor ordenado por nome com sucesso!\n");
}

void buscarSequencialVetor() {
    if (totalItensVetor == 0) {
        printf("Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Busca Sequencial (Vetor) ===\n");
    printf("Nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    comparacoesSequencial = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochilaVetor[i].nome);
            printf("Tipo: %s\n", mochilaVetor[i].tipo);
            printf("Quantidade: %d\n", mochilaVetor[i].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
}

void buscarBinariaVetor() {
    if (totalItensVetor == 0) {
        printf("Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }

    if (!vetorOrdenado) {
        printf("Vetor nao esta ordenado. Ordenando antes da busca binaria...\n");
        ordenarVetor();
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Busca Binaria (Vetor) ===\n");
    printf("Nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    comparacoesBinaria = 0;
    int esquerda = 0;
    int direita = totalItensVetor - 1;
    int encontrado = 0;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoesBinaria++;
        
        int comparacao = strcmp(mochilaVetor[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochilaVetor[meio].nome);
            printf("Tipo: %s\n", mochilaVetor[meio].tipo);
            printf("Quantidade: %d\n", mochilaVetor[meio].quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
        printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
    }
}

No* criarNo(Item item) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }
    novo->dados = item;
    novo->proximo = NULL;
    return novo;
}

void inserirItemLista() {
    if (totalItensLista >= MAX_ITENS) {
        printf("Mochila cheia! Capacidade maxima: %d itens.\n", MAX_ITENS);
        return;
    }

    Item novoItem;
    printf("\n=== Cadastrar Item (Lista Encadeada) ===\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Tipo (ex: arma, municao, cura, ferramenta): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    if (novoItem.quantidade <= 0) {
        printf("Quantidade invalida! Item nao cadastrado.\n");
        return;
    }

    No* novo = criarNo(novoItem);
    if (novo == NULL) {
        return;
    }

    if (mochilaLista == NULL) {
        mochilaLista = novo;
    } else {
        No* atual = mochilaLista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    totalItensLista++;
    printf("Item cadastrado com sucesso!\n");
}

void removerItemLista() {
    if (totalItensLista == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Remover Item (Lista Encadeada) ===\n");
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL) {
                mochilaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            totalItensLista--;
            printf("Item '%s' removido com sucesso!\n", nomeBusca);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
}

void listarItensLista() {
    if (totalItensLista == 0) {
        printf("\nMochila vazia! Nenhum item cadastrado.\n");
        return;
    }

    printf("\n=== Itens na Mochila (Lista Encadeada) ===\n");
    printf("%-30s %-20s %s\n", "Nome", "Tipo", "Quantidade");
    printf("------------------------------------------------------------\n");

    No* atual = mochilaLista;
    while (atual != NULL) {
        printf("%-30s %-20s %d\n", 
               atual->dados.nome, 
               atual->dados.tipo, 
               atual->dados.quantidade);
        atual = atual->proximo;
    }

    printf("\nTotal: %d item(ns)\n", totalItensLista);
}

void buscarSequencialLista() {
    if (totalItensLista == 0) {
        printf("Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Busca Sequencial (Lista Encadeada) ===\n");
    printf("Nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    comparacoesSequencial = 0;
    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
}

void liberarLista() {
    No* atual = mochilaLista;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    mochilaLista = NULL;
    totalItensLista = 0;
}

void menuVetor() {
    int opcao;
    while (1) {
        printf("\n=== MOCHILA COM VETOR ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (sequencial)\n");
        printf("5. Ordenar vetor\n");
        printf("6. Buscar item (binaria)\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItemVetor();
                listarItensVetor();
                break;
            case 2:
                removerItemVetor();
                listarItensVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4:
                buscarSequencialVetor();
                break;
            case 5:
                ordenarVetor();
                listarItensVetor();
                break;
            case 6:
                buscarBinariaVetor();
                break;
            case 7:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

void menuLista() {
    int opcao;
    while (1) {
        printf("\n=== MOCHILA COM LISTA ENCADEADA ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (sequencial)\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItemLista();
                listarItensLista();
                break;
            case 2:
                removerItemLista();
                listarItensLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4:
                buscarSequencialLista();
                break;
            case 5:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido! Capacidade maxima: %d componentes.\n", MAX_COMPONENTES);
        return;
    }

    printf("\n=== Cadastrar Componente ===\n");
    printf("Nome do componente: ");
    scanf(" %[^\n]", componentes[totalComponentes].nome);

    printf("Tipo (ex: controle, suporte, propulsao): ");
    scanf(" %[^\n]", componentes[totalComponentes].tipo);

    printf("Prioridade (1 a 10): ");
    scanf("%d", &componentes[totalComponentes].prioridade);

    if (componentes[totalComponentes].prioridade < 1 || componentes[totalComponentes].prioridade > 10) {
        printf("Prioridade invalida! Deve estar entre 1 e 10.\n");
        return;
    }

    totalComponentes++;
    ordenadoPorNome = 0;
    printf("Componente cadastrado com sucesso!\n");
}

void mostrarComponentes(Componente comp[], int total) {
    if (total == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    printf("\n=== Componentes da Torre ===\n");
    printf("%-30s %-20s %s\n", "Nome", "Tipo", "Prioridade");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-30s %-20s %d\n", 
               comp[i].nome, 
               comp[i].tipo, 
               comp[i].prioridade);
    }

    printf("\nTotal: %d componente(s)\n", total);
}

void bubbleSortPorNome(Componente comp[], int total) {
    comparacoesOrdenacao = 0;
    clock_t inicio = clock();

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoesOrdenacao++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    ordenadoPorNome = 1;
    printf("\nOrdenacao concluida (Bubble Sort por Nome)!\n");
    printf("Comparacoes realizadas: %d\n", comparacoesOrdenacao);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
}

void insertionSortPorTipo(Componente comp[], int total) {
    comparacoesOrdenacao = 0;
    clock_t inicio = clock();

    for (int i = 1; i < total; i++) {
        Componente chave = comp[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoesOrdenacao++;
            if (strcmp(comp[j].tipo, chave.tipo) > 0) {
                comp[j + 1] = comp[j];
                j--;
            } else {
                break;
            }
        }
        comp[j + 1] = chave;
    }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    ordenadoPorNome = 0;
    printf("\nOrdenacao concluida (Insertion Sort por Tipo)!\n");
    printf("Comparacoes realizadas: %d\n", comparacoesOrdenacao);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
}

void selectionSortPorPrioridade(Componente comp[], int total) {
    comparacoesOrdenacao = 0;
    clock_t inicio = clock();

    for (int i = 0; i < total - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < total; j++) {
            comparacoesOrdenacao++;
            if (comp[j].prioridade < comp[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            Componente temp = comp[i];
            comp[i] = comp[indiceMenor];
            comp[indiceMenor] = temp;
        }
    }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    ordenadoPorNome = 0;
    printf("\nOrdenacao concluida (Selection Sort por Prioridade)!\n");
    printf("Comparacoes realizadas: %d\n", comparacoesOrdenacao);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
}

void buscaBinariaPorNome(Componente comp[], int total, char nomeBusca[]) {
    if (total == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    if (!ordenadoPorNome) {
        printf("Componentes nao estao ordenados por nome. Ordenando antes da busca...\n");
        bubbleSortPorNome(comp, total);
    }

    comparacoesBinaria = 0;
    clock_t inicio = clock();

    int esquerda = 0;
    int direita = total - 1;
    int encontrado = 0;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoesBinaria++;
        
        int comparacao = strcmp(comp[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            clock_t fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            printf("\n=== Componente-Chave Encontrado! ===\n");
            printf("Nome: %s\n", comp[meio].nome);
            printf("Tipo: %s\n", comp[meio].tipo);
            printf("Prioridade: %d\n", comp[meio].prioridade);
            printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
            printf("Tempo de execucao: %.6f segundos\n", tempo);
            printf("\nTorre de resgate pode ser ativada!\n");
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    if (!encontrado) {
        clock_t fim = clock();
        double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        printf("Componente '%s' nao encontrado.\n", nomeBusca);
        printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
        printf("Tempo de execucao: %.6f segundos\n", tempo);
    }
}

void menuTorre() {
    int opcao;
    while (1) {
        printf("\n=== TORRE DE RESGATE - MONTAGEM FINAL ===\n");
        printf("1. Cadastrar componente\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Buscar componente-chave (Busca Binaria)\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarComponente();
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 2:
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 3:
                if (totalComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                } else {
                    bubbleSortPorNome(componentes, totalComponentes);
                    mostrarComponentes(componentes, totalComponentes);
                }
                break;
            case 4:
                if (totalComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                } else {
                    insertionSortPorTipo(componentes, totalComponentes);
                    mostrarComponentes(componentes, totalComponentes);
                }
                break;
            case 5:
                if (totalComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                } else {
                    selectionSortPorPrioridade(componentes, totalComponentes);
                    mostrarComponentes(componentes, totalComponentes);
                }
                break;
            case 6:
                if (totalComponentes == 0) {
                    printf("Nenhum componente cadastrado.\n");
                } else {
                    char nomeBusca[TAM_NOME];
                    printf("\n=== Buscar Componente-Chave ===\n");
                    printf("Nome do componente a buscar: ");
                    scanf(" %[^\n]", nomeBusca);
                    buscaBinariaPorNome(componentes, totalComponentes, nomeBusca);
                }
                break;
            case 7:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

int main() {
    int opcao;

    printf("=== SISTEMA DE INVENTARIO - FREE FIRE ===\n");
    printf("Comparacao entre Vetor e Lista Encadeada\n");
    printf("Modulo de Torre de Resgate\n\n");

    while (1) {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Trabalhar com Vetor (Lista Sequencial)\n");
        printf("2. Trabalhar com Lista Encadeada\n");
        printf("3. Torre de Resgate (Ordenacao e Busca)\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 3:
                menuTorre();
                break;
            case 4:
                liberarLista();
                printf("Encerrando sistema...\n");
                return 0;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}

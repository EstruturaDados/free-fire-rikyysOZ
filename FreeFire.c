#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Estrutura do Nó para lista encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// Variáveis globais para o vetor
struct Item mochilaVetor[10];
int totalItensVetor = 0;
int comparacoes = 0;

// Variáveis globais para a lista encadeada
struct No* inicioLista = NULL;
int totalItensLista = 0;

// Protótipos de funções vetor
void inserirItemVetor() ;
void removerItemVetor() ;
void listarItensVetor() ;
void ordenarVetor() ;
int buscarSequencialVetor(char nome[]) ;
int buscarBinariaVetor(char nome[]) ;
void buscarItemVetor() ;

// Protótipos de funções lista encadeada
void inserirItemLista() ;
void removerItemLista() ;
void listarItensLista() ;
int buscarSequencialLista(char nome[]) ;
void buscarItemLista() ;

//protótipos de menus
void menuLista() ;
void menuVetor() ;

int main() {
    int opcao;
    
    printf("=== SISTEMA DE GERENCIAMENTO DA MOCHILA ===\n");
    printf("Comparação: Vetor vs Lista Encadeada\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Usar implementação com VETOR\n");
        printf("2. Usar implementação com LISTA ENCADEADA\n");
        printf("3. Sair do sistema\n");    
        printf("Escolha uma opção (1-3): ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;            
            case 3: printf("\n🎮 Obrigado por usar o sistema! Saindo...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
        
    } while (opcao != 3);
    
    // Liberar memória da lista encadeada
    struct No* atual = inicioLista;
    while (atual != NULL) {
        struct No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    return 0;
}


// Funções para a versão com vetor

void inserirItemVetor() {
    if (totalItensVetor >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n=== CADASTRO DE ITEM (VETOR) ===\n");
    
    while (getchar() != '\n'); // Limpa buffer
    
    printf("Nome do item: ");
    fgets(mochilaVetor[totalItensVetor].nome, 30, stdin);
    mochilaVetor[totalItensVetor].nome[strcspn(mochilaVetor[totalItensVetor].nome, "\n")] = '\0';
    
    printf("Tipo (arma, municao, cura): ");
    fgets(mochilaVetor[totalItensVetor].tipo, 20, stdin);
    mochilaVetor[totalItensVetor].tipo[strcspn(mochilaVetor[totalItensVetor].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    
    totalItensVetor++;
    printf("✅ Item cadastrado com sucesso!\n");
}

void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOÇÃO DE ITEM (VETOR) ===\n");
    
    char nomeBusca[30];
    while (getchar() != '\n');
    
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int indice = -1;
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice != -1) {
        printf("✅ Item '%s' removido com sucesso!\n", mochilaVetor[indice].nome);
        
        for (int i = indice; i < totalItensVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        
        totalItensVetor--;
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

void listarItensVetor() {
    printf("\n=== LISTA DE ITENS NA MOCHILA (VETOR) ===\n");
    
    if (totalItensVetor == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("%-30s %-20s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%-30s %-20s %-10d\n", 
               mochilaVetor[i].nome, 
               mochilaVetor[i].tipo, 
               mochilaVetor[i].quantidade);
    }
    printf("Total de itens: %d/10\n", totalItensVetor);
}

void ordenarVetor() {
    if (totalItensVetor == 0) {
        printf("\n❌ Mochila vazia! Não há itens para ordenar.\n");
        return;
    }
    
    // Bubble Sort para ordenar por nome
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca os itens
                struct Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    
    printf("✅ Itens ordenados por nome com sucesso!\n");
    listarItensVetor();
}

int buscarSequencialVetor(char nome[]) {
    comparacoes = 0;
    
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i; // Item encontrado
        }
    }
    
    return -1; // Item não encontrado
}

int buscarBinariaVetor(char nome[]) {
    comparacoes = 0;
    
    // Verifica se o vetor está ordenado
    for (int i = 0; i < totalItensVetor - 1; i++) {
        if (strcmp(mochilaVetor[i].nome, mochilaVetor[i + 1].nome) > 0) {
            printf("⚠️  Vetor não está ordenado. Use a opção de ordenação primeiro.\n");
            return -1;
        }
    }
    
    int inicio = 0;
    int fim = totalItensVetor - 1;
    
    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(nome, mochilaVetor[meio].nome);
        
        if (comparacao == 0) {
            return meio; // Item encontrado
        } else if (comparacao < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    
    return -1; // Item não encontrado
}

void buscarItemVetor() {
    if (totalItensVetor == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA DE ITEM (VETOR) ===\n");
    
    char nomeBusca[30];
    while (getchar() != '\n');
    
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    printf("\n1. Busca Sequencial\n");
    printf("2. Busca Binária (requer vetor ordenado)\n");
    printf("Escolha o tipo de busca: ");
    
    int opcao;
    scanf("%d", &opcao);
    
    int resultado;
    
    if (opcao == 1) {
        resultado = buscarSequencialVetor(nomeBusca);
        printf("\n🔍 BUSCA SEQUENCIAL:\n");
    } else if (opcao == 2) {
        resultado = buscarBinariaVetor(nomeBusca);
        printf("\n🔍 BUSCA BINÁRIA:\n");
    } else {
        printf("❌ Opção inválida!\n");
        return;
    }
    
    if (resultado != -1) {
        printf("✅ Item encontrado na posição %d!\n", resultado);
        printf("Nome: %s\n", mochilaVetor[resultado].nome);
        printf("Tipo: %s\n", mochilaVetor[resultado].tipo);
        printf("Quantidade: %d\n", mochilaVetor[resultado].quantidade);
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
    
    printf("Número de comparações realizadas: %d\n", comparacoes);
}


// Funções para a versão com lista encadeada

void inserirItemLista() {
    if (totalItensLista >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n=== CADASTRO DE ITEM (LISTA ENCADEADA) ===\n");
    
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("❌ Erro de alocação de memória!\n");
        return;
    }
    
    while (getchar() != '\n');
    
    printf("Nome do item: ");
    fgets(novoNo->dados.nome, 30, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';
    
    printf("Tipo (arma, municao, cura): ");
    fgets(novoNo->dados.tipo, 20, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    totalItensLista++;
    
    printf("✅ Item cadastrado com sucesso!\n");
}

void removerItemLista() {
    if (inicioLista == NULL) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOÇÃO DE ITEM (LISTA ENCADEADA) ===\n");
    
    char nomeBusca[30];
    while (getchar() != '\n');
    
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    struct No* atual = inicioLista;
    struct No* anterior = NULL;
    int encontrado = 0;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            encontrado = 1;
            
            if (anterior == NULL) {
                // Remove o primeiro nó
                inicioLista = atual->proximo;
            } else {
                // Remove nó do meio ou final
                anterior->proximo = atual->proximo;
            }
            
            printf("✅ Item '%s' removido com sucesso!\n", atual->dados.nome);
            free(atual);
            totalItensLista--;
            break;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

void listarItensLista() {
    printf("\n=== LISTA DE ITENS NA MOCHILA (LISTA ENCADEADA) ===\n");
    
    if (inicioLista == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("%-30s %-20s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------\n");
    
    struct No* atual = inicioLista;
    while (atual != NULL) {
        printf("%-30s %-20s %-10d\n", 
               atual->dados.nome, 
               atual->dados.tipo, 
               atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("Total de itens: %d/10\n", totalItensLista);
}

int buscarSequencialLista(char nome[]) {
    comparacoes = 0;
    struct No* atual = inicioLista;
    int posicao = 0;
    
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return posicao; // Item encontrado
        }
        atual = atual->proximo;
        posicao++;
    }
    
    return -1; // Item não encontrado
}

void buscarItemLista() {
    if (inicioLista == NULL) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA DE ITEM (LISTA ENCADEADA) ===\n");
    
    char nomeBusca[30];
    while (getchar() != '\n');
    
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    printf("\n🔍 BUSCA SEQUENCIAL (única disponível para lista encadeada):\n");
    
    int resultado = buscarSequencialLista(nomeBusca);
    
    if (resultado != -1) {
        // Encontrar o item para exibir detalhes
        struct No* atual = inicioLista;
        for (int i = 0; i < resultado; i++) {
            atual = atual->proximo;
        }
        
        printf("✅ Item encontrado na posição %d!\n", resultado);
        printf("Nome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
    
    printf("Número de comparações realizadas: %d\n", comparacoes);
}


// Menus

void menuVetor() {
    int opcao;
    
    do {
        printf("\n=== SISTEMA DE MOCHILA - VETOR ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Ordenar itens por nome\n");
        printf("5. Buscar item\n");
        printf("6. Voltar ao menu principal\n");
        printf("Escolha uma opção (1-6): ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarItemVetor(); break;
            case 6: printf("Retornando ao menu principal...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while (opcao != 6);
}

void menuLista() {
    int opcao;
    
    do {
        printf("\n=== SISTEMA DE MOCHILA - LISTA ENCADEADA ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opção (1-5): ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarItemLista(); break;
            case 5: printf("Retornando ao menu principal...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while (opcao != 5);
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item com os campos solicitados
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Vetor global para armazenar até 10 itens
struct Item mochila[10];
int totalItens = 0; // Contador de itens cadastrados

// Função para cadastrar um novo item na mochila
void inserirItem() {
    // Verifica se a mochila está cheia
    if (totalItens >= 10) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n=== CADASTRO DE ITEM ===\n");
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');
    
    // Leitura do nome do item
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0'; // Remove o \n
    
    // Leitura do tipo do item
    printf("Tipo (arma, municao, cura): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0'; // Remove o \n
    
    // Leitura da quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    
    totalItens++;
    printf("✅ Item cadastrado com sucesso!\n");
    
    // Lista todos os itens após o cadastro
    listarItens();
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n=== REMOÇÃO DE ITEM ===\n");
    
    char nomeBusca[30];
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');
    
    // Leitura do nome do item a ser removido
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o \n
    
    // Busca pelo item na mochila
    int indice = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    // Se encontrou o item, remove deslocando os itens seguintes
    if (indice != -1) {
        printf("✅ Item '%s' removido com sucesso!\n", mochila[indice].nome);
        
        // Desloca os itens para preencher o espaço vazio
        for (int i = indice; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        totalItens--;
    } else {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
    
    // Lista todos os itens após a remoção
    listarItens();
}

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n=== LISTA DE ITENS NA MOCHILA ===\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("%-30s %-20s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("%-30s %-20s %-10d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("Total de itens: %d/10\n", totalItens);
}

// Função de busca sequencial por nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n=== BUSCA DE ITEM ===\n");
    
    char nomeBusca[30];
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');
    
    // Leitura do nome do item a ser buscado
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o \n
    
    // Busca sequencial pelo item
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n=== SISTEMA DE GERENCIAMENTO DA MOCHILA ===\n");
    printf("1. Cadastrar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Sair do sistema\n");
    printf("Escolha uma opção (1-5): ");
}

// Função principal
int main() {
    int opcao;
    
    printf("Bem-vindo ao Sistema de Gerenciamento da Mochila!\n");
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\n🎮 Obrigado por usar o Sistema de Gerenciamento da Mochila!\n");
                printf("Saindo...\n");
                break;
            default:
                printf("\n❌ Opção inválida! Por favor, escolha uma opção entre 1 e 5.\n");
        }
        
    } while (opcao != 5);
    
    return 0;
}
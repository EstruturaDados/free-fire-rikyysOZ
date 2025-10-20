#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do Componente para a torre de fuga
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

// Variáveis globais
struct Componente mochila[20];
int totalComponentes = 0;
int comparacoes = 0;
int ordenadoPorNome = 0; // 0 = não ordenado, 1 = ordenado

// Protótipos das funções
void adicionarComponente();
void descartarComponente();
void listarComponentes();
void organizarMochila();
void buscaBinariaComponente();
void ativarTorreFuga();
void mostrarMenu();
void bubbleSortNome(struct Componente componentes[], int n);
void insertionSortTipo(struct Componente componentes[], int n);
void selectionSortPrioridade(struct Componente componentes[], int n);
int buscaBinariaPorNome(struct Componente componentes[], int n, char nome[]);
void medirTempo(void (*algoritmo)(struct Componente[], int), struct Componente componentes[], int n, char* nomeAlgoritmo);

// Função principal
int main() {
    printf("=== PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE) ===\n");
    
    int opcao;
    do {
        mostrarMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n'); // Limpa buffer
        
        switch(opcao) {
            case 1: adicionarComponente(); break;
            case 2: descartarComponente(); break;
            case 3: listarComponentes(); break;
            case 4: organizarMochila(); break;
            case 5: buscaBinariaComponente(); break;
            case 0: ativarTorreFuga(); break;
            default: 
                if(opcao != 0) 
                    printf("\n❌ Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 6);
    
    return 0;
}

void mostrarMenu() {
    printf("\n=== PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE) ===\n");
    printf("Itens na Mochila: %d/20\n", totalComponentes);
    printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
    printf("\n1. Adicionar Componente");
    printf("\n2. Descartar Componente");
    printf("\n3. Listar Componentes (Inventario)");
    printf("\n4. Organizar Mochila (Ordenar Componentes)");
    printf("\n5. Busca Binaria por Componente-Chave (por nome)");
    printf("\n0. ATIVAR TORRE DE FUGA (Sair)");
    printf("\n---");
}

void adicionarComponente() {
    if(totalComponentes >= 20) {
        printf("\n❌ Mochila cheia! Capacidade maxima atingida (20 componentes).\n");
        return;
    }
    
    printf("\n--- Coletando Novo Componente ---\n");
    
    printf("Nome: ");
    fgets(mochila[totalComponentes].nome, 30, stdin);
    mochila[totalComponentes].nome[strcspn(mochila[totalComponentes].nome, "\n")] = '\0';
    
    printf("Tipo (Estrutural, Eletronico, Energia, Controle, Propulsao): ");
    fgets(mochila[totalComponentes].tipo, 20, stdin);
    mochila[totalComponentes].tipo[strcspn(mochila[totalComponentes].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    int quantidade;
    scanf("%d", &quantidade);
    
    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &mochila[totalComponentes].prioridade);
    
    // Validação da prioridade
    if(mochila[totalComponentes].prioridade < 1) 
        mochila[totalComponentes].prioridade = 1;
    if(mochila[totalComponentes].prioridade > 5) 
        mochila[totalComponentes].prioridade = 5;
    
    totalComponentes++;
    ordenadoPorNome = 0; // Nova inserção desfaz a ordenação
    
    printf("\n✅ Componente '%s' adicionado com sucesso!\n", mochila[totalComponentes-1].nome);
    
    // Mostra inventário atualizado
    listarComponentes();
}

void descartarComponente() {
    if(totalComponentes == 0) {
        printf("\n❌ Mochila vazia! Nenhum componente para descartar.\n");
        return;
    }
    
    printf("\n--- Descartar Componente ---\n");
    printf("Nome do componente a ser descartado: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int indice = -1;
    for(int i = 0; i < totalComponentes; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if(indice != -1) {
        printf("✅ Componente '%s' descartado!\n", mochila[indice].nome);
        
        // Remove deslocando os componentes
        for(int i = indice; i < totalComponentes - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        totalComponentes--;
        ordenadoPorNome = 0; // Remoção desfaz a ordenação
    } else {
        printf("❌ Componente '%s' nao encontrado na mochila.\n", nomeBusca);
    }
    
    listarComponentes();
}

void listarComponentes() {
    printf("\n--- INVENTARIO ATUAL (%d/20) ---\n", totalComponentes);
    
    if(totalComponentes == 0) {
        printf("Inventario vazio!\n");
        return;
    }
    
    printf("------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s | %s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("------------------------------------------------------------\n");
    
    for(int i = 0; i < totalComponentes; i++) {
        printf("%-20s | %-15s | %-10d | %d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               1, // Quantidade fixa para simplificar
               mochila[i].prioridade);
    }
    printf("------------------------------------------------------------\n");
}

// Bubble Sort para ordenação por nome
void bubbleSortNome(struct Componente componentes[], int n) {
    comparacoes = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if(strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                struct Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    ordenadoPorNome = 1;
}

// Insertion Sort para ordenação por tipo
void insertionSortTipo(struct Componente componentes[], int n) {
    comparacoes = 0;
    for(int i = 1; i < n; i++) {
        struct Componente chave = componentes[i];
        int j = i - 1;
        
        while(j >= 0) {
            comparacoes++;
            if(strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
    ordenadoPorNome = 0;
}

// Selection Sort para ordenação por prioridade
void selectionSortPrioridade(struct Componente componentes[], int n) {
    comparacoes = 0;
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            comparacoes++;
            if(componentes[j].prioridade > componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca o componente encontrado com o primeiro
        struct Componente temp = componentes[min_idx];
        componentes[min_idx] = componentes[i];
        componentes[i] = temp;
    }
    ordenadoPorNome = 0;
}

// Função para medir tempo de execução
void medirTempo(void (*algoritmo)(struct Componente[], int), struct Componente componentes[], int n, char* nomeAlgoritmo) {
    clock_t inicio, fim;
    double tempo_gasto;
    
    // Cria cópia do array para não modificar o original durante teste
    struct Componente copia[20];
    memcpy(copia, componentes, sizeof(struct Componente) * n);
    
    inicio = clock();
    algoritmo(copia, n);
    fim = clock();
    
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n📊 METRICAS DO %s:\n", nomeAlgoritmo);
    printf("• Comparacoes realizadas: %d\n", comparacoes);
    printf("• Tempo de execucao: %.6f segundos\n", tempo_gasto);
    
    if(tempo_gasto < 0.001) {
        printf("• Velocidade: ⚡ ULTRA RAPIDO\n");
    } else if(tempo_gasto < 0.01) {
        printf("• Velocidade: 🚀 RAPIDO\n");
    } else {
        printf("• Velocidade: 🐢 LENTO\n");
    }
}

void organizarMochila() {
    if(totalComponentes == 0) {
        printf("\n❌ Mochila vazia! Nada para ordenar.\n");
        return;
    }
    
    printf("\n=== ORGANIZAR MOCHILA - ESTRATEGIA DE MONTAGEM ===\n");
    printf("Escolha o criterio de ordenacao:\n");
    printf("1. Por NOME (Bubble Sort) - Para busca binaria\n");
    printf("2. Por TIPO (Insertion Sort) - Agrupar por categoria\n");
    printf("3. Por PRIORIDADE (Selection Sort) - Ordem de montagem\n");
    printf("Opcao: ");
    
    int opcao;
    scanf("%d", &opcao);
    
    // Cria cópia para mostrar métricas sem afetar dados reais
    struct Componente copia[20];
    memcpy(copia, mochila, sizeof(struct Componente) * totalComponentes);
    
    switch(opcao) {
        case 1:
            printf("\n🎯 ORDENANDO POR NOME (BUBBLE SORT)...\n");
            medirTempo(bubbleSortNome, copia, totalComponentes, "BUBBLE SORT");
            bubbleSortNome(mochila, totalComponentes);
            printf("✅ Componentes ordenados por nome!\n");
            break;
            
        case 2:
            printf("\n🎯 ORDENANDO POR TIPO (INSERTION SORT)...\n");
            medirTempo(insertionSortTipo, copia, totalComponentes, "INSERTION SORT");
            insertionSortTipo(mochila, totalComponentes);
            printf("✅ Componentes agrupados por tipo!\n");
            break;
            
        case 3:
            printf("\n🎯 ORDENANDO POR PRIORIDADE (SELECTION SORT)...\n");
            medirTempo(selectionSortPrioridade, copia, totalComponentes, "SELECTION SORT");
            selectionSortPrioridade(mochila, totalComponentes);
            printf("✅ Componentes ordenados por prioridade de montagem!\n");
            break;
            
        default:
            printf("❌ Opcao invalida!\n");
            return;
    }
    
    listarComponentes();
}

// Busca binária por nome
int buscaBinariaPorNome(struct Componente componentes[], int n, char nome[]) {
    comparacoes = 0;
    int inicio = 0;
    int fim = n - 1;
    
    while(inicio <= fim) {
        comparacoes++;
        int meio = inicio + (fim - inicio) / 2;
        int resultado = strcmp(nome, componentes[meio].nome);
        
        if(resultado == 0) {
            return meio; // Encontrado
        } else if(resultado < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    
    return -1; // Não encontrado
}

void buscaBinariaComponente() {
    if(totalComponentes == 0) {
        printf("\n❌ Mochila vazia! Nenhum componente para buscar.\n");
        return;
    }
    
    if(!ordenadoPorNome) {
        printf("\n⚠️  ATENCAO: Mochila nao esta ordenada por nome!\n");
        printf("Deseja ordenar antes da busca binaria? (s/n): ");
        
        char resposta;
        scanf("%c", &resposta);
        
        if(resposta == 's' || resposta == 'S') {
            bubbleSortNome(mochila, totalComponentes);
            printf("✅ Mochila ordenada por nome!\n");
        } else {
            printf("❌ Busca binaria requer ordenacao por nome.\n");
            return;
        }
    }
    
    printf("\n=== BUSCA BINARIA - COMPONENTE-CHAVE ===\n");
    printf("Nome do componente critico: ");
    
    char nomeBusca[30];
    while(getchar() != '\n'); // Limpa buffer
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int resultado = buscaBinariaPorNome(mochila, totalComponentes, nomeBusca);
    
    printf("\n🔍 RESULTADO DA BUSCA BINARIA:\n");
    printf("• Componente buscado: %s\n", nomeBusca);
    printf("• Comparacoes realizadas: %d\n", comparacoes);
    
    if(resultado != -1) {
        printf("✅ COMPONENTE-CHAVE ENCONTRADO!\n");
        printf("• Posicao na mochila: %d\n", resultado);
        printf("• Tipo: %s\n", mochila[resultado].tipo);
        printf("• Prioridade: %d/5\n", mochila[resultado].prioridade);
        printf("\n🎯 STATUS: Torre pode ser ativada!\n");
    } else {
        printf("❌ COMPONENTE-CHAVE NAO ENCONTRADO!\n");
        printf("⚠️  Torre de fuga nao pode ser montada.\n");
    }
}

void ativarTorreFuga() {
    printf("\n=== ATIVACAO DA TORRE DE FUGA ===\n");
    
    if(totalComponentes == 0) {
        printf("❌ ALERTA CRITICO: Nenhum componente disponivel!\n");
        printf("   Impossivel montar a torre de resgate.\n");
        return;
    }
    
    // Verifica se temos componentes essenciais
    int componentesEssenciais = 0;
    char* essenciais[] = {"PainelSolar", "ChipCentral", "AntenaComando", "BaseEstrutural"};
    int totalEssenciais = 4;
    
    printf("🔍 Verificando componentes essenciais...\n");
    
    for(int i = 0; i < totalEssenciais; i++) {
        int encontrado = 0;
        for(int j = 0; j < totalComponentes; j++) {
            if(strcmp(mochila[j].nome, essenciais[i]) == 0) {
                encontrado = 1;
                componentesEssenciais++;
                break;
            }
        }
        printf("• %s: %s\n", essenciais[i], encontrado ? "✅ ENCONTRADO" : "❌ FALTANDO");
    }
    
    printf("\n📊 RESUMO DA MONTAGEM:\n");
    printf("• Componentes totais: %d/20\n", totalComponentes);
    printf("• Componentes essenciais: %d/%d\n", componentesEssenciais, totalEssenciais);
    
    if(componentesEssenciais >= 3) {
        printf("\n🎉 SUCESSO! TORRE DE FUGA ATIVADA!\n");
        printf("💫 Escape da ilha garantido!\n");
        printf("🏆 VOCE SOBREVIVEU AO DESAFIO FINAL!\n");
    } else {
        printf("\n❌ FALHA CRITICA NA MONTAGEM!\n");
        printf("💀 Torre colapsou - Missao fracassada!\n");
    }
    
    printf("\nSaindo do sistema...\n");
}
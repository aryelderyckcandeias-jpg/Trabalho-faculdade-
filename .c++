#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
// Esta struct agrupa informações relacionadas a um território: nome, cor do exército e quantidade de tropas
struct Territorio {
    char nome[30];  // Campo para armazenar o nome do território (até 29 caracteres + null terminator)
    char cor[10];   // Campo para armazenar a cor do exército (até 9 caracteres + null terminator)
    int tropas;     // Campo para armazenar a quantidade de tropas (número inteiro)
};

// Vetor de missões estratégicas pré-definidas
// Contém 5 descrições de missões que podem ser sorteadas para os jogadores
char* missoes[] = {
    "Conquistar 3 territorios",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar territorios com mais de 10 tropas",
    "Ter pelo menos 5 territorios da mesma cor",
    "Reduzir as tropas totais do inimigo para menos de 20"
};
int totalMissoes = 5;  // Número total de missões disponíveis

// Função para atribuir uma missão sorteada a um jogador
// Recebe um ponteiro para o destino (missão do jogador), o vetor de missões e o total de missões
// Usa rand() para sortear e strcpy para copiar a missão
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

// Função para exibir a missão de um jogador
// Recebe a missão por valor (cópia) para exibição
void exibirMissao(char missao[100]) {
    printf("Sua missao: %s\n", missao);
}

// Função para verificar se a missão foi cumprida
// Recebe a missão por referência (ponteiro) para acesso direto, o mapa de territórios e o tamanho
// Implementa lógica simples para verificação baseada na descrição da missão
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        // Conta territórios conquistados (assumindo cor do jogador como "azul" para exemplo; em produção, passe cor do jogador)
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) count++;  // Exemplo: cor do jogador
        }
        return count >= 3;
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        // Verifica se não há tropas vermelhas
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    } else if (strcmp(missao, "Controlar territorios com mais de 10 tropas") == 0) {
        // Verifica se controla pelo menos um território com >10 tropas
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 10) return 1;  // Exemplo
        }
        return 0;
    } else if (strcmp(missao, "Ter pelo menos 5 territorios da mesma cor") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) count++;  // Exemplo
        }
        return count >= 5;
    } else if (strcmp(missao, "Reduzir as tropas totais do inimigo para menos de 20") == 0) {
        int totalInimigo = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) totalInimigo += mapa[i].tropas;  // Exemplo: inimigo vermelho
        }
        return totalInimigo < 20;
    }
    return 0;  // Missão não reconhecida ou não cumprida
}

// Função para cadastrar os territórios
// Recebe um ponteiro para o vetor de territórios e o número de territórios
void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("Cadastro do Territorio %d:\n", i + 1);
        
        // Entrada do nome do território
        printf("Digite o nome do territorio: ");
        scanf("%s", mapa[i].nome);
        
        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        scanf("%s", mapa[i].cor);
        
        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");  // Linha em branco para separar os cadastros
    }
}

// Função para exibir os dados dos territórios
// Recebe um ponteiro para o vetor de territórios e o número de territórios
void exibirMapa(struct Territorio* mapa, int numTerritorios) {
    printf("Dados dos Territorios:\n");
    printf("======================\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exercito: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("\n");
    }
}

// Função para simular um ataque entre dois territórios
// Recebe ponteiros para o atacante e defensor
// Utiliza números aleatórios para simular rolagem de dados (1-6)
// Se atacante vencer, transfere cor e metade das tropas; se perder, atacante perde 1 tropa
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Rolagem de dados: 1 a 6 para cada lado
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Resultado do ataque:\n");
    printf("Dado do Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do Defensor (%s): %d\n", defensor->nome, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence: transfere cor e metade das tropas (divisão inteira)
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        printf("Atacante venceu! %s agora controla %s com %d tropas.\n", atacante->nome, defensor->nome, defensor->tropas);
    } else {
        // Defensor vence ou empate: atacante perde 1 tropa (se possível)
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
        printf("Defensor venceu! Atacante perdeu 1 tropa. Tropas restantes: %d\n", atacante->tropas);
    }
    printf("\n");
}

// Função para liberar a memória alocada dinamicamente
// Recebe ponteiros para o mapa de territórios e as missões dos jogadores
void liberarMemoria(struct Territorio* mapa, char* missaoJogador1, char* missaoJogador2) {
    free(mapa);        // Libera memória dos territórios
    free(missaoJogador1);  // Libera memória da missão do jogador 1
    free(missaoJogador2);  // Libera memória da missão do jogador 2
}

int main() {
    // Inicialização do gerador de números aleatórios para garantir aleatoriedade
    srand(time(NULL));
    
    int numTerritorios;
    printf("Digite o numero de territorios a cadastrar: ");
    scanf("%d", &numTerritorios);
    
    // Alocação dinâmica de memória para o vetor de territórios
    // Usamos calloc para inicializar a memória com zeros
    struct Territorio* mapa = (struct Territorio*) calloc(numTerritorios, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para territorios!\n");
        return 1;  // Sai do programa em caso de erro
    }
    
    // Alocação dinâmica para as missões dos jogadores (2 jogadores)
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));  // Espaço para string da missão
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));
    if (missaoJogador1 == NULL || missaoJogador2 == NULL) {
        printf("Erro ao alocar memoria para missoes!\n");
        free(mapa);
        return 1;
    }
    
    // Cadastro dos territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Atribuição de missões sorteadas para os jogadores
    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);
    
    // Exibição das missões (apenas uma vez, no início)
    printf("Jogador 1, ");
    exibirMissao(missaoJogador1);
    printf("Jogador 2, ");
    exibirMissao(missaoJogador2);
    printf("\n");
    
    // Exibição inicial do mapa
    exibirMapa(mapa, numTerritorios);
    
    // Loop para simulação de ataques (turnos alternados entre jogadores)
    // Após cada ataque, verifica se algum jogador cumpriu a missão
    int turno = 1;  // 1 para Jogador 1, 2 para Jogador 2
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        printf("Turno do Jogador %d\n", turno);
        
        int indiceAtacante, indiceDefensor;
        
        // Seleção do território atacante
        printf("Escolha o indice do territorio atacante (1 a %d): ", numTerritorios);
        scanf("%d", &indiceAtacante);
        indiceAtacante--;  // Ajuste para índice baseado em 0
        
        // Seleção do território defensor
        printf("Escolha o indice do territorio defensor (1 a %d): ", numTerritorios);
        scanf("%d", &indiceDefensor);
        indiceDefensor--;  // Ajuste para índice baseado em 0
        
        // Validação: verificar se os índices são válidos e se as cores são diferentes
        if (indiceAtacante < 0 || indiceAtacante >= numTerritorios ||
            indiceDefensor < 0 || indiceDefensor >= numTerritorios ||
            indiceAtacante == indiceDefensor) {
            printf("Indices invalidos ou iguais! Tente novamente.\n\n");
            continue;
        }
        
        if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
            printf("Nao e possivel atacar um territorio da mesma cor! Tente novamente.\n\n");
            continue;
        }
        
        // Simulação do ataque usando ponteiros
        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        
        // Exibição do mapa atualizado
        exibirMapa(mapa, numTerritorios);
        
        // Verificação silenciosa das missões após o ataque
        if (verificarMissao(missaoJogador1, mapa, numTerritorios)) {
            printf("Jogador 1 venceu! Missao cumprida: %s\n", missaoJogador1);
            break;
        }
        if (verificarMissao(missaoJogador2, mapa, numTerritorios)) {
            printf("Jogador 2 venceu! Missao cumprida: %s\n", missaoJogador2);
            break;
        }
        
        // Alterna turno
        turno = (turno == 1) ? 2 : 1;
        
        // Perguntar se deseja continuar
        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);  // Espaço antes de %c para ignorar newline
    }
    
    // Liberação da memória alocada
    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    
    printf("Programa encerrado. Memoria liberada com sucesso!\n");
    return 0;
}

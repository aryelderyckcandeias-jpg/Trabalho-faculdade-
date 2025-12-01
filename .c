#include <stdio.h>  // Biblioteca para entrada e saída padrão (printf, scanf)
#include <string.h> // Biblioteca para manipulação de strings (embora não seja usada diretamente aqui, incluída conforme requisitos)

/*
 * Definição da struct Territorio:
 * Esta estrutura agrupa dados relacionados a um território, incluindo nome, cor do exército e quantidade de tropas.
 * Campos:
 * - nome: string de até 29 caracteres (mais o terminador nulo) para armazenar o nome do território.
 * - cor: string de até 9 caracteres para a cor do exército.
 * - tropas: inteiro para o número de tropas.
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração de um vetor de structs para armazenar 5 territórios
    struct Territorio territorios[5];
    
    // Loop para entrada dos dados dos 5 territórios
    // Usamos um laço for para iterar de 0 a 4, preenchendo cada struct no vetor
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Território %d:\n", i + 1);
        
        // Entrada do nome: usamos scanf("%s") para ler uma string sem espaços
        // Nota: se o nome tiver espaços, apenas a primeira palavra será lida
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);
        
        // Entrada da cor: similar ao nome, lê uma string sem espaços
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);
        
        // Entrada do número de tropas: scanf("%d") para inteiro
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");  // Linha em branco para separar cadastros
    }
    
    // Exibição dos dados após o cadastro
    // Percorremos o vetor novamente para imprimir as informações de cada território
    printf("Dados dos Territórios Cadastrados:\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Número de Tropas: %d\n\n", territorios[i].tropas);
    }
    
    return 0;  // Fim do programa
}

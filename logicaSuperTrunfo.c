#include <stdio.h>

// Define as constantes para o número de estados e cidades
#define NUM_ESTADOS 8 // Número total de estados
#define NUM_CIDADES 4 // Número de cidades por estado

// Estrutura para representar os dados de uma carta (uma cidade)
typedef struct {
    char codigoCarta[4];     // Código único da carta, ex: A01
    char nomeCidade[50];     // Nome da cidade
    int populacao;           // População da cidade
    float area;              // Área da cidade em km²
    float PIB;               // Produto Interno Bruto (PIB) da cidade
    int pontosTuristicos;    // Número de pontos turísticos da cidade
    float densidade;         // Densidade populacional (calculada)
    float pibPerCapita;      // PIB per capita (calculado)
} Carta;

// Função para calcular propriedades adicionais das cartas (Aventureiro)
void calcularPropriedades(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade = carta->populacao / carta->area; // Calcula a densidade populacional
    } else {
        carta->densidade = 0; // Evita divisão por zero
    }

    if (carta->populacao > 0) {
        carta->pibPerCapita = carta->PIB / carta->populacao; // Calcula o PIB per capita
    } else {
        carta->pibPerCapita = 0; // Evita divisão por zero
    }
}

// Função para exibir os dados de uma carta
void exibirCarta(Carta carta) {
    printf("\nCodigo da Carta: %s\n", carta.codigoCarta);            // Exibe o código único da carta
    printf("Nome da Cidade: %s\n", carta.nomeCidade);               // Exibe o nome da cidade
    printf("Populacao: %d\n", carta.populacao);                     // Exibe a população da cidade
    printf("Area em Km²: %.2f\n", carta.area);                      // Exibe a área da cidade
    printf("PIB: %.2f\n", carta.PIB);                               // Exibe o PIB da cidade
    printf("Pontos Turisticos: %d\n", carta.pontosTuristicos);      // Exibe os pontos turísticos
    printf("Densidade Populacional: %.2f habitantes/km²\n", carta.densidade); // Exibe a densidade
    printf("PIB Per Capita: %.2f\n", carta.pibPerCapita);           // Exibe o PIB per capita
}

// Função principal
int main() {
    Carta cartas[NUM_ESTADOS * NUM_CIDADES]; // Array para armazenar todas as cartas
    int totalCartas = 0; // Contador para o total de cartas cadastradas

    // Mensagem inicial do programa
    printf("Bem-vindo ao cadastro de cartas do Super Trunfo - Países!\n");
    printf("Por favor, insira os dados das cidades.\n");

    // Cadastro das cartas (Novato e Aventureiro)
    for (char estado = 'A'; estado < 'A' + NUM_ESTADOS; estado++) {
        for (int cidadeNum = 1; cidadeNum <= NUM_CIDADES; cidadeNum++) {
            Carta novaCarta;
            sprintf(novaCarta.codigoCarta, "%c%02d", estado, cidadeNum); // Gera o código da carta

            printf("\n--- Cadastro da Carta %s ---\n", novaCarta.codigoCarta);

            printf("Digite o nome da cidade: ");
            scanf(" %49[^\n]", novaCarta.nomeCidade); // Limita entrada a 49 caracteres

            do {
                printf("Digite a populacao da cidade: ");
                scanf("%d", &novaCarta.populacao);
                if (novaCarta.populacao < 0) {
                    printf("Erro: A populacao nao pode ser negativa.\n");
                }
            } while (novaCarta.populacao < 0);

            do {
                printf("Digite a area da cidade (em km²): ");
                scanf("%f", &novaCarta.area);
                if (novaCarta.area <= 0) {
                    printf("Erro: A area deve ser maior que zero.\n");
                }
            } while (novaCarta.area <= 0);

            do {
                printf("Digite o PIB da cidade: ");
                scanf("%f", &novaCarta.PIB);
                if (novaCarta.PIB < 0) {
                    printf("Erro: O PIB nao pode ser negativo.\n");
                }
            } while (novaCarta.PIB < 0);

            do {
                printf("Digite o numero de pontos turisticos: ");
                scanf("%d", &novaCarta.pontosTuristicos);
                if (novaCarta.pontosTuristicos < 0) {
                    printf("Erro: O numero de pontos turisticos nao pode ser negativo.\n");
                }
            } while (novaCarta.pontosTuristicos < 0);

            calcularPropriedades(&novaCarta); // Calcula propriedades adicionais (Aventureiro)

            cartas[totalCartas] = novaCarta; // Armazena a carta no array
            totalCartas++;
            printf("Carta %s cadastrada com sucesso!\n", novaCarta.codigoCarta);
        }
    }

    // Exibição de todas as cartas cadastradas
    printf("\n--- Cartas Cadastradas ---\n");
    for (int i = 0; i < totalCartas; i++) {
        exibirCarta(cartas[i]); // Exibe todas as informações, incluindo as propriedades calculadas
    }

    // Comparação de cartas (Mestre)
    printf("\n--- Comparacao de Cartas ---\n");
    printf("Digite os números das cartas que deseja comparar (ex: 1 2): ");
    int carta1, carta2;
    scanf("%d %d", &carta1, &carta2);

    // Ajusta os índices para o array (índices começam em 0)
    carta1--;
    carta2--;

    if (carta1 >= 0 && carta1 < totalCartas && carta2 >= 0 && carta2 < totalCartas) {
        printf("\nComparando Carta %s com Carta %s:\n", cartas[carta1].codigoCarta, cartas[carta2].codigoCarta);
        printf("Densidade Populacional: %s vence\n",
               cartas[carta1].densidade < cartas[carta2].densidade ? cartas[carta1].codigoCarta : cartas[carta2].codigoCarta);
        printf("PIB Per Capita: %s vence\n",
               cartas[carta1].pibPerCapita > cartas[carta2].pibPerCapita ? cartas[carta1].codigoCarta : cartas[carta2].codigoCarta);
        printf("Populacao: %s vence\n",
               cartas[carta1].populacao > cartas[carta2].populacao ? cartas[carta1].codigoCarta : cartas[carta2].codigoCarta);
        printf("Pontos Turisticos: %s vence\n",
               cartas[carta1].pontosTuristicos > cartas[carta2].pontosTuristicos ? cartas[carta1].codigoCarta : cartas[carta2].codigoCarta);
    } else {
        printf("Erro: Indice de carta invalido.\n");
    }

    // Mensagem final do programa
    printf("\nObrigado por participar do desafio Super Trunfo!\n");
    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
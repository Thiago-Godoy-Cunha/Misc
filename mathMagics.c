#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

/*int raizQuadrada(int tam) {
    int i = 1;
    int t = tam;
    int resultado = 0;

    while (i <= t)
    {
        int meio = i + (t - i) / 2;
        if (meio == (tam/meio)) return meio;
        if (meio < (tam/meio)) 
        {
            i = meio + 1;
            resultado = meio;
        } 
        else t = meio - 1;      
    }

    if (resultado * resultado == tam) return resultado;
    else return -1;
}*/

uint8_t shift(uint8_t index)
{
    return (60 - (index * 4));
}

void inputCarta(int64_t *deck, int8_t carta, uint8_t index)
{
    *deck &= ~(0xFULL << shift(index)); // Se não for long long, ele atribui 32 bits e o bit shifting não funciona
    *deck |= ((int64_t)(carta & 0xF) << shift(index));
}

// uint8_t inputCartaReturn(int64_t deck, int8_t carta, uint8_t index)
// {
//     deck &= ~(0xFULL << shift(index)); // Se não for long long, ele atribui 32 bits e o bit shifting não funciona
//     deck |= ((int64_t)(carta & 0xF) << shift(index));
//     return carta;
// }

// #define inputCarta(d, c, i) _Generic((d), int64_t*: inputCartaPont, int64_t: inputCartaReturn)(d, c, i) // Sim, usei IA pra fazer overload de função em C puro

uint8_t lerCarta(int64_t deck, uint8_t index)
{
    return (deck >> shift(index)) & 0xF;
}

void shuffle(int64_t *deck) 
{
    int64_t d = (*deck);
    for (uint8_t i = 0xF; i > 0; i--)
    {
        uint8_t randIndex = rand()%0xF;
        int64_t temp = lerCarta(d, randIndex);
        int64_t value = lerCarta(d, i);
        d &= ~(0xFULL << shift(randIndex));
        d |= (value << shift(randIndex));
        d &= ~(0xFULL << shift(i));
        d |= (temp << shift(i));
        int8_t carta = lerCarta(d, i);
    }
    *deck = d;
}

int main()
{
    srand(time(NULL));

    // Princípios de preenchimento e visualizção do baralho 
    int64_t deck=0;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (i%4+1 < 2) inputCarta(&deck, (((i%4)+1)|8), i); // Enche o deck com cartas de um a quatro, 
        else inputCarta(&deck, ((i%4)+1), i);               // reservando o último bit para o sinal caso seja um Ás
    }

    printf("Baralho original: ");
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t carta = lerCarta(deck, i);
        if (carta>8) printf("%d, ", carta-8);
        else printf("%d, ", carta);
    }
    printf("\n\n");

    printf("Baralho ases virados: ");
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t carta = lerCarta(deck, i);
        if (carta > 7) printf("%d, ", (carta ^ 0x8)*(-1));
        else printf("%d, ", (carta));
    }
    printf("\n\n");

    shuffle(&deck);
    printf("Baralho embaralhado: ");
    for (uint8_t i = 0; i < 16; i++)
    {
        uint8_t carta = lerCarta(deck, i);
        if (carta > 7) printf("%d, ", (carta ^ 0x8)*(-1));
        else printf("%d, ", (carta));
    }
    printf("\n\n");

    /*
    for (size_t i = 0; i < tam; i++) if ((i+1)%2==0) deck[i]=deck[i]*(-1);
    printf("Deck caótico: "); // O baralho após fazer a sequência de mantém, vira, mantém, vira
    for (size_t i = 0; i < tam; i++) printf("%d, ", deck[i]);
    printf("\n");
    
    for (size_t i = 0; i < tam; i++) if (rand()%2==0) if (i%2==0) // Só pra pegar os pares de cartas de forma aleatória
    { 
        deck[i]=deck[i]*(-1);
        deck[i+1]=deck[i+1]*(-1);
    }
    printf("Deck caótico ²: "); // O baralho após virar ou manter duplas de cartas de forma aleatória
    for (size_t i = 0; i < tam; i++) printf("%d, ", deck[i]);
    printf("\n");

    int ladoMatriz = raizQuadrada((int)tam);

    printf("Matriz normal:\n");
    for (int i = 0; i < ladoMatriz; i++)
    {
        if (i%2!=0) for (int x = ladoMatriz; x > ladoMatriz/2; x--) { // Isso inverte a ordem das linhas pares da matriz (espero)
            int aux =  deck[((ladoMatriz*i) + x) - 1];
            deck[((ladoMatriz*i) + x) - 1] = deck[((ladoMatriz*(i+1)) - x)];
            deck[((ladoMatriz*(i+1)) - x)] = aux;
        }
        for (int j = ladoMatriz*i; j < ladoMatriz*(i+1); j++) printf("| %d\t", deck[j]); // printa a matriz formatada corretamente
        printf("|\n");
    }
        int par[2];
        
        // pqp tarde demais pra usar alocação dinâmica
        // vou de gambiarra
        int escolha = 0;
        if (rand()%2==0) escolha++;
        escolha = escolha*(escolha+1);
        if (rand()%2==0) escolha++;

        switch (escolha)
        {
            case 0: // primeira coluna
                for (int i = 0; i < ladoMatriz; i++) 
                {
                    par[0] = deck[ladoMatriz*i]*(-1);
                    par[1] = deck[(ladoMatriz*i)+1];     
                    deck[ladoMatriz*i] = (intptr_t)par; 
                    deck[(ladoMatriz*i)+1] = 0;  
                    if (deck[i] == 0) deck[i] = deck[i+1];
                }
                printf("Primeira coluna\n");
                break;
            
            case 1: // última coluna
                for (int i = 0; i < ladoMatriz; i++) 
                {
                    par[0] = deck[(ladoMatriz*(i+1))-1]*(-1);
                    par[1] = deck[(ladoMatriz*(i+1))-2];
                    deck[(ladoMatriz*(i+1))-1] = (intptr_t)par;
                    deck[(ladoMatriz*(i+1))-2] = 0;
                    if (deck[i] == 0) deck[i] = deck[i+1];
                }
                printf("Última coluna\n");
                break;
            case 2: // primeira linha
                for (int i = 0; i < ladoMatriz; i++) 
                {
                    par[0] = deck[i]*(-1);
                    par[1] = deck[ladoMatriz+i];
                    deck[i] = (intptr_t)par;
                    for (int j = ladoMatriz; j < ((ladoMatriz*ladoMatriz)-ladoMatriz)/ladoMatriz; j++) deck[ladoMatriz*i+j] = deck[ladoMatriz*(i+1)+j];
                }
                printf("Primeira linha\n");
                break;
            
            case 3: // última linha
                for (int i = 0; i < ladoMatriz; i++) 
                {
                    par[0] = deck[(int)tam-1-i]*(-1);
                    par[1] = deck[(int)tam-ladoMatriz-1-i];
                    deck[(int)tam-ladoMatriz-1-i] = (intptr_t)par;
                    deck[(int)tam-1-i] = 0;
                }
                printf("Última coluna\n");
                break;
            
            default: // sei la o que pode dar errado
                break;
        }
    printf("Matriz reduzida:\n");
    for (int i = 0; i < ladoMatriz; i++)
    {
        for (int j = ladoMatriz*i; j < ladoMatriz*(i+1); j++) if (deck[j] < ladoMatriz*(-1) || deck[j] > ladoMatriz) printf("| %d\t", &deck[j]); else printf("| %d\t", deck[j]); // printa a matriz formatada corretamente
        printf("|\n");
    }*/
}
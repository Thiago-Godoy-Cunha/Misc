#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int raizQuadrada(int tam) {

    int i = 1;
    int t = tam;
    int resultado = 0;

    while (i <= t)
    {
        int meio = i + (t - i) / 2;

        if (meio == (tam/meio)) return meio;

        if (meio < (tam/meio)) {
            i = meio + 1;
            resultado = meio;
        } 
        else {
            t = meio - 1;
        }       
    }

    if (resultado * resultado == tam) return resultado;
    else return -1;
}

int main()
{
    srand(time(NULL));
    int64_t d=8070450532247928832;
    printf("%ld\n", d);
    printf("%ld\n", (d >> 60) & 0xF);
    

    /*intptr_t deck[] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    size_t tam = sizeof(deck) / sizeof(intptr_t);

    printf("Deck original: "); // O baralho normal, com todas as cartas normalmente colocadas nele
    for (size_t i = 0; i < tam; i++) printf("%d, ", deck[i]);
    printf("\n");

    for (size_t i = 0; i < tam; i++) if (deck[i]==1) deck[i]=deck[i]*(-1);
    printf("Deck azes virados: "); // o baralho após colocar os azes virados (representei cartas viradas como os números negatidos)
    for (size_t i = 0; i < tam; i++) printf("%d, ", deck[i]);
    printf("\n");

    for (size_t i = tam-1; i > 0; i--) // Preguiça de transformar esse trechinho em uma função pra substituir o shuffle
    {
        size_t j = rand() % tam;
        int temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }

    printf("Deck embaralhado: "); // o baralho após embaralhar novamente
    for (size_t i = 0; i < tam; i++) printf("%d, ", deck[i]);
    printf("\n");

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
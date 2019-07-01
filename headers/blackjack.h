#include "baralho.h"

void inicializarMao(struct Carta mao[]);
void adicionarCartaMao(struct Carta mao[], struct Carta carta, int pos);
void comprarCarta(struct Carta mao[], struct Baralho *baralho);
int somaValorMao(struct Carta mao[], int valorA);
int jogadorGanhou(struct Carta maoBanqueiro[], int somaJogador);
int jogadorEstourou(int soma);
int banqueiroDeveComprar(struct Carta maoBanqueiro[], int pontuacaoJogador);
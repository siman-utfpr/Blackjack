#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Carta {
	int numero;
	int naipe;
	char caminhoImagem[50];
};

struct Baralho {
	struct Carta baralho[52];
};

// Preenche o baralho com todas as cartas
struct Baralho preencherBaralho();

// Todas essas funções recebem o ponteiro do baralho porque uma carta deve ser removida do baralho original

struct Carta sortearCarta(struct Baralho *baralho);
int descobrirIndiceCarta(struct Baralho *baralho, struct Carta carta, int pos);
void removerCartaBaralho(struct Baralho *baralho, struct Carta carta);
struct Carta sacarCarta(struct Baralho *baralho);
struct Carta getCartaVazia();
int isCartaVazia(struct Carta carta);
int getValorCarta(struct Carta carta);
#include <string.h>
#include <stdio.h>
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
struct Baralho preencherBaralho(struct Baralho baralho);

// Todas essas funções recebem o ponteiro do baralho porque uma carta deve ser removida do baralho 
// original, que foi passado como parâmetro

struct Carta sortearCarta(struct Baralho *baralho);
int descobrirIndiceCarta(struct Baralho *baralho, struct Carta carta, int pos);
void removerCartaBaralho(struct Baralho *baralho, struct Carta carta);
struct Carta sacarCarta(struct Baralho *baralho);
struct Carta getCartaVazia();
int isCartaVazia(struct Carta carta);

struct Baralho preencherBaralho(struct Baralho baralho){
	int posicao = 0;
	char aux[20];
	for(int i = 1; i <= 13; i++){
		for(int j = 0; j < 4; j++){
			char basePath[50] = "../recursos/baralho/";
			baralho.baralho[posicao].numero = i;
			baralho.baralho[posicao].naipe = j;
			switch(j){
				case 0:
					sprintf(aux, "%i", i);
					strcat(aux, "ouros.png");
					strcat(basePath, aux);
					strcpy(baralho.baralho[posicao].caminhoImagem, basePath);
					break;
				case 1:
					sprintf(aux, "%i", i);
					strcat(aux, "paus.png");
					strcat(basePath, aux);
					strcpy(baralho.baralho[posicao].caminhoImagem, basePath);
					break;
				case 2:
					sprintf(aux, "%i", i);
					strcat(aux, "copas.png");
					strcat(basePath, aux);
					strcpy(baralho.baralho[posicao].caminhoImagem, basePath);
					break;
				case 3:
					sprintf(aux, "%i", i);
					strcat(aux, "espadas.png");
					strcat(basePath, aux);
					strcpy(baralho.baralho[posicao].caminhoImagem, basePath);
					break;										
			}
			posicao++;
		}
	}
	return baralho;
}

struct Carta sortearCarta(struct Baralho *baralho){
	srand(time(NULL));
	int aleatorio = rand() % 51;
	return baralho->baralho[aleatorio];
}

int descobrirIndiceCarta(struct Baralho *baralho, struct Carta carta, int pos){
	if(baralho->baralho[pos].numero == carta.numero &&
		baralho->baralho[pos].naipe == carta.naipe){
		return pos;
	}else{
		return descobrirIndiceCarta(baralho, carta, pos + 1);
	}
}

void removerCartaBaralho(struct Baralho *baralho, struct Carta carta){
	int indice = descobrirIndiceCarta(baralho, carta, 0);
	baralho->baralho[indice] = getCartaVazia();
	//baralho->baralho[indice].numero = -1;
	//baralho->baralho[indice].naipe = -1;
}

struct Carta sacarCarta(struct Baralho *baralho){
	struct Carta c1 = sortearCarta(baralho);
	while(isCartaVazia(c1)){
		c1 = sortearCarta(baralho);
	}
	removerCartaBaralho(baralho, c1);
	return c1;
}

struct Carta getCartaVazia(){
	struct Carta carta = {-1, -1, "a"};
	return carta;
}

int isCartaVazia(struct Carta carta){
	return carta.numero == -1 ? 1 : 0;
}




#include <stdio.h>

void inicializarMao(struct Carta mao[]);
void adicionarCartaMao(struct Carta mao[], struct Carta carta, int pos);
void comprarCarta(struct Carta mao[], struct Baralho *baralho);

void inicializarMao(struct Carta mao[]){
	for(int i = 0; i < 5; i++){
		mao[i] = getCartaVazia();
	}
}

void adicionarCartaMao(struct Carta mao[], struct Carta carta, int pos){
	if(isCartaVazia(mao[pos])){
		mao[pos] = carta;
	}else{
		adicionarCartaMao(mao, carta, pos + 1);
	}
}

void comprarCarta(struct Carta mao[], struct Baralho *baralho){
	struct Carta carta = sacarCarta(baralho);
	adicionarCartaMao(mao, carta, 0);
}
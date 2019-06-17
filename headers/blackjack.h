#include <stdio.h>

void inicializarMao(struct Carta mao[]);
void adicionarCartaMao(struct Carta mao[], struct Carta carta, int pos);
void comprarCarta(struct Carta mao[], struct Baralho *baralho);
int somaValorMao(struct Carta mao[], int valorA);

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

int somaValorMao(struct Carta mao[], int valorA){
	int soma = 0;
	for(int i = 0; i < 5; i++){
		soma += mao[i].numero == 1 ? valorA : getValorCarta(mao[i]);
	}
	return soma;
}
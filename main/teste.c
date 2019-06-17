#include "../headers/baralho.h"
#include "../headers/blackjack.h"
#include <stdio.h>
#include <string.h>

void main(){
	struct Baralho baralho;
	baralho = preencherBaralho(baralho);

	/*
	struct Carta c1 = sacarCarta(&baralho);


	for(int i = 0; i < 52; i++){
		printf("Número da carta %d: %d\n",i, baralho.baralho[i].numero);
		printf("Naipe da carta %d: %d\n",i, baralho.baralho[i].naipe);
		printf("Caminho da carta %d: %s\n",i, baralho.baralho[i].caminhoImagem);
	}
	*/
	

	struct Carta mao[5];
	inicializarMao(mao);

	comprarCarta(mao, &baralho);
	comprarCarta(mao, &baralho);

	int valor1 = somaValorMao(mao, 1);
	int valor2 = somaValorMao(mao, 11);

	for(int i = 0; i < 5; i++){
		printf("Número da carta %d: %d\n",i, mao[i].numero);
		printf("Naipe da carta %d: %d\n",i, mao[i].naipe);
		printf("Caminho da carta %d: %s\n",i, mao[i].caminhoImagem);
	}

	printf("%d\n", valor1);
	printf("%d\n", valor2);

/*	
	
	printf("Número da carta: %d\n", c1.numero);
	printf("Naipe da carta: %d\n", c1.naipe);
	printf("Caminho da carta: %s\n", c1.caminhoImagem);
	
	int pos = descobrirIndiceCarta(c1, &baralho, 0);
	printf("%d \n",pos );
	*/
}
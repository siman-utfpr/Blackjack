#include "../headers/baralho.h"
#include "../headers/blackjack.h"
#include <stdio.h>

int fichas;
int apostaMaxima;
int apostaMinima;
int fichasAtuais;

void definirValores(){
	printf("Quantas fichas serão apostadas? \n");
	scanf("%d", &fichas);
	printf("Qual o valor da aposta mínima? \n");
	scanf("%d", &apostaMinima);
	apostaMinima = (apostaMinima < 1 || apostaMinima > fichas) ? 1 : apostaMinima;
	printf("Qual o valor da aposta máxima? \n");
	scanf("%d", &apostaMaxima);
	apostaMaxima = (apostaMaxima < apostaMinima || apostaMaxima > fichas) ? fichas : apostaMaxima;
}

void imprimirCarta(struct Carta carta){
	if(carta.numero != -1){
		switch(carta.naipe){
			case 0:
				printf("%d de ouros\n",carta.numero);
				break;
			case 1:
				printf("%d de paus\n",carta.numero);
				break;
			case 2:
				printf("%d de copas\n",carta.numero);
				break;
			case 3:
				printf("%d de espadas\n",carta.numero);
				break;									
		}	
	}

}

int avaliarSituacao(struct Carta maoJogador[], struct Carta maoBanqueiro[]){
	/*
		0 - nada
		1 - banqueiro ganhou
		2 - banqueiro estourou
		3 - jogador ganhou
		4 - jogador estourou
	*/
	if(somaValorMao(maoBanqueiro, 11) == 21){
		return 1;
	}else if(somaValorMao(maoBanqueiro, 11) > 21){
		return 2;
	}else if(somaValorMao(maoJogador, 11) == 21){
		return 3;
	}else if(somaValorMao(maoJogador, 11) > 21){
		return 4;
	}else{
		return 0;
	}
}

void menuOpcoes(){
	printf("1 - Comprar mais uma carta \n2 - Encerrar \n");
}

void rodada(){
	struct Baralho baralho;
	baralho = preencherBaralho(baralho);
	printf("Quantas fichas serão apostadas nessa rodada? \n");
	scanf("%d", &fichasAtuais);
	fichasAtuais = (fichasAtuais < apostaMinima || fichasAtuais > apostaMaxima) ? apostaMinima : fichasAtuais;
	struct Carta maoJogador[5];
	struct Carta maoBanqueiro[5];
	inicializarMao(maoJogador);
	inicializarMao(maoBanqueiro);

	comprarCarta(maoBanqueiro, &baralho);
	comprarCarta(maoBanqueiro, &baralho);
	if(avaliarSituacao(maoJogador, maoBanqueiro) == 1){
		printf("Vitória do banqueiro: \n");
		imprimirCarta(maoBanqueiro[0]);
		imprimirCarta(maoBanqueiro[1]);
	} else {
		comprarCarta(maoJogador, &baralho);
		comprarCarta(maoJogador, &baralho);
		int op = 0;	
		while(maoCheia(maoJogador) != 1 && op != 2){
			
			printf("Mão atual: \n");
			for(int i = 0; i < 5; i++){
				imprimirCarta(maoJogador[i]);
			}
			menuOpcoes();
			scanf("%d", &op);
			if(op == 1){
				comprarCarta(maoJogador, &baralho);
			}
		}
	}
}

void main(){
	definirValores();
	rodada();
}


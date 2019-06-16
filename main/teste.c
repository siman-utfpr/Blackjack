#include "../headers/baralho.h"
#include <stdio.h>
#include <string.h>

void main(){

	struct Baralho baralho;
	baralho = preencherBaralho(baralho);

	struct Carta c1 = sacarCarta(&baralho);


	for(int i = 0; i < 52; i++){
		printf("Número da carta %d: %d\n",i, baralho.baralho[i].numero);
		printf("Naipe da carta %d: %d\n",i, baralho.baralho[i].naipe);
		printf("Caminho da carta %d: %s\n",i, baralho.baralho[i].caminhoImagem);
	}
	



/*	
	
	printf("Número da carta: %d\n", c1.numero);
	printf("Naipe da carta: %d\n", c1.naipe);
	printf("Caminho da carta: %s\n", c1.caminhoImagem);
	
	int pos = descobrirIndiceCarta(c1, &baralho, 0);
	printf("%d \n",pos );
	*/
	
	

	/*


	char aux[20];

	strcpy(aux, "13espadas.png");

	struct Carta c1;



	struct Baralho b1;
	strcpy(b1.baralho[0].caminhoImagem, aux);

	printf("%s\n", b1.baralho[0].caminhoImagem);
	*/
	


}
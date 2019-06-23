void inicializarMao(struct Carta mao[]);
void adicionarCartaMao(struct Carta mao[], struct Carta carta, int pos);
void comprarCarta(struct Carta mao[], struct Baralho *baralho);
int somaValorMao(struct Carta mao[], int valorA);
int jogadorGanhou(struct Carta maoBanqueiro[], int somaJogador);
int jogadorEstourou(int soma);

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

int banqueiroDeveComprar(struct Carta maoBanqueiro[], int pontuacaoJogador){
	int soma = somaValorMao(maoBanqueiro, 11) > 21 ?  somaValorMao(maoBanqueiro, 1) : somaValorMao(maoBanqueiro, 11);
	if(soma < 17 && soma < pontuacaoJogador){
		return 1;
	}else {
		return 0;
	}
}

int jogadorGanhou(struct Carta maoBanqueiro[], int somaJogador){
	int somaBanqueiro = somaValorMao(maoBanqueiro, 11) > 21 ?  somaValorMao(maoBanqueiro, 1) : somaValorMao(maoBanqueiro, 11);
	if(somaJogador > 21){
		return 0;
	} else if(somaBanqueiro == 21){
		return 0;
	}else if(somaBanqueiro > 21){
		return 1;
	}else if(somaJogador == somaBanqueiro){
		return 0;
	} else if(somaJogador < somaBanqueiro){
		return 0;
	}
}

int jogadorEstourou(int soma){
	if(soma > 21){
		return 1;
	} else {
		return 0;
	}
}
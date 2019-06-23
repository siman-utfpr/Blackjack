#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>	
#include "../headers/baralho.h"
#include "../headers/blackjack.h"

// gcc -o jogo jogo.c `pkg-config --cflags --libs gtk+-3.0`

// PROTÓTIPOS

// Cria a janela do jogo
void inicializarJanelaJogo();

// Cria a janela de definição dos valores de aposta
void inicializarJanelaAposta();

// Verifica se o valor da aposta atual é válido e corrige se necessário
// Inicializa todas as mãos com cartas vazias
// Cria um novo baralho
// O banqueiro compra suas cartas iniciais
// Inicia a verificação da mão do banqueiro
void iniciarRodada();

// Esconde os botões de ação do jogador
// Verifica quem é o vencedor
// Altera o número de fichas dos jogadores
// Descobre se o jogo acabou
void finalizarRodada();

// Limpa todas as imagens de carta
// Esconde os botões de ação do usuário
// Esconde a label de resulta e o botão de continuar
// Esvazia as labels de pontuação 
// Atualiza as labels de fichas dos jogadores
void resetar();

// O jogador compra as cartas iniciais
// Mostra os botões de ação do jogador
// Descobre a pontuação atual do jogador
// Encerra a rodada, caso o jogador tenha conseguido um 21
void inicializarJogador();

// Preenche a label de pontuação cujo ponteiro foi passado, mostrando 2 possíveis valores caso o jogador/banqueiro 
// tenha um ás e o valor alto do ás não faça com que a mão estoure 
void preencherLabelPontuacao(GtkWidget *label, int p1, int p2);

// Define a pontuação 1 e 2 (ás alto e ás baixo) do jogador/banqueiro
void calcularPontuacoesJogador(struct Carta mao[], int *p1, int *p2, int *pontuacaoJogador);

// Define o total de fichas e a aposta máxima / mínima
// Fecha a janela de aposta e abre a de jogo
void iniciarJogo(GtkWidget *button, gpointer data);

// Ações do jogador

// Esconde o botão de dividir
// Adiciona uma carta à mão ativa, atualiza a imagem da carta, a pontuação e as labels de pontuação
// Caso o jogador tenha estourado, força o fim da rodada
// Caso o jogador tenha 5 cartas, força a ação de permanecer
// Caso o jogador estoure a mão 1 e possua uma mão 2, ativa a segunda e muda o texto 'Trocar mão' para 'Permanecer'
// Caso o jogador possua duas mãos e estoure a segunda, força a ação de permanecer
// Caso o jogador possua duas mãos e estoure ambas, força o fim da rodada
void acaoComprar(GtkWidget* widget, gpointer data);

// Esconde os botões de dividir e dobrar
// Mostra a label de pontuação da mão 2
// Joga a segunda carta da mão 1 para a mão 2
// Atualiza as imagens de carta e as labels de pontuação
void acaoDividir(GtkWidget* widget, gpointer data);

// Dobra o valor da aposta atual (considerando o número de fichas do jogador como limite)
// Chama a ação de comprar uma carta
// Caso o jogador estoure, finaliza a rodada
// Senão, chama a ação de permanecer
void acaoDobrar(GtkWidget* widget, gpointer data);

// Caso a mão 1 esteja ativa e exista uma mão 2, define a mão 2 como ativa
// Esconde os botões de ação do jogador
// Vira a segunda carta do banqueiro
// Redefine a pontuação do banqueiro e sua label
// Inicia as ações do banqueiro
void acaoPermanecer(GtkWidget* widget, gpointer data);


// Fecha a janela do jogo, encerrando o programa
void fim(GtkWidget* widget, gpointer data);

//	Define se a mão 1 ou a mão 2 do jogador será usada para decidir a rodada
int escolherMaoComparacao();

// Caso a carta virada para cima do banqueiro seja um ás, vira a outra carta
// Caso o banqueiro consiga um 21, ganha o dobre do valor da aposta e a rodada é encerrada
// Caso o banqueiro não tenha um ás virado para cima ou não consiga um 21, inicializa o jogador
gboolean verificaMaoBanqueiro();

// Atualiza a pontuação do banqueiro e sua label
// Enquanto o banqueiro não tiver 5 cartas ou não tenha atingido sua condição de parada de compra,
// compra uma carta e atualiza as imagens de carta, além da pontuação e sua label
// Finaliza a rodada
gboolean acaoBanqueiro();

// VARIÁVEIS GLOBAIS

// Dimensões para as imagens de carta
int larguraCarta = 95;
int alturaCarta = 115;

// Valores de aposta
int totalFichas;
int apostaMaxima;
int apostaMinima;
int fichasJogador;
int fichasBanqueiro;
int apostaAtual;

// Qual mão está sendo alterada (em caso de split)
int maoAtiva = 1;

// A ação dobrar aconteceu na rodada atual
int dobrado = 0;

// Quantas cartas possui cada mão
int tamanhoMao1 = 0;
int tamanhoMao2 = 0;
int tamanhoMaoBanqueiro = 0;

// Pontuação com ás alto / pontuação com ás baixo / pontuação VÁLIDA mais alta
int pontuacao1Jogador;
int pontuacao2Jogador;
int pontuacaoJogador;
int pontuacao1JogadorMao2;
int pontuacao2JogadorMao2;
int pontuacaoJogadorMao2;
int pontuacao1Banqueiro;
int pontuacao2Banqueiro;
int pontuacaoBanqueiro;

// Janelas
GtkWidget *janelaAposta;
GtkWidget *janelaJogo;

// Caixas de texto da janela de aposta
GtkWidget *textBoxTotalFichas;
GtkWidget *textBoxApostaMaxima;
GtkWidget *textBoxApostaMinima;

// Caixa de texto com o valor da aposta de cada rodada
GtkWidget *formApostaAtual;

// Label com o número de fichas de cada jogador
GtkWidget *labelFichasBanqueiro;
GtkWidget *labelFichasJogador;

// Estruturas pixbuf com a descrição de cada imagem de carta das mãos dos jogadores
GdkPixbuf *pixbufMaoBanqueiro[5];
GdkPixbuf *pixbufMao1Jogador[5];
GdkPixbuf *pixbufMao2Jogador[5];

// Estruturas pixbuf com a descrição da imagem de carta virada
GdkPixbuf *pixbufCartaVirada;

// Vetores com as cartas de cada mão de cada um dos jogadores
GtkWidget *imagensMaoBanqueiro[5];
GtkWidget *imagensMao1Jogador[5];
GtkWidget *imagensMao2Jogador[5];

// Vitória, derrota ou fim de jogo
GtkWidget *labelResultado;

// Próxima rodada
GtkWidget *botaoContinuar;

// Botões de ação do jogador
GtkWidget *botaoComprar;
GtkWidget *botaoPermanecer;
GtkWidget *botaoDividir;
GtkWidget *botaoDobrar;

// Encerrar o programa
GtkWidget *botaoFIM;

// Pontuações dos jogadores
GtkWidget *labelPontuacaoJogador;
GtkWidget *labelPontuacaoJogadorMao2;
GtkWidget *labelPontuacaoBanqueiro;

// Legenda da label da pontuação da mão 2 do jogador (é global pq precisa ser escondida por várias funções)
GtkWidget *labelLegendaPontuacaoJogadorMao2;

// Baralho - reiniciado a cada rodada
struct Baralho baralho;

// Mãos - iniciam vazias em cada rodada e são preenchidas conforme o fluxo do jogo
struct Carta maoBanqueiro[5];
struct Carta mao1Jogador[5];
struct Carta mao2Jogador[5];

int main(int argc, char **argv){
	pixbufCartaVirada = gdk_pixbuf_new_from_file("../recursos/baralho/cartavirada.jpg",NULL);
	pixbufCartaVirada = gdk_pixbuf_scale_simple(pixbufCartaVirada,larguraCarta, alturaCarta,GDK_INTERP_BILINEAR);

	gtk_init(&argc, &argv);
	inicializarJanelaAposta();
	gtk_main();
	return 0;
}

void inicializarJanelaAposta(){
	
	GtkWidget *labelTotal;
	GtkWidget *labelMaximo;
	GtkWidget *labelMinimo;
	GtkWidget *conteudo;
	GtkWidget *botao;

	janelaAposta = gtk_window_new(GTK_WINDOW_TOPLEVEL);	
	gtk_window_set_position(GTK_WINDOW(janelaAposta), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW(janelaAposta), FALSE);
	gtk_window_set_default_size(GTK_WINDOW(janelaAposta), 550, 400);

	conteudo = gtk_grid_new();
	gtk_widget_set_halign (conteudo, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (conteudo, GTK_ALIGN_CENTER);

	labelTotal = gtk_label_new("Total de fichas do jogador: ");
	textBoxTotalFichas = gtk_entry_new();
	labelMaximo = gtk_label_new("Aposta máxima: ");
	textBoxApostaMaxima = gtk_entry_new();
	labelMinimo = gtk_label_new("Aposta mínima: ");
	textBoxApostaMinima = gtk_entry_new();

	botao = gtk_button_new_with_label("Iniciar");

	gtk_container_add(GTK_CONTAINER(janelaAposta), conteudo);
	gtk_grid_attach(GTK_GRID(conteudo), labelTotal, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(conteudo), textBoxTotalFichas, 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(conteudo), labelMaximo, 0, 1, 1, 1);	
	gtk_grid_attach(GTK_GRID(conteudo), textBoxApostaMaxima, 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(conteudo), labelMinimo, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(conteudo), textBoxApostaMinima, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(conteudo), botao, 1, 4, 1, 1);

	gtk_grid_set_row_spacing (GTK_GRID(conteudo), 20);
	gtk_grid_set_column_spacing (GTK_GRID(conteudo), 20);

	g_signal_connect(G_OBJECT(janelaAposta), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(botao), "clicked", G_CALLBACK(iniciarJogo), NULL);

	gtk_widget_show_all(janelaAposta);
}

void inicializarJanelaJogo(){

	janelaJogo = gtk_window_new(GTK_WINDOW_TOPLEVEL);	
	gtk_window_maximize(GTK_WINDOW(janelaJogo));

	GtkWidget *conteudo;
	conteudo = gtk_grid_new();
	gtk_grid_set_row_homogeneous(GTK_GRID(conteudo),TRUE);
	gtk_widget_set_margin_end(conteudo, 50);
	gtk_widget_set_margin_start(conteudo, 50);

	GtkWidget *topo;
	GtkWidget *meio;
	GtkWidget *baixo;
	topo = gtk_grid_new();
	meio = gtk_grid_new();
	baixo = gtk_grid_new();

	GtkWidget *areaAposta;
	GtkWidget *formAposta;
	GtkWidget *labelLegendaApostaMaxima;
	GtkWidget *labelLegendaApostaMinima;
	GtkWidget *labelLegendaApostaAtual;
	GtkWidget *labelApostaMaxima;
	GtkWidget *labelApostaMinima;
	formAposta = gtk_grid_new();
	areaAposta = gtk_grid_new();
	formApostaAtual = gtk_entry_new();
	labelLegendaApostaMinima = gtk_label_new("Aposta mínima: ");
	labelLegendaApostaMaxima = gtk_label_new("Aposta máxima: ");
	labelLegendaApostaAtual = gtk_label_new("Aposta atual: ");
	char textoApostaMax[128];
	sprintf(textoApostaMax, "%d", apostaMaxima);
	labelApostaMaxima = gtk_label_new(textoApostaMax);
	char textoApostaMin[128];
	sprintf(textoApostaMin, " %d", apostaMinima);
	labelApostaMinima = gtk_label_new(textoApostaMin);
	char textoApostaAtual[128];
	sprintf(textoApostaAtual, "%d", apostaMinima);
	gtk_entry_set_text(GTK_ENTRY(formApostaAtual), textoApostaAtual);
	char textJogador[128];
	char textBanqueiro[128];
	sprintf(textJogador, "Suas fichas: %d", fichasJogador);
	sprintf(textBanqueiro, "Fichas do oponente: %d", fichasBanqueiro);
	labelFichasJogador = gtk_label_new(textJogador);
	labelFichasBanqueiro = gtk_label_new(textBanqueiro);

	GtkWidget *areaPontuacoes;
	GtkWidget *labelLegendaPontuacaoJogador;
	GtkWidget *labelLegendaPontuacaoBanqueiro;
	areaPontuacoes = gtk_grid_new();
	labelLegendaPontuacaoBanqueiro = gtk_label_new("Pontuação do banqueiro: ");
	labelLegendaPontuacaoJogador = gtk_label_new("Pontuação do jogador: ");
	labelLegendaPontuacaoJogadorMao2 = gtk_label_new("Pontuação do jogador (Mão 2): ");
	labelPontuacaoBanqueiro = gtk_label_new("");
	labelPontuacaoJogador = gtk_label_new("");
	labelPontuacaoJogadorMao2 = gtk_label_new("");

	GtkWidget *areaBanqueiro;
	GtkWidget *areaCartasJogador;
	GtkWidget *area1Jogador;
	GtkWidget *area2Jogador;
	GtkWidget *areaAcoes;
	areaBanqueiro = gtk_grid_new();
	areaCartasJogador = gtk_grid_new();
	area1Jogador = gtk_grid_new();
	area2Jogador = gtk_grid_new();
	areaAcoes = gtk_grid_new();	
	for(int i = 0; i < 5; i++){
		imagensMaoBanqueiro[i] = gtk_image_new_from_pixbuf(pixbufCartaVirada);
		gtk_image_clear(GTK_IMAGE(imagensMaoBanqueiro[i]));
		imagensMao1Jogador[i] = gtk_image_new_from_pixbuf(pixbufCartaVirada);
		gtk_image_clear(GTK_IMAGE(imagensMao1Jogador[i]));
		imagensMao2Jogador[i] = gtk_image_new_from_pixbuf(pixbufCartaVirada);
		gtk_image_clear(GTK_IMAGE(imagensMao2Jogador[i]));
	}
	gtk_widget_set_hexpand(areaBanqueiro, TRUE);
	gtk_widget_set_halign(areaBanqueiro,  GTK_ALIGN_CENTER);
	gtk_widget_set_hexpand(areaCartasJogador, TRUE);
	gtk_widget_set_halign(areaCartasJogador,  GTK_ALIGN_CENTER);

	labelResultado = gtk_label_new("");
	botaoContinuar = gtk_button_new_with_label("Continuar");
	botaoFIM = gtk_button_new_with_label("Ok");
	gtk_widget_set_hexpand(labelResultado, TRUE);
	gtk_widget_set_hexpand(botaoContinuar, TRUE);

	botaoComprar = gtk_button_new_with_label("Comprar");
	botaoPermanecer = gtk_button_new_with_label("Permanecer");
	botaoDobrar = gtk_button_new_with_label("Dobrar");
	botaoDividir = gtk_button_new_with_label("Dividir");

	gtk_container_add(GTK_CONTAINER(janelaJogo), conteudo);
	gtk_grid_attach(GTK_GRID(conteudo), topo, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(conteudo), meio, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(conteudo), baixo, 0, 2, 1, 1);

	gtk_grid_attach(GTK_GRID(topo), formAposta, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(topo), areaBanqueiro, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(topo), areaAposta, 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(meio), labelResultado, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(meio), botaoContinuar, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(meio), botaoFIM, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(baixo), areaPontuacoes, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(baixo), areaCartasJogador, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(baixo), areaAcoes, 2, 0, 1, 1);

	gtk_grid_attach(GTK_GRID(formAposta), labelLegendaApostaMaxima, 0, 0 , 1, 1);
	gtk_grid_attach(GTK_GRID(formAposta), labelApostaMaxima, 1, 0 , 1, 1);
	gtk_grid_attach(GTK_GRID(formAposta), labelLegendaApostaMinima, 0, 1 , 1, 1);
	gtk_grid_attach(GTK_GRID(formAposta), labelApostaMinima, 1, 1 , 1, 1);
	gtk_grid_attach(GTK_GRID(formAposta), labelLegendaApostaAtual, 0, 2 , 1, 1);
	gtk_grid_attach(GTK_GRID(formAposta), formApostaAtual, 1, 2 , 1, 1);
	for(int i =0; i < 5; i++){
		gtk_grid_attach(GTK_GRID(areaBanqueiro), imagensMaoBanqueiro[i], i, 0 , 1, 1);
	}
	gtk_grid_attach(GTK_GRID(areaAposta), labelFichasJogador, 0, 0 , 1, 1);
	gtk_grid_attach(GTK_GRID(areaAposta), labelFichasBanqueiro, 0, 1 , 1, 1);
	gtk_grid_attach(GTK_GRID(areaPontuacoes), labelLegendaPontuacaoJogador, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(areaPontuacoes), labelLegendaPontuacaoJogadorMao2, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(areaPontuacoes), labelLegendaPontuacaoBanqueiro, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(areaPontuacoes), labelPontuacaoJogador, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(areaPontuacoes), labelPontuacaoJogadorMao2, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(areaPontuacoes), labelPontuacaoBanqueiro, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(areaCartasJogador), area1Jogador, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(areaCartasJogador), area2Jogador, 0, 1, 1, 1);	
	gtk_grid_attach(GTK_GRID(areaAcoes), botaoComprar, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(areaAcoes), botaoPermanecer, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(areaAcoes), botaoDobrar, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(areaAcoes), botaoDividir, 0, 3, 1, 1);

	for(int i =0; i < 5; i++){
		gtk_grid_attach(GTK_GRID(area1Jogador), imagensMao1Jogador[i], i, 0 , 1, 1);
	}
	for(int i =0; i < 5; i++){
		gtk_grid_attach(GTK_GRID(area2Jogador), imagensMao2Jogador[i], i, 0 , 1, 1);
	}

	g_signal_connect(G_OBJECT(janelaJogo), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(formApostaAtual), "activate", G_CALLBACK(iniciarRodada), NULL);
	g_signal_connect(G_OBJECT(botaoComprar), "clicked", G_CALLBACK(acaoComprar), NULL);
	g_signal_connect(G_OBJECT(botaoDividir), "clicked", G_CALLBACK(acaoDividir), NULL);
	g_signal_connect(G_OBJECT(botaoPermanecer), "clicked", G_CALLBACK(acaoPermanecer), NULL);
	g_signal_connect(G_OBJECT(botaoDobrar), "clicked", G_CALLBACK(acaoDobrar), NULL);
	g_signal_connect(G_OBJECT(botaoContinuar), "clicked", G_CALLBACK(resetar), NULL);
	g_signal_connect(G_OBJECT(botaoFIM), "clicked", G_CALLBACK(fim), NULL);
	
	gtk_widget_show_all(janelaJogo);
	gtk_widget_set_visible(botaoContinuar, FALSE);
	gtk_widget_set_visible(botaoFIM, FALSE);
	gtk_widget_set_visible(botaoComprar, FALSE);
	gtk_widget_set_visible(botaoPermanecer, FALSE);
	gtk_widget_set_visible(botaoDobrar, FALSE);
	gtk_widget_set_visible(botaoDividir, FALSE);

	gtk_widget_set_visible(labelLegendaPontuacaoJogadorMao2, FALSE);
}

void iniciarJogo(GtkWidget *button, gpointer data){
	totalFichas = atol(gtk_entry_get_text(GTK_ENTRY(textBoxTotalFichas)));
	apostaMaxima = atol(gtk_entry_get_text(GTK_ENTRY(textBoxApostaMaxima)));
	apostaMinima = atol(gtk_entry_get_text(GTK_ENTRY(textBoxApostaMinima)));

	totalFichas = (totalFichas <= 0) ? 100 : totalFichas;
	apostaMaxima = (apostaMaxima <= 0 || apostaMaxima > totalFichas) ? totalFichas : apostaMaxima;
	apostaMinima = (apostaMinima <= 0 || apostaMinima > apostaMaxima) ? 1 : apostaMinima;
	fichasBanqueiro = totalFichas;
	fichasJogador = totalFichas;

	gtk_widget_hide(janelaAposta);
	inicializarJanelaJogo();
}

void atualizarImagem(GdkPixbuf *pixbuf, struct Carta carta, GtkWidget *imagem){
	pixbuf = gdk_pixbuf_new_from_file(carta.caminhoImagem, NULL);
	pixbuf = gdk_pixbuf_scale_simple(pixbuf, larguraCarta, alturaCarta, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(imagem), pixbuf);
}

void iniciarRodada(GtkWidget* widget, gpointer data){
	tamanhoMao1 = 0;
	tamanhoMao2 = 0;
	tamanhoMaoBanqueiro = 0;
	dobrado = 0;
	maoAtiva = 1;
	apostaAtual = atol(gtk_entry_get_text(GTK_ENTRY(formApostaAtual)));
	// A aposta atual não pode ser maior do que a aposta máxima, menor do que a aposta mínima ou maior que o total de fichas do jogador
	apostaAtual = apostaAtual > fichasJogador ? fichasJogador : apostaAtual;
	apostaAtual = (apostaAtual > apostaMaxima) ? apostaMaxima : (apostaAtual < apostaMinima) ? apostaMinima : apostaAtual;
	char textoApostaAtual[128];
	sprintf(textoApostaAtual, "%d", apostaAtual);
	gtk_entry_set_text(GTK_ENTRY(formApostaAtual), textoApostaAtual);
	gtk_widget_set_sensitive(formApostaAtual, FALSE);

	baralho = preencherBaralho();
	inicializarMao(maoBanqueiro);
	inicializarMao(mao1Jogador);
	inicializarMao(mao2Jogador);

	comprarCarta(maoBanqueiro, &baralho);
	comprarCarta(maoBanqueiro, &baralho);

	tamanhoMaoBanqueiro += 2;

	atualizarImagem(pixbufMaoBanqueiro[0], maoBanqueiro[0], imagensMaoBanqueiro[0]);
	gtk_image_set_from_pixbuf(GTK_IMAGE(imagensMaoBanqueiro[1]), pixbufCartaVirada);
	g_timeout_add_seconds(2, verificaMaoBanqueiro, NULL);
}

gboolean verificaMaoBanqueiro(){
	if(maoBanqueiro[0].numero == 1){
		atualizarImagem(pixbufMaoBanqueiro[1], maoBanqueiro[1], imagensMaoBanqueiro[1]);
		calcularPontuacoesJogador(maoBanqueiro, &pontuacao1Banqueiro, &pontuacao2Banqueiro, &pontuacaoBanqueiro);
		preencherLabelPontuacao(labelPontuacaoBanqueiro, pontuacao1Banqueiro, pontuacao2Banqueiro);
		if(somaValorMao(maoBanqueiro, 11) == 21){
			apostaAtual = (apostaAtual * 2 > fichasJogador) ? fichasJogador : apostaAtual * 2;
			finalizarRodada();
		}else {
			inicializarJogador();
		}
		return FALSE;
	} else {
		inicializarJogador();
		return FALSE;
	}
}

void acaoComprar(GtkWidget* widget, gpointer data){
	gtk_widget_set_visible(botaoDividir, FALSE);
	if(maoAtiva == 1){
		comprarCarta(mao1Jogador, &baralho);
		atualizarImagem(pixbufMao1Jogador[tamanhoMao1], mao1Jogador[tamanhoMao1], imagensMao1Jogador[tamanhoMao1]);
		calcularPontuacoesJogador(mao1Jogador, &pontuacao1Jogador, &pontuacao2Jogador, &pontuacaoJogador);
		preencherLabelPontuacao(labelPontuacaoJogador, pontuacao1Jogador, pontuacao2Jogador);
		if(jogadorEstourou(pontuacaoJogador)){
			if(mao2Jogador[0].numero != -1){
				maoAtiva = 2;
				gtk_button_set_label(GTK_BUTTON(botaoPermanecer), "Permanecer");
			} else {
				finalizarRodada();
			}
		} else {
			tamanhoMao1++;
			if(tamanhoMao1 == 5 || pontuacaoJogador == 21 || dobrado == 1){
				acaoPermanecer(NULL, NULL);
			}
		}

	}else {
		comprarCarta(mao2Jogador, &baralho);
		atualizarImagem(pixbufMao2Jogador[tamanhoMao2], mao2Jogador[tamanhoMao2], imagensMao2Jogador[tamanhoMao2]);
		calcularPontuacoesJogador(mao2Jogador, &pontuacao1JogadorMao2, &pontuacao2JogadorMao2, &pontuacaoJogadorMao2);
		preencherLabelPontuacao(labelPontuacaoJogadorMao2, pontuacao1JogadorMao2, pontuacao2JogadorMao2);
		if(jogadorEstourou(pontuacaoJogadorMao2)){
			if(jogadorEstourou(pontuacaoJogador)){
				finalizarRodada();
			}else {
				acaoPermanecer(NULL, NULL);
			}
		} else{
			tamanhoMao2++;
			if(tamanhoMao2 == 5 || pontuacaoJogadorMao2 == 21){
				acaoPermanecer(NULL, NULL);
			}
		}
	}
}

void acaoDividir(GtkWidget* widget, gpointer data){
	tamanhoMao1 = 1;
	tamanhoMao2 = 1;
	gtk_widget_set_visible(botaoDividir, FALSE);
	gtk_widget_set_visible(botaoDobrar, FALSE);
	gtk_widget_set_visible(labelLegendaPontuacaoJogadorMao2, TRUE);
	mao2Jogador[0] = mao1Jogador[1];
	mao1Jogador[1] = getCartaVazia();
	gtk_image_clear(GTK_IMAGE(imagensMao1Jogador[1]));
	atualizarImagem(pixbufMao2Jogador[0], mao2Jogador[0], imagensMao2Jogador[0]);
	gtk_button_set_label(GTK_BUTTON(botaoPermanecer), "Trocar mão");
	calcularPontuacoesJogador(mao1Jogador, &pontuacao1Jogador, &pontuacao2Jogador, &pontuacaoJogador);
	preencherLabelPontuacao(labelPontuacaoJogador, pontuacao1Jogador, pontuacao2Jogador);
	calcularPontuacoesJogador(mao2Jogador, &pontuacao1JogadorMao2, &pontuacao2JogadorMao2, &pontuacaoJogadorMao2);
	preencherLabelPontuacao(labelPontuacaoJogadorMao2, pontuacao1JogadorMao2, pontuacao2JogadorMao2);
}

void acaoDobrar(GtkWidget* widget, gpointer data){
	dobrado = 1;
	apostaAtual = ((apostaAtual * 2) > fichasJogador) ? fichasJogador : apostaAtual * 2;
	gtk_widget_set_visible(botaoComprar, FALSE);
	gtk_widget_set_visible(botaoPermanecer, FALSE);
	gtk_widget_set_visible(botaoDobrar, FALSE);
	gtk_widget_set_visible(botaoDividir, FALSE);
	acaoComprar(NULL, NULL);
}

void acaoPermanecer(GtkWidget* widget, gpointer data){
	if(maoAtiva == 1 && mao2Jogador[0].numero != -1){
		maoAtiva = 2;
		gtk_button_set_label(GTK_BUTTON(botaoPermanecer), "Permanecer");
	} else {
		gtk_widget_set_visible(botaoComprar, FALSE);
		gtk_widget_set_visible(botaoPermanecer, FALSE);
		gtk_widget_set_visible(botaoDobrar, FALSE);
		gtk_widget_set_visible(botaoDividir, FALSE);
		atualizarImagem(pixbufMaoBanqueiro[1], maoBanqueiro[1], imagensMaoBanqueiro[1]);
		calcularPontuacoesJogador(maoBanqueiro, &pontuacao1Banqueiro, &pontuacao2Banqueiro, &pontuacaoBanqueiro);
		preencherLabelPontuacao(labelPontuacaoBanqueiro, pontuacao1Banqueiro, pontuacao2Banqueiro);
		g_timeout_add_seconds(2, acaoBanqueiro, NULL);
	}
}

gboolean acaoBanqueiro(){
	calcularPontuacoesJogador(maoBanqueiro, &pontuacao1Banqueiro, &pontuacao2Banqueiro, &pontuacaoBanqueiro);
	preencherLabelPontuacao(labelPontuacaoBanqueiro, pontuacao1Banqueiro, pontuacao2Banqueiro);
	if(tamanhoMaoBanqueiro < 5){
		if(banqueiroDeveComprar(maoBanqueiro, pontuacaoJogador)){
			comprarCarta(maoBanqueiro, &baralho);
			atualizarImagem(pixbufMaoBanqueiro[tamanhoMaoBanqueiro], maoBanqueiro[tamanhoMaoBanqueiro], imagensMaoBanqueiro[tamanhoMaoBanqueiro]);
			tamanhoMaoBanqueiro++;
			calcularPontuacoesJogador(maoBanqueiro, &pontuacao1Banqueiro, &pontuacao2Banqueiro, &pontuacaoBanqueiro);
			preencherLabelPontuacao(labelPontuacaoBanqueiro, pontuacao1Banqueiro, pontuacao2Banqueiro);
			return TRUE;
		} else {
			finalizarRodada();
			return FALSE;
		}		
	} else {
		finalizarRodada();
		return FALSE;
	}
}

void finalizarRodada(){
	gtk_widget_set_visible(botaoComprar, FALSE);
	gtk_widget_set_visible(botaoPermanecer, FALSE);
	gtk_widget_set_visible(botaoDobrar, FALSE);
	gtk_widget_set_visible(botaoDividir, FALSE);
	int pont = escolherMaoComparacao();
	if(jogadorGanhou(maoBanqueiro, pont)){
		fichasJogador += apostaAtual;
		fichasBanqueiro -= apostaAtual;
		if(fichasBanqueiro <= 0){
			gtk_label_set_text(GTK_LABEL(labelResultado), "FIM DE JOGO! VOCÊ GANHOU");
			gtk_widget_set_visible(botaoFIM, TRUE);
			gtk_widget_grab_focus(botaoFIM);
		}else {
			gtk_label_set_text(GTK_LABEL(labelResultado), "VITÓRIA!");
			gtk_widget_set_visible(botaoContinuar, TRUE);
			gtk_widget_grab_focus(botaoContinuar);
		}
		gtk_widget_show(labelResultado);
	} else {
		fichasJogador -= apostaAtual;
		fichasBanqueiro += apostaAtual;	
		if(fichasJogador <= 0){
			gtk_label_set_text(GTK_LABEL(labelResultado), "FIM DE JOGO! VOCÊ PERDEU");
			gtk_widget_set_visible(botaoFIM, TRUE);
			gtk_widget_grab_focus(botaoFIM);
		}else {
			gtk_label_set_text(GTK_LABEL(labelResultado), "DERROTA!");
			gtk_widget_set_visible(botaoContinuar, TRUE);
			gtk_widget_grab_focus(botaoContinuar);
		}
		gtk_widget_show(labelResultado);
	}
}

void resetar(){
	for(int i = 0; i < 5; i++){
		gtk_image_clear(GTK_IMAGE(imagensMaoBanqueiro[i]));
		gtk_image_clear(GTK_IMAGE(imagensMao1Jogador[i]));
		gtk_image_clear(GTK_IMAGE(imagensMao2Jogador[i]));
	}
	gtk_widget_set_visible(botaoComprar, FALSE);
	gtk_widget_set_visible(botaoPermanecer, FALSE);
	gtk_widget_set_visible(botaoDobrar, FALSE);
	gtk_widget_set_visible(botaoDividir, FALSE);
	gtk_widget_set_visible(botaoContinuar, FALSE);
	gtk_widget_set_visible(labelResultado, FALSE);
	gtk_label_set_text(GTK_LABEL(labelPontuacaoJogador), "");
	gtk_label_set_text(GTK_LABEL(labelPontuacaoJogadorMao2), "");
	gtk_widget_set_visible(labelLegendaPontuacaoJogadorMao2, FALSE);
	gtk_label_set_text(GTK_LABEL(labelPontuacaoBanqueiro), "");
	gtk_widget_set_sensitive(formApostaAtual, TRUE);
	gtk_widget_grab_focus(formApostaAtual);
	char textJogador[128];
	char textBanqueiro[128];
	sprintf(textJogador, "Suas fichas: %d", fichasJogador);
	sprintf(textBanqueiro, "Fichas do oponente: %d", fichasBanqueiro);
	gtk_label_set_text(GTK_LABEL(labelFichasJogador), textJogador);
	gtk_label_set_text(GTK_LABEL(labelFichasBanqueiro), textBanqueiro);
}

void inicializarJogador(){
	comprarCarta(mao1Jogador, &baralho);
	comprarCarta(mao1Jogador, &baralho);
	tamanhoMao1 += 2;
	pontuacao1Jogador = somaValorMao(mao1Jogador, 11);
	pontuacao2Jogador = somaValorMao(mao1Jogador, 1);
	pontuacaoJogador = (pontuacao1Jogador <= 21 && pontuacao1Jogador > pontuacao2Jogador) ? pontuacao1Jogador : pontuacao2Jogador;
	atualizarImagem(pixbufMao1Jogador[0], mao1Jogador[0], imagensMao1Jogador[0]);
	atualizarImagem(pixbufMao1Jogador[1], mao1Jogador[1], imagensMao1Jogador[1]);
	gtk_widget_set_visible(botaoComprar, TRUE);
	gtk_widget_set_visible(botaoPermanecer, TRUE);
	gtk_widget_set_visible(botaoDividir, (mao1Jogador[0].numero == mao1Jogador[1].numero) && tamanhoMao1 == 2);
	gtk_widget_set_visible(botaoDobrar, TRUE);
	calcularPontuacoesJogador(mao1Jogador, &pontuacao1Jogador, &pontuacao2Jogador, &pontuacaoJogador);
	preencherLabelPontuacao(labelPontuacaoJogador, pontuacao1Jogador, pontuacao2Jogador);
	if(somaValorMao(mao1Jogador, 11) == 21){
		apostaAtual = (apostaAtual * 2 > fichasBanqueiro) ? fichasBanqueiro : apostaAtual * 2;
		// Evitar que o banqueiro ganhe em uma situação em que o jogador consegue um blackjack e o banqueiro possui um oculto
		pontuacaoBanqueiro = 0;
		finalizarRodada();
	} else {
		gtk_widget_grab_focus(botaoComprar);
	}
}

void preencherLabelPontuacao(GtkWidget *label, int p1, int p2){
	char aux[128];
	if(p2 != p1 && p1 <= 21){
		sprintf(aux, "%d ou %d", p1, p2);
	}else {
		sprintf(aux, "%d", p2);
	}
	gtk_label_set_text(GTK_LABEL(label), aux);
}

void calcularPontuacoesJogador(struct Carta mao[], int *pontuacao1Jogador, int *pontuacao2Jogador, int *pontuacaoJogador){
	*pontuacao1Jogador = somaValorMao(mao, 11);
	*pontuacao2Jogador = somaValorMao(mao, 1);
	*pontuacaoJogador = (*pontuacao1Jogador <= 21 && *pontuacao1Jogador > *pontuacao2Jogador) ? *pontuacao1Jogador : *pontuacao2Jogador;
}

int escolherMaoComparacao(){
	if(pontuacaoJogador <= 21){
		if(pontuacaoJogador > pontuacaoJogadorMao2){
			return pontuacaoJogador;
		}else {
			if(pontuacaoJogadorMao2 <= 21){
				return pontuacaoJogadorMao2;
			} else {
				return pontuacaoJogador;
			}
		}
	} else {
		return pontuacaoJogadorMao2;
	}
}

void fim(GtkWidget* widget, gpointer data){
	gtk_window_close(GTK_WINDOW(janelaJogo));
}
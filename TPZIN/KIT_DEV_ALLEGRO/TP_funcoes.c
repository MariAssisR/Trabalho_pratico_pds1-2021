#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> //escrever
#include <allegro5/allegro_ttf.h> //escrever
#include <allegro5/allegro_primitives.h> //formas
#include <allegro5/allegro_image.h> //imagens
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include"TP_funcoes.h"

//-----------------------Score---------------------------------------
/*void adicionarScore(char nome_arquivo[], int pontos_atual){
	FILE *arq;

	arq = fopen(nome_arquivo,"a"); //adicionar
	if(arq == NULL) {
		printf("\nErro ao abrir o arquivo!");
		return;
	}

	fprintf(arq, "%d,\n", pontos_atual);
	fclose(arq);
}*/    //PARA ADICIONAR SCORE EM ARQUIO COM VARIAS

int descobrirScore(char nome_arquivo[], int pontos_atual){
	char linha[5];	//cria variavel para a linha
	int highscore;
	FILE *arq, *temp;

	arq = fopen(nome_arquivo, "r"); //abrir highscore
	temp = fopen("temp.txt", "w");
	if(arq == NULL) {
		printf("\nErro ao abrir o arquivo!");
		return;
	}

	fgets(linha, 5, arq);
	highscore = atoi(strtok(linha,","));//atoi = string to int
	if(pontos_atual > highscore)//se a nova score e a maior
	{
		highscore = pontos_atual;
	}		
	
	fprintf(temp, "%d,\n", highscore); //escrever no temp a highscore nova
	
	fclose(arq);
	fclose(temp);

	//renomeia o arquivo temporario
	remove(nome_arquivo);
	rename("temp.txt", nome_arquivo);

	return highscore;
}
//--------------------------------------------------------------
float distanciaPonto(float x1, float x2, float y1, float y2){
	return sqrt(pow(x1-x2, 2)+ pow(y1-y2, 2));
}

void initGlobais() {

	//COR_CENARIO = al_map_rgb(20,20,20);
}

//-----------------------Plano fundo---------------------------------------
void desenhaCenario(){
	al_clear_to_color(COR_CENARIO);
}
void initEstrela(Estrela estrela[][NUM_ESTRELAS], int num_plano, int tam_estrelas){
	int i, j;
	for(i = 0; i < num_plano; i++)
	{
		for(j = 0; j < tam_estrelas; j++)
		{
			if(i == 0) //primeiro plano
			{
				estrela[i][j].ID = ESTRELA;
				estrela[i][j].x = 5 + rand() %(SCREEN_W - 10);
				estrela[i][j].y = 5 + rand() %(SCREEN_W - 10);
				estrela[i][j].vel_estrela = 5; //mais rapido
			}
			else if(i == 1) //segundo
			{
				estrela[i][j].ID = ESTRELA;
				estrela[i][j].x = 5 + rand() %(SCREEN_W - 10);
				estrela[i][j].y = 5 + rand() %(SCREEN_W - 10);
				estrela[i][j].vel_estrela = 2;
			}
			else if(i == 2) //terceiro
			{
				estrela[i][j].ID = ESTRELA;
				estrela[i][j].x = 5 + rand() %(SCREEN_W - 10);
				estrela[i][j].y = 5 + rand() %(SCREEN_W - 10);
				estrela[i][j].vel_estrela = 1;
			}
		}
	}
}
void atualizaEstrela(Estrela estrela[][NUM_ESTRELAS], int num_plano, int tam_estrelas){
	int i, j;
	for(i = 0; i < num_plano; i++)
	{
		for(j = 0; j < tam_estrelas; j++)
		{
			estrela[i][j].x -= estrela[i][j].vel_estrela;
			if(estrela[i][j].x < 0)
				estrela[i][j].x = SCREEN_W;
		}
	}
}
void desenhaEstrela(Estrela estrela[][NUM_ESTRELAS], int num_plano, int tam_estrelas){
	int i, j;
	for(i = 0; i < num_plano; i++)
	{
		for(j = 0; j < tam_estrelas; j++)
		{
			al_draw_pixel(estrela[i][j].x, estrela[i][j].y, al_map_rgb(255,255,255) );
		}
	}
}
//-----------------------NAVE---------------------------------------
//inicializar nave
void initNave(Nave *nave) {

	nave->x = 10 + NAVE_W;
	nave->y = SCREEN_H/2;
    nave->dir_x = 0;
    nave->dir_y = 0;
	nave->cor = al_map_rgb(192 + rand()%64, 192 + rand()%64, 192 + rand()%64);
    nave->vel_nave = VELOCIDADE_NAVE;

	nave->pontos = 0;
	nave->pontos_dificuldade = 25;
	nave->modelo = 0;
	nave->power = 0; //1 shield  //2 arma melhor
	nave->tempo_power = 0;

}
//atualizar nave
void atualizaNave(Nave *nave) {

	//colisaoNaveLado(Nave *nave);
    nave->y += nave->dir_y * nave->vel_nave;
    nave->x += nave->dir_x * nave->vel_nave;
}
//-----------------------FLOOR/ bloco2-------------------------------------
void initBase(Base *base){
	base->x = 0; //comeca no 0x, e anda ate -screenw
	base->y = TAM_BASE; //SCREEN_H - 40;
	base->w = 2*SCREEN_W; //tem o comprimento de 2screenw
	base->h = SCREEN_H - (base->y);
	base->cor = al_map_rgb(rand(), rand(), rand()); 
	base->vel_base = VELOCIDADE_BLOCO;
}
void atualizaBase(Base *base){
    
    base->x -= base->vel_base;

    if(base->x + base->w/2 < 0) //ai reinicia, e impressao de movimento
        initBase(base);
}
void desenhaBase(Base base, ALLEGRO_BITMAP *chao) {
	//al_draw_bitmap_region(extras, 224, 736, 96, 32,base.x, base.y, 0 );
	al_draw_bitmap(chao, base.x, base.y, 0 );
}
//-----------------------BLOCO-------------------------------------
//w > screenw
//h > 1/5 screenh
void initBloco(Bloco *bloco) {

	bloco->x = SCREEN_W + rand()%(SCREEN_W); //localizacao bloco
	bloco->y = rand()%(4*SCREEN_H/5);
    bloco->w = SCREEN_W + rand()%(SCREEN_W); //tamanho bloco >>>>>   w > screenw
	bloco->h = 3*SCREEN_H/5 + rand()%(2*SCREEN_H/5) - 2*NAVE_H - 40;// >>>>>   h > 1/5 screenh
    //- a altura da nave e da base para sempre ter espaco pra nave passar
	bloco->cor = al_map_rgb(rand(), rand(), rand());
	bloco->vel_bloco = VELOCIDADE_BLOCO;
}
void atualizaBloco(Bloco *bloco) {
    
    bloco->x -= bloco->vel_bloco;

    if(bloco->x + bloco->w < 0)
        initBloco(bloco);
}
void desenhaBloco(Bloco bloco, ALLEGRO_BITMAP *rocha1) {
    //al_draw_filled_rectangle(bloco.x, bloco.y, bloco.x + bloco.w, bloco.y + bloco.h, bloco.cor);
	al_draw_scaled_bitmap(rocha1, 0,0,512,512, bloco.x, bloco.y, bloco.w, bloco.h, 0);
}

//-----------------------TIRO---------------------------------------
void initTiro(Tiro tiro[], int tamanho) {
	int i;
	for(i = 0; i < tamanho; i++)
	{
		tiro[i].ID = TIRO;
		tiro[i].vel_tiro = 10;
		tiro[i].ativo = 0;
	}
}

void atiraTiro(Tiro tiro[], int tamanho, Nave nave) {
	int i;
	for(i = 0; i < tamanho; i++) 
	{
		if(!tiro[i].ativo)
		{
			tiro[i].x = nave.x + 15; //+15 para o tiro bonitnho sair bonitinho
			if(nave.modelo == 3)
				tiro[i].y = nave.y + 10; // na sd o  tiro sai diferente
			else
				tiro[i].y = nave.y;
			tiro[i].raio = 6;
			tiro[i].ativo = 1;
			break;
		}
	}
}

void atualizaTiro(Tiro tiro[], int tamanho) {
	int i;
	for(i = 0; i < tamanho; i++)
	{
		if(tiro[i].ativo)
		{	
			tiro[i].x += tiro[i].vel_tiro; 

			if(tiro[i].x > SCREEN_W)
				tiro[i].ativo = 0;
		}
	}
}

void desenhaTiro(Tiro tiro[], int tamanho, ALLEGRO_BITMAP *tiro_sprite) {
	int i;
	for(i = 0; i < tamanho; i++)
	{
		if(tiro[i].ativo)
			al_draw_bitmap_region(tiro_sprite,
			168, 136, 49, 14, tiro[i].x-43, tiro[i].y-tiro[i].raio, 0);
   			//al_draw_filled_circle(tiro[i].x, tiro[i].y, tiro[i].raio, al_map_rgb(64,224,208));
	}
}

//TIRO HARD
void initTirao(Tirao *tirao) {

	tirao->ID = TIRAO;
	tirao->vel_tirao = 10;
	tirao->ativo = 0;
	tirao->pronto = 0;
}

void atiraTiraoMelhor(Tirao *tirao, Nave nave) { //apertar e segurar espaco
	if(!tirao->ativo)
	{
		tirao->x = nave.x + (tirao->raio)/2;
		tirao->y = nave.y;
		tirao->raio = 5; 
		tirao->cor = al_map_rgb(20,20,20);
		tirao->ativo = 1;	
	}
}

void atualizaTirao(Tirao *tirao, Nave nave, ALLEGRO_TIMER *timer) {
	if(!tirao->pronto) //quando a barra ta apertada
	{	
		tirao->x = nave.x + (tirao->raio)/2;
		tirao->y = nave.y;
		if(tirao->raio <= 21) //aumentar tiro
		{
			if(al_get_timer_count(timer)%((int)FPS/8) == 0) //cada seg/8 o raio aumenta
				tirao->raio += 4;
			if(tirao->raio >= 21)
				tirao->cor = al_map_rgb(64,224,208); //muda de cor caso estiver carregado
		}//TAM MAX E 25
	}
	if(tirao->ativo && tirao->pronto) //se existir tiro e barra solta
	{
		tirao->x += tirao->vel_tirao; 
		if(tirao->raio < 21)
		{
			tirao->ativo = 0;
			tirao->pronto = 0;
		}
		if(tirao->x > SCREEN_W)
		{
			tirao->ativo = 0;
			tirao->pronto = 0;
		}
	}
}

void desenhaTirao(Tirao tirao, ALLEGRO_BITMAP *tiro_sprite) {
    if(tirao.ativo && !tirao.pronto){
		al_draw_filled_circle(tirao.x, tirao.y, tirao.raio, tirao.cor);
	}
	if(tirao.ativo && tirao.pronto){ 
		//al_draw_filled_circle(tirao.x, tirao.y, tirao.raio, tirao.cor);
		al_draw_bitmap_region(tiro_sprite,
		0, 187, 50, 50, tirao.x-tirao.raio, tirao.y-tirao.raio,0);
	}
	
}

//-------------ExtraTiro---------------------
void initExtraTiro(ExtraTiro *extraTiro) {

	extraTiro->vel_ExtraTiro = 10;
	extraTiro->ativo = 0;
	extraTiro->pronto = 0;
}

void atiraExtraTiro(ExtraTiro *extraTiro, Nave nave) { //apertar e segurar espaco
	if(!extraTiro->ativo)
	{
		extraTiro->x = nave.x + (extraTiro->raio)/2;
		extraTiro->y = nave.y;
		extraTiro->raio = 20; 
		extraTiro->cor = al_map_rgb(2,20,20);
		extraTiro->ativo = 1;	
	}
}

void atualizaExtraTiro(ExtraTiro *extraTiro, Nave nave) {
	
	if(extraTiro->ativo) //se existir tiro e barra solta
	{
		extraTiro->x += extraTiro->vel_ExtraTiro; 
		if(extraTiro->x > SCREEN_W)
		{
			extraTiro->ativo = 0;
		}
	}
}

void desenhaExtraTiro(ExtraTiro extraTiro) {
    if(extraTiro.ativo){
		al_draw_filled_circle(extraTiro.x, extraTiro.y, extraTiro.raio, extraTiro.cor);
	}
}

//-----------------------INIMIGOS---------------------------------------
//os inimigos
void initEnemy(Enemy enemy[], int tam) {
	int i;
	int j = 0;
	for(i =0; i < tam; i++)
	{
		enemy[i].ID = INIMIGOS;
		enemy[i].ativo = 0;
		enemy[i].qual_id = j;
		enemy[i].cor_enemy = rand()%3; // 0, 1, 2
		j++;
	}
}

void soltaEnemy(Enemy enemy[], int tam) {
	int i, x;
	for(i = 0; i < tam; i++)
	{
		if(!enemy[i].ativo)
		{
			x = rand() % 2000; //caso o num aleatorio seja 0,1,2,3 ira setar um novo cometa //1/500 em 60fps
			if( x < 4)
			{
				enemy[i].raio = 25 + rand()% 26;
				enemy[i].x = SCREEN_W + enemy[i].raio;//+ rand()%SCREEN_W;
				enemy[i].y = (enemy[i].raio) + (rand()%(SCREEN_H - 2*enemy[i].raio - 40));//limitar para as bolinhas nn sairem
				enemy[i].vel_enemy = 6 + rand()%3; //max vel eh 8	
				enemy[i].ativo = 1;
				break; //ja sair do laco caso nn seja sorteado
				//FAZER CONTADOR 
				//FAZER OUTRO IF E IR AUMENTANDO PROBABILIDADE COMETA CONFORME JOGO FOR PASSANDO
				//EX: 4 MIN RAND()%300
			}
		}	
	}
}

void atualizaEnemy(Enemy enemy[], int tam) {
	int i;
	for(i = 0; i < tam; i++)
	{
		if(enemy[i].ativo)
		{
			enemy[i].x -= enemy[i].vel_enemy;
			if(enemy[i].x < -enemy[i].raio)
				enemy[i].ativo = 0;
		}		
	}
}

void desenhaEnemy(Enemy enemy[], int tam, ALLEGRO_BITMAP *cometa) {
	int i;
	for(i = 0; i < tam; i++){
		if(enemy[i].ativo && enemy[i].cor_enemy == 0)
		{
			//al_draw_filled_circle(enemy[i].x, enemy[i].y, enemy[i].raio, al_map_rgb(180,180,180));
			al_draw_scaled_bitmap(cometa,0,0,499,500, (enemy[i].x - enemy[i].raio), 
			(enemy[i].y - enemy[i].raio), enemy[i].raio*2, enemy[i].raio*2, 0);
		}	
		else if(enemy[i].ativo && enemy[i].cor_enemy == 1)
		{
			al_draw_tinted_scaled_bitmap(cometa, al_map_rgb(50,50,50),0,0,499,500, (enemy[i].x - enemy[i].raio), 
			(enemy[i].y - enemy[i].raio), enemy[i].raio*2, enemy[i].raio*2, 0);
		}	
		else if(enemy[i].ativo && enemy[i].cor_enemy == 2)
		{
			al_draw_tinted_scaled_bitmap(cometa, al_map_rgb(130,70,10),0,0,499,500, (enemy[i].x - enemy[i].raio), 
			(enemy[i].y - enemy[i].raio), enemy[i].raio*2, enemy[i].raio*2, 0);
		}	
	}
}

//-----------------------COLISOES---------------------------------------
//NAVE + BORDA ou NAVE + BASE
int checarColisaoLado(Nave *nave, Base *base) {
	if((nave->x - NAVE_W ) <= 0) //lado esq
    	nave->x = NAVE_W;
	if(nave->x >= SCREEN_W) //lado dir
		nave->x = SCREEN_W;
	if((nave->y + (NAVE_H/2)) >= base->y) //baixo
		return 1;
	if((nave->y - NAVE_H/2) <= 0) //topo
		nave->y = NAVE_H/2;
	return 0;
}
// NAVE + BLOCO
int colisaoNaveBloco(Nave *nave, Bloco *bloco) {
    if(nave->x > bloco->x &&//frente da nave com esq bloco
	   (nave->x - NAVE_W) < (bloco->x + bloco->w) &&//tras nave com dir bloco
	   (nave->y + NAVE_H/2) > bloco->y  &&//baixo nave c topo bloco
	   (nave->y - NAVE_H/2) < (bloco->y + bloco->h)) //topo nave c baixo bloco
    	return 1;
	else
		return 0;
}
// NAVE + ENEMY
int colisaoNaveEnemy(Nave *nave, Enemy enemy[], int tam) {
	int i;
	for(i = 0; i < tam; i++)
	{
		if(enemy[i].ativo && nave->power != 1) // nave power 1 == shield enemy
		{
			//int opa = distanciaPonto(nave.x,enemy->x,nave.y,enemy->y);
			if(nave->x > (enemy[i].x - enemy[i].raio) &&//frente da nave com esq tiro
			   (nave->x - NAVE_W) < (enemy[i].x + enemy[i].raio) && //tras nave com dir tiro
			   (nave->y + NAVE_H/2) > (enemy[i].y - enemy[i].raio) &&//baixo nave c topo tiro
			   (nave->y - NAVE_H/2) < (enemy[i].y + enemy[i].raio)) //topo nave c baixo tiro
			{
				enemy[i].ativo = 0;
				return 1;
				//MUDAR PARA VOID E TIRAR RETORNO PARA MUDAR MODO
			}
		}
	}
	return 0;
}
//TIRO + ENEMY    //bitmap e timer para explosão
int colisaoTiroEnemy(Tiro tiro[], int tam_t, Enemy enemy[], int tam_e, Nave *nave) {
	int i, j;
	//para cada tiro ativo buscar cometa ativo e checar se bate
	for(i = 0; i < tam_t; i++)
	{
		if(tiro[i].ativo)
		{
			for(j = 0; j<tam_e; j++)
			{
				if(enemy[j].ativo)
				{
					if(distanciaPonto(tiro[i].x, enemy[j].x, tiro[i].y, enemy[j].y) < (enemy[j].raio + tiro[i].raio))
					{
						enemy[j].ativo = 0;
						tiro[i].ativo = 0;

						nave->pontos += enemy[j].raio/10;
						return 1;
						/*if(enemy[j].raio == 50)//se for maior
							nave->pontos += 5; //mais pontos
						else//for outro tamanho
							nave->pontos++; */
					}
				}
			}
		}
	}
	return 0;
}
//TIRO + BLOCO
void colisaoTiroBloco(Tiro tiro[], int tam_t, Bloco bloco) {
	int i;
	for( i = 0; i < tam_t; i++)
	{
		if(tiro[i].ativo)
		{
			if(tiro[i].x + tiro[i].raio > bloco.x &&//frente do tiro com esq bloco
	   		   (tiro[i].x - tiro[i].raio) < (bloco.x + bloco.w) &&//tras tiro com dir bloco
	   		   (tiro[i].y + tiro[i].raio) > bloco.y &&//baixo tiro c topo bloco
	   		   (tiro[i].y - tiro[i].raio) < (bloco.y + bloco.h)) //topo tiro c baixo bloco
				  tiro[i].ativo = 0;
		}	
	}    
}
//TIRAO + ENEMY
int colisaoTiraoEnemy(Tirao *tirao, Enemy enemy[], int tam_e, Nave *nave) {
	int j;
	//para tirao ativo buscar cometa ativo e checar se bate
	if(tirao->ativo && tirao->pronto)//confirmar se existe e se foi disparado
	{
		for(j = 0; j<tam_e; j++)
		{
			if(enemy[j].ativo)
			{
				if(distanciaPonto(tirao->x, enemy[j].x, tirao->y, enemy[j].y) < (enemy[j].raio + tirao->raio))
				{
					enemy[j].ativo = 0; //se bater so o enemy morre

					nave->pontos += enemy[j].raio/10;

					return 1;
				}
			}
		}
	}
	return 0;
}
//TIRAO + BLOCO
void colisaoTiraoBloco(Tirao *tirao, Bloco bloco){
	if(tirao->ativo && tirao->pronto)
	{
		if(tirao->x + tirao->raio > bloco.x &&//frente do tiro com esq bloco
		   (tirao->x - tirao->raio) < (bloco.x + bloco.w) &&//tras tiro com dir bloco
  		   (tirao->y + tirao->raio) > bloco.y &&//baixo tiro c topo bloco
   		   (tirao->y - tirao->raio) < (bloco.y + bloco.h)) //topo tiro c baixo bloco
		{
			tirao->ativo = 0;
			tirao->pronto = 0;
		}
	}	
}
//ENEMY + BLOCO
void colisaoEnemyBloco(Enemy enemy[], int tam_e, Bloco bloco) {
	int i;
	for( i = 0; i < tam_e; i++)
	{
		if(enemy[i].ativo)
		{
			if(enemy[i].x + enemy[i].raio > bloco.x &&//tras do enemy com esq bloco
	   		   (enemy[i].x - enemy[i].raio) < (bloco.x + bloco.w) &&//frente enemy com dir bloco
	   		   (enemy[i].y + enemy[i].raio) > bloco.y &&//baixo enemy c topo bloco
	   		   (enemy[i].y - enemy[i].raio) < (bloco.y + bloco.h)) //topo enemy c baixo bloco
				  enemy[i].ativo = 0;
		}	
	}    
}
//ENEMY + ENEMY
void colisaoEnemyEnemy(Enemy enemy[], int tam) {
	int i, j;
	for(i = 0; i < tam; i++)
	{
		if(enemy[i].ativo)
		{
			for(j = 0; j<tam; j++)
			{
				if(enemy[j].ativo && enemy[i].qual_id != enemy[j].qual_id)
				{
					if(distanciaPonto(enemy[i].x, enemy[j].x, enemy[i].y, enemy[j].y) < (enemy[i].raio + enemy[j].raio))
					{
						enemy[i].ativo = 0;
						enemy[j].ativo = 0;
					}
				}
			}
		}
	}
}

//-----------------------INTERACOES EXTRAS---------------------------------------

void initPowerUp(Power power[], int tam_p){
	int i;
	for(i = 0; i < tam_p; i++)
	{
		power[i].vel_power = VELOCIDADE_BLOCO; //= vel bloco
		power[i].ativo = 0; //nn ativo
		power[i].tipo_power = 0; //sem tipo
	}
}
void soltarPowerUp(Power power[], int tam_p,ALLEGRO_TIMER *timer){
	int i, x;
	for(i = 0; i < tam_p; i++)
	{
		if(!power[i].ativo && (al_get_timer_count(timer)%((int)FPS) == 0)) //a cada segundo se nn tiver
		{
			x = rand()%125;
			if(x < 5) // 5/125 de vir power
			{
				power[i].tipo_power = 1; //shield
				/*if(x < 3) // 0 1 2
					power[i].tipo_power = 1; //shield
				else // 3 4
					power[i].tipo_power = 2; //metralha*/
				power[i].ativo = 1;
				power[i].w = 50;
				power[i].h = 50;
				power[i].x = SCREEN_W;
				power[i].y = 2*power[i].h + (rand()%(TAM_BASE - 3*power[i].h));
			}
		}
	}
}
void attPowerUp(Power power[], int tam_p, Bloco bloco, Nave *nave, ALLEGRO_BITMAP *powerShi, ALLEGRO_TIMER *timer){
	int i;
	for(i = 0; i < tam_p; i++)
	{
		if(power[i].ativo)
		{
			power[i].x -= power[i].vel_power; //atualizar vel
			if(power[i].x + power[i].w < 0) //desativar se sair tela
			{
				power[i].ativo = 0;
				power[i].tipo_power = 0;
			}		
			if(power[i].tipo_power == 1) //shield
				//al_draw_filled_rectangle(power[i].x, power[i].y, power[i].x + power[i].w, power[i].y + power[i].h, al_map_rgb(120,1,120));
				al_draw_scaled_bitmap(powerShi, 0,0,200,200, 
   				power[i].x, power[i].y, power[i].w, power[i].h, 0);
			/*else if(power[i].tipo_power == 2) //metralha
				al_draw_scaled_bitmap(powerMet, 0,0,200,200, 
   				power[i].x, power[i].y, power[i].w, power[i].h, 0);*/
		}
		
	}
	//checar colisoes
	for( i = 0; i < tam_p; i++)
	{
		if(power[i].ativo)
		{
			//colisao bloco
			if(power[i].x + power[i].w > bloco.x &&
	   		   (power[i].x) < (bloco.x + bloco.w) &&
	   		   (power[i].y + power[i].h) > bloco.y &&
	   		   (power[i].y) < (bloco.y + bloco.h)) 
			{
				power[i].ativo = 0;
				power[i].tipo_power = 0;
			}
			//colisao nave e dar o power 
			else if(power[i].x + power[i].w > (nave->x - NAVE_W) &&
	   		   (power[i].x) < nave->x &&
	   		   (power[i].y + power[i].h) > (nave->y - NAVE_H/2) &&
	   		   (power[i].y) < (nave->y + NAVE_H/2))
			{
				nave->power = power[i].tipo_power; //
				nave->tempo_power = 8; //8 seg para os dois power
				power[i].ativo = 0;
				power[i].tipo_power = 0;
			}
		}	
	}
	//ATUALIZAR PODER PARA A NAVE  
	if(nave->power != 0)
	{	
		if(al_get_timer_count(timer)%((int)FPS) == 0) //a cada seg
		{
			nave->tempo_power--;
			//printf("\n\n tempo power %d",al_get_timer_count(timer)%((int)FPS) == 0 );
			//printf("\n\n tempo power %d",nave->tempo_power);
			if(nave->tempo_power == 0)
				nave->power = 0;
		}
	}  
}



#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> //escrever
#include <allegro5/allegro_ttf.h> //escrever
#include <allegro5/allegro_primitives.h> //formas
#include <allegro5/allegro_image.h> //imagens
#include <allegro5/allegro_audio.h> //possibilitar o pc de audio
#include <allegro5/allegro_acodec.h> //extensoes audio
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include"TP_funcoes.h"

const float FPS = 100;  
const int SCREEN_W = 960;
const int SCREEN_H = 540;
 
const int NAVE_W = 100;
const int NAVE_H = 50;
const int TAM_BASE = 500; //SCREEN_H -40
const int VELOCIDADE_NAVE = 5;
const int VELOCIDADE_BLOCO = 4; //vel bloco, base e power
const int NUM_ESTRELAS = 100; //num estrelaas por plano
const int NUM_PLANOS = 3;
const int NUM_ENEMIES = 13; //num de inimigos por vez
const int NUM_TIROS = 20;
const int NUM_POWER = 2;



//-------------INICIALIZAÇÃO E JOGO-------------
int main(int argc, char **argv){

    srand(time(NULL));
	
	
	//tela // fila de eventos allegro  //timer
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *menu_escolha1 = NULL;
	ALLEGRO_BITMAP *menu_escolha2 = NULL;
	ALLEGRO_BITMAP *menu_escolha3 = NULL;
	ALLEGRO_BITMAP *menu_escolha4 = NULL;
	ALLEGRO_BITMAP *nave_milf_lado = NULL;
	ALLEGRO_BITMAP *nave_sd_lado = NULL;
	ALLEGRO_BITMAP *nave_xw_lado = NULL;
	ALLEGRO_BITMAP *fundo = NULL;
	ALLEGRO_BITMAP *chao = NULL;
	ALLEGRO_BITMAP *rocha1 = NULL;
	ALLEGRO_BITMAP *powerShi = NULL;
	ALLEGRO_BITMAP *cometa = NULL;
	ALLEGRO_BITMAP *tiro_sprite = NULL;

	ALLEGRO_SAMPLE *bck_som = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_bck_som = NULL;
	ALLEGRO_SAMPLE *imperial_march = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_imperial_march = NULL;
	ALLEGRO_SAMPLE *throne_room = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_throne_room = NULL;
	ALLEGRO_SAMPLE *select_som = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_select_som = NULL;
	ALLEGRO_SAMPLE *click_som = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_click_som = NULL;
	ALLEGRO_SAMPLE *shot_som = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_shot_som = NULL;
	ALLEGRO_SAMPLE *shot_forte_som = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_shot_forte_som = NULL;

   
	//----------------------- rotinas de INICIALIZAÇÃO---------------------------------------
	//printa oque estiver errado
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //primitivas do Allegro
	al_init_primitives_addon();
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
   
	//temporizador 
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//-------------IMG-------------
	//imagens no jogo
	al_init_image_addon();
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}

	background = al_load_bitmap("imagens/_estrelas.jpg");
	menu_escolha1 = al_load_bitmap("imagens/escolha1.png");
	menu_escolha2 = al_load_bitmap("imagens/escolha2.png");
	menu_escolha3 = al_load_bitmap("imagens/escolha3.png");
	menu_escolha4 = al_load_bitmap("imagens/escolha4.png");
	nave_milf_lado = al_load_bitmap("imagens/navelado_mf.png");
	nave_sd_lado = al_load_bitmap("imagens/navelado_sd.png");
	nave_xw_lado = al_load_bitmap("imagens/navelado_xw.png");
	fundo = al_load_bitmap("imagens/space5.jpg");
	chao = al_load_bitmap("imagens/chao.png");
	rocha1 = al_load_bitmap("imagens/rocha1.png");
	powerShi = al_load_bitmap("imagens/powerShil.png");
	cometa = al_load_bitmap("imagens/cometa1.png");
	tiro_sprite = al_load_bitmap("imagens/r-typesheet1.gif");
	if(!background)
    {
        fprintf(stderr, "failed to load background bitmap!\n");
        return -1;
    }

	//teclado
	al_install_keyboard();
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	//-------------FONTE-------------
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *fonttitle = al_load_font("fontes/_Starjhol.ttf", 72, 1);
	ALLEGRO_FONT *fontsubt_grande = al_load_font("fontes/_Starjedi.ttf", 42, 1);
	ALLEGRO_FONT *fontsubt = al_load_font("fontes/_Starjedi.ttf", 26, 1);
	ALLEGRO_FONT *fontsubt_menor = al_load_font("fontes/_Starjedi.ttf", 18, 1);
	ALLEGRO_FONT *fonticon = al_load_font("fontes/_DpolyImperial-4MgY.ttf", 48, 1);
	ALLEGRO_FONT *fontarrows = al_load_font("fontes/_arrows.ttf", 40, 1);
	ALLEGRO_FONT *fontarrows_grande = al_load_font("fontes/_arrows.ttf", 90, 1);
	ALLEGRO_FONT *fontmand = al_load_font("fontes/_mandalor.ttf", 26, 1);
	if (!fonttitle || !fontsubt || !fontsubt_menor || !fonticon || !fontarrows || !fontarrows_grande || !fontmand)
    {
        fprintf(stderr, "Falha ao carregar fontes.\n");
        al_destroy_display(display);
        return -1;
    }

	//-------------SOM-------------
	al_install_audio();
	if(!al_install_audio()){
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}
	al_init_acodec_addon();
	if(!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}
	al_reserve_samples(20); 
	bck_som = al_load_sample("audio/theme_Main.ogg");
	imperial_march = al_load_sample("audio/theme_Imperial_March.ogg");
	throne_room = al_load_sample("audio/theme_Throne_Room.ogg");
	click_som = al_load_sample("audio/sci-fi-click-900.ogg");
	select_som = al_load_sample("audio/sci-fi-switch.ogg");
	shot_som = al_load_sample("audio/tiro2.wav");
	shot_forte_som = al_load_sample("audio/tiro1.wav");
	
	if (!bck_som)
    {
        fprintf(stderr, "Falha ao carregar fontes.\n");
        al_destroy_display(display);
        return -1;
    }

	//evitar bug dos sons
	inst_bck_som = al_create_sample_instance(bck_som);
	inst_imperial_march = al_create_sample_instance(imperial_march);
	inst_throne_room = al_create_sample_instance(throne_room);
	inst_click_som = al_create_sample_instance(click_som);
	inst_select_som = al_create_sample_instance(select_som);
	inst_shot_som = al_create_sample_instance(shot_som);
	inst_shot_forte_som = al_create_sample_instance(shot_forte_som);
	
	//mixar
	al_attach_sample_instance_to_mixer(inst_bck_som, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_imperial_march, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_throne_room, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_click_som, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_select_som, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_shot_som, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_shot_forte_som, al_get_default_mixer());

	//definir loop ou unico som
	al_set_sample_instance_playmode(inst_bck_som, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(inst_imperial_march, ALLEGRO_PLAYMODE_LOOP );
	al_set_sample_instance_playmode(inst_throne_room, ALLEGRO_PLAYMODE_ONCE );
	al_set_sample_instance_playmode(inst_click_som, ALLEGRO_PLAYMODE_ONCE );
	al_set_sample_instance_playmode(inst_select_som, ALLEGRO_PLAYMODE_ONCE );
	al_set_sample_instance_playmode(inst_shot_som, ALLEGRO_PLAYMODE_ONCE );
	al_set_sample_instance_playmode(inst_shot_forte_som, ALLEGRO_PLAYMODE_ONCE );

	//vol som
	al_set_sample_instance_gain(inst_bck_som, 1.1);
	al_set_sample_instance_gain(inst_imperial_march, 1.1);
	al_set_sample_instance_gain(inst_throne_room, 1.1);
	al_set_sample_instance_gain(inst_click_som, 0.8);
	al_set_sample_instance_gain(inst_select_som, 0.9);
	al_set_sample_instance_gain(inst_shot_som, 0.8);
	al_set_sample_instance_gain(inst_shot_forte_som, 0.9);

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   


	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());	


	//-------------inicializacao obj-------------
    initGlobais();
    
	Estrela estrela[NUM_PLANOS][NUM_ESTRELAS];
	initEstrela(estrela, NUM_PLANOS, NUM_ESTRELAS);

    Nave nave;
    initNave(&nave);

	Base base;
	initBase(&base);

    Bloco bloco;
    initBloco(&bloco);

	Tiro tiro[NUM_TIROS];
	initTiro(tiro, NUM_TIROS);

	Tirao tirao;
	initTirao(&tirao);

	Enemy enemy[NUM_ENEMIES];
	initEnemy(enemy, NUM_ENEMIES);

	Power power[NUM_POWER];
	initPowerUp(power, NUM_POWER);

	
	ALLEGRO_COLOR COR_CENARIO = al_map_rgb(20,20,20);
	ALLEGRO_COLOR COR_TEXTO = al_map_rgb(255,255,255);
	ALLEGRO_COLOR COR_AMARELO = al_map_rgb(220,190,25);
	ALLEGRO_COLOR COR_PRETO = al_map_rgb(0,0,0);

	//-------------GAME GAME GAME GAME GAME GAME-------------
    //inicia o temporizador
	al_start_timer(timer);

	int seta_x = 1.2*SCREEN_W/3, seta_y = 1.35*SCREEN_H/3; //setas menu prin
	int seta_x_2 = 1.8*SCREEN_W/3, seta_y_2 = 1.35*SCREEN_H/3;
	int seta6_x = 1.2*SCREEN_W/3, seta6_y = SCREEN_H/2; //setas menu dif e back
	int seta6_x_2 = 1.8*SCREEN_W/3,seta6_y_2 = SCREEN_H/2;
	int tipo_dif_game = 1; //1 facil, 2 medio
	char dificuldade_game[20];

	int tipo_nave = 1; //1 mf, 2xw, 3sd
	char nome_nave[20];
	

	int pisca=0;//letras piscando
	int count = 0; //variavel do contador
	int scoreadd = 1; //para adicionar as scores no arquivo de all so uma vez
	int x = 0; //valor da high score
	int pause = 0; //se está pausado
	int playing = 1;
	int gametype = 10; //qual parte do jogo
	//10 intro : a galaxy far far
	//-1 reset
	//0 jogo 
	//1 menu inicial
	// 2 tela final
	// 3 menu de dicas
	// 4 menu de modos
	// 5 nave escolhida

	while(playing) {
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev); //espera por um evento e o armazena na variavel de evento ev

		//-----------------------EVENTOS E LOGICA---------------------------------------
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			//-------------APLICAR FUNCOES-------------
			if(al_get_timer_count(timer)%(int)FPS == 0){
				count = (int)(al_get_timer_count(timer)/FPS);
				//printf("\n%d segundos se passaram...",count );
			}	

			if(gametype == -1) //reset
			{
				initEstrela(estrela, NUM_PLANOS, NUM_ESTRELAS);
				initNave(&nave);
				initBase(&base);
				initBloco(&bloco);
				initTiro(tiro, NUM_TIROS);
				initTirao(&tirao);
				initEnemy(enemy, NUM_ENEMIES);
				initPowerUp(power, NUM_POWER);
				scoreadd = 1; //voltar para 1 para add nova score

				gametype = 1;
			}
            else if(gametype == 0) //JOGO
			{

				al_stop_sample_instance(inst_bck_som); //para a maintheme 
				al_play_sample_instance(inst_imperial_march); //começar a march
				//-------------COLISOES------------
				//NAVE + LADO/ NAVE + BASE
				if(checarColisaoLado(&nave, &base) == 1) //bateu na base,chao
					gametype = 2;

				//NAVE + BLOCO >>>>> GAME OVER
				if(colisaoNaveBloco(&nave, &bloco) == 1) //playing = !(colisaoNaveBloco(&nave, &bloco));
					gametype = 2;
				//NAVE + ENEMY >>>>> GAME OVER
				if(colisaoNaveEnemy(&nave, enemy, NUM_ENEMIES) == 1)
					gametype = 2;

				//TIRO + ENEMY
				colisaoTiroEnemy(tiro, NUM_TIROS, enemy, NUM_ENEMIES, &nave);
				//TIRO + BLOCO
				colisaoTiroBloco(tiro, NUM_TIROS, bloco);
				//TIRAO + ENEMY
				colisaoTiraoEnemy(&tirao, enemy, NUM_ENEMIES, &nave);
				//TIRAO + BLOCO
				colisaoTiraoBloco(&tirao, bloco);
				
				//ENEMY + BLOCO
				colisaoEnemyBloco(enemy, NUM_ENEMIES, bloco);
				//ENEMY + ENEMY
				colisaoEnemyEnemy(enemy, NUM_ENEMIES);


				//-------------DESENHOS E ATT------------
				if(!pause){
					al_draw_bitmap(fundo,0,0,0); 
					//desenhaCenario(); //colorir cenario
					atualizaEstrela(estrela, NUM_PLANOS, NUM_ESTRELAS);
					desenhaEstrela(estrela, NUM_PLANOS, NUM_ESTRELAS);
					

					atualizaNave(&nave);
					//desenhaNave(nave);
					if(nave.modelo == 1)
						al_draw_bitmap(nave_milf_lado, nave.x - NAVE_W, nave.y - NAVE_H/2, 0); 
					else if(nave.modelo == 2)
						al_draw_bitmap(nave_xw_lado, nave.x - NAVE_W, nave.y - NAVE_H/2, 0); 
					else if(nave.modelo == 3)
						al_draw_bitmap(nave_sd_lado, nave.x - NAVE_W, nave.y - NAVE_H/2, 0); 

					if(nave.power == 1){
						al_draw_tinted_bitmap_region(tiro_sprite, al_map_rgb(rand()%255,rand()%255,rand()%255),
						404, 86, 128, 98, nave.x - NAVE_W-7, nave.y - NAVE_H/2 - 24, 0);
					}

					atualizaBase(&base);
					desenhaBase(base, chao);
					atualizaBloco(&bloco);
					desenhaBloco(bloco, rocha1);

					soltarPowerUp(power, NUM_POWER, timer);
					if(tipo_dif_game == 1) //SE TIVER NO FACIL : POWER UP ON
						attPowerUp(power, NUM_POWER, bloco, &nave, powerShi, timer);
					
					atualizaTiro(tiro, NUM_TIROS);
					desenhaTiro(tiro, NUM_TIROS, tiro_sprite);

					atualizaTirao(&tirao, nave, timer); //passar timer
					desenhaTirao(tirao, tiro_sprite);

					atualizaEnemy(enemy, NUM_ENEMIES);
					soltaEnemy(enemy, NUM_ENEMIES);
					desenhaEnemy(enemy, NUM_ENEMIES,cometa);
				}
				

				//-------------ESCRITOS------------
				if(nave.tempo_power > 0)
				{
					al_draw_textf(fontsubt, COR_AMARELO, 0, 0, ALLEGRO_ALIGN_LEFT , 
					"  shield: %d seconds",nave.tempo_power);
				}
				al_draw_textf(fontsubt, COR_TEXTO, SCREEN_W, 0, ALLEGRO_ALIGN_RIGHT , 
				"pontos: %d   ", nave.pontos);
				al_draw_textf(fontsubt_menor, COR_TEXTO, 0, SCREEN_H - 40, ALLEGRO_ALIGN_LEFT ,
				"  ESC para sair / P para pausar / dificuldade: %s", dificuldade_game);
				al_flip_display();
				
			}

			else if(gametype == 1) //MENU INICIAL
			{
				//al_clear_to_color(al_map_rgb(20,20,20)); //cor de fundo
				al_draw_bitmap(background,0,0,0);//plano de fundo
				al_stop_sample_instance(inst_throne_room);
				al_play_sample_instance(inst_bck_som);
				
				al_draw_text(fonttitle, COR_AMARELO, SCREEN_W/2, SCREEN_H/6, ALLEGRO_ALIGN_CENTRE , 
				"Star-Type");
				//setas
				al_draw_text(fontarrows, COR_TEXTO, seta_x, seta_y, ALLEGRO_ALIGN_CENTRE, 
				"a");
				al_draw_text(fontarrows, COR_TEXTO, seta_x_2, seta_y_2, ALLEGRO_ALIGN_CENTRE, 
				"b");
				al_draw_text(fontsubt, COR_TEXTO, SCREEN_W/2, 1.3*SCREEN_H/3, ALLEGRO_ALIGN_CENTRE, 
				"Começar");
				al_draw_text(fontsubt, COR_TEXTO, SCREEN_W/2, 1.6*SCREEN_H/3, ALLEGRO_ALIGN_CENTRE, 
				"Como jogar");
				al_draw_text(fontsubt, COR_TEXTO, SCREEN_W/2, 1.9*SCREEN_H/3, ALLEGRO_ALIGN_CENTRE, 
				"Sair do jogo");
				al_draw_text(fonticon, COR_TEXTO, SCREEN_W/2, 2.2*SCREEN_H/3, ALLEGRO_ALIGN_CENTRE, 
				"R"); //icone starwars
				
				if(pisca>100) pisca = 0;
				if(pisca<50){
					al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, SCREEN_H - 50, ALLEGRO_ALIGN_CENTRE, 
					"press space to select");
				}
				pisca++;
				al_flip_display();
			}
			else if(gametype == 2) //MENU FINAL
			{	
				/*
				if(scoreadd == 1){
					adicionarScore("scores_todas.txt", nave.pontos);
					scoreadd++;
				} //file com todas as scores*/
				if(scoreadd == 1){
					x = descobrirScore("records.txt",nave.pontos);
					scoreadd++;
				} 
				al_stop_sample_instance(inst_imperial_march); //parar march imperial
				al_play_sample_instance(inst_throne_room);
				
				al_clear_to_color(al_map_rgb(20,20,20)); //cor de fundo
				al_draw_bitmap(background,0,0,0);//plano de fundo

				al_draw_textf(fonttitle, COR_TEXTO, SCREEN_W/2, SCREEN_H/5, ALLEGRO_ALIGN_CENTRE ,
				"game over");  
				al_draw_textf(fontsubt, COR_TEXTO, SCREEN_W/2, SCREEN_H/2 - 10 , ALLEGRO_ALIGN_CENTRE ,	
				"pontos: %d",nave.pontos);
				al_draw_textf(fontsubt, COR_TEXTO, SCREEN_W/2, SCREEN_H/2 + 20 , ALLEGRO_ALIGN_CENTRE ,	
				"highscore: %d", x); //descobrir highscore e armazenar atual
			
				if(nave.pontos >= x){
					al_draw_textf(fontsubt, COR_AMARELO, SCREEN_W/2, SCREEN_H/2 + 60 , ALLEGRO_ALIGN_CENTRE ,	
					"você fez um novo record!!! parabéns");
				}

				if(pisca>80) pisca = 0;
				if(pisca<40){
					al_draw_textf(fontsubt_menor, COR_TEXTO, SCREEN_W/2, SCREEN_H/2 + 125 , ALLEGRO_ALIGN_CENTRE ,	
					"ESC para sair");
					al_draw_textf(fontsubt_menor, COR_TEXTO, SCREEN_W/2, SCREEN_H/2 + 150 , ALLEGRO_ALIGN_CENTRE ,	
					"ENTER para jogar novamente");
				}
				pisca++;

				al_flip_display();
			}
			else if(gametype == 3) //AJUDAS
			{	
				al_clear_to_color(al_map_rgb(20,20,20)); //cor de fundo
				al_draw_bitmap(background,0,0,0);//plano de fundo

				al_draw_text(fontmand, COR_TEXTO, SCREEN_W/2, SCREEN_H/7, ALLEGRO_ALIGN_CENTRE, 
				"Parabéns você encontrou o easter egg em linguagem do mandaloriano");
				al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, 1.5*SCREEN_H/5, ALLEGRO_ALIGN_CENTRE, 
				"a,w,s,d para se locomover");
				al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, 1.9*SCREEN_H/5, ALLEGRO_ALIGN_CENTRE, 
				"clique espaço para atirar");
				al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, 2.3*SCREEN_H/5, ALLEGRO_ALIGN_CENTRE, 
				"clique e segure espaço para atirar tiro mais poderoso");
				al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, 2.5*SCREEN_H/5, ALLEGRO_ALIGN_CENTRE, 
				"obs: segurar até este ficar azul(pronto)");
				al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, 2.9*SCREEN_H/5, ALLEGRO_ALIGN_CENTRE, 
				"desvie de blocos");
				al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, 3.3*SCREEN_H/5, ALLEGRO_ALIGN_CENTRE, 
				"destrua cometas e faça pontos");
				al_draw_text(fontsubt_menor, COR_TEXTO, SCREEN_W/2, 3.7*SCREEN_H/5, ALLEGRO_ALIGN_CENTRE, 
				"pegue power ups");
				al_draw_text(fontarrows, COR_TEXTO, seta_x, seta_y, ALLEGRO_ALIGN_CENTRE, 
				"a");
				al_draw_text(fontarrows, COR_TEXTO, seta_x_2, seta_y_2, ALLEGRO_ALIGN_CENTRE, 
				"b");
				al_draw_text(fontsubt, COR_TEXTO, SCREEN_W/2, 3.4*SCREEN_H/4, ALLEGRO_ALIGN_CENTRE, 
				"voltar para menu inicial");
				al_flip_display();
			}
			else if(gametype == 4) //ESCOLHER NAVE
			{
				
				
				if(tipo_nave == 1)
				{
					al_draw_bitmap(menu_escolha1, 0, 0, 0); //desenhar mf
					al_draw_text(fontarrows_grande, COR_TEXTO,  7*SCREEN_W/8, SCREEN_H/2.3, ALLEGRO_ALIGN_CENTRE, "a");
					al_draw_text(fontarrows_grande, COR_TEXTO,  SCREEN_W/8, SCREEN_H/2.3, ALLEGRO_ALIGN_CENTRE, "b");
					al_draw_text(fontmand, COR_TEXTO, 4.5*SCREEN_W/5, 10, ALLEGRO_ALIGN_CENTRE, 
					"Escolha sua nave");
					al_draw_text(fontsubt_menor, COR_PRETO, SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE, 
					"escolha a nave");
					al_draw_text(fonticon, COR_PRETO, 2.5*SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE, 
					"R   A   I"); //icone starwars	

					al_draw_text(fontsubt, COR_TEXTO,  1.1*SCREEN_W/4, SCREEN_H/4, ALLEGRO_ALIGN_LEFT, "millennium falcon");
					al_draw_text(fonticon, COR_TEXTO, 2.8*SCREEN_W/4, 1.05*SCREEN_H/4, ALLEGRO_ALIGN_CENTRE, "R"); //icone starwars
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 1.5*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "light freighter");
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 1.8*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "rebel alliance"); 
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 2.1*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "aka:YT-1300");
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 2.4*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "Han Solo");
					
				}
				else if(tipo_nave == 2)
				{
					al_draw_bitmap(menu_escolha2, 0, 0, 0); //desenhar xw
					al_draw_text(fontarrows_grande, COR_TEXTO,  SCREEN_W/8, SCREEN_H/2.3, ALLEGRO_ALIGN_CENTRE, "b");
					al_draw_text(fontmand, COR_TEXTO, 4.5*SCREEN_W/5, 10, ALLEGRO_ALIGN_CENTRE, 
					"Escolha sua nave");
					al_draw_text(fontsubt_menor, COR_PRETO, SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE, 
					"escolha a nave");
					al_draw_text(fonticon, COR_PRETO, 2.5*SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE, 
					"R   A   I"); //icone starwars	

					al_draw_text(fontsubt, COR_TEXTO,  1.1*SCREEN_W/4, SCREEN_H/4, ALLEGRO_ALIGN_LEFT, "x-wing");
					al_draw_text(fonticon, COR_TEXTO, 2.8*SCREEN_W/4,1.05*SCREEN_H/4, ALLEGRO_ALIGN_CENTRE, "A"); //icone starwars
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 1.5*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "starfighter"); 
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 1.8*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "rebel alliance");
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 2.1*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "jedi order");
				}
				else if(tipo_nave == 3)
				{	
					al_draw_bitmap(menu_escolha3, 0, 0, 0); //desenhar sd
					al_draw_text(fontarrows_grande, COR_TEXTO, 7*SCREEN_W/8, SCREEN_H/2.3, ALLEGRO_ALIGN_CENTRE, "a");
					al_draw_text(fontmand, COR_TEXTO, 4.5*SCREEN_W/5, 10, ALLEGRO_ALIGN_CENTRE, 
					"Escolha sua nave");
					al_draw_text(fontsubt_menor, COR_PRETO, SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE, 
					"escolha a nave");
					al_draw_text(fonticon, COR_PRETO, 2.5*SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE, 
					"R   A   I"); //icone starwars

					al_draw_text(fontsubt, COR_TEXTO, 1.1*SCREEN_W/4, SCREEN_H/4, ALLEGRO_ALIGN_LEFT, "star destroyer");
					al_draw_text(fonticon, COR_TEXTO, 2.8*SCREEN_W/4, 1.05*SCREEN_H/4, ALLEGRO_ALIGN_CENTRE, "I"); //icone starwars
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 1.5*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "capital ship"); 
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 1.8*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "empire");
					al_draw_text(fontsubt_menor, COR_TEXTO, 2.9*SCREEN_W/4, 2.1*SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "sith eternal");
				}
				al_flip_display();
			}
			else if(gametype == 5) //nave escolhida
			{
				al_draw_bitmap(menu_escolha4, 0, 0, 0);
				al_draw_text(fontmand, COR_TEXTO, 4.5*SCREEN_W/5, 10, ALLEGRO_ALIGN_CENTRE, 
				"Escolha sua nave");
				al_draw_text(fontsubt_menor, COR_PRETO, SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE, 
				"escolha a nave");
				al_draw_text(fonticon, COR_PRETO, 2.5*SCREEN_W/7, 10, ALLEGRO_ALIGN_CENTRE,"R   A   I"); //icone starwars

				al_draw_text(fonttitle, COR_PRETO, SCREEN_W/2, SCREEN_H/2 - 140, ALLEGRO_ALIGN_CENTRE, nome_nave);
				al_draw_text(fontsubt, COR_PRETO, SCREEN_W/2, SCREEN_H/2 -40, ALLEGRO_ALIGN_CENTRE, 
				"dificuldade:");
				al_draw_text(fontarrows, COR_PRETO, seta6_x, seta6_y, ALLEGRO_ALIGN_CENTRE, 
				"a");
				al_draw_text(fontarrows, COR_PRETO, seta6_x_2, seta6_y_2, ALLEGRO_ALIGN_CENTRE, 
				"b");
				if(tipo_dif_game == 1)
					sprintf(dificuldade_game, "facil");
				else {
					sprintf(dificuldade_game, "medio");
					al_draw_text(fontsubt_menor, COR_PRETO, SCREEN_W/2, SCREEN_H/2 +30, ALLEGRO_ALIGN_CENTRE, 
				"sem power up");
				}
				al_draw_text(fontsubt, COR_PRETO, SCREEN_W/2, SCREEN_H/2 - 10, ALLEGRO_ALIGN_CENTRE, 
				dificuldade_game);
				

				if(pisca>100) pisca = 0;
				if(pisca<50){
					al_draw_text(fontsubt_menor, COR_PRETO, SCREEN_W/2, SCREEN_H/2 +90, ALLEGRO_ALIGN_CENTRE, 
					"press enter to play");
				}
				al_draw_text(fontsubt_menor, COR_PRETO, SCREEN_W/2, SCREEN_H/2 +110, ALLEGRO_ALIGN_CENTRE, 
				"esc to go back");
				pisca++;
				
				al_flip_display();
			}
			else if(gametype == 10)
			{
				al_draw_bitmap(background,0,0,0);//plano de fundo 
				al_draw_textf(fontsubt_grande, COR_AMARELO, SCREEN_W/2, SCREEN_H/2 - 46 , ALLEGRO_ALIGN_CENTRE ,	
				"a long time ago in a galaxy");
				al_draw_textf(fontsubt_grande, COR_AMARELO, SCREEN_W/2, SCREEN_H/2  , ALLEGRO_ALIGN_CENTRE ,
				"far far away...");
				if((int)(al_get_timer_count(timer)/FPS) > 3)
					gametype = 1;
				al_flip_display();
			}
			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		
		//-----------------------TECLADO---------------------------------------
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch(ev.keyboard.keycode){
			//sair do jogo , qualquer momento
			case ALLEGRO_KEY_ESCAPE:
				if(gametype == 5)
				{
					gametype = 4; //mudar para escolha nave
					al_draw_bitmap(menu_escolha1, 0,0, 0);
					al_flip_display();
				}
				else if(gametype == 4)
				{
					al_stop_sample_instance(inst_click_som);
					al_play_sample_instance(inst_click_som);
					gametype = 1;
				}
				else	
					playing = 0;
			break;

			case ALLEGRO_KEY_W:
				if(gametype == 0)
                	nave.dir_y--;
				else if(gametype == 1){
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(seta_y == 1.35*SCREEN_H/3){
						seta_y = 1.95*SCREEN_H/3;
						seta_x = 1.05*SCREEN_W/3;
						seta_y_2 = 1.95*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
					else if(seta_y == 1.65*SCREEN_H/3){
						seta_y = 1.35*SCREEN_H/3;
						seta_x = 1.2*SCREEN_W/3;
						seta_y_2 = 1.35*SCREEN_H/3;
						seta_x_2 = 1.8*SCREEN_W/3;
					}
					else if(seta_y == 1.95*SCREEN_H/3){
						seta_y = 1.65*SCREEN_H/3;
						seta_x = 1.1*SCREEN_W/3;
						seta_y_2 = 1.65*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
				}
            break;

            case ALLEGRO_KEY_S:
				if(gametype == 0)
                	nave.dir_y++;
				else if(gametype == 1){
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(seta_y == 1.35*SCREEN_H/3){
						seta_y = 1.65*SCREEN_H/3;
						seta_x = 1.1*SCREEN_W/3;
						seta_y_2 = 1.65*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
					else if(seta_y == 1.65*SCREEN_H/3){
						seta_y = 1.95*SCREEN_H/3;
						seta_x = 1.05*SCREEN_W/3;
						seta_y_2 = 1.95*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
					else if(seta_y == 1.95*SCREEN_H/3){
						seta_y = 1.35*SCREEN_H/3;
						seta_x = 1.2*SCREEN_W/3;
						seta_y_2 = 1.35*SCREEN_H/3;
						seta_x_2 = 1.8*SCREEN_W/3;
					}
				}
            break;

            case ALLEGRO_KEY_A:
                if(gametype == 0)
					nave.dir_x--;
				else if(gametype == 4)
				{
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_nave == 1) //se tiver na mf
						tipo_nave = 3;//ir para sd
					else if(tipo_nave == 2) //se tiver na xw
						tipo_nave = 1;//ir para mf
					else if(tipo_nave == 3) //se tiver na sd
						tipo_nave = 3;//ir para sd
				}
				else if(gametype == 5)
				{
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_dif_game == 1) 
						tipo_dif_game = 2;
					else if(tipo_dif_game == 2) 
						tipo_dif_game = 1;			
				}
            break;

            case ALLEGRO_KEY_D:
                if(gametype == 0)
					nave.dir_x++;
				else if(gametype == 4)
				{	
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_nave == 1) //se tiver na mf
						tipo_nave = 2;//ir para xw
					else if(tipo_nave == 2) //se tiver na xw
						tipo_nave = 2;//ir para xw
					else if(tipo_nave == 3) //se tiver na sd
						tipo_nave = 1;
				}
				else if(gametype == 5)
				{
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_dif_game == 1) 
						tipo_dif_game = 2;
					else if(tipo_dif_game == 2) 
						tipo_dif_game = 1;			
				}
            break;

			case ALLEGRO_KEY_LEFT:
				if(gametype == 4)
				{
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_nave == 1) //se tiver na mf
						tipo_nave = 3;//ir para sd
					else if(tipo_nave == 2) //se tiver na xw
						tipo_nave = 1;//ir para mf
					else if(tipo_nave == 3) //se tiver na sd
						tipo_nave = 3;//ir para sd
				}
				else if(gametype == 5)
				{
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_dif_game == 1) 
						tipo_dif_game = 2;
					else if(tipo_dif_game == 2) 
						tipo_dif_game = 1;			
				}
			break;

			case ALLEGRO_KEY_RIGHT:
				if(gametype == 4)
				{	
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_nave == 1) //se tiver na mf
						tipo_nave = 2;//ir para xw
					else if(tipo_nave == 2) //se tiver na xw
						tipo_nave = 2;//ir para xw
					else if(tipo_nave == 3) //se tiver na sd
						tipo_nave = 1;
				}
				else if(gametype == 5)
				{
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(tipo_dif_game == 1) 
						tipo_dif_game = 2;
					else if(tipo_dif_game == 2) 
						tipo_dif_game = 1;			
				}
			break;

			case ALLEGRO_KEY_UP:
				if(gametype == 1){
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(seta_y == 1.35*SCREEN_H/3){
						seta_y = 1.95*SCREEN_H/3;
						seta_x = 1.05*SCREEN_W/3;
						seta_y_2 = 1.95*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
					else if(seta_y == 1.65*SCREEN_H/3){
						seta_y = 1.35*SCREEN_H/3;
						seta_x = 1.2*SCREEN_W/3;
						seta_y_2 = 1.35*SCREEN_H/3;
						seta_x_2 = 1.8*SCREEN_W/3;
					}
					else if(seta_y == 1.95*SCREEN_H/3){
						seta_y = 1.65*SCREEN_H/3;
						seta_x = 1.1*SCREEN_W/3;
						seta_y_2 = 1.65*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
				}
			break;
			
			case ALLEGRO_KEY_DOWN:
				if(gametype == 1){
					al_stop_sample_instance(inst_select_som);
					al_play_sample_instance(inst_select_som);
					if(seta_y == 1.35*SCREEN_H/3){
						seta_y = 1.65*SCREEN_H/3;
						seta_x = 1.1*SCREEN_W/3;
						seta_y_2 = 1.65*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
					else if(seta_y == 1.65*SCREEN_H/3){
						seta_y = 1.95*SCREEN_H/3;
						seta_x = 1.05*SCREEN_W/3;
						seta_y_2 = 1.95*SCREEN_H/3;
						seta_x_2 = 1.9*SCREEN_W/3;
					}
					else if(seta_y == 1.95*SCREEN_H/3){
						seta_y = 1.35*SCREEN_H/3;
						seta_x = 1.2*SCREEN_W/3;
						seta_y_2 = 1.35*SCREEN_H/3;
						seta_x_2 = 1.8*SCREEN_W/3;
					}
				}
			break;

			case ALLEGRO_KEY_SPACE:
				if(gametype == 1){
					al_stop_sample_instance(inst_click_som);
					al_play_sample_instance(inst_click_som);
					if(seta_y == 1.35*SCREEN_H/3){
						gametype = 4; //mudar para escolha nave
						al_draw_bitmap(menu_escolha1, 0,0, 0);
						al_flip_display();
					}
					else if(seta_y == 1.65*SCREEN_H/3){
						seta_y =  3.5*SCREEN_H/4;
						seta_x = 0.75*SCREEN_W/3;
						seta_y_2 =  3.5*SCREEN_H/4;
						seta_x_2 = 2.25*SCREEN_W/3;
						gametype = 3; //menu de dicas
					}
					else if(seta_y == 1.95*SCREEN_H/3){
						playing = 0; //sair do jogo
					}
				}
				else if(gametype == 3) {
					al_stop_sample_instance(inst_click_som);
					al_play_sample_instance(inst_click_som);
					seta_y = 1.65*SCREEN_H/3;
					seta_x = 1.1*SCREEN_W/3;
					seta_y_2 = 1.65*SCREEN_H/3;
					seta_x_2 = 1.9*SCREEN_W/3;
					gametype = 1;
				}	
				else if(gametype == 4)
				{
					al_stop_sample_instance(inst_click_som);
					al_play_sample_instance(inst_click_som);
					if(tipo_nave == 1) //se tiver na mf
					{
						sprintf(nome_nave, "millennium falc.");
						nave.modelo = 1;
						gametype = 5;
					}
					else if(tipo_nave == 2) //se tiver na xw
					{
						sprintf(nome_nave, "x-wing");
						nave.modelo = 2;
						gametype = 5;
					}
					else if(tipo_nave == 3) //se tiver na sd
					{
						sprintf(nome_nave, "star destroyer");
						nave.modelo = 3;
						gametype = 5;
					}
				}/*
				else if(gametype == 5){
					al_stop_sample_instance(inst_click_som);
					al_play_sample_instance(inst_click_som);
					gametype = 0;
				}*/
			break;

			case ALLEGRO_KEY_ENTER:
				if(gametype == 5){
					al_stop_sample_instance(inst_click_som);
					al_play_sample_instance(inst_click_som);
					gametype = 0;
				}
				else if(gametype == 2)
					gametype = -1;
			break;

			case ALLEGRO_KEY_P:
                if(gametype == 0){
					if(pause == 0)
						pause = 1;
					else
						pause = 0;
				}
            break;
			}
			//imprime qual tecla foi
			//printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {

            switch(ev.keyboard.keycode) {
				//movimento nave
                case ALLEGRO_KEY_W:
					if(gametype == 0)
                    	nave.dir_y++;
                break;

                case ALLEGRO_KEY_S:
                    if(gametype == 0)
						nave.dir_y--;
                break;

                case ALLEGRO_KEY_A:
                    if(gametype == 0)
						nave.dir_x++;
                break;

                case ALLEGRO_KEY_D:
                    if(gametype == 0)
						nave.dir_x--;
                break;

				//liberar tirao
				case ALLEGRO_KEY_SPACE:
					if(gametype == 0){ 
						if(tirao.ativo && !pause){
							tirao.pronto = 1; //quando libera barra espaço solta o tiro
							al_stop_sample_instance(inst_shot_forte_som);
							al_play_sample_instance(inst_shot_forte_som);
						}	
					}	
				break;
            }
        }
		//ev de pressionr tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_CHAR) {
			//espaço segurado : tirao
			if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE && ev.keyboard.repeat) 
			{
				if(gametype == 0 && !pause)
					atiraTiraoMelhor(&tirao, nave);
			}
			//espaço clicado : tiro normal
			else if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE && !ev.keyboard.repeat)
			{ 
				if(gametype == 0 && !pause)
				{
					al_stop_sample_instance(inst_shot_som);
					al_play_sample_instance(inst_shot_som);
					atiraTiro(tiro, NUM_TIROS, nave);
				}
			}
		}


	} //fim do while
     
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(fonttitle);
	al_destroy_font(fontsubt_grande);
	al_destroy_font(fontsubt);
	al_destroy_font(fonticon);
	al_destroy_font(fontsubt_menor);
	al_destroy_font(fontarrows);
	al_destroy_font(fontmand);
	al_destroy_font(fontarrows_grande);
	al_destroy_bitmap(background);
	al_destroy_bitmap(menu_escolha1);
	al_destroy_bitmap(menu_escolha2);
	al_destroy_bitmap(menu_escolha3);
	al_destroy_bitmap(menu_escolha4);
	al_destroy_bitmap(nave_milf_lado);
	al_destroy_bitmap(nave_sd_lado);
	al_destroy_bitmap(nave_xw_lado);
	al_destroy_bitmap(fundo);
	al_destroy_bitmap(chao);
	al_destroy_bitmap(rocha1);
	al_destroy_bitmap(powerShi);
	al_destroy_bitmap(cometa);
	al_destroy_bitmap(tiro_sprite);
	
	al_destroy_sample(bck_som);
	al_destroy_sample_instance(inst_bck_som);
	al_destroy_sample(imperial_march);
	al_destroy_sample_instance(inst_imperial_march);
	al_destroy_sample(throne_room);
	al_destroy_sample_instance(inst_throne_room);
	al_destroy_sample(select_som);
	al_destroy_sample_instance(inst_select_som);
	al_destroy_sample(click_som);
	al_destroy_sample_instance(inst_click_som);
	al_destroy_sample(shot_som);
	al_destroy_sample_instance(inst_shot_som);
	al_destroy_sample(shot_forte_som);
	al_destroy_sample_instance(inst_shot_forte_som);

	return 0;
}
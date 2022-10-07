const float FPS;  
const int SCREEN_W;
const int SCREEN_H;
const int NAVE_W;
const int NAVE_H;
const int TAM_BASE;
const int VELOCIDADE_NAVE;
const int VELOCIDADE_BLOCO;
const int NUM_ESTRELAS;
const int NUM_PLANOS;
const int NUM_ENEMIES; //num de inimigos por vez
const int NUM_TIROS;
const int NUM_POWER;

enum IDS {JOGADOR, TIRO, TIRAO ,INIMIGOS, ESTRELA} ids;
ALLEGRO_COLOR COR_CENARIO;

typedef struct Estrela{
	int ID;
	int x, y;
	int vel_estrela;
} Estrela;

//criar nave
typedef struct Nave {
	
	int x, y;
    int vel_nave;
    int dir_x, dir_y;
	ALLEGRO_COLOR cor;
	int pontos; //score
	int pontos_dificuldade;
	int modelo; //qual desenho da nave
	int power; //se estiver com algum power 
	int tempo_power;

} Nave;

//criar chao
typedef struct Base {
	int x, y;
    int w, h;
	ALLEGRO_COLOR cor;
	int vel_base;
} Base;

//criar bloco
typedef struct Bloco{

    int x, y;
	ALLEGRO_COLOR cor;
    int w, h;
	int vel_bloco;

} Bloco;

//tiro simples
typedef struct Tiro{

	int ID;
	int vel_tiro;
	int ativo;//caso 1: true e estiver ativo
	int x, y;
	int raio;
	int tirao;

} Tiro;

typedef struct Tirao{

	int ID;
	int vel_tirao;
	int ativo;//caso 1: true e estiver ativo
	int pronto;
	int disparado;

	ALLEGRO_COLOR cor;
	int x, y;
	int raio;

} Tirao;

typedef struct Enemy{
	int ID;
	int vel_enemy;
	int ativo;
	int x, y;
	int raio;
	int qual_id;
	int cor_enemy; //para mudar o "tipo" dele, mudar a cor/sprite
	
} Enemy;

typedef struct Power{
	int vel_power; //=vel_bloco
	int ativo;
	int tipo_power;
	int x, y;
	int w, h;
} Power;
 

void adicionarScore(char nome_arquivo[], int pontos_atual);
int descobrirScore(char nome_arquivo[], int pontos_atual);
void initGlobais(); 
void desenhaCenario();

void initEstrela(Estrela estrela[][NUM_ESTRELAS], int num_plano, int tam_estrelas);
void atualizaEstrela(Estrela estrela[][NUM_ESTRELAS], int num_plano, int tam_estrelas);
void desenhaEstrela(Estrela estrela[][NUM_ESTRELAS], int num_plano, int tam_estrelas);

void initNave(Nave *nave);
void atualizaNave(Nave *nave);
void desenhaNave(Nave nave) ;
void initBase(Base *base);
void atualizaBase(Base *base);
void desenhaBase(Base base, ALLEGRO_BITMAP *extras);
void initBloco(Bloco *bloco);
void atualizaBloco(Bloco *bloco);
void desenhaBloco(Bloco bloco, ALLEGRO_BITMAP *rocha1);

void initTiro(Tiro tiro[], int tamanho);
void atiraTiro(Tiro tiro[], int tamanho, Nave nave);
void atualizaTiro(Tiro tiro[], int tamanho);
void desenhaTiro(Tiro tiro[], int tamanho, ALLEGRO_BITMAP *tiro_sprite);

void initTirao(Tirao *tirao);
void atiraTiraoMelhor(Tirao *tirao, Nave nave);
void atualizaTirao(Tirao *tirao, Nave nave, ALLEGRO_TIMER *timer);
void desenhaTirao(Tirao tirao, ALLEGRO_BITMAP *tiro_sprite);

void initEnemy(Enemy enemy[], int tam) ;
void soltaEnemy(Enemy enemy[], int tam);
void atualizaEnemy(Enemy enemy[], int tam);
void desenhaEnemy(Enemy enemy[], int tam, ALLEGRO_BITMAP *cometa) ;

int checarColisaoLado(Nave *nave, Base *base);
int colisaoNaveBloco(Nave *nave, Bloco *bloco);
int colisaoNaveEnemy(Nave *nave, Enemy enemy[], int tam);

int colisaoTiroEnemy(Tiro tiro[], int tam_t, Enemy enemy[], int tam_e, Nave *nave);
void colisaoTiroBloco(Tiro tiro[], int tam_t, Bloco bloco);
int colisaoTiraoEnemy(Tirao *tirao, Enemy enemy[], int tam_e, Nave *nave);
void colisaoTiraoBloco(Tirao *tirao, Bloco bloco);
void colisaoEnemyBloco(Enemy enemy[], int tam_e, Bloco bloco);
void colisaoEnemyEnemy(Enemy enemy[], int tam);

void initPowerUp(Power power[], int tam_p);
void soltarPowerUp(Power power[], int tam_p, ALLEGRO_TIMER *timer);
void attPowerUp(Power power[], int tam_p, Bloco bloco, Nave *nave, 
	ALLEGRO_BITMAP *powerShi, ALLEGRO_TIMER *timer);
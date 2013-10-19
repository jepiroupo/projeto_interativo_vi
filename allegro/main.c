#include <stdio.h>
#include <allegro5/allegro.h>

const float FPS = 15;
const int SCREEN_W = 1415;
const int SCREEN_H = 734;
const int SELETOR_SIZE = 57;
const int margem_x = 15;
const int margem_y = 15;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

ALLEGRO_BITMAP *parede;
ALLEGRO_BITMAP *caminho;
ALLEGRO_BITMAP *p_azul;
ALLEGRO_BITMAP *p_verde;
ALLEGRO_BITMAP *p_amarelo;
ALLEGRO_BITMAP *p_vermelho;
ALLEGRO_BITMAP *pa_azul;
ALLEGRO_BITMAP *pa_verde;
ALLEGRO_BITMAP *pa_amarelo;
ALLEGRO_BITMAP *pa_vermelho;
ALLEGRO_BITMAP *background;

void lerConf(int mapa[840][3])
{
	char linha;
	
	FILE *fp;

	int pos_x, pos_y, tipo;
	char aux_p[4];
	char aux_t[2];
	int contador = 0;

	int contador_item = 0;

	fp = fopen("map/map1.txt","r");

	if( fp == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	
	while((linha = fgetc(fp)) != EOF )
	{
		if(contador < 4)
		{
			aux_p[contador] = linha;
		}
		else if(contador < 8)
		{
			aux_p[contador - 4] = linha;
		}
		else
		{
			aux_t[0] = linha;
		}

		contador++;

		if(contador == 4)
		{
			sscanf(aux_p, "%d", &pos_x);
			mapa[contador_item][0] = pos_x;
		}
		else if(contador == 8)
		{
			sscanf(aux_p, "%d", &pos_y);
			mapa[contador_item][1] = pos_y;
		}
		else if(contador == 9)
		{
			contador = 0;
			sscanf(aux_t, "%d", &tipo);
//			printf("pos_x: %d\npos_y: %d\ntipo: %d\n", pos_x, pos_y, tipo);
//			printf("contador: %d\n", contador_item);
			mapa[contador_item][2] = tipo;
			contador_item = contador_item + 1;
		}
	}

   fclose(fp);
}

void inicializaBitmaps()
{
	parede = al_load_bitmap("img/parede.png");
	caminho = al_load_bitmap("img/caminho.png");
	p_azul = al_load_bitmap("img/p_azul.png");
	p_verde = al_load_bitmap("img/p_verde.png");
	p_amarelo = al_load_bitmap("img/p_amarelo.png");
	p_vermelho = al_load_bitmap("img/p_vermelho.png");
	pa_azul = al_load_bitmap("img/pa_azul.png");
	pa_verde = al_load_bitmap("img/pa_verde.png");
	pa_amarelo = al_load_bitmap("img/pa_amarelo.png");
	pa_vermelho = al_load_bitmap("img/pa_vermelho.png");
}

int desenhaMapa(int mapa[840][3])
{
	for(int i = 0; i < 840; i++)
	{
		if((int)mapa[i][2] == 0)
		{
			al_draw_bitmap(caminho, (float)(mapa[i][0] + margem_x), (float)(mapa[i][1] + margem_y), 0);
		}
		else if((int)mapa[i][2] == 1)
		{
			al_draw_bitmap(parede, (float)(mapa[i][0] + margem_x), (float)(mapa[i][1] + margem_y), 0);
		}
	}

}

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *seletor = NULL;

    float tamanho = 25;
    float espacamento = SELETOR_SIZE + 4;
    float seletor_x = 678;
    float seletor_y = 5;
    bool key[4] = { false, false, false, false };
    bool redraw = true;
    bool doexit = false;
    float posicao = 0;
	int mapa[840][3];

	inicializaBitmaps();
	lerConf(mapa);

	//Inicia o allegro
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_init_image_addon();

	//Cria a lista de eventos
    event_queue = al_create_event_queue();

	//Cria o timer
    timer = al_create_timer(1.0 / FPS);

	//Cria a janela
    display = al_create_display(SCREEN_W, SCREEN_H);

	//Limpa a janela com a cor preta
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
	//Carrega a imagem de fundo na variável
    background = al_load_bitmap("img/fundo.png");
	//Desenha a imagem de fundo na posição (0,0)
    al_draw_bitmap(background, 0, 0, 0);

	//Carrega a imagem do seletor na variável
    seletor = al_load_bitmap("img/selecao.png");
	//Desenha o seletor na posição (658,5)
    al_draw_bitmap(seletor, 658, 5, 0);

	desenhaMapa(mapa);

    //Registra os eventos
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_flip_display();

    //Inicia o timer
    al_start_timer(timer);

	//While do jogo
    while(!doexit)
    {
		//Aguarda o evento
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

		//Se der o tempo do timer, verifica qual tecla foi pressionada e se é possível se mover para a posição de destino
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if(key[KEY_LEFT] && (posicao == 1 || posicao == 3)) {
                seletor_x -= espacamento;
                if(posicao == 1)
                    posicao = 0;
                else
                    posicao = 2;
            }
            if(key[KEY_RIGHT] && (posicao == 0 || posicao == 2)) {
                seletor_x += espacamento;
                if(posicao == 0)
                    posicao = 1;
                else
                    posicao = 3;
            }
            if(key[KEY_UP] && (posicao == 2 || posicao == 3)) {
                seletor_y -= espacamento;
                if(posicao == 2)
                    posicao = 0;
                else
                    posicao = 1;
            }
            if(key[KEY_DOWN] && (posicao == 0 || posicao == 1)) {
                seletor_y += espacamento;
                if(posicao == 0)
                    posicao = 2;
                else
                    posicao = 3;
            }

            redraw = true;
        }
		//Se a janela for fechada, termina o jogo
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
		//Se o evento for um tecla pressionada, seta a variável dessa tecla para "true" (pressionada)
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT: 
                    key[KEY_LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
            }
        }
		//Se o evento for um tecla solta, seta a variável dessa tecla para "false" (caso seja Esc, encerra o programa)
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) { 
                case ALLEGRO_KEY_LEFT: 
                    key[KEY_LEFT] = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
            }
        }

		//Redesenha o jogo
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(seletor, seletor_x, seletor_y, 0);
			desenhaMapa(mapa);
            al_flip_display();
        }
    }

	//Destrói os objetos
    al_destroy_bitmap(background);
    al_destroy_bitmap(seletor);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

// gcc -o teste main.c -lallegro_image -lallegro $(pkg-config --cflags --libs allegro-5.0 allegro_primitives-5.0)

#include <stdio.h>
#include<time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const int SPRITE_SIZE = 32;
int shift = 0;
const float FPS = 30;
const int SCREEN_W = 1415;
const int SCREEN_H = 734;
const int SELETOR_SIZE = 97;
const int margem_x = 15;
const int margem_y = 15;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
const int VERMELHO = 2;
const int AZUL = 1;
const int VERDE = 3;
const int AMARELO = 4;

const int CIMA = 0;
const int DIREITA = 1;
const int BAIXO = 2;
const int ESQUERDA = 3;

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
ALLEGRO_BITMAP *c_azul;
ALLEGRO_BITMAP *c_verde;
ALLEGRO_BITMAP *c_amarelo;
ALLEGRO_BITMAP *c_vermelho;
ALLEGRO_BITMAP *imagemPerguntas;

//ALLEGRO_BITMAP *cachorro;
ALLEGRO_BITMAP *cachorro_lado;
ALLEGRO_BITMAP *cachorro_cima;
ALLEGRO_BITMAP *cachorro_baixo;
ALLEGRO_BITMAP *sprite;
/* 0 - Cima | 1 - Direita | 2 - Baixo | 3 - Esquerda */
int direcao_atual = 3;
int pos_x_cachorro = 0;
int pos_y_cachorro = 0;
int frame_cachorro = 0;

clock_t init_time; //Valor inicial
clock_t last_time; //Valor atual
int wait_time = 8000 * 1000; //Valor de espera
int janela_aberta = 0;
int pergunta_selecionada = 0;

ALLEGRO_FONT *font;

const char *perguntas[45];
const char *respostas[135];
const char *corretas[45];
const char *sorteadas[45];
int numero = 0;
int atual = 0;
int libera_portas = 0;

void leituraPerguntas(){
    perguntas[0] = "Qual o país que tem a forma de uma bota?";
	respostas[0] = "a) Itália.";
	respostas[1] = "b) Chile.";
	respostas[2] = "c) França.";
	corretas[0] = "a";

	perguntas[1] = "Que país usou armas químicas em aproximadamente agosto de 2013?";
	respostas[3] = "a) Iraque.";
	respostas[4] = "b) Israel.";
	respostas[5] = "c) Síria.";
	corretas[1] = "c";

	perguntas[2] = "Em que dia é comemorado o dia dos namorados no Brasil?";
	respostas[6] = "a) 12 de junho.";
	respostas[7] = "b) 14 de fevereiro.";
	respostas[8] = "c) 14 de junho.";
	corretas[2] = "a";

	perguntas[3] = "Qual é o mês do ano que tem 28 dias?";
	respostas[9] = "a) Janeiro.";
	respostas[10] = "b) Todos.";
	respostas[11] = "c) Fevereiro.";
	corretas[3] = "c";

	perguntas[4] = "Como se chama o mês sagrado do jejum dos muçulmanos?";
	respostas[12] = "a) Meca.";
	respostas[13] = "b) Ramadan.";
	respostas[14] = "c) Salam.";
	corretas[4] = "b";

	perguntas[5] = "Em que país é localizado a torre Eiffel?";
	respostas[15] = "a) Paris.";
	respostas[16] = "b) Itália.";
	respostas[17] = "c) Austrália.";
    corretas[5] = "a";

	perguntas[6] = "Qual é o menor país do mundo?";
	respostas[18] = "a) Líbano.";
	respostas[19] = "b) Vaticano.";
	respostas[20] = "c) Indonésia.";
	corretas[6] = "b";

	perguntas[7] = "Qual é o nome da torre inclinada?";
	respostas[21] = "a) Torre de Babel.";
	respostas[22] = "b) Torre Eiffel.";
	respostas[23] = "c) Torre de Pisa.";
	corretas[7] = "c";

	perguntas[8] = "Em que país é localizado a Torre de Pisa?";
	respostas[24] = "a) Itália.";
	respostas[25] = "b) Babilônia.";
	respostas[26] = "c) Paris.";
	corretas[8] = "a";

	perguntas[9] = "Quem é o atual presidente dos EUA?";
	respostas[27] = "a) George W. Bush.";
	respostas[28] = "b) Barack Obama.";
	respostas[29] = "c) Bill Clinton.";
	corretas[9] = "b";

	perguntas[10] = "Qual é a raiz quadrada de 25?";
	respostas[30] = "a) 2,5.";
	respostas[31] = "b) 5.";
	respostas[32] = "c) 10.";
	corretas[10] = "b";

	perguntas[11] = "Qual é data comemorativa da Independência do Brasil?";
	respostas[33] = "a) 15 de novembro.";
	respostas[34] = "b) 15 de setembro.";
	respostas[35] = "c) 7 de setembro.";
	corretas[11] = "c";

	perguntas[12] = "Qual é o ano que vai ser realizado a Copa no Brasil?";
	respostas[36] = "a) 2014.";
	respostas[37] = "b) 2012.";
	respostas[38] = "c) 2016.";
	corretas[12] = "a";

	perguntas[13] = "Em que mês vai ser realizada a copa no Brasil?";
	respostas[39] = "a) Julho.";
	respostas[40] = "b) Abril.";
	respostas[41] = "c) Junho.";
	corretas[13] = "c";

	perguntas[14] = "Quem é o vice-presidente do Brasil?";
	respostas[42] = "a) Lula.";
	respostas[43] = "b) Michel Temer.";
	respostas[44] = "c) Dilma.";
	corretas[14] = "b";

	perguntas[15] = "Qual é a fórmula da água?";
	respostas[45] = "a) H20.";
	respostas[46] = "b) O2";
	respostas[47] = "c) O.";
	corretas[15] = "a";

	perguntas[16] = "Qual é o símbolo químico do Oxigênio?";
	respostas[48] = "a) H2O.";
	respostas[49] = "b) C.";
	respostas[50] = "c) O.";
	corretas[16] = "c";

	perguntas[17] = "As leis de Newton foram formuladas por...";
	respostas[51] = "a) Galileu Galilei.";
	respostas[52] = "b) Albert Einstein.";
	respostas[53] = "c) Isaac Newton.";
	corretas[17] ="c";

	perguntas[18] = "Qual é a terceira lei de Newton?";
	respostas[54] = "a) Ação e Reação.";
	respostas[55] = "b) Inércia.";
	respostas[56] = "c) Princípio fundamental da dinâmica.";
	corretas[18] = "a";

	perguntas[19] = "Qual a derivada de sen(x)?";
	respostas[57] = "a) sen(X).";
	respostas[58] = "b) cos(x).";
	respostas[59] = "c) -cos(X).";
	corretas[19] = "b";

	perguntas[20] = "Em que ano Steve Jobs morreu?";
	respostas[60] = "a) 2010.";
	respostas[61] = "b) 2012.";
	respostas[62] = "c) 2011.";
	corretas[20] = "b";

	perguntas[21] = "Com quantos anos Steve Jobs morreu?";
	respostas[63] = "a) 50.";
	respostas[64] = "b) 56.";
	respostas[65] = "c) 60.";
	corretas[21] = "b";

	perguntas[22] = "Quem foi o criador da Apple?";
	respostas[66] = "a) Bill Gates.";
	respostas[67] = "b) Paul Allen.";
	respostas[68] = "c) Steve Jobs.";
	corretas[22] = "c";

	perguntas[23] = "Qual é a capital do Egito?";
	respostas[69] = "a) Cairo.";
	respostas[70] = "b) Bagdá.";
	respostas[71] = "c) Bairut.";
	corretas[23] = "a";

	perguntas[24] = "Quantos meses tem 3 anos e meio?";
	respostas[72] = "a) 40.";
	respostas[73] = "b) 42.";
	respostas[74] = "c) 44.";
	corretas[24] = "b";

	perguntas[25] = "Em que ano ocorreu o atentado do World Trade Center?";
	respostas[75] = "a) 2000.";
	respostas[76] = "b) 2002.";
	respostas[77] = "c) 2001.";
	corretas[25] = "c";

	perguntas[26] = "Qual das palavras abaixo é um adjetivo?";
	respostas[78] = "a) Lindo.";
	respostas[79] = "b) João.";
	respostas[80] = "c) Maria.";
	corretas[26] = "a";

	perguntas[27] = "Resolva: (6 * 6) / (5 + 7)?";
	respostas[81] = "a) 3.";
	respostas[82] = "b) 6.";
	respostas[83] = "c) 9.";
	corretas[27] = "a";

	perguntas[28] = "Nome do navegador português que, que descobriu o Brasil.";
	respostas[84] = "a) Américo Vespúcio.";
	respostas[85] = "b) Cristóvão Colombo.";
	respostas[86] = "c) Pedro Álvares Cabral.";
	corretas[28] = "c";

	perguntas[29] = "Estação do ano que antecede a Primavera?";
	respostas[87] = "a) Outono.";
	respostas[88] = "b) Verão.";
	respostas[89] = "c) Inverno.";
	corretas[29] = "c";

	perguntas[30] = "Nome da princesa que assinou a Lei que acabou a escravidão, dos negros, no Brasil.";
	respostas[90] = "a) Princesa Isabel.";
	respostas[91] = "b) Princesa Mirabel.";
	respostas[92] = "c) Princesa Leopoldina.";
	corretas[30] = "a";

	perguntas[31] = "Complete a frase a seguir: 'De Grão em grão...'";
	respostas[93] = "a) A galinha fica mais gorda.";
	respostas[94] = "b) A galinha enche o papo.";
	respostas[95] = "c) O pintinho vai ficando gordo.";
	corretas[31] = "b";

	perguntas[32] = "A primeira capital do Brasil foi:";
	respostas[96] = "a) Rio de Janeiro.";
	respostas[97] = "b) Salvador.";
	respostas[98] = "c) São Paulo.";
	corretas[32] = "b";

	perguntas[33] = "Quantas cores tem a bandeira do Brasil?";
	respostas[99] = "a) 4.";
	respostas[100] = "b) 6.";
	respostas[101] = "c) 5.";
	corretas[33] = "a";

	perguntas[34] = "Quais das cores abaixo não pertence ao arco-iris?";
	respostas[102] = "a) Azul.";
	respostas[103] = "b) Preto.";
	respostas[104] = "c) Amarelo.";
	corretas[34] = "b";

	perguntas[35] = "Qual é a capital da Austrália?";
	respostas[105] = "a) Canberra.";
	respostas[106] = "b) Sydney.";
	respostas[107] = "c) Melbourne.";
	corretas[35] = "a";

	perguntas[36] = "Qual é a derivada de cos(x)?";
	respostas[108] = "a) cos(x).";
	respostas[109] = "b) -cos(x).";
	respostas[110] = "c) -sen(x).";
	corretas[36] = "c";

	perguntas[37] = "Qual das palavras abaixo é um substantivo Composto?";
	respostas[111] = "a) Maria.";
	respostas[112] = "b) Guarda chuva.";
	respostas[113] = "c) Brasil.";
	corretas[37] = "b";

	perguntas[38] = "Como se escreve 42 em algarismos romanos?";
	respostas[114] = "a) XLII.";
	respostas[115] = "b) LXII.";
	respostas[116] = "c) DII.";
	corretas[38] = "a";

	perguntas[39] = "Qual é a capital do Estados Unidos?";
	respostas[117] = "a) Nova York.";
	respostas[118] = "b) Washington, D.C.";
	respostas[119] = "c) Miami.";
	corretas[39] = "b";

	perguntas[40] = "Que número é esse: 'DXV'?";
	respostas[120] = "a) 515.";
	respostas[121] = "b) 505.";
	respostas[122] = "c) 545.";
	corretas[40] = "a";

	perguntas[41] = "Como se escreve 970 em números romanos?";
	respostas[123] = "a) CML.";
	respostas[124] = "b) CMLX.";
	respostas[125] = "c) CMLXX.";
	corretas[41] = "c";

	perguntas[42] = "Qual é a resposta para a Vida, Universo e tudo mais?";
	respostas[126] = "a) 32.";
	respostas[127] = "b) 42.";
	respostas[128] = "c) 52.";
	corretas[42] = "b";

	perguntas[43] = "'Água mole em pedra dura, tanto bate até...'";
	respostas[129] = "a) Que a pedra fica polida.";
	respostas[130] = "b) Que cria lodo.";
	respostas[131] = "c) Que fura.";
	corretas[43] = "c";

	perguntas[44] = "Em que ano teve início a Segunda Guerra Mundial?";
	respostas[132] = "a) 1939.";
	respostas[133] = "b) 1938.";
	respostas[134] = "c) 1940.";
	corretas[44] = "a";
}

int seleciona_pergunta(int numero){
	//int numero = rand() % 45;
	al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 250, ALLEGRO_ALIGN_CENTRE, "%s", perguntas[numero]);
	if (atual == 0){
        al_draw_textf(font, al_map_rgb(255, 0, 0), (SCREEN_W ) - 1000, 350, ALLEGRO_ALIGN_LEFT, "%s", respostas[numero * 3]);
        al_draw_textf(font, al_map_rgb(255, 255, 255), (SCREEN_W) - 1000, 400, ALLEGRO_ALIGN_LEFT, "%s", respostas[(numero * 3) + 1]);
        al_draw_textf(font, al_map_rgb(255, 255, 255), (SCREEN_W) - 1000, 450, ALLEGRO_ALIGN_LEFT, "%s", respostas[(numero * 3) + 2]);
	}else if (atual == 1){
        al_draw_textf(font, al_map_rgb(255, 255, 255), (SCREEN_W) - 1000, 350, ALLEGRO_ALIGN_LEFT, "%s", respostas[numero * 3]);
        al_draw_textf(font, al_map_rgb(255, 0, 0), (SCREEN_W ) - 1000, 400, ALLEGRO_ALIGN_LEFT, "%s", respostas[(numero * 3) + 1]);
        al_draw_textf(font, al_map_rgb(255, 255, 255), (SCREEN_W) - 1000, 450, ALLEGRO_ALIGN_LEFT, "%s", respostas[(numero * 3) + 2]);
	}else if (atual == 2){
        al_draw_textf(font, al_map_rgb(255, 255, 255), (SCREEN_W ) - 1000, 350, ALLEGRO_ALIGN_LEFT, "%s", respostas[numero * 3]);
        al_draw_textf(font, al_map_rgb(255, 255, 255), (SCREEN_W) - 1000, 400, ALLEGRO_ALIGN_LEFT, "%s", respostas[(numero * 3) + 1]);
        al_draw_textf(font, al_map_rgb(255, 0, 0), (SCREEN_W ) - 1000, 450, ALLEGRO_ALIGN_LEFT, "%s", respostas[(numero * 3) + 2]);
	}

	/*printf("Pergunta: %d\n", numero);
	printf("Pergunta: %s\n", perguntas[numero]);
	printf("Resposta 1: %s\n", respostas[numero * 3]);
	printf("Resposta 2: %s\n", respostas[(numero * 3) + 1]);
	printf("Resposta 3: %s\n", respostas[(numero * 3) + 2]);*/
}

int confere(int numero){
    int aux = 0;
    if (corretas[numero] == "a"){
        aux = 0;
    }else if (corretas[numero] == "b"){
        aux = 1;
    }else if (corretas[numero] == "c"){
        aux = 2;
    }

    if (aux == atual){
        libera_portas += 1;
    }
}

//Inicia a contagem
int initClock(void) {
    init_time = clock();
    last_time = init_time;
    return (int)init_time;
}

//Atualiza o time
bool checkClock(void) {
    last_time = clock();
    //printf("last: %d, init: %d\n", (int)last_time, (int)init_time);
    //printf("sub: %d\n", (int)last_time-init_time);
    //printf("wait: %d\n", wait_time);
    if ( last_time-init_time >= wait_time ) {
        //printf("1");
        return true;//O relogio atingiu o tempo de espera; }
    }else{
        //printf("0");
        return false; // o tempo de espera ainda não foi atingido;
    }
}

void lerConf(int mapa[770][3]){
    char linha;

    FILE *fp;

    int pos_x, pos_y, tipo;
    char aux_p[4];
    char aux_t[3];
    int contador = 0;

    int contador_item = 0;

    fp = fopen("map/map1.txt","r");

    if( fp == NULL ){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }


    while((linha = fgetc(fp)) != EOF ){
        if(contador_item == 770){
            break;
        }

        if(contador < 4)
            aux_p[contador] = linha;
        else if(contador < 8)
            aux_p[contador - 4] = linha;
        else
            aux_t[contador - 8] = linha;

        contador++;

        if(contador == 4){
            sscanf(aux_p, "%d", &pos_x);
            mapa[contador_item][0] = pos_x;
        }
        else if(contador == 8){
            sscanf(aux_p, "%d", &pos_y);
            mapa[contador_item][1] = pos_y;
        }
        else if(contador == 10){
            contador = 0;
            sscanf(aux_t, "%d", &tipo);
//            printf("pos_x: %d\npos_y: %d\ntipo: %d\n", pos_x, pos_y, tipo);
//            printf("contador: %d\n", contador_item);
            mapa[contador_item][2] = tipo;
            contador_item = contador_item + 1;
        }
    }

   fclose(fp);
}

void inicializaBitmaps(){
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
    c_azul = al_load_bitmap("img/c_azul.png");
    c_verde = al_load_bitmap("img/c_verde.png");
    c_amarelo = al_load_bitmap("img/c_amarelo.png");
    c_vermelho = al_load_bitmap("img/c_vermelho.png");
    imagemPerguntas = al_load_bitmap("img/perguntas.png");

    font = al_load_font("font/roboto.ttf", 22, 0);

    //cachorro = al_load_bitmap("img/cachorro/sprites/cachorro_lado.png");
    cachorro_lado = al_load_bitmap("img/cachorro/sprites/cachorro_lado.png");
    cachorro_cima = al_load_bitmap("img/cachorro/sprites/cachorro_fundo.png");
    cachorro_baixo = al_load_bitmap("img/cachorro/sprites/cachorro_frente.png");
}

bool validaProximo(int mapa[770][3], int posicao){
    if(mapa[posicao][2] == 0)
        return true;
    else if(mapa[posicao][2] == 6)
        return true;
    else if(mapa[posicao][2] == 7)
        return true;
    else if(mapa[posicao][2] == 8)
        return true;
    else if(mapa[posicao][2] == 9)
        return true;
    else if(mapa[posicao][2] == 10)
        return true;
    else if(mapa[posicao][2] == 11)
        return true;
    else if(mapa[posicao][2] == 12)
        return true;
    else if(mapa[posicao][2] == 13)
        return true;
    else if(mapa[posicao][2] == 14)
        return true;
    return false;
}

int atualizaCachorro(){
    int flags = 0;
    if(direcao_atual == 0){
        flags = 0;
        pos_y_cachorro = pos_y_cachorro - 8;
        sprite = al_create_sub_bitmap(cachorro_cima, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
    else if(direcao_atual == 1){
        flags = ALLEGRO_FLIP_HORIZONTAL;
        pos_x_cachorro = pos_x_cachorro + 8;
        sprite = al_create_sub_bitmap(cachorro_lado, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
    else if(direcao_atual == 2){
        flags = 0;
        pos_y_cachorro = pos_y_cachorro + 8;
        sprite = al_create_sub_bitmap(cachorro_baixo, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
    else if(direcao_atual == 3){
        flags = 0;
        pos_x_cachorro = pos_x_cachorro - 8;
        sprite = al_create_sub_bitmap(cachorro_lado, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
}

void movimento(int mapa[770][3]){
    int aux_x = pos_x_cachorro/32;
    int aux_y = pos_y_cachorro/32;
    int aux = 0;

    bool v_cima=false, v_direita=false, v_baixo=false, v_esquerda=false;

    v_cima = validaProximo(mapa, ((aux_y-1)*35)+aux_x);
    v_direita = validaProximo(mapa, (aux_y*35)+aux_x+1);
    v_baixo = validaProximo(mapa, ((aux_y+1)*35)+aux_x);
    v_esquerda = validaProximo(mapa, (aux_y*35)+aux_x-1);

    if (frame_cachorro == 3){
        if(direcao_atual == CIMA){
            /* Sem saída */
            if(!v_cima && !v_direita && !v_esquerda) direcao_atual = BAIXO;
            /* Uma opção */
            else if(!v_cima && v_direita && !v_esquerda) direcao_atual = DIREITA;
            else if(!v_cima && !v_direita && v_esquerda) direcao_atual = ESQUERDA;
            /* Duas opções */
            else if(v_cima && v_direita && !v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = DIREITA;
            }
            else if(v_cima && !v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = ESQUERDA;
            }
            else if(!v_cima && v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
            else if(v_cima && v_direita && v_esquerda){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = CIMA;
                else if(aux == 1) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
        }
        else if(direcao_atual == DIREITA){
            /* Sem saída */
            if(!v_cima && !v_baixo && !v_direita) direcao_atual = ESQUERDA;
            /* Uma opção */
            else if(!v_cima && v_baixo && !v_direita) direcao_atual = BAIXO;
            else if(v_cima && !v_baixo && !v_direita) direcao_atual = CIMA;
            /* Duas opções */
            else if(v_cima && v_baixo && !v_direita){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = BAIXO;
            }
            else if(v_cima && !v_baixo && v_direita){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = DIREITA;
            }
            else if(!v_cima && v_baixo && v_direita){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = DIREITA;
            }
            else if(v_cima && v_baixo && v_direita){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = CIMA;
                else if(aux == 1) direcao_atual = DIREITA;
                else direcao_atual = BAIXO;
            }
        }
        else if(direcao_atual == BAIXO){
            /* Sem saída */
            if(!v_esquerda && !v_baixo && !v_direita) direcao_atual = CIMA;
            /* Uma opção */
            else if(!v_baixo && v_direita && !v_esquerda) direcao_atual = DIREITA;
            else if(!v_baixo && !v_direita && v_esquerda) direcao_atual = ESQUERDA;
            /* Duas opções */
            else if(v_baixo && v_direita && !v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = DIREITA;
            }
            else if(v_baixo && !v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = ESQUERDA;
            }
            else if(!v_baixo && v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
            else if(v_baixo && v_direita && v_esquerda){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = BAIXO;
                else if(aux == 1) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
        }
        else if(direcao_atual == ESQUERDA){
            /* Sem saída */
            if(!v_esquerda && !v_baixo && !v_cima) direcao_atual = DIREITA;
            /* Uma opção */
            else if(!v_cima && v_baixo && !v_esquerda) direcao_atual = BAIXO;
            else if(v_cima && !v_baixo && !v_esquerda) direcao_atual = CIMA;
            /* Duas opções */
            else if(v_cima && v_baixo && !v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = BAIXO;
            }
            else if(v_cima && !v_baixo && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = ESQUERDA;
            }
            else if(!v_cima && v_baixo && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = ESQUERDA;
            }
            else if(v_cima && v_baixo && v_esquerda){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = CIMA;
                else if(aux == 1) direcao_atual = BAIXO;
                else direcao_atual = ESQUERDA;
            }
        }
    }
    atualizaCachorro();
    frame_cachorro = (frame_cachorro + 1) % 4;
}

int desenhaMapa(int mapa[770][3], bool envio[4]){
    int x, y, tipo;

    for(int i = 0; i < 770; i++){
        x = mapa[i][0];
        y = mapa[i][1];
        tipo = mapa[i][2];

        if(tipo == 0)
            al_draw_bitmap(caminho, x + margem_x, y + margem_y, 0);
        else if(tipo == 1)
            al_draw_bitmap(parede, x + margem_x, y + margem_y, 0);
        else if(tipo == 2){
            if(envio[VERMELHO] == false){
                al_draw_bitmap(p_vermelho, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 6;
                al_draw_bitmap(pa_vermelho, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 3){
            if(envio[AZUL] == false){
                al_draw_bitmap(p_azul, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 7;
                al_draw_bitmap(pa_azul, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 4){
            if(envio[VERDE] == false){
                al_draw_bitmap(p_verde, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 8;
                al_draw_bitmap(pa_verde, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 5){
            if(envio[AMARELO] == false){
                al_draw_bitmap(p_amarelo, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 9;
                al_draw_bitmap(pa_amarelo, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 6){
            if(envio[VERMELHO] == false){
                al_draw_bitmap(pa_vermelho, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 2;
                al_draw_bitmap(p_vermelho, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 7){
            if(envio[AZUL] == false){
                al_draw_bitmap(pa_azul, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 3;
                al_draw_bitmap(p_azul, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 8){
            if(envio[VERDE] == false){
                al_draw_bitmap(pa_verde, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 4;
                al_draw_bitmap(p_verde, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 9){
            if(envio[AMARELO] == false){
                al_draw_bitmap(pa_amarelo, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 5;
                al_draw_bitmap(p_amarelo, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 10 && pos_x_cachorro == 0 && pos_y_cachorro == 0){
            //printf("i: %d - x: %d - y: %d\n", i, x, y);
            pos_x_cachorro = x;
            pos_y_cachorro = y;
            //al_draw_bitmap(cachorro_lado, x + margem_x, y + margem_y, 0);
            atualizaCachorro();
        }
        else if(tipo == 11){
            mapa[i][2] = 11;
            al_draw_bitmap(c_vermelho, x + margem_x, y + margem_y, 0);
        }
        else if(tipo == 12){
            mapa[i][2] = 12;
            al_draw_bitmap(c_azul, x + margem_x, y + margem_y, 0);
        }
        else if(tipo == 13){
            mapa[i][2] = 13;
            al_draw_bitmap(c_verde, x + margem_x, y + margem_y, 0);
        }
        else if(tipo == 14){
            mapa[i][2] = 14;
            al_draw_bitmap(c_amarelo, x + margem_x, y + margem_y, 0);
        }
    }

    if(envio[VERMELHO] == true)
        envio[VERMELHO] = false;
    if(envio[AZUL] == true)
        envio[AZUL] = false;
    if(envio[VERDE] == true)
        envio[VERDE] = false;
    if(envio[AMARELO] == true)
        envio[AMARELO] = false;

    al_draw_text(font, al_map_rgb(255, 0, 0), (SCREEN_W / 2) + 530, 325, ALLEGRO_ALIGN_CENTRE, "Jogador 1");
    al_draw_textf(font, al_map_rgb(255, 0, 0), SCREEN_W / 2 + 655, 325, ALLEGRO_ALIGN_LEFT, "%d", libera_portas);
    al_draw_text(font, al_map_rgb(0, 255, 0), (SCREEN_W / 2) + 530, 366, ALLEGRO_ALIGN_CENTRE, "Jogador 2");
    al_draw_textf(font, al_map_rgb(0, 255, 0), SCREEN_W / 2 + 655, 366, ALLEGRO_ALIGN_LEFT, "%d", libera_portas);
    al_draw_text(font, al_map_rgb(0, 0, 255), (SCREEN_W / 2) + 530, 407, ALLEGRO_ALIGN_CENTRE, "Jogador 3");
    al_draw_textf(font, al_map_rgb(0, 0, 255), SCREEN_W / 2 + 655, 407, ALLEGRO_ALIGN_LEFT, "%d", libera_portas);
    al_draw_text(font, al_map_rgb(255, 255, 0), (SCREEN_W / 2) + 530, 448, ALLEGRO_ALIGN_CENTRE, "Jogador 4");
    al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_W / 2 + 655, 448, ALLEGRO_ALIGN_LEFT, "%d", libera_portas);
}

int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *seletor = NULL;

    float tamanho = 25;
    float espacamento = SELETOR_SIZE + 19;
    float seletor_x = 1174;
    float seletor_y = 40;
    bool key[4] = { false, false, false, false };
    bool redraw = true;
    bool doexit = false;
    float posicao = 0;
    int mapa[770][3];
    bool envio[4] = { false, false, false, false };


    //Inicia o allegro
    al_init();
    al_init_image_addon();
    al_install_keyboard();

     // Inicialização do add-on para uso de fontes
    al_init_font_addon();
    al_init_ttf_addon();

    inicializaBitmaps();
    lerConf(mapa);

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
    //Desenha o seletor na posição (1174,40)
    al_draw_bitmap(seletor, 1174, 40, 0);

    desenhaMapa(mapa, envio);

    //Registra os eventos
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_flip_display();

    //Inicia o timer
    al_start_timer(timer);

    //Inicia contagem de tempo para a pergunta aparecer
    initClock();

    //Inicia as perguntas
    leituraPerguntas();
    //While do jogo
    while(!doexit){
        //Aguarda o evento
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        //Se der o tempo do timer, verifica qual tecla foi pressionada e se é possível se mover para a posição de destino
        if(ev.type == ALLEGRO_EVENT_TIMER){
            if(key[KEY_LEFT] && (posicao == 1 || posicao == 3) && (janela_aberta == 0)) {
                seletor_x -= espacamento;
                if(posicao == 1)
                    posicao = 0;
                else
                    posicao = 2;
            }
            if(key[KEY_RIGHT] && (posicao == 0 || posicao == 2) && (janela_aberta == 0)) {
                seletor_x += espacamento;
                if(posicao == 0)
                    posicao = 1;
                else
                    posicao = 3;
            }
            if(key[KEY_UP] && (posicao == 2 || posicao == 3) && (janela_aberta == 0)) {
                seletor_y -= espacamento;
                if(posicao == 2)
                    posicao = 0;
                else
                    posicao = 1;
            }

            if(key[KEY_DOWN] && (posicao == 0 || posicao == 1) && (janela_aberta == 0)) {
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
                    if (janela_aberta == 1) {
                        if (atual == 2){
                            atual = 1;
                        }else if (atual == 1){
                            atual = 0;
                        }
                    }
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    if (janela_aberta == 1) {
                        if (atual == 0){
                            atual = 1;
                        }else if (atual == 1){
                            atual = 2;
                        }
                    }
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
                case ALLEGRO_KEY_ENTER:
                    if ((janela_aberta == 0) && (libera_portas > 0)){
                        if(posicao == 0){
                            libera_portas -= 1;
                            envio[VERMELHO] = true;
                        }else if(posicao == 1){
                            libera_portas -= 1;
                            envio[AZUL] = true;
                        }else if(posicao == 2){
                            libera_portas -= 1;
                            envio[VERDE] = true;
                        }else if(posicao == 3){
                            libera_portas -= 1;
                            envio[AMARELO] = true;
                        }
                    }else if (janela_aberta == 1){
                        confere(numero);
                        janela_aberta = 0;
                    }

            }
        }

        //Redesenha o jogo
        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_draw_bitmap(background, 0, 0, 0);
            desenhaMapa(mapa, envio);
            movimento(mapa);
            if (janela_aberta == 0){
                if (checkClock()){
                    janela_aberta = 1;
                    pergunta_selecionada = 0;
                }
            }else{
                al_draw_bitmap(imagemPerguntas, 0, 0, 0);
                if (pergunta_selecionada == 0){
                    numero = rand() % 45;
                    atual = 0;
                    seleciona_pergunta(numero);
                    pergunta_selecionada = 1;
                }else{
                    seleciona_pergunta(numero);
                }
                initClock();
            }

            al_draw_bitmap(seletor, seletor_x, seletor_y, 0);
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

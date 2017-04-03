#include <windows.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 250
#define ALTURA_JANELA 250
#define LOOP_TIME 30

typedef struct _ponto {
    int x;
    int y;
} Ponto;

Ponto criarPonto(int x, int y) {
    Ponto p;
    p.x = x;
    p.y = y;
    return p;
}


/* Declara os 4 pontos dos quadrados
   Sendo:
   quad*_p1 = superior esquero;
   quad*_p2 = superior direito;
   quad*_p3 = inferior esquerdo;
   quad*_p4 = inferior direito;
   
   E considerando quad1 os pontos do quadrado que se move sozinho
*/
Ponto quad1_p1, quad1_p2, quad1_p3, quad1_p4;
Ponto quad2_p1, quad2_p2, quad2_p3, quad2_p4;

//Incremento de x, e de y para o quadrado automático.
int xIncre, yIncre;
int up, down, left, right;

int tempo = 0;

/* Função chamada a cada 100 ms. É responsável por atualizar a
posição do quad1, que se move sozinho (sem entrada do teclado).
*/

/* Função para capturar teclas especiais digitadas pelo usuário
O primeiro parâmetro inteiro (variável "tecla") representa o código
da tecla pressionada.*/

bool pontoDentroQuadrado(Ponto p) {
    if(quad1_p1.x < p.x && quad1_p2.x > p.x && quad1_p1.y  < p.y && quad1_p3.y > p.y)
        return true;
    return false;
}

bool testarColisao() {
    return (pontoDentroQuadrado(quad2_p1) || pontoDentroQuadrado(quad2_p2) ||
                pontoDentroQuadrado(quad2_p3) || pontoDentroQuadrado(quad2_p4));
}

void AtualizarPosicao() {
    
    int alteracaoX = 0, alteracaoY = 0;
    
    if(down == 1) {
        if(quad2_p1.y > 0)
            alteracaoY = -3;
    }
    else if(up == 1) {
        if(quad2_p3.y < ALTURA_JANELA)
            alteracaoY = 3;
    }
    
    if(left == 1) {
        if(quad2_p1.x > 0)
            alteracaoX = -3;
    }
    else if(right == 1) {
        if(quad2_p2.x < LARGURA_JANELA)
            alteracaoX = 3;
    }
    
    quad2_p1.x += alteracaoX;
    quad2_p2.x += alteracaoX;
    quad2_p3.x += alteracaoX;
    quad2_p4.x += alteracaoX;
    
    quad2_p1.y += alteracaoY;
    quad2_p2.y += alteracaoY;
    quad2_p3.y += alteracaoY;
    quad2_p4.y += alteracaoY;
    
    glutPostRedisplay();
}

bool parar;
int minimo = 1, batidas = 0;

void AtuaQuadAutomatico(int i) {
    
    parar = testarColisao();
    
    if(quad1_p1.x <= 0 && xIncre < 0) {
        xIncre = (rand()%5)+minimo;
        batidas++;
    }
    else if(quad1_p2.x >= LARGURA_JANELA && xIncre > 0) {
        xIncre = -((rand()%5)+minimo);
        batidas++;
    }
    
    if(quad1_p3.y >= ALTURA_JANELA && yIncre > 0) {
        yIncre = -((rand()%5)+minimo);
        batidas++;
    }
    else if (quad1_p1.y <= 0 && yIncre < 0) {
        yIncre = (rand()%5)+minimo;
        batidas++;
    }
    
    if(batidas >= 3) {
        batidas = 0;
        minimo++;
    }

    AtualizarPosicao();
    
    quad1_p1.x += xIncre;
    quad1_p2.x += xIncre;
    quad1_p3.x += xIncre;
    quad1_p4.x += xIncre;
    
    quad1_p1.y += yIncre;
    quad1_p2.y += yIncre;
    quad1_p3.y += yIncre;
    quad1_p4.y += yIncre;
    
    glutPostRedisplay();
    
    tempo++;
    
    if(!parar)
        glutTimerFunc(LOOP_TIME, AtuaQuadAutomatico, 0);
}

void desenharQuadrado(void) {
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
                   
     // Limpa a janela de visualização com a cor de fundo especificada
     glClear(GL_COLOR_BUFFER_BIT);

     // Especifica que a cor corrente é vermelha
     //         R     G     B
     glColor3f(1.0f, 0.0f, 0.0f);

     // Desenha um quadrado preenchido com a cor corrente
     glBegin(GL_QUADS);
               glVertex2i(quad1_p3.x,quad1_p3.y);
               glVertex2i(quad1_p1.x,quad1_p1.y);
               // Esquad1_pecifica que a cor corrente é azul
               glVertex2i(quad1_p2.x,quad1_p2.y);
               glVertex2i(quad1_p4.x,quad1_p4.y);
     glEnd();
     
     //Azul escuro
     glColor3f(0.0f, 0.0f, 0.6f);
     glBegin(GL_QUADS);
               glVertex2i(quad2_p3.x,quad2_p3.y);
               glVertex2i(quad2_p1.x,quad2_p1.y);
               // Esquad2_pecifica que a cor corrente é azul
               glVertex2i(quad2_p2.x,quad2_p2.y);
               glVertex2i(quad2_p4.x,quad2_p4.y);
     glEnd();

    if(parar) {
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2i((LARGURA_JANELA/2)-70, (ALTURA_JANELA/2)-10);
        glColor3i(0, 200, 0);
        
        char *c1 = "Game Over (Pontos = ";
        
        for(int i = 0; i < 11; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c1[i]);
        
        char c2[20];
		_itoa_s(-1, c2, 10);
        
        int size = strlen(c2);
        
        for(int i = 0; i < size; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c2[i]);
        }
        
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ')');
     }
    
     // Executa os comandos OpenGL
     glFlush();
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    desenharQuadrado();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    parar = false;
    xIncre = 1;
    yIncre = 1;
    
    up = 0; down = 0; left = 0; right = 0;
    
    srand(time(NULL));
    
    //Ponto superior esquerdo
    quad1_p1 = criarPonto(30,80);
    //Ponto superior direito
    quad1_p2 = criarPonto(80,80);    
    //Ponto inferior direito
    quad1_p3 = criarPonto(30,130);    
    //Ponto inferior esquerdo
    quad1_p4 = criarPonto(80,130);
    
    //Ponto superior esquerdo
    quad2_p1 = criarPonto(0,0);
    //Ponto superior direito
    quad2_p2 = criarPonto(20,0);    
    //Ponto inferior direito
    quad2_p3 = criarPonto(0,20);    
    //Ponto inferior esquerdo
    quad2_p4 = criarPonto(20,20);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
     // Evita a divisão por zero
     if(h == 0) h = 1;
                           
     // Especifica as dimensões da Viewport
     glViewport(0, 0, w, h);

     // Inicializa o sistema de coordenadas
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     // Estabelece a janela de seleção (left, right, bottom, top)     
     if (w <= h)  {
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h/w);
     }
     else  {
		gluOrtho2D(0.0f, 250.0f*h/w, 0.0f, 250.0f);
     }
}

void SetarTeclaPressionada(int tecla, int x, int y) {
    if(tecla == GLUT_KEY_DOWN) {
        down = 1;
    }
    else if(tecla == GLUT_KEY_UP) {
        up = 1;
    }
    
    if(tecla == GLUT_KEY_LEFT) {
        left = 1;
    }
    else if(tecla == GLUT_KEY_RIGHT) {
        right = 1;
    }
}

void SoltarTecla(int tecla, int x, int y) {
    if(tecla == GLUT_KEY_DOWN)
        down = 0;
    else if(tecla == GLUT_KEY_UP)
        up = 0;
    else if(tecla == GLUT_KEY_LEFT)
        left = 0;
    else if(tecla == GLUT_KEY_RIGHT)
        right = 0;
}


// Programa Principal 
int main(void)
{
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
     glutInitWindowPosition(50, 50);
     glutCreateWindow("Trabalho 1");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     
     /*cadastra a função "CapturarTeclas" para ser chamada sempre
     que uma tecla especial é pressionada (código não ASCII)*/
     glutIgnoreKeyRepeat(GLUT_KEY_DOWN);
     glutIgnoreKeyRepeat(GLUT_KEY_LEFT);
     glutIgnoreKeyRepeat(GLUT_KEY_RIGHT);
     glutIgnoreKeyRepeat(GLUT_KEY_UP);
     glutSpecialFunc(SetarTeclaPressionada);
     glutSpecialUpFunc(SoltarTecla);
     
     /*cadastra a função "AtuaQuadAutomatico" para ser chamada automaticamente
     a cada 30 ms. Esta função é responsável por movimentar o quadrado vermelho
     ao longo da tela.*/
     glutTimerFunc(LOOP_TIME, AtuaQuadAutomatico, 0);
     Inicializa();
     glutMainLoop();
}

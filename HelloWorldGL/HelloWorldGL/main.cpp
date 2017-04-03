#include <GL/glut.h>

//Função callback chamada para fazer o desenho
void displaySquare(void)
{
	//Limpa a janela de visualização
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
		//Define os pontos x, y e z
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();

	//Executa os comandos OpenGL
    glFlush();
}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

	//Define tamanho e posição da janela
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
	
	//Cria janela com label "Hello World"
    glutCreateWindow("Hello World");

	//Chama função Callback
    glutDisplayFunc(displaySquare);

    glutMainLoop();
    return 0;
}
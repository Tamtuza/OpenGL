#include <GL/glut.h>

//Fun��o callback chamada para fazer o desenho
void displaySquare(void)
{
	//Limpa a janela de visualiza��o
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

	//Define tamanho e posi��o da janela
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
	
	//Cria janela com label "Hello World"
    glutCreateWindow("Hello World");

	//Chama fun��o Callback
    glutDisplayFunc(displaySquare);

    glutMainLoop();
    return 0;
}
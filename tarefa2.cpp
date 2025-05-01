#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

bool desenha = false;
bool apaga = false;
GLint cordx = 0;
GLint cordy = 0;

void display();
void displayInicial();

void init(void)
{
    // Define a cor de fundo da janela
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Define o sistema de visualização - tipo de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 800, -1, 1);  // Define a área visível (ajustado para a janela)
    glClearColor(1.0, 1.0, 1.0, 1.0);
}



void display()
{

    if (desenha) {
        // Desenha o ponto (representado como um quadrado de 50x50 pixels)
        glBegin(GL_QUADS);
        glColor3f(0, 0, 0);  // Cor preta
        glVertex2f(cordx - 25, cordy - 25);  // Canto inferior esquerdo
        glVertex2f(cordx + 25, cordy - 25);  // Canto inferior direito
        glVertex2f(cordx + 25, cordy + 25);  // Canto superior direito
        glVertex2f(cordx - 25, cordy + 25);  // Canto superior esquerdo
        glEnd();
        
        desenha = false;
    }
    else if (apaga) {
        glClear(GL_COLOR_BUFFER_BIT);  // Limpa a tela ao apertar o botão direito
        apaga = false;
        glutPostRedisplay();
    }

    glFlush();  // Força a renderização imediata
}

void reshape(int w, int h)
{
    // Ajusta a projeção ao redimensionar a janela
    glViewport(0, 0, w, h);  // Define a nova área de exibição
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);  // Ajusta a projeção de acordo com a nova largura e altura
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    y = windowHeight - y;  // Inverte a coordenada Y para ficar no sistema OpenGL

    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                desenha = true;
                cordx = x;
                cordy = y;
            }
            break;

        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                apaga = true;
            }
            break;

        default:
            break;
    }

    display();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Desenhando Ponto");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);  // Registra a função de redimensionamento
    glutMouseFunc(mouse);  // Registra a função de clique do mouse

    glutMainLoop();
    return 0;
}

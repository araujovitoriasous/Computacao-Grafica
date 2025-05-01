#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

void init(void)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-1, 1, -1, 1, -1, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 1);
    glVertex3f(-0.5, -0.5, 0);
    glColor3f(0.5, 0.5, 1);
    glVertex3f(0.5, -0.5, 0);
    glColor3f(0.5, 0.5, 1);
    glVertex3f(0.5, 0.4, 0);
    glColor3f(0.5, 0.5, 1);
    glVertex3f(-0.5, 0.4, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1,0 , 0);
    glVertex3f(-0.5, 0.4, 0);
    glColor3f(1, 0, 0);
    glVertex3f(0.5, 0.4, 0);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0.75, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-0.2, -0.48, 0);
    glColor3f(1, 1, 1);
    glVertex3f(0.2, -0.48, 0);
    glColor3f(1, 1, 1);
    glVertex3f(0.2, 0.3, 0);
    glColor3f(1, 1, 1);
    glVertex3f(-0.2, 0.3, 0);
    glEnd();

    glFlush();

}

void mouse(GLint x, GLint y)
{
  std::cout<<"Movendo mouse sem clicar para posicao (x:"<<x<<", y:"<<y<<")\n";
}

void mouse_test3(GLint x, GLint y)
{
  std::cout<<"Arrastando o mouse para posicao (x:"<<x<<", y:"<<y<<")\n";
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':
            glClearColor(0.0,0.0,0.0,1.0);
            break;
        default:
            glClearColor(1.0,1.0,1.0,1.0);
            break;
    }
    display();
}

int main (int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (200, 200);
    glutCreateWindow ("Casa");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    //glutPassiveMotionFunc(mouse);
    glutMainLoop();
    return 0;

}


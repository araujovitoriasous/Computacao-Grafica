
#include <GL/glut.h>
#include <cmath>
#include <ctime>


void init(void);
void display(void);
double PI =3.14159;

int frameNumber=0;
int dx=0;
int dxAnterior=0;
int frameIncialObjeto=0;

void Teclado( unsigned char key, int x, int y )
{
	switch( key ) {
	case 'd':case 'D':
        dxAnterior = dx;
		dx+=1;
	break;

	case 'a' : case 'A' :
        dxAnterior = dx;
        dx-=1;

	break;
	}
}

void init(void)
{
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-8, 8, -8, 8, -8, 8);
}

void square()
{
      glBegin(GL_POLYGON);
        glVertex3f(-1, -1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(-1, 1, 0);
      glEnd();
}

void triangle() {
      glBegin(GL_LINE_LOOP);
      glVertex3f(-1, 0, 0);
      glVertex3f(0, 1, 0);
      glVertex3f(1, 0, 0);
    glEnd();
}

void Disk(double radius){
    glBegin(GL_POLYGON);
    for (int d=0; d<32;d++){
        double angle = (2*PI/32)*d;
        glVertex3f(radius*cos(angle),radius*sin(angle),0);
    }
    glEnd();
}

void Sol(){
 
    glPushMatrix();
    glScaled(1.5,1.5,1);
    glColor3f(1,1,0);
    glBegin(GL_LINES);
    for (int i=0;i<12;i++)
    {
        float angle = (2*PI/12)*i;
        glVertex3f(0,0,0);
        glVertex3f(cos(angle),sin(angle),0);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    Disk(1);
    glPopMatrix();
}

void Estrada(){

    glPushMatrix();
    glTranslated(0,-1.5,0);
    
    glPushMatrix();
    glScaled(8,1.5,1);
    glColor3f(0.56,0.56,0.56);
    square();
    glPopMatrix();

    
    glPushMatrix();
    glScaled(8,0.2,1);
    glColor3f(1,1,1);
    square();
    glPopMatrix();

    glPopMatrix();
}

void Roda(){
    
    glPushMatrix();
    if (-6+frameNumber/5){
        glRotated((-frameNumber)*2,0,0,1);
        } 
    glColor3f(0,0,0);
    Disk(1);
    
    glPushMatrix();
    glColor3f(0.8,0.8,0.8);
    glScaled(0.8,0.8,1);
    Disk(1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0,0);
    glScaled(0.4,0.4,1);
    Disk(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    for (int i=0;i<12;i++)
    {
        float angle = (2*PI/12)*i;
        glVertex3f(0,0,0);
        glVertex3f(cos(angle),sin(angle),0);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

void Roda2(){
    
    glPushMatrix();
    if (-6+frameNumber/5){
        glRotated((frameNumber)*2,0,0,1);
        } 
    glColor3f(0,0,0);
    Disk(1);
    
    glPushMatrix();
    glColor3f(0.8,0.8,0.8);
    glScaled(0.8,0.8,1);
    Disk(1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0,0);
    glScaled(0.4,0.4,1);
    Disk(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    for (int i=0;i<12;i++)
    {
        float angle = (2*PI/12)*i;
        glVertex3f(0,0,0);
        glVertex3f(cos(angle),sin(angle),0);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

void Elice(){
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0.5,-0.1,0);
    glVertex3f(1.5,0,0);
    glVertex3f(0.5,0.1,0);
    glEnd();
    glPopMatrix();

}

void WindMill(){
    glPushMatrix();

    glColor3f(0.9,0.9,0.9);
    glTranslated(0,1.5,0);
    glScaled(0.05,1.5,1);
    square();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,3,0);

    glPushMatrix();
    glRotated((frameNumber)/5,0,0,1);

    glPushMatrix();
    glRotated(75,0,0,1);
    Elice();
    glPopMatrix();

    
    
    glPushMatrix();
    glRotated(195,0,0,1);
    Elice();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(315,0,0,1);
    Elice();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

void DesenhaCarro(){

    //RODA ESQUERDA
    glPushMatrix();
    glTranslated(-1, 0.4, 0);
    glScaled(0.4 , 0.4, 1);
    Roda();
    glPopMatrix();

    // RODA DIREITA
    glPushMatrix();
    glTranslated(1, 0.4, 0);
    glScaled(0.4 , 0.4, 1);
    Roda();
    glPopMatrix();

    // CORPO DO CARRO
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslated(0,0.7,0);
    glScaled(1.8,0.3,1);
    square();
    glPopMatrix();

    // TETO DO CARRO
    glPushMatrix();
    glTranslated(-0.5,1.25,0);
    glScaled(0.5,0.25,1);
    glColor3f(1, 0, 0);
    square();
    glPopMatrix();

}

void DesenhaCarro2(){

    //RODA ESQUERDA
    glPushMatrix();
    glTranslated(-1, 0.4, 0);
    glScaled(0.4 , 0.4, 1);
    Roda2();
    glPopMatrix();

    // RODA DIREITA
    glPushMatrix();
    glTranslated(1, 0.4, 0);
    glScaled(0.4 , 0.4, 1);
    Roda2();
    glPopMatrix();

    // CORPO DO CARRO
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslated(0,0.7,0);
    glScaled(1.8,0.3,1);
    square();
    glPopMatrix();

    // TETO DO CARRO
    glPushMatrix();
    glTranslated(0.5,1.25,0);
    glScaled(0.5,0.25,1);
    glColor3f(1, 0, 0);
    square();
    glPopMatrix();

}

void Fundo1 (){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0,0.5,0);
    glVertex3f(-8,-8,0);
    glVertex3f(8,-8,0);
    glVertex3f(8,2,0);

    glVertex3f(6,3,0);
    glVertex3f(2,2,0);
    glVertex3f(-2,6,0);
    glVertex3f(-4,3,0);
    glVertex3f(-6,4,0);
    

    glVertex3f(-8,1,0);
    glEnd();
    glPopMatrix();
}
void Fundo (){
    glPushMatrix();
    glScaled(8,8,1);
    glColor3f(0,0,0.3);
    square();
    glPopMatrix();
}

void display() {

  // Limpa a janela, colocando na tela a cor definida pela função glClearColor
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();

    glColor3f(0, 0, 0);
    glLoadIdentity();

    Fundo();
    Fundo1();

    glPushMatrix();
    glTranslated(1, 2, 0);
    WindMill();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3, 3, 0);
    glScaled(0.6,0.6,1);
    WindMill();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6, 2.8, 0);
    glScaled(0.9,0.9,1);
    WindMill();
    glPopMatrix();

    Estrada();

    glPushMatrix();
    if (-6+dx <= 6 && -6+dx >= -6){
    glTranslated(-6+dx, -2, 0);
    } else {
        glTranslated(6,-2,0);
    }
    if (dxAnterior > dx){
        DesenhaCarro2();
    } else {
        DesenhaCarro();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(5,6,0);
    glRotated((-frameNumber)/4,0,0,1);
    Sol();
    glPopMatrix();
    srand(time(NULL));
    int v1 = rand()%20;
    int v2 = rand();
   if (v1%3==0 || (frameNumber -frameIncialObjeto < 20 )){
        frameIncialObjeto = frameNumber;
        glPushMatrix();
        glTranslated(v2%16-8,-1.5,0);
        glColor3f(0,0,1);
        square();
        glPopMatrix();
   }


 // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
  glFlush();
}

void Frame(int v){
    frameNumber++;
    display();
    glutTimerFunc(20,Frame,0);

}


int main(int argc, char** argv)
{

 //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
 //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  glutInitDisplayMode (GLUT_RGB|GLUT_SINGLE);

  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize (800, 800);
  glutInitWindowPosition (0, 0);
  

  // Cria uma janela e define seu título
  glutCreateWindow ("Estrada");

  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();

  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
 
  glutDisplayFunc(display);
  glutTimerFunc(20,Frame,0);
  glutKeyboardFunc(Teclado);

  //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}

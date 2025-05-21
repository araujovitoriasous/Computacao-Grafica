//parametrizar movimento do pinguim, movimento pautado na posicao atual
//parametrizar movimento dos peixes, movimento pautado na posicao atual
//parametrizar movimento dos petrel, movimento pautado na posicao atual
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

double proximo_passo_direita_x();
double proximo_passo_esquerda_x();
double rasante(double a, double h, double k, double x);
bool PINGUIM_FRENTE();
bool PINGUIM_NO_LAGO_TRAS();
bool PINGUIM_NO_VERDE();

#pragma region Variaveis Globais
int _5minutos = 15000;
int _1minuto = 3000;
double PI = 3.14159;
int frameNumber = 0;
int cronometroPinguimFilhote = 0;
double lago_X0 = -1;
double lago_X1 = 7;
double lago_Y0 = 0.1;
double lago_Y1 = -6.6;
bool perdeu = false;
double verde_X0 = -8;
double verde_X1 = -1;
int conta_peixes = 0;
#pragma endregion

#pragma region Variaveis Petrel
bool direcao_esquerda = false;
int framePetrel = 0;
double velocidade_petrel = 0.1;
double petrel_x = -7;
double petrel_y = 5;
double altura_rasante;
double ponto_rasante;
bool no_rasante = false;
double a, verticeX, verticeY;
int petrel_limite_direita = 7;
int petrel_limite_esquerda = -7;
double posX = -7;
double posY = 5;
#pragma endregion

#pragma region Variaveis Peixes
double velocidade_peixe = 0.02;
bool peixeCapturado[4] = {true, true, true, true};
double peixeX[4];
double peixeY[4];
bool esquerda[4] = {false, false, false, false};
bool direita[4] = {false, false, false, false};
bool peixe_virou[4] = {false, false, false, false};
bool peixeDirecaoInicial[4];
int dxPeixe[4] = {0, 0, 0, 0};
double posicaoPeixeX[4] = {0, 0, 0, 0};
double cabeçaPeixe;
double caudaPeixe;
double barrigaPeixe;
double costaPeixe;
#pragma endregion

#pragma region Variaveis Pinguim
int dx = 0;
int dy = 0;
bool tras = false;
int dxAnterior = 0;
int dyAnterior = 0;
double cabecaPinguim;
double pataPinguim;
double barrigaPinguim;
double costaPinguim;
bool pegouPeixe = false;
double posicao_filhote = -7.5;
double posicao_inicial_pinguimX = -6.9;
double posicao_inicial_pinguimY = 0.1;
double barrigaPinguim_Inicial = -6.6;
double posicaoPinguimX = posicao_inicial_pinguimX;
double posicaoPinguimY = posicao_inicial_pinguimY;
bool pinguim_Mergulhou = false;
double velocidade_pinguim = 0.5;
#pragma endregion
void A() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 0.0);
  glVertex2f(0.0, 1.0);

  glVertex2f(0.5, 0.0);
  glVertex2f(0.0, 1.0);

  glVertex2f(-0.25, 0.5);
  glVertex2f(0.25, 0.5);

  glEnd();

  glPopMatrix();
}

void C() {
  glPushMatrix();

  glBegin(GL_LINE_STRIP);

  glVertex2f(0.4, 0.9);
  glVertex2f(-0.5, 0.9);

  glVertex2f(-0.5, 0.1);
  glVertex2f(0.4, 0.1);

  glEnd();

  glPopMatrix();
}

void D() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 0.0);
  glVertex2f(-0.5, 1.0);

  glVertex2f(-0.5, 1.0);
  glVertex2f(0.3, 0.85);

  glVertex2f(0.3, 0.85);
  glVertex2f(0.3, 0.15);

  glVertex2f(0.3, 0.15);
  glVertex2f(-0.5, 0.0);

  glEnd();

  glPopMatrix();
}

void E() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 1.0);
  glVertex2f(0.4, 1.0);

  glVertex2f(-0.5, 0.5);
  glVertex2f(0.4, 0.5);

  glVertex2f(-0.5, 0.0);
  glVertex2f(0.4, 0.0);

  glVertex2f(-0.5, 1.0);
  glVertex2f(-0.5, 0.0);

  glEnd();

  glPopMatrix();
}

void G() {
  glPushMatrix();

  glBegin(GL_LINE_STRIP);

  glVertex2f(0.4, 0.9);
  glVertex2f(-0.5, 0.9);

  glVertex2f(-0.5, 0.1);
  glVertex2f(0.4, 0.1);

  glVertex2f(0.4, 0.1);
  glVertex2f(0.4, 0.5);

  glVertex2f(0.4, 0.5);
  glVertex2f(0.0, 0.5);

  glEnd();

  glPopMatrix();
}

void H() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 0.0);
  glVertex2f(-0.5, 1.0);

  glVertex2f(0.5, 0.0);
  glVertex2f(0.5, 1.0);

  glVertex2f(-0.5, 0.5);
  glVertex2f(0.5, 0.5);

  glEnd();

  glPopMatrix();
}

void N() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 0.0);
  glVertex2f(-0.5, 1.0);

  glVertex2f(-0.5, 1.0);
  glVertex2f(0.5, 0.0);

  glVertex2f(0.5, 0.0);
  glVertex2f(0.5, 1.0);

  glEnd();

  glPopMatrix();
}

void O() {
  glPushMatrix();

  glBegin(GL_LINE_LOOP);

  glVertex2f(-0.5, 0.1);
  glVertex2f(-0.5, 0.9);

  glVertex2f(0.5, 0.9);
  glVertex2f(0.5, 0.1);

  glEnd();

  glPopMatrix();
}

void P() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 0.0);
  glVertex2f(-0.5, 1.0);

  glVertex2f(-0.5, 1.0);
  glVertex2f(0.4, 1.0);

  glVertex2f(0.4, 1.0);
  glVertex2f(0.4, 0.5);

  glVertex2f(0.4, 0.5);
  glVertex2f(-0.5, 0.5);

  glEnd();

  glPopMatrix();
}

void R() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 0.0);
  glVertex2f(-0.5, 1.0);

  glVertex2f(-0.5, 1.0);
  glVertex2f(0.4, 1.0);

  glVertex2f(0.4, 1.0);
  glVertex2f(0.4, 0.5);

  glVertex2f(0.4, 0.5);
  glVertex2f(-0.5, 0.5);

  glVertex2f(-0.5, 0.5);
  glVertex2f(0.5, 0.0);

  glEnd();

  glPopMatrix();
}

void T() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 1.0);

  glVertex2f(-0.5, 1.0);
  glVertex2f(0.5, 1.0);

  glEnd();

  glPopMatrix();
}

void U() {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(-0.5, 1.0);
  glVertex2f(-0.5, 0.1);

  glVertex2f(-0.5, 0.1);
  glVertex2f(0.5, 0.1);

  glVertex2f(0.5, 0.1);
  glVertex2f(0.5, 1.0);

  glEnd();

  glPopMatrix();
}

void zero()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(-0.5,0,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,1,0);

  glEnd();
  glPopMatrix();

}

void um()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0,0,0);
  glVertex3f(0,2,0);
  glVertex3f(0,2,0);
  glVertex3f(-0.5,1,0);
  glEnd();
  glPopMatrix();

}

void dois()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(-0.5,0,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(-0.5,2,0);
  glEnd();
  glPopMatrix();

}

void tres()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(-0.5,2,0);
  glEnd();
  glPopMatrix();

}

void quatro()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,2,0);
  glEnd();
  glPopMatrix();

}

void cinco()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(0.5,2,0);
  glEnd();
  glPopMatrix();

}

void seis()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(-0.5,0,0);
  glVertex3f(-0.5,1,0);

  glEnd();
  glPopMatrix();

}

void sete()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(-0.5,2,0);
  glEnd();
  glPopMatrix();

}

void oito()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(-0.5,0,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,1,0);

  glEnd();
  glPopMatrix();

}

void nove()
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(-0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,0,0);
  glVertex3f(0.5,1,0);
  glVertex3f(0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,1,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(-0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,2,0);
  glVertex3f(0.5,1,0);

  glEnd();
  glPopMatrix();

}

void impreme_pontuacao()
{
  int dezena, resto_dezena, unidade;
  dezena = conta_peixes/10;
  resto_dezena = conta_peixes%10;
  unidade = resto_dezena;
  
  switch (dezena)
  {
    case 1:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    um();
    glPopMatrix();
      break;
    case 2:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    dois();
    glPopMatrix();
      break;
    case 3:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    tres();
    glPopMatrix();
      break;
    case 4:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    quatro();
    glPopMatrix();
      break;
    case 5:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    cinco();
    glPopMatrix();
      break;
    case 6:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    seis();
    glPopMatrix();
      break;
    case 7:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    sete();
    glPopMatrix();
      break;
    case 8:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    oito();
    glPopMatrix();
      break;
    case 9:
    glPushMatrix();
    glTranslated(6,7,0);
    glScaled(0.2,0.2,1);
    nove();
    glPopMatrix();
      break;
  }

  switch (unidade)
  {
    case 0:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    zero();
    glPopMatrix();
      break;
    case 1:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    um();
    glPopMatrix();
      break;
    case 2:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    dois();
    glPopMatrix();
      break;
    case 3:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    tres();
    glPopMatrix();
      break;
    case 4:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    quatro();
    glPopMatrix();
      break;
    case 5:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    cinco();
    glPopMatrix();
      break;
    case 6:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    seis();
    glPopMatrix();
      break;
    case 7:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    sete();
    glPopMatrix();
      break;
    case 8:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    oito();
    glPopMatrix();
      break;
    case 9:
    glPushMatrix();
    glTranslated(6.5,7,0);
    glScaled(0.2,0.2,1);
    nove();
    glPopMatrix();
      break;
  }
}

bool petrel_atinge()
{
  if (!PINGUIM_NO_LAGO_TRAS() && PINGUIM_NO_VERDE())
  {
    if (PINGUIM_FRENTE())
    {
      return posY <= cabecaPinguim && posX >= costaPinguim && posX <= barrigaPinguim;
    }
    else
    {
      return posY <= cabecaPinguim && posX >= barrigaPinguim && posX <= costaPinguim;
    }
  }
  return false;
}

void movimento_padrao_petrel()
{
  if (!direcao_esquerda)
  {
    if (proximo_passo_direita_x() <= petrel_limite_direita)
    {
      posX = proximo_passo_direita_x();
      posY = petrel_y;
    }
    else
    {
      petrel_x = petrel_limite_direita;
      framePetrel = 0;
      posX = proximo_passo_esquerda_x();
      posY = petrel_y;
      direcao_esquerda = true;
    }
  }
  else
  {
    if (proximo_passo_esquerda_x() >= petrel_limite_esquerda)
    {
      posX = proximo_passo_esquerda_x();
      posY = petrel_y;
    }
    else
    {
      petrel_x = petrel_limite_esquerda;
      framePetrel = 0;
      posX = proximo_passo_direita_x();
      posY = petrel_y;
      direcao_esquerda = false;
    }
  }
}

void procura_ponto_rasante()
{
  if (!direcao_esquerda)
  {
    for (double i = petrel_limite_esquerda; i < petrel_limite_direita; i = i + 0.1)
    {
      if (rasante(a, verticeX, verticeY, i) <= petrel_y)
      {
        ponto_rasante = i;
        return;
      }
    }
  }
  else
  {
    for (double i = petrel_limite_direita; i > petrel_limite_esquerda; i = i - 0.1)
    {
      if (rasante(a, verticeX, verticeY, i) <= petrel_y)
      {
        ponto_rasante = i;
        return;
      }
    }
  }
}

double proximo_passo_direita_x()
{
  return petrel_x + framePetrel * velocidade_petrel;
}

double proximo_passo_esquerda_x()
{
  return petrel_x - framePetrel * velocidade_petrel;
}

bool comecando_rasante()
{
  if (no_rasante)
  {
    return false;
  }
  else
  {
    if (!direcao_esquerda && petrel_x == petrel_limite_esquerda)
    {
      no_rasante = true;
      petrel_x = posX;
      petrel_y = posY;
      framePetrel = 0;
      a = (double)rand() / RAND_MAX;
      do
      {
        verticeX = ((double)rand() / RAND_MAX) * 7;
        verticeY = ((double)rand() / RAND_MAX) * 2;
        altura_rasante = ((double)rand() / RAND_MAX) * 6;
        procura_ponto_rasante();
      } while (verticeX > petrel_limite_direita || altura_rasante < verticeY + 1 || altura_rasante < 3 || ponto_rasante < petrel_x || rasante(a, verticeX, verticeY, petrel_limite_direita) < 2);
      return true;
    }
    else if (direcao_esquerda && petrel_x == petrel_limite_direita)
    {
      no_rasante = true;
      petrel_x = posX;
      petrel_y = posY;
      framePetrel = 0;
      a = (float)rand() / RAND_MAX;
      do
      {
        verticeX = ((double)rand() / RAND_MAX) * -7;
        verticeY = ((double)rand() / RAND_MAX) * 2;
        altura_rasante = ((double)rand() / RAND_MAX) * 6;
        procura_ponto_rasante();
      } while (verticeX < petrel_limite_esquerda || altura_rasante < verticeY + 1 || altura_rasante < 3 || ponto_rasante > petrel_x || rasante(a, verticeX, verticeY, petrel_limite_esquerda) < 2);
      // cout << (rasante(a, verticeX, verticeY, 7) < 2) << endl;
      return true;
    }
    return false;
  }
}

bool testeCapturaFrente()
{
  bool encontroCosta = (barrigaPinguim <= costaPeixe && barrigaPinguim >= barrigaPeixe);
  bool encontroBarriga = (costaPinguim >= barrigaPeixe && costaPinguim <= costaPeixe);
  bool encontroCabeca = (cabecaPinguim >= cabeçaPeixe && pataPinguim <= cabeçaPeixe) && ((barrigaPinguim <= barrigaPeixe && costaPinguim >= costaPeixe) || encontroCosta || encontroBarriga);
  bool encontroCauda = (cabecaPinguim >= caudaPeixe && pataPinguim <= caudaPeixe) && ((barrigaPinguim <= barrigaPeixe && costaPinguim >= costaPeixe) || encontroCosta || encontroBarriga);
  return (encontroCabeca || encontroCauda);
}

bool testeCapturaTras()
{
  bool encontroCosta = (barrigaPinguim <= costaPeixe && barrigaPinguim >= barrigaPeixe);
  bool encontroBarriga = (costaPinguim >= barrigaPeixe && costaPinguim <= costaPeixe);
  bool encontroCabeca = (cabecaPinguim <= cabeçaPeixe && pataPinguim >= cabeçaPeixe) && ((barrigaPinguim <= barrigaPeixe && costaPinguim >= costaPeixe) || encontroCosta || encontroBarriga);
  bool encontroCauda = (cabecaPinguim <= caudaPeixe && pataPinguim >= caudaPeixe) && ((barrigaPinguim <= barrigaPeixe && costaPinguim >= costaPeixe) || encontroCosta || encontroBarriga);
  return (encontroCabeca || encontroCauda);
}

void Teclado(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'd':
  case 'D':
    tras = false;
    dx += 1;
    break;

  case 'a':
  case 'A':
    tras = true;
    dx -= 1;
    break;

  case 'w':
  case 'W':
    dy += 1;
    break;

  case 's':
  case 'S':
    dy -= 1;
    break;
  }
}

bool Troca_Direita(double pos, int i)
{
  if (pos <= lago_X0 + 0.5)
  {
    direita[i] = true;
    esquerda[i] = false;
    dxPeixe[i] = 0;
    peixe_virou[i] = true;
  }
  return direita[i];
}

bool Troca_Esquerda(double pos, int i)
{
  if (pos >= lago_X1 - 0.5)
  {
    direita[i] = false;
    esquerda[i] = true;
    dxPeixe[i] = 0;
    peixe_virou[i] = true;
  }
  return esquerda[i];
}

void init(void)
{
  // define a cor de background da janela
  glClearColor(0.6784, 0.8471, 0.902, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8, 8, -8, 8, -8, 8);
}

double funcao_quadratica(double a, double b, double c, double x)
{
  return a * x * x + b * x + c;
}

void petrel()
{
  glPushMatrix();
  glLineWidth(5);
  glBegin(GL_LINES);
  glColor3f(1, 0.4353, 0.6118);
  for (double i = 1.2; i >= 0.01; i = i - 0.01)
  {
    glVertex3f(i - 0.01, funcao_quadratica(-1, 2, 0, i), 0);
    glVertex3f(i, funcao_quadratica(-1, 2, 0, i), 0);
  }
  glEnd();
  glBegin(GL_LINES);
  for (double i = 0.01; i >= -1.2; i = i - 0.01)
  {
    glVertex3f(i - 0.01, funcao_quadratica(-1, -2, 0, i), 0);
    glVertex3f(i, funcao_quadratica(-1, -2, 0, i), 0);
  }
  glEnd();
  glPopMatrix();
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

void triangle()
{
  glBegin(GL_POLYGON);
  glVertex3f(-1, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(1, 0, 0);
  glEnd();
}

void Disk(double radius)
{
  glBegin(GL_POLYGON);
  for (int d = 0; d < 32; d++)
  {
    double angle = (2 * PI / 32) * d;
    glVertex3f(radius * cos(angle), radius * sin(angle), 0);
  }
  glEnd();
}

void Pinguim()
{
  // BICO
  glPushMatrix();
  glTranslated(0.45, 1.3, 0);
  glScaled(0.3, 0.1, 1);
  glColor3f(1, 1, 0);
  glRotated(110, 0, 0, 1);
  triangle();
  glPopMatrix();

  // CABEÇA
  glPushMatrix();
  glTranslated(0, 1.5, 0);
  glScaled(0.35, 0.35, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // CORPO
  glPushMatrix();
  glTranslated(0, 0.4, 0);
  glScaled(0.5, 0.8, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // PELO BRANCO
  glPushMatrix();
  glTranslated(0.25, 0.45, 0);
  glScaled(0.2, 0.55, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // OLHO
  glPushMatrix();
  glTranslated(0.2, 1.5, 0);
  glScaled(0.1, 0.1, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // PATA1
  glPushMatrix();
  glTranslated(-0.2, -0.7, 0);
  glScaled(0.1, 0.3, 1);
  glColor3f(0.702, 0.1294, 0.2039);
  triangle();
  glPopMatrix();

  // PATA2
  glPushMatrix();
  glTranslated(0.2, -0.7, 0);
  glScaled(0.1, 0.3, 1);
  glColor3f(0.702, 0.1294, 0.2039);
  triangle();
  glPopMatrix();
}

void Pinguim_Contrario()
{
  // BICO
  glPushMatrix();
  glTranslated(-0.45, 1.3, 0);
  glScaled(0.3, 0.1, 1);
  glColor3f(1, 1, 0);
  glRotated(-110, 0, 0, 1);
  triangle();
  glPopMatrix();

  // CABEÇA
  glPushMatrix();
  glTranslated(0, 1.5, 0);
  glScaled(0.35, 0.35, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // CORPO
  glPushMatrix();
  glTranslated(0, 0.4, 0);
  glScaled(0.5, 0.8, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // PELO BRANCO
  glPushMatrix();
  glTranslated(-0.25, 0.45, 0);
  glScaled(0.2, 0.55, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // OLHO
  glPushMatrix();
  glTranslated(-0.2, 1.5, 0);
  glScaled(0.1, 0.1, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // PATA1
  glPushMatrix();
  glTranslated(0.2, -0.7, 0);
  glScaled(0.1, 0.3, 1);
  glColor3f(0.702, 0.1294, 0.2039);
  triangle();
  glPopMatrix();

  // PATA2
  glPushMatrix();
  glTranslated(-0.2, -0.7, 0);
  glScaled(0.1, 0.3, 1);
  glColor3f(0.702, 0.1294, 0.2039);
  triangle();
  glPopMatrix();
}

void Pinguim_Filhote()
{
  glPushMatrix();
  glScaled(0.5, 0.5, 1);
  glTranslated(1, -0.8, 0);

  // BICO
  glPushMatrix();
  glTranslated(1.45, 1.3, 0);
  glScaled(0.3, 0.1, 1);
  glColor3f(1, 1, 0);
  glRotated(110, 0, 0, 1);
  triangle();
  glPopMatrix();

  // CABEÇA
  glPushMatrix();
  glTranslated(1, 1.5, 0);
  glScaled(0.35, 0.35, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // OLHO
  glPushMatrix();
  glTranslated(1.2, 1.5, 0);
  glScaled(0.1, 0.1, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  glPopMatrix();

  // CORPO
  glPushMatrix();
  glTranslated(1, -0.2, 0);
  glScaled(0.3, 0.4, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // PELO BRANCO
  glPushMatrix();
  glTranslated(1.1, -0.2, 0);
  glScaled(0.15, 0.3, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // PATA1
  glPushMatrix();
  glTranslated(0.9, -0.7, 0);
  glScaled(0.1, 0.1, 1);
  glColor3f(0, 0, 0);
  triangle();
  glPopMatrix();

  // PATA2
  glPushMatrix();
  glTranslated(1.1, -0.7, 0);
  glScaled(0.1, 0.1, 1);
  glColor3f(0, 0, 0);
  triangle();
  glPopMatrix();
}

void Peixe()
{
  glPushMatrix();
  glLineWidth(3);
  glBegin(GL_LINE_LOOP);
  for (double i = 2.5; i >= -2; i = i - 0.1)
  {
    glVertex3f(i, funcao_quadratica(0.3, 0, -1, i), 0);
  }
  for (double i = -2; i <= 2.5; i = i + 0.1)
  {
    glVertex3f(i, funcao_quadratica(-0.3, 0, 1, i), 0);
  }
  glEnd();
  glPopMatrix();
}

bool PINGUIM_FRENTE()
{
  return !tras;
}

bool PINGUIM_NO_LAGO_FRENTE()
{
  if (PINGUIM_FRENTE())
  {
    if ((-7.5 + dx * velocidade_pinguim >= lago_X0 && -7.5 + dx * velocidade_pinguim <= lago_X1 - 2) && (0.1 + dy * velocidade_pinguim >= lago_Y1 + 0.8 && 0.1 + dy * velocidade_pinguim <= lago_Y0))
    {
      dxAnterior = dx;
      dyAnterior = dy;
      return true;
    }

    if ((-7.5 + dx * velocidade_pinguim < lago_X0 && -7.5 + dx * velocidade_pinguim < lago_X1 - 2 && 0.1 + dy * velocidade_pinguim >= lago_Y0))
    {
      pinguim_Mergulhou = false;
      dxAnterior = dx;
      dy = posicao_inicial_pinguimY;
      return false;
    }
    dx = dxAnterior;
    dy = dyAnterior;
    return true;
  }
  return false;
}

bool PINGUIM_NO_LAGO_TRAS()
{
  if (!PINGUIM_FRENTE())
  {
    if ((-5.6 + dx * velocidade_pinguim >= 0 && -5.6 + dx * velocidade_pinguim <= 7) && (-1.1 + dy * velocidade_pinguim >= -7 && -1.1 + dy * velocidade_pinguim <= -1))
    {
      dxAnterior = dx;
      dyAnterior = dy;
      return true;
    }

    if ((-5.6 + dx * velocidade_pinguim < -1) && (-5.6 + dx * velocidade_pinguim > -0.3) && (-1.1 + dy * velocidade_pinguim == -1.1))
    {
      dxAnterior = dx;
      dyAnterior = dy;
      pinguim_Mergulhou = false;
      return true;
    }

    if ((-5.6 + dx * velocidade_pinguim < 0) && (-1.1 + dy * velocidade_pinguim == -1.1))
    {
      pinguim_Mergulhou = false;
      return false;
    }

    if ((-7.5 + dx * 0.5 <= -2) && ((-1.1 + dyAnterior * 0.25 == -1.1)))
    {
      pinguim_Mergulhou = false;
      return false;
    }

    dx = dxAnterior;
    dy = dyAnterior;
    return true;
  }

  return false;
}

bool PINGUIM_NO_VERDE()
{
  if ((-7.5 + dx * velocidade_pinguim < lago_X0 && -7.5 + dx * velocidade_pinguim >= posicao_filhote) && !pinguim_Mergulhou)
  {
    dy = 0;
    dyAnterior = 0;
    dxAnterior = dx;
    return true;
  }

  if (-7.5 + dx * velocidade_pinguim <= posicao_filhote)
  {
    dy = dyAnterior;
    dx = dxAnterior;
    return true;
  }

  return false;
}

void CapturaPeixe(int i)
{
  if (!pegouPeixe && !PINGUIM_NO_VERDE())
  {
    if (PINGUIM_FRENTE())
    {
      if (testeCapturaFrente())
      {
        peixeCapturado[i] = true;
        pegouPeixe = true;
      }
    }
    else
    {
      if (testeCapturaTras())
      {
        peixeCapturado[i] = true;
        pegouPeixe = true;
      }
    }
  }
}

double rasante(double a, double h, double k, double x)
{
  return a * x * x - 2 * a * x * h + a * h * h + k;
}

double proximo_movimento_pinguim_x()
{
  return posicaoPinguimX + dx*velocidade_pinguim;
}

void display()
{
  srand((unsigned)time(NULL));
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if ((frameNumber <= _5minutos) && (cronometroPinguimFilhote <= _1minuto) && !perdeu)
  {
    // Limpa a janela, colocando na tela a cor definida pela função glClearColor
    // QUADRADO VERDE
    glPushMatrix();
    glTranslated(-5, -3.5, 0);
    glScaled(4, 3.2, 1);
    glColor3f(0, 1, 0);
    square();
    glPopMatrix();

    // QUADRADO AZUL
    glPushMatrix();
    glTranslated(3, -3.5, 0);
    glScaled(4, 3.2, 1);
    glColor3f(0, 0, 1);
    square();
    glPopMatrix();

    // PEIXES
    for (int i = 0; i < 4; i++)
    {
      if (peixeCapturado[i])
      {
        peixeDirecaoInicial[i] = rand() % 2;
        peixeX[i] = ((double)rand() / RAND_MAX) * 7;
        peixeY[i] = -0.5 + ((double)rand() / RAND_MAX) * -6;

        bool colisao;
        do
        {
          colisao = false;
          for (int j = 3; j >= 0; j--)
          {
            double barrigaPeixe_j = peixeY[j] - 0.2;
            double costaPeixe_j = peixeY[j] + 0.2;
            barrigaPeixe = peixeY[i] - 0.2;
            costaPeixe = peixeY[i] + 0.2;
            if ((j != i) && ((barrigaPeixe >= barrigaPeixe_j - 0.1 && barrigaPeixe <= costaPeixe_j + 0.1) || (costaPeixe >= barrigaPeixe_j - 0.1 && costaPeixe <= costaPeixe_j + 0.1)))
            {
              peixeY[i] = -0.5 + ((double)rand() / RAND_MAX) * -6;
              colisao = true;
              break;
            }
          }
        } while (colisao);
        glPushMatrix();
        glTranslated(peixeX[i], peixeY[i], 0);
        glScaled(0.2, 0.2, 1);
        glColor3f(1, 0.549, 0);
        Peixe();
        glPopMatrix();
        posicaoPeixeX[i] = peixeX[i];
        dxPeixe[i] = 0;
        direita[i] = false;
        esquerda[i] = false;
        peixeCapturado[i] = false;
        peixe_virou[i] = false;
      }
      else
      {
        dxPeixe[i]++;
        if (!peixe_virou[i])
        {
          if (peixeDirecaoInicial[i] && !Troca_Direita(peixeX[i] - dxPeixe[i] * velocidade_peixe, i))
          {
            posicaoPeixeX[i] = peixeX[i] - dxPeixe[i] * velocidade_peixe;
            glPushMatrix();
            glTranslated(posicaoPeixeX[i], peixeY[i], 0);
            glScaled(0.2, 0.2, 1);
            glColor3f(1, 0.549, 0);
            Peixe();
            glPopMatrix();
            cabeçaPeixe = posicaoPeixeX[i] - 0.5;
            caudaPeixe = posicaoPeixeX[i] + 0.5;
            barrigaPeixe = peixeY[i] - 0.2;
            costaPeixe = peixeY[i] + 0.2;
          }
          else if (!peixeDirecaoInicial[i] && !Troca_Esquerda(peixeX[i] + dxPeixe[i] * velocidade_peixe, i))
          {
            posicaoPeixeX[i] = peixeX[i] + dxPeixe[i] * velocidade_peixe;
            glPushMatrix();
            glTranslated(posicaoPeixeX[i], peixeY[i], 0);
            glScaled(0.2, 0.2, 1);
            glColor3f(1, 0.549, 0);
            glRotated(-180, 0, 0, 1);
            Peixe();
            glPopMatrix();
            cabeçaPeixe = posicaoPeixeX[i] + 0.5;
            caudaPeixe = posicaoPeixeX[i] - 0.5;
            barrigaPeixe = peixeY[i] - 0.2;
            costaPeixe = peixeY[i] + 0.2;
          }
        }
        else
        {
          if (direita[i] && !Troca_Esquerda(-0.5 + dxPeixe[i] * velocidade_peixe, i))
          {
            posicaoPeixeX[i] = -0.5 + dxPeixe[i] * velocidade_peixe;
            glPushMatrix();
            glTranslated(posicaoPeixeX[i], peixeY[i], 0);
            glScaled(0.2, 0.2, 1);
            glColor3f(1, 0.549, 0);
            glRotated(-180, 0, 0, 1);
            Peixe();
            glPopMatrix();
            cabeçaPeixe = posicaoPeixeX[i] - 0.5;
            caudaPeixe = posicaoPeixeX[i] + 0.5;
            barrigaPeixe = peixeY[i] - 0.2;
            costaPeixe = peixeY[i] + 0.2;
          }
          else if (esquerda[i] && !Troca_Direita(6.5 - dxPeixe[i] * velocidade_peixe, i))
          {
            posicaoPeixeX[i] = 6.5 - dxPeixe[i] * velocidade_peixe, peixeY[i], 0;
            glPushMatrix();
            glTranslated(posicaoPeixeX[i], peixeY[i], 0);
            glScaled(0.2, 0.2, 1);
            glColor3f(1, 0.549, 0);
            Peixe();
            glPopMatrix();
            cabeçaPeixe = posicaoPeixeX[i] + 0.5;
            caudaPeixe = posicaoPeixeX[i] - 0.5;
            barrigaPeixe = peixeY[i] - 0.2;
            costaPeixe = peixeY[i] + 0.2;
          }
        }
      }
      CapturaPeixe(i);
    }

    if (!PINGUIM_NO_LAGO_TRAS() && PINGUIM_NO_VERDE())
    {
      pinguim_Mergulhou = false;
      posicaoPinguimX = posicao_inicial_pinguimX + dx * velocidade_pinguim;
      posicaoPinguimY = posicao_inicial_pinguimY;
      glPushMatrix();
      glTranslated(posicaoPinguimX, posicaoPinguimY, 0);

      if (PINGUIM_FRENTE())
      {
        barrigaPinguim = posicaoPinguimX + 0.3;
        pataPinguim = posicaoPinguimY - 0.6;
        cabecaPinguim = posicaoPinguimY + 1.5;
        costaPinguim = posicaoPinguimX - 0.3;

        if (pegouPeixe)
        {
          glPushMatrix();
          glTranslated(0.5, 0.8, 0);
          glRotated(-45, 0, 0, 1);
          glScaled(0.2, 0.2, 1);
          glColor3f(1, 0.549, 0);
          Peixe();
          glPopMatrix();
        }
        glPushMatrix();
        glScaled(0.6, 0.8, 1);
        Pinguim();
        glPopMatrix();
      }
      else
      {
        barrigaPinguim = posicaoPinguimX - 0.3;
        pataPinguim = posicaoPinguimY - 0.6;
        cabecaPinguim = posicaoPinguimY + 1.5;
        costaPinguim = posicaoPinguimX + 0.3;

        if (pegouPeixe)
        {
          glPushMatrix();
          glTranslated(-0.5, 0.8, 0);
          glRotated(225, 0, 0, 1);
          glScaled(0.2, 0.2, 1);
          glColor3f(1, 0.549, 0);
          Peixe();
          glPopMatrix();
        }

        glPushMatrix();
        glScaled(0.6, 0.8, 1);
        Pinguim_Contrario();
        glPopMatrix();
      }
      glPopMatrix();
    }
    else if (PINGUIM_NO_LAGO_FRENTE())
    {
      pinguim_Mergulhou = true;
      posicaoPinguimX = -7 + dx * velocidade_pinguim + 0.4;
      posicaoPinguimY = 0.1 + dy * velocidade_pinguim - 0.6;
      cabecaPinguim = posicaoPinguimX + 1;
      pataPinguim = posicaoPinguimX - 1;
      barrigaPinguim = posicaoPinguimY - 0.4;
      costaPinguim = posicaoPinguimY + 0.4;

      glPushMatrix();
      glTranslated(-7 + dx * velocidade_pinguim, -0.5 + dy * velocidade_pinguim, 0);
      glRotated(-90, 0, 0, 1);
      glTranslated(0, 0, 0);

      if (pegouPeixe)
      {
        glPushMatrix();
        glTranslated(0.5, 0.8, 0);
        glRotated(-45, 0, 0, 1);
        glScaled(0.2, 0.2, 1);
        glColor3f(1, 0.549, 0);
        Peixe();
        glPopMatrix();
      }

      glPushMatrix();
      glScaled(0.6, 0.8, 1);
      Pinguim();
      glPopMatrix();

      glPopMatrix();
    }
    else
    {
      posicaoPinguimX = -5.6 + dx * velocidade_pinguim - 0.4;
      posicaoPinguimY = -0.5 + dy * velocidade_pinguim;
      cabecaPinguim = posicaoPinguimX - 1;
      pataPinguim = posicaoPinguimX + 1;
      barrigaPinguim = posicaoPinguimY - 0.4;
      costaPinguim = posicaoPinguimY + 0.4;
      glPushMatrix();
      glTranslated(-5.6 + dx * velocidade_pinguim, -0.5 + dy * velocidade_pinguim, 0);
      glRotated(90, 0, 0, 1);
      glTranslated(0, 0, 0);

      if (pegouPeixe)
      {
        glPushMatrix();
        glTranslated(-0.5, 0.8, 0);
        glRotated(225, 0, 0, 1);
        glScaled(0.2, 0.2, 1);
        glColor3f(1, 0.549, 0);
        Peixe();
        glPopMatrix();
      }

      glPushMatrix();
      glScaled(0.6, 0.8, 1);
      Pinguim_Contrario();
      glPopMatrix();

      glPopMatrix();
    }

    glPushMatrix();
    glTranslated(-8.5, 0.2, 0);
    Pinguim_Filhote();
    glPopMatrix();

    if (pegouPeixe && -7.5 + dx * velocidade_pinguim <= -7)
    {
      conta_peixes++;
      cronometroPinguimFilhote = 0;
      pegouPeixe = false;
    }

    glPushMatrix();

    if ((!comecando_rasante() && !no_rasante))
    {
      movimento_padrao_petrel();
    }
    else
    {
      if (!direcao_esquerda)
      {
        if (proximo_passo_direita_x() >= ponto_rasante)
        {
          if (proximo_passo_direita_x() <= petrel_limite_direita)
          {
            posX = proximo_passo_direita_x();
            posY = rasante(a, verticeX, verticeY, posX);
          }
          else
          {
            petrel_x = petrel_limite_direita;
            direcao_esquerda = true;
            framePetrel = 0;
            posX = proximo_passo_esquerda_x();
            posY = rasante(a, verticeX, verticeY, posX);
            petrel_y = posY;
            no_rasante = false;
            verticeX = 0;
            verticeY = 0;
          }
          if (posX > verticeX && posY >= altura_rasante)
          {
            petrel_x = posX;
            petrel_y = posY;
            verticeX = 0;
            verticeY = 0;
            framePetrel = 0;
            no_rasante = false;
          }
        }
        else
        {
          movimento_padrao_petrel();
        }
      }
      else
      {
        if (proximo_passo_esquerda_x() <= ponto_rasante)
        {
          if (proximo_passo_esquerda_x() >= petrel_limite_esquerda)
          {
            posX = proximo_passo_esquerda_x();
            posY = rasante(a, verticeX, verticeY, posX);
          }
          else
          {
            petrel_x = petrel_limite_esquerda;
            direcao_esquerda = false;
            framePetrel = 0;
            posX = proximo_passo_direita_x();
            posY = rasante(a, verticeX, verticeY, posX);
            petrel_y = posY;
            no_rasante = false;
            verticeX = 0;
            verticeY = 0;
          }
          if (posX < verticeX && posY >= altura_rasante)
          {
            petrel_x = posX;
            petrel_y = posY;
            framePetrel = 0;
            no_rasante = false;
            verticeX = 0;
            verticeY = 0;
          }
        }
        else
        {
          movimento_padrao_petrel();
        }
      }
    }
    glTranslated(posX, posY, 0);
    glScaled(0.8, 0.8, 1);
    petrel();
    glPopMatrix();

    glPopMatrix();

    if (petrel_atinge())
    {
      perdeu = true;
    }
    glPushMatrix();
    glColor3f(0,0,0);
    impreme_pontuacao();
    glPopMatrix();

  } else {
    if (frameNumber <= _5minutos){
    glPushMatrix();
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(-2,0,0);
    P();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(-0.9,0,0);
    E();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(0.1,0,0);
    R();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(1.1,0,0);
    D();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(2.1,0,0);
    E();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(3.1,0,0);
    U();
    glPopMatrix();
    glPopMatrix();
    }
    else {
    glPushMatrix();
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(-2,0,0);
    G();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(-0.9,0,0);
    A();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(0.1,0,0);
    N();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(1.3,0,0);
    H();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(2.5,0,0);
    O();
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslated(3.7,0,0);
    U();
    glPopMatrix();

    glPopMatrix();
    } 
    glPushMatrix();
    glColor3f(1,1,1);
    impreme_pontuacao();
    glPopMatrix();
    }
  glFlush();
}

void Frame(int v)
{
  frameNumber++;
  framePetrel++;
  cronometroPinguimFilhote++;
  display();
  glutTimerFunc(20, Frame, 0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Alimente o Pinguim Filhote");
  init();
  glutDisplayFunc(display);
  glutTimerFunc(20, Frame, 0);
  glutKeyboardFunc(Teclado);
  glutMainLoop();
  return 0;
}
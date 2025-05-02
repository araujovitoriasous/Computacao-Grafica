#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

#pragma region Variaveis Globais
double PI = 3.14159;
int frameNumber = 0;
int cronometroPinguimFilhote = 0;
int lago_X0=-1;
int lago_X1=7;
int quadrado_verde_X0=-8;
int quadrado_verde_X1=-1;
double velocidade_pinguim=0.05;
double velocidade_peixe=0.002;
double velocidade_petrel = 0.01;
// bool noLago = false;
#pragma endregion

#pragma region Variaveis Petrel
bool direcao_esquerda = false;
int framePetrel = 0;
#pragma endregion

#pragma region Variaveis Peixes
bool peixeCapturado[4] = {true, true, true, true};
int peixeX[4];
int peixeY[4];
bool esquerda[4] = {false, false, false, false};
bool direita[4] = {false, false, false, false};
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
double posicaoPinguimX;
double posicaoPinguimY;
bool pegouPeixe = false;
#pragma endregion

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
  if (pos <= -0.5)
  {
    direita[i] = true;
    esquerda[i] = false;
    dxPeixe[i] = 0;
  }
  return direita[i];
}

bool Troca_Esquerda(double pos, int i)
{

  if (pos >= 6.5)
  {
    // cout <<pos<<endl;
    direita[i] = false;
    esquerda[i] = true;
    dxPeixe[i] = 0;
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

double funcao_peixe(double x)
{
  return 0.3 * x * x - 1;
}

double funcao_petrel_esquerda(double x)
{
  return -x * x - 2 * x;
}

double funcao_petrel_direita(double x)
{
  return -x * x + 2 * x;
}

void petrel()
{

  glPushMatrix();
  glLineWidth(5);
  glBegin(GL_LINES);
  glColor3f(1, 0.4353, 0.6118);
  for (double i = 1.2; i >= 0.01; i = i - 0.01)
  {
    glVertex3f(i - 0.01, funcao_petrel_direita(i), 0);
    glVertex3f(i, funcao_petrel_direita(i), 0);
  }
  glEnd();
  glBegin(GL_LINES);
  for (double i = 0.01; i >= -1.2; i = i - 0.01)
  {
    glVertex3f(i - 0.01, funcao_petrel_esquerda(i), 0);
    glVertex3f(i, funcao_petrel_esquerda(i), 0);
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

  // CORPO
  glPushMatrix();
  glTranslated(1, 0.4, 0);
  glScaled(0.5, 0.8, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // PELO BRANCO
  glPushMatrix();
  glTranslated(1.25, 0.45, 0);
  glScaled(0.2, 0.55, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // OLHO
  glPushMatrix();
  glTranslated(1.2, 1.5, 0);
  glScaled(0.1, 0.1, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // PATA1
  glPushMatrix();
  glTranslated(0.8, -0.7, 0);
  glScaled(0.1, 0.3, 1);
  glColor3f(0.702, 0.1294, 0.2039);
  triangle();
  glPopMatrix();

  // PATA2
  glPushMatrix();
  glTranslated(1.2, -0.7, 0);
  glScaled(0.1, 0.3, 1);
  glColor3f(0.702, 0.1294, 0.2039);
  triangle();
  glPopMatrix();
}

void Pinguim_Contrario()
{

  // BICO
  glPushMatrix();
  glTranslated(0.55, 1.3, 0);
  glScaled(0.3, 0.1, 1);
  glColor3f(1, 1, 0);
  glRotated(-110, 0, 0, 1);
  triangle();
  glPopMatrix();

  // CABEÇA
  glPushMatrix();
  glTranslated(1, 1.5, 0);
  glScaled(0.35, 0.35, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // CORPO
  glPushMatrix();
  glTranslated(1, 0.4, 0);
  glScaled(0.5, 0.8, 1);
  glColor3f(0, 0, 0);
  Disk(1);
  glPopMatrix();

  // PELO BRANCO
  glPushMatrix();
  glTranslated(0.75, 0.45, 0);
  glScaled(0.2, 0.55, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // OLHO
  glPushMatrix();
  glTranslated(0.8, 1.5, 0);
  glScaled(0.1, 0.1, 1);
  glColor3f(1, 1, 1);
  Disk(1);
  glPopMatrix();

  // PATA1
  glPushMatrix();
  glTranslated(0.8, -0.7, 0);
  glScaled(0.1, 0.3, 1);
  glColor3f(0.702, 0.1294, 0.2039);
  triangle();
  glPopMatrix();

  // PATA2
  glPushMatrix();
  glTranslated(1.2, -0.7, 0);
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
    glVertex3f(i, funcao_peixe(i), 0);
  }
  for (double i = -2; i <= 2.5; i = i + 0.1)
  {
    glVertex3f(i, -funcao_peixe(i), 0);
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

    if ((-7.5 + dx * 0.5 >= -1 && -7.5 + dx * 0.5 <= 5) && (0.1 + dy * 0.25 >= -5.8 && 0.1 + dy * 0.25 <= 0.1))
    {
      // noLago = true;
      dxAnterior = dx;
      dyAnterior = dy;
      return true;
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
    if ((-5.6 + dx * 0.5 >= 0 && -5.6 + dx * 0.5 <= 7) && (-1.1 + dy * 0.25 >= -7 && -1.1 + dy * 0.25 <= -1))
    {

      dxAnterior = dx;
      dyAnterior = dy;
      // cout << "Dentro" << endl;
      return true;
    }

    if ((-5.6 + dx * 0.5 < -1) && (-5.6 + dx * 0.5 > -0.3) && (-1.1 + dy * 0.25 == -1.1))
    {

      dxAnterior = dx;
      dyAnterior = dy;
      // cout << "Saiu" << endl;
      return true;
    }

    if ((-5.6 + dx * 0.5 < 0) && (-1.1 + dy * 0.25 == -1.1))
    {

      return false;
    }
    if ((-7.5 + dx * 0.5 <= -2) && ((-1.1 + dyAnterior * 0.25 == -1.1)))
    {
      // cout <<"oi111"<<endl;
      return false;
    }

    // cout <<-7.5 + dx * 0.5 <<endl;
    // cout <<-1.1 + dy * 0.25<<endl;
    dx = dxAnterior;
    dy = dyAnterior;
    return true;
  }

  return false;
}

bool PINGUIM_NO_VERDE()
{
  if ((-7.5 + dx * 0.5 < -1 && -7.5 + dx * 0.5 >= -7.5) && (dy==0))
  {
    // cout <<"oi222"<<endl;
    // noLago = false;
    dyAnterior = 0;
    dxAnterior = dx;
    //cout <<"oi222"<<endl;
    return true;
  }

  if (-7.5 + dx * 0.5 <= -7.5)
  {
    // noLago = false;
    dy = dyAnterior;
    dx = dxAnterior;
    //cout <<"oi111"<<endl;
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
        // cout << cabecaPinguim << " "<<cabeçaPeixe<<endl;
        peixeCapturado[i] = true;
        pegouPeixe = true;
      }
    }
    else
    {
      // cout << (cabecaPinguim<=cabeçaPeixe) <<endl;
      if (testeCapturaTras())
      {
        // cout << cabecaPinguim << " " << cabeçaPeixe << endl;
        peixeCapturado[i] = true;
        pegouPeixe = true;
      }
    }
  }
}

void display()
{

  if (frameNumber <= 15000 && (cronometroPinguimFilhote <= 3000))
  {
    // Limpa a janela, colocando na tela a cor definida pela função glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
        peixeX[i] = -0.5 + rand() % 8;
        peixeY[i] = -1 - rand() % 6;

        bool colisao;
        do
        {
          colisao = false;
          for (int j = 3; j >= 0; j--)
          {
            if (j != i && peixeY[i] == peixeY[j])
            {
              peixeY[i] = -1 - rand() % 6;
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
      }
      else
      {
        dxPeixe[i]++;

        if (!direita[i] && !esquerda[i] && peixeDirecaoInicial[i] && !Troca_Direita(peixeX[i] - dxPeixe[i] * 0.02, i))
        {
          posicaoPeixeX[i] = peixeX[i] - dxPeixe[i] * 0.02;
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

        else if (!direita[i] && !esquerda[i] && !peixeDirecaoInicial[i] && !Troca_Esquerda(peixeX[i] + dxPeixe[i] * 0.02, i))
        {
          posicaoPeixeX[i] = peixeX[i] + dxPeixe[i] * 0.02;
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

        else
        {

          if (direita[i] && !Troca_Esquerda(-0.5 + dxPeixe[i] * 0.02, i))
          {
            posicaoPeixeX[i] = -0.5 + dxPeixe[i] * 0.02;
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
          else if (esquerda[i] && !Troca_Direita(6.5 - dxPeixe[i] * 0.02, i))
          {
            posicaoPeixeX[i] = 6.5 - dxPeixe[i] * 0.02, peixeY[i], 0;
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
      
      glPushMatrix();
      glPointSize(5);
      glBegin(GL_POINTS);
      glColor3f(1, 0, 0);
      glVertex3f(cabeçaPeixe, peixeY[i], 0);
      glColor3f(0, 1, 0);
      glVertex3f(caudaPeixe, peixeY[i], 0);
      glColor3f(1, 0, 0);
      glVertex3f(posicaoPeixeX[i], costaPeixe, 0);
      glColor3f(1, 0, 0);
      glVertex3f(posicaoPeixeX[i], barrigaPeixe, 0);
      glColor3f(1, 1, 0);
      glVertex3f(posicaoPeixeX[i], peixeY[i], 0);
      glEnd();
      glPopMatrix();
      CapturaPeixe(i);
    }

    if (!PINGUIM_NO_LAGO_TRAS() && PINGUIM_NO_VERDE())
    {
      glPushMatrix();
      glTranslated(-7.5 + dx * 0.5, 0.1, 0);
      posicaoPinguimX = -6.9 + dx * 0.5;
      posicaoPinguimY = 0.5;
      // glScaled(0.6, 0.8, 1);

      if (PINGUIM_FRENTE())
      {
        barrigaPinguim = posicaoPinguimX + 0.3;
        pataPinguim = posicaoPinguimY-1;
        cabecaPinguim = posicaoPinguimY +1;
        costaPinguim = posicaoPinguimX - 0.3;
        glPushMatrix();
        glScaled(0.6, 0.8, 1);
        Pinguim();
        glPopMatrix();
        if (pegouPeixe)
        {
          glPushMatrix();
          glTranslated(1.2, 0.8, 0);
          glRotated(-45, 0, 0, 1);
          glScaled(0.2, 0.2, 1);
          glColor3f(1, 0.549, 0);
          Peixe();
          glPopMatrix();
        }

      }
      else
      {
        barrigaPinguim = posicaoPinguimX - 0.3;
        pataPinguim = posicaoPinguimY-1;
        cabecaPinguim = posicaoPinguimY +1;
        costaPinguim = posicaoPinguimX + 0.3;
        glPushMatrix();
        glScaled(0.6, 0.8, 1);
        Pinguim_Contrario();
        glPopMatrix();
        // Pinguim_Contrario();
        if (pegouPeixe)
        {
          glPushMatrix();
          glTranslated(0, 0.8, 0);
          glRotated(225, 0, 0, 1);
          glScaled(0.2, 0.2, 1);
          glColor3f(1, 0.549, 0);
          Peixe();
          glPopMatrix();
        }
      }
      glPopMatrix();

      glPushMatrix();
      glPointSize(5);
      glBegin(GL_POINTS);
      glColor3f(1,0,0);
      glVertex3f(posicaoPinguimX,posicaoPinguimY, 0);

      glPushMatrix();
      glPointSize(5);
      glBegin(GL_POINTS);
      glColor3f(1, 0, 0);
      glVertex3f(posicaoPinguimX, pataPinguim, 0);
      glColor3f(0, 1, 0);
      glVertex3f(posicaoPinguimX, cabecaPinguim, 0);
      glColor3f(1, 0, 0);
      glVertex3f(barrigaPinguim, posicaoPinguimY, 0);
      glColor3f(0, 1, 0);
      glVertex3f(costaPinguim, posicaoPinguimY, 0);
      glEnd();
      glPopMatrix();
      
      glEnd();
      glPopMatrix();
    }
    else if (PINGUIM_NO_LAGO_FRENTE())
    {
      posicaoPinguimX = -7 + dx * 0.5 + 0.4;
      posicaoPinguimY = 0.1 + dy * 0.25 - 0.6;
      cabecaPinguim = posicaoPinguimX + 1;
      pataPinguim = posicaoPinguimX - 1;
      barrigaPinguim = posicaoPinguimY - 0.4;
      costaPinguim = posicaoPinguimY + 0.4;

      glPushMatrix();
      glTranslated(-7 + dx * 0.5, 0.1 + dy * 0.25, 0);
      glRotated(-90, 0, 0, 1);
      glTranslated(0, 0, 0);

      glPushMatrix();
      glScaled(0.6, 0.8, 1);
      Pinguim();
      glPopMatrix();

      if (pegouPeixe)
      {
        glPushMatrix();
        glTranslated(1.2, 0.8, 0);
        glRotated(-45, 0, 0, 1);
        glScaled(0.2, 0.2, 1);
        glColor3f(1, 0.549, 0);
        Peixe();
        glPopMatrix();
      }

      glPopMatrix();

      glPushMatrix();
      glPointSize(5);
      glBegin(GL_POINTS);
      glColor3f(1, 0, 0);
      glVertex3f(pataPinguim, posicaoPinguimY, 0);
      glColor3f(0, 1, 0);
      glVertex3f(cabecaPinguim, posicaoPinguimY, 0);
      glColor3f(1, 0, 0);
      glVertex3f(posicaoPinguimX, barrigaPinguim, 0);
      glColor3f(0, 1, 0);
      glVertex3f(posicaoPinguimX, costaPinguim, 0);
      glColor3f(1, 1, 0);
      glVertex3f(posicaoPinguimX, posicaoPinguimY, 0);

      glEnd();
      glPopMatrix();
    }
    else
    {
      // cout <<"("<<-7.5+dx*0.5<<","<<-1.1+dy*0.25<< ")"<<endl;
      posicaoPinguimX = -5.6 + dx * 0.5 -0.4;
      posicaoPinguimY = 0.1 + dy * 0.25 - 0.6;
      cabecaPinguim = posicaoPinguimX - 1;
      pataPinguim = posicaoPinguimX + 1;
      barrigaPinguim = posicaoPinguimY - 0.4;
      costaPinguim = posicaoPinguimY + 0.4;
      glPushMatrix();
      glTranslated(-5.6 + dx * 0.5, -1.1 + dy * 0.25, 0);
      glRotated(90, 0, 0, 1);
      glTranslated(0, 0, 0);
      glPushMatrix();
      glScaled(0.6, 0.8, 1);
      Pinguim_Contrario();
      glPopMatrix();

      if (pegouPeixe)
      {
        glPushMatrix();
        glTranslated(0, 0.8, 0);
        glRotated(225, 0, 0, 1);
        glScaled(0.2, 0.2, 1);
        glColor3f(1, 0.549, 0);
        Peixe();
        glPopMatrix();
      }
      glPopMatrix();
      glPushMatrix();
      glPointSize(5);
      glBegin(GL_POINTS);
      glColor3f(1, 0, 0);
      glVertex3f(pataPinguim, posicaoPinguimY, 0);
      glColor3f(0, 1, 0);
      glVertex3f(cabecaPinguim, posicaoPinguimY , 0);
      glColor3f(1, 0, 0);
      glVertex3f(posicaoPinguimX, barrigaPinguim, 0);
      glColor3f(1, 0, 0);
      glVertex3f(posicaoPinguimX, costaPinguim, 0);
      glColor3f(1, 1, 0);
      glVertex3f(posicaoPinguimX , posicaoPinguimY, 0);
      
      glEnd();
      glPopMatrix();
    }

    glPushMatrix();
    glTranslated(-8.5, 0.2, 0);
    Pinguim_Filhote();
    glPopMatrix();

    if (pegouPeixe && -7.5 + dx * 0.5 <= -7)
    {
      cronometroPinguimFilhote = 0;
      pegouPeixe = false;
    }

    glPushMatrix();
    if (!direcao_esquerda)
    {
      if (-6.5 + framePetrel * 0.1 <= 7)
      {
        glTranslated(-7 + framePetrel * 0.1, 3, 0);
      }
      else
      {
        direcao_esquerda = true;
        framePetrel = 0;
        glTranslated(7 - framePetrel * 0.1, 3, 0);
      }
    }
    else
    {
      if (6.5 - framePetrel * 0.1 >= -7)
      {
        glTranslated(7 - framePetrel * 0.1, 3, 0);
      }
      else
      {
        direcao_esquerda = false;
        framePetrel = 0;
        glTranslated(-7 + framePetrel * 0.1, 3, 0);
      }
    }
    glScaled(0.8, 0.8, 1);
    petrel();
    glPopMatrix();

    glPushMatrix();
    glPointSize(5);

    glBegin(GL_POINTS);
    
    glColor3f(1, 0, 0);
    glVertex3f(-8,0,0);
    glPointSize(5);
    

    glColor3f(0, 0, 1);
    glVertex3f(-1,0,0);

    glColor3f(0, 0, 1);
    glVertex3f(7,0,0);

    glEnd();
    glPopMatrix();
    // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
    glFlush();
  }
  else
  {
    return;
  }
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
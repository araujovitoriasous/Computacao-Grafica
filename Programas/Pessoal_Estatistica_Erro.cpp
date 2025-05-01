#include <stdio.h>
#include <string.h>
#include <math.h>

#define TAM 20

int flutuante=1;
int virgula=0;
int i=0;

void abreArquivo (double valores[]);
void Leitura (char c, double valores[]);
void Imprime (double valores[]);

int main (){
	double distancia[TAM];
	double tempo[TAM];
	double vel[TAM];
	abreArquivo (distancia);
	abreArquivo (tempo);
	abreArquivo (vel);
	Imprime (distancia);
	Imprime (tempo);
	Imprime (distancia);
}

void abreArquivo (double valores[]){
	FILE * arq;
	char nome[100];
	char c;
	
	fgets (nome,100,stdin);
	arq = fopen (nome,"r");
		
	while ((c=getc(arq))!=EOF){
		Leitura (c,valores);
	}
	fclose (arq);
}

void Leitura (char c, double valores[]){
	switch (c){
	case ',':
		virgula+=1;
		break;
	case '\n':
		flutuante=1;
		virgula=0;
		i++;
		break;
	default:
       	    if ((!virgula)&&(c>='0')&&(c<='9')){
               	valores[i]=10*valores[i] + (c-'0');
               	}
        	    else if ((c>='0')&&(c<='9')){
            	valores[i]= valores[i] + (c-'0')/(pow(10,flutuante));
            	flutuante=flutuante + 1;
				}
			break;
		}
	}
	
void Imprime (double valores[]){
	int j;
	for (j=0;j<TAM;j++){
		printf ("%lf\n",valores[i]);
	}
}

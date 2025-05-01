#include <stdio.h>
#include <math.h>
double altura[20];
double tempo[20];
long flutuante=1;
int i=0;
int quantidade=0;
int main (void){
	FILE * arquivo;
	double gravidades[20];
	double velAoQuadrado[20];
	char c;
	arquivo = fopen(medidas.txt,"r");
	while (c=getc(arquivo)!=EOF){
		Leitura (c);
		}
		

void leitura (c){
	if (quantidade==0){
		switch (c){
		case ',':
			virgula+=1
			break;
		case '\t':
			quantidade+=1;
			flutuante=0;
			virgula=0;
			break;
		default:
       	    	if ((!virtula)&&(c>='0')&&(c<='9'))
                	altura[i]=10*altura[i] + (c-'0');
        	    else if ((c>='0')&&(c<='9')){
            	    altura[i]= altura[i] + ((float)(c-'0')/(10*flutuante));
            	    flutuante=flutuante *10;
					}
				break;
		}
	}
	else if (quantidade==1){
		switch (c){
            case ',':
        		virgula=1;
        		break;
        	case '\n':
        		i+=1;
        		quantidadee=0;
        		flutuante=0;
        		virgula;
            default:
       	    	if ((!virgula)&&(c>='0')&&(c<='9')){
                	tempo[i]=10*tempo[i] + (c-'0');
        	    }else if ((c>='0')&&(c<='9')) {
            	    tempo[i]= tempo[i] + ((float)(c-'0')/(10*flutuante));
            	    flutuante=flutuante *10;          	 
					}
				break;
        }
	}
}
double Gravidade (double altura, double tempo){
	double gravidade;
	gravidade=(2*altura)\(pow(tempo,2));
	retuern gravidade;
}
double Velocidades (double altura, double gravidade){
	double velocidade;
	velocidade=2*gravidade*altura
	return velocidade;
}

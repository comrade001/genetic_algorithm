/*Algoritmo Genetico
Se busca maximizar la siguiente funcion
matematica:
    f(x,y)=50-(x-5)^2-(y-5)^2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//Definicion de la estructura INDIVIDUO
typedef struct  {
    unsigned char* cromosoma;   //genotipo
	unsigned char* bits_GenX;
    float* valor; //fenotipo (convierte el valor bit a decimal)
	/*Bits que tiene cada Gen, pueden ser tamaños distintos 
	 * para cada Gen, segun sea el caso.*/
    unsigned int* BitsPorGen;
	/*Valor decimal de cada uno de sus 
	 * genes*/
	unsigned int* gen_decimal;
    float fit;
	float best_fit;
}INDIVIDUO;

typedef struct{
	unsigned int idGbest;
	INDIVIDUO* pInd;
}POBLACION;

/*Variables globales*/
const unsigned int Numero_de_Genes=2;
const unsigned int Numero_de_Individuos=5;
const unsigned int Bits_por_Gen=10;
const unsigned int GenX=10, GenY=10;
const unsigned int LimitInf=0;
const unsigned int LimitSup=10;
const float pc=0.8; 
const float p_muta=0.3;

/*Prototipo de funciones*/
POBLACION* CrearPoblacion(const unsigned int Numero_de_Genes, const unsigned int Numero_de_Individuos);
void InicializarPoblacion(POBLACION *pPob);
void EvaluarPoblacion(POBLACION *pPob);
void EliminarPoblacion(POBLACION *pPob, const unsigned int Numero_de_Individuos);
int SeleccionarPoblacion(POBLACION *pPob);
void CruzarPoblacion(POBLACION *pPob, int padre, int madre);
void MutarPoblacion(POBLACION *pPob, int padre, int madre);
void MostrarPoblacion(POBLACION *pPob);

int main()
{
	unsigned int padre, madre;
	srand(time(NULL));
	POBLACION *pPob;
	pPob=CrearPoblacion(Numero_de_Genes, Numero_de_Individuos);
	InicializarPoblacion(pPob);
	EvaluarPoblacion(pPob);
	padre = madre = SeleccionarPoblacion(pPob);
	CruzarPoblacion(pPob, padre, madre);
	printf("\nMutarPoblacion\n");
	MutarPoblacion(pPob, padre, madre);
	
	EliminarPoblacion(pPob, Numero_de_Individuos);

	return 0;
}

void MostrarPoblacion(POBLACION *pPob)
{
	unsigned int i, j;

	for(i=0; i<Numero_de_Individuos; i++)
		for(j=0; j<(GenX+GenY); j++)
		printf("%c", pPob->pInd[i].cromosoma[j]);
}

void MutarPoblacion(POBLACION *pPob, int padre, int madre)
{
	unsigned int i, j;
	float random;
	
	for(j=0; j<(GenX+GenY); j++)
	{
		random=((double)rand()/RAND_MAX);
		if(random<p_muta)
		{
			for(i=0; i<(GenX+GenY); i++)
				printf("%c", pPob->pInd[padre].cromosoma[i]);
			
			printf("\nMuto el bit: %i\n", j);
			pPob->pInd[padre].cromosoma[j]^=1;
			
			for(i=0; i<(GenX+GenY); i++)
				printf("%c", pPob->pInd[padre].cromosoma[i]);		
			printf("\n");
		}
	}
	printf("\n");
	
	for(j=0; j<(GenX+GenY); j++)
	{
		random=((double)rand()/RAND_MAX);
		if(random<p_muta)
		{
			for(i=0; i<(GenX+GenY); i++)
				printf("%c", pPob->pInd[madre].cromosoma[i]);
			
			printf("\nMuto el bit: %i\n", j);
			pPob->pInd[madre].cromosoma[j]^=1;
			
			for(i=0; i<(GenX+GenY); i++)
				printf("%c", pPob->pInd[madre].cromosoma[i]);		
			printf("\n");
		}
	}
}

void CruzarPoblacion(POBLACION *pPob, int padre, int madre)
{
	unsigned int j, px;
	float random=rand()/(float)RAND_MAX;

	if(random<pc)
	{
		for(j=0; j<(GenX+GenY); j++)
			printf("%c", pPob->pInd[padre].cromosoma[j]);
		printf("\t");
		for(j=0; j<(GenX+GenY); j++)
			printf("%c", pPob->pInd[madre].cromosoma[j]);
		printf("\n");

		px = (rand()%(GenX+GenY));
		unsigned char aux1[GenX+GenY], aux2[GenX+GenY];
		printf("px=%i\n", px);
		memcpy(aux2, pPob->pInd[padre].cromosoma, px*sizeof(unsigned char));
		memcpy(aux1, pPob->pInd[madre].cromosoma, px*sizeof(unsigned char));
		memcpy(&aux1[px], &pPob->pInd[padre].cromosoma[px], ((GenX+GenY)-px)*sizeof(unsigned char));
		memcpy(&aux2[px], &pPob->pInd[madre].cromosoma[px], ((GenX+GenY)-px)*sizeof(unsigned char));
		
		memcpy(pPob->pInd[padre].cromosoma, aux1, (GenX+GenY)*sizeof(unsigned char));	
		memcpy(pPob->pInd[madre].cromosoma, aux2, (GenX+GenY)*sizeof(unsigned char));
		//printf("%s\t%s\n", aux1, aux2);
		for(j=0; j<(GenX+GenY); j++)
			printf("%c", pPob->pInd[padre].cromosoma[j]);
		printf("\t");
		for(j=0; j<(GenX+GenY); j++)
			printf("%c", pPob->pInd[madre].cromosoma[j]);
		printf("\n");
	}		
}

int SeleccionarPoblacion(POBLACION *pPob)
{
	unsigned int i;
	float f_t=0.0, p_i[Numero_de_Individuos], offset=0.0;
	float random=rand()/(float)RAND_MAX;

	for(i=0; i<Numero_de_Individuos; i++)
		f_t=f_t+pPob->pInd[i].fit;

	for(i=0; i<Numero_de_Individuos; i++)
		p_i[i]=pPob->pInd[i].fit/f_t;

	/*Metodo de la ruleta*/
	for(i=0; i<Numero_de_Individuos; i++)
	{
		offset+=p_i[i];
		if(random<offset)
		{
			//flecha=i;
			//break;
			return i;
		}
	}
	return -1;
}



void EvaluarPoblacion(POBLACION *pPob)
{	
	float n=1, m=0;
	unsigned int count=0, i, j;
	unsigned int max_bitX=pow(2, GenX);
	unsigned int max_bitY=pow(2, GenY);
	/*Decodificacion de los individuos*/
	for(i=0; i<Numero_de_Individuos; i++)
	{
		for(j=0; j<(GenX+GenY); j++)
		{
			printf("%c", pPob->pInd[i].cromosoma[j]);

			if(j<(GenX+GenY)/Numero_de_Genes-1)
				n=n+((pPob->pInd[i].cromosoma[j]-'0')*(pow(2,((GenX+GenY)/Numero_de_Genes-1)-count)));
			if(j>(GenX+GenY)/Numero_de_Genes-1)
				m=m+((pPob->pInd[i].cromosoma[j]-'0')*(pow(2,((GenX+GenY)-1)-count)));
			count++;
		}		
		printf("\n%f\n%f\n",n, m);
		/*Calculo del fenotipo de los individuos*/
		pPob->pInd[i].valor[0]=(float)((n/(1.0*max_bitX))*LimitSup)+LimitInf;
		pPob->pInd[i].valor[1]=(float)((m/(1.0*max_bitY))*LimitSup)+LimitInf;
		
		printf("%f, %f", pPob->pInd[i].valor[0], pPob->pInd[i].valor[1]);
		
		/*Evaluacion de la funcion para obtener fitness*/
		pPob->pInd[i].fit=(50-(pPob->pInd[i].valor[0]-5)*(pPob->pInd[i].valor[0]-5)
				-(pPob->pInd[i].valor[1]-5)*(pPob->pInd[i].valor[1]-5));
		n=1;
		m=0;
		count=0;
		printf("\n\n");
	}

	for(i=0; i<Numero_de_Individuos; i++)
		printf("%f\n", pPob->pInd[i].fit);

}

void InicializarPoblacion(POBLACION *pPob)
{
	unsigned int i, j;
	float random;
	/*Inicializar un valor entre 0 y 1*/
		
	for(i=0; i<Numero_de_Individuos; i++)
		for(j=0; j<(GenX+GenY); j++)
		{
			random=((double)rand()/RAND_MAX);
			if(random < 0.5)
				pPob->pInd[i].cromosoma[j]='0';
			else
				pPob->pInd[i].cromosoma[j]='1';
		}

	for(i=0; i<Numero_de_Individuos; i++)
	{
			pPob->pInd[i].BitsPorGen[0]=GenX;
			pPob->pInd[i].BitsPorGen[1]=GenY;
	}

}

POBLACION* CrearPoblacion(const unsigned int Numero_de_Genes, const unsigned int Numero_de_Individuos)
{
	POBLACION *pPob;
	unsigned int i;
	/*Asignar memoria a la estructura Poblacion*/
	pPob=(POBLACION*)malloc(sizeof(POBLACION));
	if(pPob == NULL)
	{
		printf("Error en memoria\n");
		exit(0);
	}
	
	/*Asignar memoria a la estructura Individuo*/
	pPob->pInd=(INDIVIDUO*)malloc(sizeof(INDIVIDUO)*Numero_de_Individuos);
	if(pPob->pInd == NULL)
	{
		printf("Error en memoria\n");
		exit(0);
	}

	for(i=0; i<Numero_de_Individuos; i++)
		{
			pPob->pInd[i].cromosoma=(unsigned char*)malloc(sizeof(unsigned char)*(GenX+GenY));
			pPob->pInd[i].valor=(float*)malloc(sizeof(float)*Numero_de_Genes);	
			pPob->pInd[i].BitsPorGen=(unsigned int*)malloc(sizeof(unsigned int)*Numero_de_Genes);
		}

	return(pPob);
}

void EliminarPoblacion(POBLACION *pPob, const unsigned int Numero_de_Individuos)
{
	unsigned int i;
	/*Liberar memoria para cada individuo*/
	for(i=0; i<Numero_de_Individuos; i++)
	{
		free(pPob->pInd[i].cromosoma);
		free(pPob->pInd[i].valor);
		free(pPob->pInd[i].BitsPorGen);
	}
	/*Liberar memoria de los individuos*/
	free(pPob->pInd);
	/*Liberar memoria de la poblacion*/
	free(pPob);
}

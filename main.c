/*Algoritmo Genetico
Se busca maximizar la siguiente funcion
matematica:
    f(x,y)=50-(x-5)^2-(y-5)^2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Definicion de la estructura INDIVIDUO
typedef struct  {
    unsigned char* cromosoma;   //genotipo
    float* valor; //fenotipo (convierte el valor bit a decimal)
	/*Bits que tiene cada Gen, pueden ser tamaños distintos 
	 * para cada Gen, segun sea el caso.*/
    unsigned int* BitsPorGen;
    float fitness;
}INDIVIDUO;

typedef struct{
	unsigned int idGbest;
	INDIVIDUO* pInd;
}POBLACION;

/*Variables globales*/
const unsigned int Numero_de_Genes=2;
const unsigned int Numero_de_Individuos=5;
//const unsigned int Bits_por_Gen=10;
const unsigned int GenX=10, GenY=10;
const unsigned int LimitInf=0;
const unsigned int LimitSup=10;

/*Prototipo de funciones*/
POBLACION* CrearPoblacion(const unsigned int Numero_de_Genes, const unsigned int Numero_de_Individuos);
void InicializarPoblacion(POBLACION *pPob);
void EvaluarPoblacion(POBLACION *pPob);
void EliminarPoblacion(POBLACION *pPob, const unsigned int Numero_de_Individuos);

int main()
{
	POBLACION *pPob;
	pPob=CrearPoblacion(Numero_de_Genes, Numero_de_Individuos);
	InicializarPoblacion(pPob);
	EvaluarPoblacion(pPob);

	return 0;
}

void EvaluarPoblacion(POBLACION *pPob)
{	
	int n=1, m=0, count=0, i, j, k;
	unsigned int max_bitX=pow(2, GenX);
	unsigned int max_bitY=pow(2, GenY);
	for(i=0, k=0; i<Numero_de_Individuos; i++, k+=2)
	{
		for(j=0; j<(GenX+GenY); j++)
		{
			printf("%c", pPob->pInd[i].cromosoma[j]);
			//if(pPob->pInd[i].cromosoma[j] == '1')
			//	n=n+pow(2,(Numero_de_Genes*Bits_por_Gen-1)-count);
			//n=n+((pPob->pInd[i].cromosoma[j]-'0') * (pow(2,(Numero_de_Genes*Bits_por_Gen-1)-count)));

			if(j<(GenX+GenY)/Numero_de_Genes-1)
				n=n+((pPob->pInd[i].cromosoma[j]-'0') * (pow(2,((GenX+GenY)/Numero_de_Genes-1)-count)));
			if(j>(GenX+GenY)/Numero_de_Genes-1)
				m=m+((pPob->pInd[i].cromosoma[j]-'0') * (pow(2,((GenX+GenY)-1)-count)));
			count++;
		}		
		printf("\n%i\n%i",n, m);
		pPob->pInd[i].valor[k]=(float)((n/(1.0*max_bitX))*LimitSup)+LimitInf;
		pPob->pInd[i].valor[k+1]=(float)((m/(1.0*max_bitY))*LimitSup)+LimitInf;
		n=1;
		m=0;
		count=0;
		printf("\n");
	}

	for(i=0, k=0; i<Numero_de_Individuos; i++, k+=2)
	{
		printf("%f\n", pPob->pInd[i].valor[k]);
		printf("%f\n", pPob->pInd[i].valor[k+1]);
	}

/*Algoritmo Genetico
Se busca maximizar la siguiente funcion
matematica:
    f(x,y)=50-(x-5)^2-(y-5)^2
*/
	
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
			//if(pInd->valor == NULL)
			//	printf("Error al asignar memoria");

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





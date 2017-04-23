/*Algoritmo Genetico
Se busca maximizar la siguiente funcion
matematica:
    f(x,y)=50-(x-5)^2-(y-5)^2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Definicion de la estructura INDIVIDUO
typedef struct  {
    unsigned char* cromosoma;   //genotipo
    float* valor; //fenotipo (convierte el valor bit a decimal)
    unsigned int* BitPorGen;
    float fitness;
}INDIVIDUO;

typedef struct{
	INDIVIDUO* pInd;
}POBLACION;

/*Variables globales*/
const unsigned int Numero_de_Genes=2;
const unsigned int Numero_de_Individuos=5;
const unsigned int Bits_por_Gen=10;
//INDIVIDUO Pob[Numero_de_Individuos];

/*Prototipo de funciones*/
POBLACION* CrearPoblacion(const unsigned int Numero_de_Genes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos);
void InicializarPoblacion(POBLACION *pPob, const unsigned int NumeroGenes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos);
void EvaluarPoblacion(POBLACION *pPob, const unsigned int Numero_de_Genes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos);
void EliminarPoblacion(POBLACION *pPob, const unsigned int Numero_de_Individuos);

int main()
{
	POBLACION *pPob;
	pPob=CrearPoblacion(Numero_de_Genes, Bits_por_Gen, Numero_de_Individuos);
	InicializarPoblacion(pPob, Numero_de_Genes, Bits_por_Gen, Numero_de_Individuos);
	EvaluarPoblacion(pPob, Numero_de_Genes, Bits_por_Gen, Numero_de_Individuos);

	return 0;
}

void EvaluarPoblacion(POBLACION *pPob, const unsigned int Numero_de_Genes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos)
{	
	int n=1, m=0, count=0, i, j, k;
	for(i=0, k=0; i<Numero_de_Individuos; i++, k+=2)
	{
		for(j=0; j<Numero_de_Genes*Bits_por_Gen; j++)
		{
			printf("%c", pPob->pInd[i].cromosoma[j]);
			//if(pPob->pInd[i].cromosoma[j] == '1')
			//	n=n+pow(2,(Numero_de_Genes*Bits_por_Gen-1)-count);
			//n=n+((pPob->pInd[i].cromosoma[j]-'0') * (pow(2,(Numero_de_Genes*Bits_por_Gen-1)-count)));
			if(j<9)
				n=n+((pPob->pInd[i].cromosoma[j]-'0') * (pow(2,(Bits_por_Gen-1)-count)));
			if(j>9)
				m=m+((pPob->pInd[i].cromosoma[j]-'0') * (pow(2,(Numero_de_Genes*Bits_por_Gen-1)-count)));
			count++;
		}		
		printf("\n%i\n%i",n, m);
		pPob->pInd[i].valor[k]=(float)((n/1024.0)*10)+0;
		pPob->pInd[i].valor[k+1]=(float)((m/1024.0)*10)+0;
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
}

void InicializarPoblacion(POBLACION *pPob, const unsigned int NumeroGenes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos)
{
	unsigned int i, j;
	float random;
	/*Inicializar un valor entre 0 y 1*/
		
	for(i=0; i<Numero_de_Individuos; i++)
		for(j=0; j<NumeroGenes*BitsGen; j++)
		{
			random=((double)rand()/RAND_MAX);
			if(random < 0.5)
				pPob->pInd[i].cromosoma[j]='0';
			else
				pPob->pInd[i].cromosoma[j]='1';
		}
}

POBLACION* CrearPoblacion(const unsigned int Numero_de_Genes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos)
{
	POBLACION *pPob;
	unsigned int i;
	/*Asignar mememoria a la estructura Individuo*/
	pPob=(POBLACION*)malloc(sizeof(POBLACION));
	if(pPob == NULL)
	{
		printf("Error en memoria\n");
		exit(0);
	}

	pPob->pInd=(INDIVIDUO*)malloc(sizeof(INDIVIDUO)*Numero_de_Individuos);
	if(pPob->pInd == NULL)
	{
		printf("Error en memoria\n");
		exit(0);
	}

	for(i=0; i<Numero_de_Individuos; i++)
		{
			pPob->pInd[i].cromosoma=(unsigned char*)malloc(sizeof(unsigned char)*Numero_de_Genes*BitsGen);
			//pPob->pInd[i].cromosoma=(int*)malloc(sizeof(int)*Numero_de_Genes*BitsGen);
			pPob->pInd[i].valor=(float*)malloc(sizeof(float)*Numero_de_Individuos*Numero_de_Genes);	
			pPob->pInd[i].BitPorGen=(unsigned int*)malloc(sizeof(unsigned int)*BitsGen);
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
		free(pPob->pInd[i].BitPorGen);
	}
	/*Liberar memoria de los individuos*/
	free(pPob->pInd);
	/*Liberar memoria de la poblacion*/
	free(pPob);
}





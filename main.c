/*Algoritmo Genetico
Se busca maximizar la siguiente funcion
matematica:
    f(x,y)=50-(x-5)^2-(y-5)^2
*/

#include <stdio.h>
#include <stdlib.h>

//Definicion de la estructura INDIVIDUO
typedef struct  {
    int* cromosoma;   //genotipo
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
void InicializarPoblacion(POBLACION *pPob, const unsigned int NumeroGenes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos);
POBLACION* CrearPoblacion(const unsigned int Numero_de_Genes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos);

int main()
{
	POBLACION *pPob;
	pPob=CrearPoblacion(Numero_de_Genes, Bits_por_Gen, Numero_de_Individuos);
	InicializarPoblacion(pPob, Numero_de_Genes, Bits_por_Gen, Numero_de_Individuos);
	printf("Print Individuos\n");
	for(int i=0; i<Numero_de_Individuos; i++)
	{
		for(int j=0; j<Numero_de_Genes*Bits_por_Gen; j++)
			printf("%i", pPob->pInd[i].cromosoma[j]);
		printf("\n");
	}

	return 0;
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
				pPob->pInd[i].cromosoma[j]=0;
			else
				pPob->pInd[i].cromosoma[j]=1;
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
			//pPob->pInd[i].cromosoma=(unsigned char*)malloc(sizeof(unsigned char)*Numero_de_Genes*BitsGen);
			pPob->pInd[i].cromosoma=(int*)malloc(sizeof(int)*Numero_de_Genes*BitsGen);
			pPob->pInd[i].valor=(float*)malloc(sizeof(float)*Numero_de_Genes);	
			pPob->pInd[i].BitPorGen=(unsigned int*)malloc(sizeof(unsigned int)*BitsGen);
		}
			//if(pInd->valor == NULL)
			//	printf("Error al asignar memoria");

	return(pPob);
}






/*Algoritmo Genetico
Se busca maximizar la siguiente funcion
matematica:
    f(x,y)=50-(x-5)^2-(y-5)^2
*/

#include <stdio.h>
#include <stdlib.h>

//Definicion de la estructura INDIVIDUO
typedef struct  {
    unsigned char* cromosoma;   //genotipo
    float* valor; //fenotipo (convierte el valor bit a decimal)
    unsigned int* BitPorGen;
    float fitness;
}INDIVIDUO;

/*Variables globales*/
const unsigned int Numero_de_Genes=2;
const unsigned int Numero_de_Individuos=5;
const unsigned int Bits_por_Gen=10;
//INDIVIDUO Pob[Numero_de_Individuos];

/*Prototipo de funciones*/
void InicializarPoblacion(INDIVIDUO Poblacion[], const unsigned int NumeroGenes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos);
INDIVIDUO* CrearIndividuo(const unsigned int Numero_de_Genes, const unsigned int BitsGen);

int main()
{
	INDIVIDUO *pInd;
	pInd=CrearIndividuo(Numero_de_Genes, Bits_por_Gen);
	INDIVIDUO Poblacion[Numero_de_Individuos];
	InicializarPoblacion(Poblacion, Numero_de_Genes, Bits_por_Gen, Numero_de_Individuos);

	return 0;
}

void InicializarPoblacion(INDIVIDUO Poblacion[], const unsigned int NumeroGenes, const unsigned int BitsGen, const unsigned int Numero_de_Individuos)
{
	unsigned char i, j;
	float random;
	//INDIVIDUO Pob[Numero_de_Individuos];
	/*Inicializar un valor entre 0 y 1*/
		
	for(i=0; i<Numero_de_Individuos; i++)
		for(j=0; j<NumeroGenes*BitsGen; j++)
		{
			random=((double)rand()/RAND_MAX);
			if(random < 0.5)
				//pInd->cromosoma[j]=0;
				Poblacion[i].cromosoma[j]=0;
			else
				//pInd->cromosoma[j]=1;
				Poblacion[i].cromosoma[j]=1;
		}
}

INDIVIDUO* CrearIndividuo(const unsigned int Numero_de_Genes, const unsigned int BitsGen)
{
	INDIVIDUO *pInd;
	/*Asignar mememoria a la estructura Individuo*/
	pInd=(INDIVIDUO*)malloc(sizeof(INDIVIDUO));

	if(pInd == NULL)
		printf("Error en memoria\n");

	pInd->cromosoma=(unsigned char*)malloc(sizeof(unsigned char)*Numero_de_Genes*BitsGen);
	*pInd->BitPorGen=BitsGen;
	pInd->valor=(float*)malloc(sizeof(float)*Numero_de_Genes);	

	return(pInd);
}






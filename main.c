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

const unsigned int Numero_de_Genes=2;
const unsigned int Numero_de_Individuos=5;

void InicializarPoblacion(const unsigned int NumeroGenes, unsigned int BitsGen);


int main()
{
    printf("Hello world!\n");
	//INDIVIDUO *pInd;
	//pInd=CrearIndividuo(Numero_de_Genes,10);
	//INDIVIDUO Poblacion[Numero_de_Individuos];
	return 0;
}

void InicializarPoblacion(const unsigned int NumeroGenes, unsigned int BitsGen)
{

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






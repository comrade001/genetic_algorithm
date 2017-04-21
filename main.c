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
INDIVIDUO Poblacion[Numero_de_Individuos];
void InicializarPoblacion(const unsigned int NumeroGenes, unsigned int BitsGen);


int main()
{
    printf("Hello world!\n");
    return 0;
}

void InicializarPoblacion(const unsigned int NumeroGenes, unsigned int BitsGen)
{

}

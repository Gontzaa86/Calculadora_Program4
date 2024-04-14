#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "binario.h"

InfoBinario binarios(int aTransformar)
{
    InfoBinario ib;

    int contador = 0;   //Cantidad de bits
    int mayorQue = 1;   //Exponentes de 2 para conocer la cantidad de bits que se van a utilizar y realizar operaciones
    while (aTransformar >= mayorQue)
    {
        mayorQue = mayorQue * 2;
        contador++;
    }
    
    mayorQue = mayorQue / 2; //Retroceder a la potencia de 2 mas cercana

    int* binario = (int*)malloc(sizeof(int)*contador); //Lista del tamaño del contador
    for (int i = 0; i < contador; i++)
    {
        //Si el numero es mayor al bit mas alto requerido (restante) se pone 1 si no 0
        if (aTransformar >= mayorQue)
        {
            binario[i] = 1;
            aTransformar = aTransformar - mayorQue;
        }
        else
        {
            binario[i] = 0;
        }
        mayorQue = mayorQue/2;
    }

    ib.numeroBinario = binario;
    ib.cantidadBits = contador;

    return ib;
}

int binario_a_decimal(long long binario) {
    int decimal = 0, exponente = 0;

    while (binario != 0) {
        
        int digito = binario % 10;

        decimal += digito * pow(2, exponente);
        
        ++exponente;
        
        binario /= 10;
    }
    
    return decimal;
}

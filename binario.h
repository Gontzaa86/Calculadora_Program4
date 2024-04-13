#ifndef BINARIO_H
#define BINARIO_H

typedef struct
{
    int* numeroBinario; //Lista de ints utilizada para almacenar 1 y 0
    int cantidadBits;   //Contador para conocer la cantidad de bits requierida
}InfoBinario;

InfoBinario binarios(int aTransformar);

#endif
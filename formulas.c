#include<stdio.h>
#include<math.h>
#include "formula.h"

float sumar(float x, float y)
{
    float resultado = x + y;
    return resultado;
}
float restar(float x, float y)
{
    float resultado = x - y;
    return resultado;
}
float multiplicar(float x, float y)
{
    float resultado = x * y;
    return resultado;
}

float division(float x, float y)
{   
     if (y != 0) {
        // Realizar la división
         float resultado = x / y;
         return resultado;       
    } else {
        printf("Error: No se puede dividir entre cero.\n");
    }
    return 0;
}

float elevar(float x, float y)
{
    float resultado = pow (x, y);
    return resultado;
}
float raizCuadrada(float x){

    float raiz = sqrt(x);
    return raiz;
}
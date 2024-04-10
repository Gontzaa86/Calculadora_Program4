#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formula.h"

void mostrarMenu(){
    printf("1. Realiza una suma\n");
}

void main (void){
    int opcion;
    float num1;
    float num2;

    mostrarMenu();

    scanf("%i", &opcion);
    switch (opcion)
    {
    case 1:
        
        printf("Introduce el primer numero:\n");
        scanf("%f", &num1);
        printf("Introduce el segundo numero:\n");
        scanf("%f", &num2);
        printf("El resultado de la suma es %f", sumar(num1, num2));
        break;
    
    default:
        break;
    }
}
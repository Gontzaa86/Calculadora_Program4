#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formula.h"

void mostrarMenu(){
    printf("\n");
    printf("Elige una de las siguientes opciones\n");
    printf("1. Realiza una suma\n");
    printf("2. Realiza una resta\n");
    printf("3. Realiza una multiplicacion\n");
    printf("Pulsa 'q' para terminar\n");
}

void main (void){
    char opcion;
    float num1;
    float num2;

    do
    {
        mostrarMenu();

        scanf("%c", &opcion);
        switch (opcion)
            {
            case '1':
                printf("Introduce el primer numero:\n");
                scanf("%f", &num1);
                printf("Introduce el segundo numero:\n");
                scanf("%f", &num2);
                printf("El resultado de la suma es %.2f\n", sumar(num1, num2));
                break;

            case '2':
                printf("Introduce el primer numero:\n");
                scanf("%f", &num1);
                printf("Introduce el segundo numero:\n");
                scanf("%f", &num2);
                printf("El resultado de la resta es %.2f\n", restar(num1, num2));

            case '3':
                printf("Introduce el primer numero:\n");
                scanf("%f", &num1);
                printf("Introduce el segundo numero:\n");
                scanf("%f", &num2);
                printf("El resultado de la multiplicacion es %.2f\n", multiplicar(num1, num2));


            default:
                break;
        }
    fflush(stdin);
    } while (opcion != 'q');
    
    
}
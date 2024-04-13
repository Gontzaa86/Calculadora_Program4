#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formula.h"
#include "binario.h"

char mostrarMenu(){
    char opcion[2];
    printf("\n");
    printf("Elige una de las siguientes opciones\n");
    printf("1. Realiza una suma\n");
    printf("2. Realiza una resta\n");
    printf("3. Realiza una multiplicacion\n");
    printf("4. Realiza una division\n");
    printf("5. Eleva un numero\n");
    printf("6. Realiza una raiz cuadrada\n");
    printf("8. Traduce un numero a binario\n");
    printf("Pulsa 'q' para terminar\n");

    fflush(stdout);
    fgets(opcion, 2, stdin);

    return *opcion;

}

void main (void){
    char opcionTeclado;
    int numeroATransformar; 
    float num1;
    float num2;

    do
    {
        opcionTeclado = mostrarMenu();


        if ((opcionTeclado >= '1' && opcionTeclado <= '9') || opcionTeclado == 'q'){
            /*Al recibir un numero grande como 67 de opcion, la variable al ser un char coge el numero como si fuese 6*/
            fflush(stdin);
            switch (opcionTeclado)
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
                break;

            case '3':
                printf("Introduce el primer numero:\n");
                scanf("%f", &num1);
                printf("Introduce el segundo numero:\n");
                scanf("%f", &num2);
                printf("El resultado de la multiplicacion es %.2f\n", multiplicar(num1, num2));
                break;
            
            case '4':
                printf("Introduce el primer numero:\n");
                scanf("%f", &num1);
                printf("Introduce el segundo numero:\n");
                scanf("%f", &num2);
                printf("El resultado de la division es %.2f\n", division(num1, num2));
                break;

            case '5':
                printf("Introduce la base:\n");
                scanf("%f", &num1);
                printf("Introduce el exponente:\n");
                scanf("%f", &num2);
                printf("El numero elevado es %.2f\n", elevar(num1, num2));
                break;

            case '6':
                printf("Introduce el numero para realizar la raiz cuadrada:\n");
                scanf("%f", &num1);
                printf("El resultado de la raiz es %.2f\n", raizCuadrada(num1));
                break;

            case '8':
                printf("Introduce el numero a transformar:\n");
                scanf("%i", &numeroATransformar);
                InfoBinario ib = binarios(numeroATransformar);

                printf("El numero binario de %i es: \n", numeroATransformar);
                for (int i = 0; i < ib.cantidadBits; i++)
                {
                    printf("%i", ib.numeroBinario[i]);
                }

                free(ib.numeroBinario);

            default:
                break;
        }
        }else{
            printf("Has introducido una opcion no disponible\n");

        }

    fflush(stdin);
    } while (opcionTeclado != 'q');
    
    
}
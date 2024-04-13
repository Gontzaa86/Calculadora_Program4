#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formula.h"
#include "binario.h"
#include <time.h>

#define MAX_DIG 10
#define FIC_LOG "log.txt"

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
    printf("7. Calcula el determinante de una matriz cuadrada\n");
    printf("8. Traduce un numero a binario\n");
    printf("Pulsa 'q' para terminar\n");

    fflush(stdout);
    fgets(opcion, 2, stdin);

    return *opcion;

}

float obtenerDeTeclado(){
    float num;
    char entrada[MAX_DIG];
    fgets(entrada, MAX_DIG, stdin); 
    sscanf(entrada, "%f", &num);
    return num;
}

void main (void){

    FILE* fichero_log = fopen(FIC_LOG, "a");

    time_t tiempo_actual = time(NULL);
    struct tm *local = localtime(&tiempo_actual);

    char formato_tiempo[20];
    strftime(formato_tiempo, sizeof(formato_tiempo), "%d/%m/%y %H:%M:%S", local);

    fprintf(fichero_log, "[%s] Se ha iniciado el programa\n", formato_tiempo);

    char opcionTeclado;
    int numeroATransformarBinario;
    int ordenMatriz; 
    int determinante;
    int **matriz;
    float num1;
    float num2;

    do
    {
        opcionTeclado = mostrarMenu();


        if ((opcionTeclado >= '1' && opcionTeclado <= '9') || opcionTeclado == 'q'){
            /*Al recibir un numero grande como 67 de opcion, la variable al ser un char coge el numero como si fuese 6*/
            fflush(stdin);
            if (opcionTeclado == 'q'){
                fprintf(fichero_log, "[%s] Se ha terminado el programa\n", formato_tiempo);
            }else{
                fprintf(fichero_log, "[%s] Se ha seleccionado la opcion %c del menu\n", formato_tiempo, opcionTeclado);
            }
            
            switch (opcionTeclado)
            {
            case '1':
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la suma es %.2f\n", sumar(num1, num2));
                break;

            case '2':
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la resta es %.2f\n", restar(num1, num2));
                break;

            case '3':
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la multiplicacion es %.2f\n", multiplicar(num1, num2));
                break;
            
            case '4':
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();;
                printf("El resultado de la division es %.2f\n", division(num1, num2));
                break;

            case '5':
                printf("Introduce la base:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el exponente:\n");
                num2 = obtenerDeTeclado();
                printf("El numero elevado es %.2f\n", elevar(num1, num2));
                break;

            case '6':
                printf("Introduce el numero para realizar la raiz cuadrada:\n");
                num1 = obtenerDeTeclado();
                printf("El resultado de la raiz es %.2f\n", raizCuadrada(num1));
                break;

            case '7':
                printf("Ingresa el orden de la matriz cuadrada: \n");
                scanf("%d", &ordenMatriz);

                matriz = (int **)malloc(ordenMatriz * sizeof(int *));
                for (int i = 0; i < ordenMatriz; i++) {
                    matriz[i] = (int *)malloc(ordenMatriz * sizeof(int));
                }

                printf("Ingresa los elementos de la matriz:\n");
                for (int i = 0; i < ordenMatriz; i++) {
                    for (int j = 0; j < ordenMatriz; j++) {
                        printf("Ingresa el elemento [%i][%i]:", i+1, j+1);
                        scanf("%i", &matriz[i][j]);
                        
                    }
                }
                determinante = determinanteMatriz(matriz, ordenMatriz);
                
  
                printf("La matriz completa:\n");
                imprimirMatriz(matriz, ordenMatriz);
                printf("El determinante es: %i\n", determinante);

                for (int i = 0; i < ordenMatriz; i++) {
                    free(matriz[i]);
                }
                free(matriz);

                break;

            case '8':
                printf("Introduce el numero a transformar:\n");
                scanf("%i", &numeroATransformarBinario);
                InfoBinario ib = binarios(numeroATransformarBinario);

                printf("El numero binario de %i es: \n", numeroATransformarBinario);
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
            fprintf(fichero_log, "[%s] El usuario ha elegio una funcion no disponible",  formato_tiempo);
        }

    fflush(stdin);
    } while (opcionTeclado != 'q');
    
    
}
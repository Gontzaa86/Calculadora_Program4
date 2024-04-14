#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formula.h"
#include "binario.h"
#include <time.h>

#define MAX_CAR 20
#define MAX_DIG 10
#define FIC_LOG "log.txt"

char registroMenu(){

    char opcionRegistro[2];
    printf("\nInicia sesion o registrate si no tienes una cuenta antes de usar la calculadora\n");
    printf("Introduce una de las siguientes opciones:\n");
    printf("1. Registrarse\n");
    printf("2. Iniciar sesion\n");

    fflush(stdout);
    fgets(opcionRegistro, 2, stdin);

    return *opcionRegistro;
}

char mostrarMenu(){
    char opcionCalc[2];
    fflush(stdout);
    printf("\n--Bienvenido a la calculadora--\n");
    printf("Elige una de las siguientes opciones\n");
    printf("1. Realiza una suma\n");
    printf("2. Realiza una resta\n");
    printf("3. Realiza una multiplicacion\n");
    printf("4. Realiza una division\n");
    printf("5. Eleva un numero\n");
    printf("6. Realiza una raiz cuadrada\n");
    printf("7. Calcula el determinante de una matriz cuadrada\n");
    printf("8. Calcula el sen\n");
    printf("9. Calcula el cos\n");
    printf("10. Calcula el tag\n");
    printf("11. Traduce un numero a binario\n");
    printf("Pulsa 'q' para terminar\n");

    fflush(stdout);
    fgets(opcionCalc, 2, stdin);

    return *opcionCalc;

}

float obtenerDeTeclado(){
    float num;
    char entrada[MAX_DIG];
    fgets(entrada, MAX_DIG, stdin); 
    sscanf(entrada, "%f", &num);
    return num;
}

void registrarAccion(char *accion, FILE* ficheroLog) {

    time_t tiempoActual = time(NULL);
    struct tm *local = localtime(&tiempoActual);
    
    char formatoTiempo[20];
    strftime(formatoTiempo, sizeof(formatoTiempo), "%d/%m/%y %H:%M:%S", local);
    
    fprintf(ficheroLog, "[%s] %s\n", formatoTiempo, accion);
}

void main (void){

    FILE* ficheroLog = fopen(FIC_LOG, "a");

    registrarAccion("Se ha iniciado el programa", ficheroLog);

    char opcionRegistro;
    int inicioSesionCompletado = 0;
    char nombre[MAX_CAR];
    char contrasenya[MAX_CAR];

    char opcionCalc;
    int numeroATransformarBinario;
    int ordenMatriz; 
    int determinante;
    int **matriz;
    float num1;
    float num2;

    while(inicioSesionCompletado == 0){
        opcionRegistro = registroMenu();   

        if (opcionRegistro == '1'){
            registrarAccion("Se ha iniciado registro de cuenta", ficheroLog);
            fflush(stdin);
            printf("Introduce tu nombre (maximo 20 caracteres):\n");
            fgets(nombre, MAX_CAR, stdin);
            printf("Introduce tu contrasenya (maximo 20 caracteres):\n");
            fgets(contrasenya, MAX_CAR, stdin);
            /*funcion para agregar a la base de datos*/
            printf("Registro completado correctamente\n");
        }else{
            if (opcionRegistro == '2'){
                registrarAccion("Se ha iniciado el inicio de sesion", ficheroLog);
                fflush(stdin);
                printf("Intrduce to nombre:\n");
                fgets(nombre, MAX_CAR, stdin);
                printf("Introduce tu contrasenya:\n");
                fgets(contrasenya, MAX_CAR, stdin);
                /*funcion para verficar*/
                inicioSesionCompletado = 1; /*Si se ha completado correctamente*/
            }else{
                fflush(stdin);
                printf("Haz introducido una opcion no disponible\n");
                registrarAccion("El usuario ha introducido una opcion de registro no disponible", ficheroLog);
            }       
        }    
    }
    registrarAccion("El usuario ha completado el resgitro, se inicia la calculadora", ficheroLog);


    do
    {
        opcionCalc = mostrarMenu();


        if ((opcionCalc >= '1' && opcionCalc <= '9') || opcionCalc == 'q'){
            /*Al recibir un numero grande como 67 de opcion, la variable al ser un char coge el numero como si fuese 6*/
            fflush(stdin);
            if (opcionCalc == 'q'){
                registrarAccion("Se ha terminado el programa", ficheroLog);
            }
            
            switch (opcionCalc)
            {
            case '1':
                registrarAccion("Se ha seleccionado la opcion 1 del menu", ficheroLog);
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la suma es %.2f\n", sumar(num1, num2));
                break;

            case '2':
                registrarAccion("Se ha seleccionado la opcion 2 del menu", ficheroLog);
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la resta es %.2f\n", restar(num1, num2));
                break;

            case '3':
                registrarAccion("Se ha seleccionado la opcion 3 del menu", ficheroLog);
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la multiplicacion es %.2f\n", multiplicar(num1, num2));
                break;
            
            case '4':
                registrarAccion("Se ha seleccionado la opcion 4 del menu", ficheroLog);
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();;
                printf("El resultado de la division es %.2f\n", division(num1, num2));
                break;

            case '5':
                registrarAccion("Se ha seleccionado la opcion 5 del menu", ficheroLog);
                printf("Introduce la base:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el exponente:\n");
                num2 = obtenerDeTeclado();
                printf("El numero elevado es %.2f\n", elevar(num1, num2));
                break;

            case '6':
                registrarAccion("Se ha seleccionado la opcion 6 del menu", ficheroLog);
                printf("Introduce el numero para realizar la raiz cuadrada:\n");
                num1 = obtenerDeTeclado();
                printf("El resultado de la raiz es %.2f\n", raizCuadrada(num1));
                break;

            case '7':
                registrarAccion("Se ha seleccionado la opcion 7 del menu", ficheroLog);
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
                registrarAccion("Se ha seleccionado la opcion 8 del menu", ficheroLog);
                double angle = 45.0;
                double radians = angle * M_PI / 180.0;
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("El resultado de la suma es %.2f\n", sen(num1));
                break;
            
            case '9':
                registrarAccion("Se ha seleccionado la opcion 9 del menu", ficheroLog);
                double angle = 45.0;
                double radians = angle * M_PI / 180.0;
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("El resultado de la suma es %.2f\n", cos(num1));
                break;
            
            case '10':
                registrarAccion("Se ha seleccionado la opcion 10 del menu", ficheroLog);
                double angle = 45.0;
                double radians = angle * M_PI / 180.0;
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("El resultado de la suma es %.2f\n", tag(num1));
                break;



            case '11':
                registrarAccion("Se ha seleccionado la opcion 11 del menu", ficheroLog);
                printf("Introduce el numero a transformar:\n");
                scanf("%i", &numeroATransformarBinario);
                InfoBinario ib = binarios(numeroATransformarBinario);

                printf("El numero binario de %i es: ", numeroATransformarBinario);
                for (int i = 0; i < ib.cantidadBits; i++)
                {
                    printf("%i", ib.numeroBinario[i]);
                }
                printf("\n");
                free(ib.numeroBinario);

            default:
                break;
        }
        }else{
            printf("Has introducido una opcion no disponible\n");
            registrarAccion("El usuario ha elegido una funcion no disponible", ficheroLog);
        }

    fflush(stdin);
    } while (opcionCalc != 'q');
    
    fclose(ficheroLog);
}

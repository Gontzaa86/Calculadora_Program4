#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formula.h"
#include "binario.h"
#include "sqlite3.h"
#include <time.h>
#include <math.h>

#define MAX_CAR 20
#define MAX_DIG 10
#define FIC_LOG "log.txt"
#define MAX_OPERACION 6
#define ALTURA_GRAFICO 10
const char* operaciones[] = {"Suma", "Resta", "Multi", "Divis", "Expon", "RaizC"};

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
    printf("7. Dibujar grafico con las frecuencias del BD\n");
    printf("8. Traduce un numero a binario\n");
    printf("9. Traduce de binario a un numero decimal\n");
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

char* obtenerHoraActual() {
    time_t tiempo_actual = time(NULL);
    struct tm *local = localtime(&tiempo_actual);
    
    char *cadena_hora = (char *)malloc(11 * sizeof(char));
    
    strftime(cadena_hora, 11, "%d-%m-%Y", local);
    
    return cadena_hora;
}

void insertarUsuario(sqlite3 *db, char nombre[MAX_CAR], char contrasenya[MAX_CAR])
{
    char sql_insert_usuario[100];
    sprintf(sql_insert_usuario, "INSERT INTO Usuario (Nombre, contraseña) VALUES ('%s', '%s');", nombre, contrasenya);

    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(db, sql_insert_usuario, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error SQL al insertar datos en Usuario: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        /*fprintf(stdout, "Datos insertados en Usuario exitosamente\n");*/
    }
}

void insertarOperacion(sqlite3 *db, int operando1, int operando2, int resultado, char* fecha, char* nombre, int id_operacion)
{
    char sql_insert_operacion[200];
    sprintf(sql_insert_operacion, "INSERT INTO Operacion (Operando1, Operando2, Resultado, Fecha, Nombre, ID_Operacion) VALUES (%d, %d, %d, '%s', '%s', %d);", operando1, operando2, resultado, fecha, nombre, id_operacion);

    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(db, sql_insert_operacion, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error SQL al insertar datos en Operacion: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        /*fprintf(stdout, "Datos insertados en Operacion exitosamente\n");*/
    }
}

int contar_id_operacion(sqlite3 *db, int *num_operaciones) {
    sqlite3_stmt *stmt;
    int rc;
    const char *sql;

    for (int i = 0; i <= MAX_OPERACION; i++) {
        num_operaciones[i] = 0;
    }
    sql = "SELECT ID_operacion FROM Operacion";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_operacion = sqlite3_column_int(stmt, 0);
        if (id_operacion >= 1 && id_operacion <= MAX_OPERACION) {
            num_operaciones[id_operacion]++;
        }
    }

    sqlite3_finalize(stmt);

    return SQLITE_OK;
}

void dibujarGraficoFrecu(int* num_operaciones){
    int valorMax = 0;
    for (int i = 1; i < MAX_OPERACION+1; i++){
        if (num_operaciones[i] > valorMax){
            valorMax = num_operaciones[i];
        }
    }

    int escala = valorMax > ALTURA_GRAFICO ? (valorMax + ALTURA_GRAFICO - 1) / ALTURA_GRAFICO : 1;

    printf("\nGRAFICO:\n\n");
    for (int nivel = ALTURA_GRAFICO; nivel > 0; nivel--) {
        printf("%2i |", nivel * escala);
        for (int i = 1; i < MAX_OPERACION+1; i++) {
            if (num_operaciones[i] / escala >= nivel) {
                printf("  ||  ");
            } else {
                printf("      ");
            }
        }
        printf("\n");
    }
    printf(" 0 |");
    for (int i = 0; i < MAX_OPERACION; i++) {
        printf("------");
    }
    printf("\n");

    printf("    ");
    for (int i = 0; i < MAX_OPERACION; i++) {
        printf("%5s ", operaciones[i]);
    }
    printf("\n");
    
}

void main (void){

    FILE* ficheroLog = fopen(FIC_LOG, "a");

    registrarAccion("Se ha iniciado el programa", ficheroLog);

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    int num_operaciones[MAX_OPERACION + 1];

    rc = sqlite3_open("database.db", &db);
    if (rc) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "Base de datos abierta exitosamente\n");
    }

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
            insertarUsuario(db, nombre, contrasenya);
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
                insertarOperacion(db, num1, num2, sumar(num1, num2), obtenerHoraActual(), nombre, 1);
                break;

            case '2':
                registrarAccion("Se ha seleccionado la opcion 2 del menu", ficheroLog);
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la resta es %.2f\n", restar(num1, num2));
                insertarOperacion(db, num1, num2, restar(num1, num2), obtenerHoraActual(), nombre, 2);
                break;

            case '3':
                registrarAccion("Se ha seleccionado la opcion 3 del menu", ficheroLog);
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();
                printf("El resultado de la multiplicacion es %.2f\n", multiplicar(num1, num2));
                insertarOperacion(db, num1, num2, multiplicar(num1, num2), obtenerHoraActual(), nombre, 3);
                break;
            
            case '4':
                registrarAccion("Se ha seleccionado la opcion 4 del menu", ficheroLog);
                printf("Introduce el primer numero:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el segundo numero:\n");
                num2 = obtenerDeTeclado();;
                printf("El resultado de la division es %.2f\n", division(num1, num2));
                insertarOperacion(db, num1, num2, division(num1, num2), obtenerHoraActual(), nombre, 4);
                break;

            case '5':
                registrarAccion("Se ha seleccionado la opcion 5 del menu", ficheroLog);
                printf("Introduce la base:\n");
                num1 = obtenerDeTeclado();
                printf("Introduce el exponente:\n");
                num2 = obtenerDeTeclado();
                printf("El numero elevado es %.2f\n", elevar(num1, num2));
                insertarOperacion(db, num1, num2, elevar(num1, num2), obtenerHoraActual(), nombre, 5);
                break;

            case '6':
                registrarAccion("Se ha seleccionado la opcion 6 del menu", ficheroLog);
                printf("Introduce el numero para realizar la raiz cuadrada:\n");
                num1 = obtenerDeTeclado();
                printf("El resultado de la raiz es %.2f\n", raizCuadrada(num1));
                insertarOperacion(db, num1, 2, raizCuadrada(num1), obtenerHoraActual(), nombre, 6);
                break;

            case '7':
                registrarAccion("Se ha seleccionado la opcion 7 del menu", ficheroLog);
                /*printf("Ingresa el orden de la matriz cuadrada: \n");
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
                free(matriz);*/
                contar_id_operacion(db, num_operaciones);
                dibujarGraficoFrecu(num_operaciones);

                break;

            case '8':
                registrarAccion("Se ha seleccionado la opcion 8 del menu", ficheroLog);
                printf("Introduce el numero a transformar a binario:\n");
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
            
            case'9':
                registrarAccion("Se ha seleccionado la opcion 9 del menu", ficheroLog);
                long long binario;
                printf("Ingrese un numero binario: ");
                scanf("%lld", &binario);
                int decimal = binario_a_decimal(binario);
                printf("El equivalente decimal es: %d\n", decimal);
        }
        }else{
            printf("Has introducido una opcion no disponible\n");
            registrarAccion("El usuario ha elegido una funcion no disponible", ficheroLog);
        }

    fflush(stdin);
    } while (opcionCalc != 'q');
    
    fclose(ficheroLog);
    sqlite3_close(db);
}

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

void intercambiarFilas(int **matriz, int fila1, int fila2, int columnas) {
    imprimirMatriz(matriz, 3);
    int *temp = matriz[fila1];
    matriz[fila1] = matriz[fila2];
    matriz[fila2] = temp;
    imprimirMatriz(matriz, 3);
}



int determinanteMatriz(int **matriz, int orden) {
    int det = 1;
    int intercambios = 0;

    // Aplicar eliminación gaussiana para convertir la matriz en una matriz triangular superior
    for (int k = 0; k < orden - 1; k++) {
        if (matriz[k][k] == 0) {
            // Si el elemento diagonal es cero, intercambiar filas para encontrar un elemento no cero
            int filaNoNula = k + 1;
            while (filaNoNula < orden && matriz[filaNoNula][k] == 0) {
                filaNoNula++;
            }
            if (filaNoNula == orden) {
                // Si todas las entradas debajo del elemento diagonal son cero, el determinante es cero
                return 0;
            }
            intercambiarFilas(matriz, k, filaNoNula, orden);
            intercambios++;
        }
        for (int i = k + 1; i < orden; i++) {
            int factor = matriz[i][k] / matriz[k][k];
            for (int j = k; j < orden; j++) {
                matriz[i][j] -= factor * matriz[k][j];
            }
        }
    }

    // Calcular el determinante multiplicando los elementos diagonales de la matriz triangular superior
    for (int i = 0; i < orden; i++) {
        det *= matriz[i][i];
    }

    // Aplicar el cambio de signo según el número de intercambios de filas realizados
    if (intercambios % 2 == 1) {
        det *= -1;
    }

    return det;
}

void imprimirMatriz(int **matriz, int orden) {
    for (int i = 0; i < orden; i++) {
        for (int j = 0; j < orden; j++) {
            printf("%i\t", matriz[i][j]);
        }
        printf("\n");
    }
}
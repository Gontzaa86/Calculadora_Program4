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
    int *temp = matriz[fila1];
    matriz[fila1] = matriz[fila2];
    matriz[fila2] = temp;
}



int determinanteMatriz(int **matriz, int orden) {
    int det = 1;
    int signo = 1;

    for (int k = 0; k < orden - 1; k++) {
        if (matriz[k][k] == 0) {
            
            int filaNoNula = k + 1;
            while (filaNoNula < orden && matriz[filaNoNula][k] == 0) {
                filaNoNula++;
            }
            if (filaNoNula == orden) {
                return 0;
            }
            intercambiarFilas(matriz, k, filaNoNula, orden);
            signo *= -1; 
        }
        for (int i = k + 1; i < orden; i++) {
            int factor = matriz[i][k] / matriz[k][k];
            for (int j = k; j < orden; j++) {
                matriz[i][j] -= factor * matriz[k][j];
            }
        }
    }
    for (int i = 0; i < orden; i++) {
        det *= matriz[i][i];
    }

    return det * signo;
}

void imprimirMatriz(int **matriz, int orden) {
    for (int i = 0; i < orden; i++) {
        for (int j = 0; j < orden; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}
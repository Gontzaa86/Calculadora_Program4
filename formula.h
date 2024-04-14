#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_


float sumar(float x, float y);
float restar(float x, float y);
float multiplicar(float x, float y);
float division(float x, float y);
float elevar(float x, float y);
float raizCuadrada(float x);
void intercambiarFilas(int **matriz, int fila1, int fila2, int columnas);
int determinanteMatriz(int **matriz, int orden);
void imprimirMatriz(int **matriz, int orden);
double sen(double x);
double cos(double x);
double tag(double x);

#endif

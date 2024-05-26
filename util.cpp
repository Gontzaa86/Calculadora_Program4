#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

std::string leerDatosConexion(int fila){
    std:: ifstream file("conexion.txt");
    std::string dato;

    int linea = 1;

    while (1){
        if (linea == fila){
            std::getline(file, dato, ',');
            std::getline(file, dato);
            return dato;
        }else{
            std::getline(file, dato);
            linea++;
        }
    }
    
}
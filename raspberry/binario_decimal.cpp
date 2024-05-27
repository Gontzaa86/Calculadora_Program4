#include <iostream>
#include <string>

int binaryToDecimal(const std::string &binary) {
    int decimal = 0;
    int power = 1; // Inicializar la potencia de 2

    // Iterar sobre cada dígito binario de derecha a izquierda
    for (int i = binary.length() - 1; i >= 0; --i) {
        // Convertir el carácter en el dígito binario correspondiente (0 o 1)
        int digit = binary[i] - '0';

        // Sumar al resultado el valor del dígito multiplicado por la potencia de 2 actual
        decimal += digit * power;

        // Actualizar la potencia de 2 para el siguiente dígito
        power *= 2;
    }

    return decimal;
}

int main() {
    // Pedir al usuario un número binario
    std::string binary;
    std::cout << "Ingrese un número binario: ";
    std::cin >> binary;

    // Verificar si el número binario es válido
    for (char bit : binary) {
        if (bit != '0' && bit != '1') {
            std::cerr << "Error: El número binario ingresado no es válido." << std::endl;
            return 1;
        }
    }

    // Convertir a decimal
    int decimal = binaryToDecimal(binary);

    // Mostrar el resultado
    std::cout << "El número decimal equivalente es: " << decimal << std::endl;

    return 0;
}

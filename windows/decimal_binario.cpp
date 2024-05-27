#include <iostream>
#include <stack>

std::string decimalToBinary(int decimal) {
    std::stack<int> binaryDigits;

    // Convertir a binario
    while (decimal > 0) {
        binaryDigits.push(decimal % 2);
        decimal /= 2;
    }

    // Construir el string binario
    std::string binaryStr = "";
    while (!binaryDigits.empty()) {
        binaryStr += std::to_string(binaryDigits.top());
        binaryDigits.pop();
    }

    return binaryStr;
}

int main() {
    // Pedir al usuario un número decimal
    int decimal;
    std::cout << "Ingrese un número decimal: ";
    std::cin >> decimal;

    // Convertir a binario
    std::string binary = decimalToBinary(decimal);

    // Mostrar el resultado
    std::cout << "El número binario equivalente es: " << binary << std::endl;

    return 0;
}

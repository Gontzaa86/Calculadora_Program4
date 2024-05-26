#include "binarioCpp.h"
#include <cmath>
#include <string>

std::string transformarBinario(int numero) 
{
    if (numero == 0) return "0";
    std::string binario = "";
    while (numero > 0) 
    {
        binario = (numero % 2 == 0 ? "0" : "1") + binario;
        numero /= 2;
    }
    return binario;
}

int transformarEntero(const std::string& binario)
{
    int numero = 0;
    int potencia = 0;
    for (int i = binario.length() - 1; i >= 0; --i) 
    {
        if (binario[i] == '1') {
            numero += std::pow(2, potencia);
        }
        ++potencia;
    }
    return numero;
}

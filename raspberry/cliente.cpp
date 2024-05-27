// cliente.cpp
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7070
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Crear el socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        std::cerr << "Error al crear el socket" << std::endl;
        return 1;
    }

    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Conectar al servidor
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error al conectar con el servidor" << std::endl;
        close(client_fd);
        return 1;
    }

    // Variable para almacenar la elección del usuario
    char choice;

    // Bucle para enviar múltiples opciones al servidor
    do {
        // Solicitar la elección al usuario
        std::cout << "Ingrese 1 para calculadora, 2 para binario a decimal, 3 para decimal a binario, 4 para encender LEDs y 0 para cerrar la sesión: ";
        std::cin >> choice;

        // Enviar la elección al servidor
        send(client_fd, &choice, sizeof(choice), 0);

        // Si elige 1, abrir el archivo ejecutable
        if (choice == '1') {
            system("./main"); // Reemplaza "archivo_ejecutable" con el nombre del archivo que deseas ejecutar
        } else if (choice == '2') {
            system("./binariodecimal"); // Asumiendo que el script se llama 'LED.py' y está en el mismo directorio
        } else if (choice == '3') {
            system("./decimalbinario"); // Reemplaza "proceso_grafico" con el nombre del proceso que deseas ejecutar
        } else if (choice == '4') {
            system("sudo python3 LED.py"); // Reemplaza "otro_archivo" con el nombre del archivo que deseas ejecutar
        }

    } while (choice != '0');

    // Cerrar el socket
    close(client_fd);
    return 0;
}

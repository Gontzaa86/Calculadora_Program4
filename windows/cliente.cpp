#include <iostream>
#include <cstring>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7070
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al inicializar Winsock" << std::endl;
        return 1;
    }

    // Crear el socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket" << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Conectar al servidor
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error al conectar con el servidor" << std::endl;
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    // Variable para almacenar la elección del usuario
    char choice;

    // Bucle para enviar múltiples opciones al servidor
    do {
        // Solicitar la elección al usuario
        std::cout << "Ingrese 1 para calculadora, 2 para binario a decimal, 3 para decimal a binario, y 0 para cerrar la sesión: ";
        std::cin >> choice;

        // Enviar la elección al servidor
        send(client_fd, &choice, sizeof(choice), 0);

        // Si elige 1, abrir el archivo ejecutable
        if (choice == '1') {
            system("main.exe"); // Reemplaza "main.exe" con el nombre del archivo ejecutable de la calculadora
        } else if (choice == '2') {
            system("binariodecimal.exe"); // Reemplaza "binariodecimal.exe" con el nombre del archivo ejecutable para binario a decimal
        } else if (choice == '3') {
            system("decimalbinario.exe"); // Reemplaza "decimalbinario.exe" con el nombre del archivo ejecutable para decimal a binario
        }

    } while (choice != '0');

    // Cerrar el socket
    shutdown(client_fd, SD_SEND);
    closesocket(client_fd);
    WSACleanup();
    return 0;
}

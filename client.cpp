// cliente.cpp
#include <iostream>
#include <winsock2.h>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Error al inicializar Winsock: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Crear el socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Conectar al servidor
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error al conectar con el servidor." << std::endl;
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    // Solicitar la elección al usuario
    std::cout << "Ingrese 1 para abrir el archivo ejecutable o 0 para cerrar la sesión: ";
    char choice;
    std::cin >> choice;

    // Enviar la elección al servidor
    send(client_fd, &choice, sizeof(choice), 0);

    // Si elige 1, abrir el archivo ejecutable
    if (choice == '1') {
        system("main.exe");
    }

    // Cerrar el socket
    closesocket(client_fd);
    WSACleanup();
    return 0;
}

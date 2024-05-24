// servidor.cpp
#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Error al inicializar Winsock: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar la dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    // Enlazar el socket a la dirección del servidor
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Error al enlazar el socket: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Escuchar las conexiones entrantes
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Error al escuchar: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "Esperando conexiones...\n";

    // Aceptar una conexión entrante
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
        std::cerr << "Error al aceptar la conexión: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Leer el mensaje del cliente
    recv(new_socket, buffer, BUFFER_SIZE, 0);
    std::cout << "Mensaje recibido del cliente: " << buffer << std::endl;

    // Procesar la elección del cliente
    if (buffer[0] == '1') {
        std::cout << "Procesando calculadora..." << std::endl;
        // Aquí puedes agregar el código para ejecutar el archivo ejecutable en el cliente
    } else if (buffer[0] == '0') {
        std::cout << "Cerrando sesión..." << std::endl;
    } else {
        std::cerr << "Elección no válida." << std::endl;
    }

    // Cerrar el socket
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}

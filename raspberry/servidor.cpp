// servidor.cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 7070
#define BUFFER_SIZE 1024

void mostrarMenu() {
    std::cout << "Menu de opciones:\n";
    std::cout << "1. Calculadora\n";
    std::cout << "2. Binario a Decimal\n";
    std::cout << "3. Decimal a Binario\n";
    std::cout << "4. Binario en LED\n";
    std::cout << "5. Salir\n";
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Crear el socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Error al crear el socket" << std::endl;
        return 1;
    }

    // Configurar la dirección del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    // Enlazar el socket a la dirección del servidor
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Error al enlazar el socket" << std::endl;
        close(server_fd);
        return 1;
    }

    // Escuchar las conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Error al escuchar" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "Esperando conexiones...\n";

    // Bucle principal del servidor para manejar conexiones
    while (true) {
        // Aceptar una conexión entrante
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            std::cerr << "Error al aceptar la conexión" << std::endl;
            close(server_fd);
            return 1;
        }

        std::cout << "Conexion establecida con el cliente.\n";
        mostrarMenu();

        // Bucle para mantener la conexión con el cliente
        while (true) {
            // Leer el mensaje del cliente
            int valread = recv(new_socket, buffer, BUFFER_SIZE, 0);
            if (valread <= 0) {
                std::cerr << "Error al leer del cliente o conexion cerrada" << std::endl;
                break;
            }
            std::cout << "Mensaje recibido del cliente: " << buffer << std::endl;

            // Procesar la elección del cliente
            if (buffer[0] == '1') {
                std::cout << "Procesando calculadora..." << std::endl;
            } else if (buffer[0] == '2') {
                std::cout << "Procesando binario a decimal..." << std::endl;
            } else if (buffer[0] == '3') {
                std::cout << "Procesando decimal a binario..." << std::endl;
            } else if (buffer[0] == '4') {
                std::cout << "Procesando binario en LED..." << std::endl;
            } else if (buffer[0] == '5') {
                std::cout << "Cerrando sesion..." << std::endl;
                close(new_socket);
                close(server_fd);
                return 0; // Salir del programa
            } else {
                std::cerr << "Eleccion no valida." << std::endl;
            }
        }

        // Cerrar el socket para esta conexión
        close(new_socket);
    }

    // Cerrar el socket principal del servidor
    close(server_fd);
    return 0;
}

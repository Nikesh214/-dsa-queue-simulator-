#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5000
#define BUFFER_SIZE 100

volatile BOOL keepRunning = TRUE;

/* Ctrl+C handler */
BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        keepRunning = FALSE;
        printf("\nCtrl+C detected. Shutting down server...\n");
        return TRUE;
    }
    return FALSE;
}

int main(void) {
    WSADATA wsa;
    SOCKET server_fd = INVALID_SOCKET;
    SOCKET client_socket = INVALID_SOCKET;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    /* Initialize Winsock */
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error code: %d\n", WSAGetLastError());
        return 1;
    }

    /* Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    /* Bind address */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    /* Start listening */
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);
    printf("Press Ctrl+C to stop the server.\n");

    /* Accept client */
    client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Client connected...\n");

    /* Receive loop */
    while (keepRunning) {
        int bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

        if (bytes_read <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }

    /* Cleanup */
    if (client_socket != INVALID_SOCKET)
        closesocket(client_socket);

    if (server_fd != INVALID_SOCKET)
        closesocket(server_fd);

    WSACleanup();
    printf("Server shut down cleanly.\n");

    return 0;
}

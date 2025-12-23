#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define PIPE_NAME "\\\\.\\pipe\\VehicleQueue"
#define MAX_TEXT 128

/* Function to get current time as string */
void getCurrentTime(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%H:%M:%S", t);
}

int main() {
    HANDLE hPipe;
    char buffer[MAX_TEXT];
    DWORD bytesRead;

    printf("Connecting to vehicle pipe...\n");

    hPipe = CreateFileA(
        PIPE_NAME,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to connect to pipe. Error: %lu\n", GetLastError());
        return 1;
    }

    printf("Connected! Receiving vehicle data...\n");
    printf("Press Ctrl+C to exit.\n\n");

    while (1) {
        BOOL success = ReadFile(
            hPipe,
            buffer,
            MAX_TEXT - 1,
            &bytesRead,
            NULL
        );

        if (!success || bytesRead == 0) {
            printf("Pipe read failed or generator disconnected. Exiting...\n");
            break;
        }

        buffer[bytesRead] = '\0'; // Null-terminate string

        char timestamp[20];
        getCurrentTime(timestamp, sizeof(timestamp));

        printf("[%s] Received: %s\n", timestamp, buffer);
    }

    CloseHandle(hPipe);
    printf("Pipe closed. Receiver exiting.\n");

    return 0;
}

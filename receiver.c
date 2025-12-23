#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <signal.h>

#define PIPE_NAME "\\\\.\\pipe\\VehicleQueue"
#define MAX_TEXT 128

volatile sig_atomic_t keepRunning = 1;

/* Ctrl+C handler */
void handleSignal(int signal) {
    (void)signal;
    keepRunning = 0;
}

/* Get current time as string */
void getCurrentTime(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%H:%M:%S", t);
}

int main() {
    signal(SIGINT, handleSignal);  // Handle Ctrl+C

    HANDLE hPipe;
    char buffer[MAX_TEXT];
    DWORD bytesRead;
    int messageCount = 0;

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

    while (keepRunning) {
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
        messageCount++;

        char timestamp[20];
        getCurrentTime(timestamp, sizeof(timestamp));

        printf("[%s] Received: %s | Total messages: %d\n", timestamp, buffer, messageCount);
    }

    CloseHandle(hPipe);
    printf("\nPipe closed. Receiver exiting. Total messages received: %d\n", messageCount);

    return 0;
}

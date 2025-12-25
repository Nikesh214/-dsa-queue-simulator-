#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <signal.h>

#define PIPE_NAME "\\\\.\\pipe\\VehicleQueue"
#define MAX_TEXT 128

// Global flag to control program loop
volatile sig_atomic_t keepRunning = 1;

// Ctrl+C handler
void handleSignal(int signal) {
    (void)signal; // Avoid unused parameter warning
    keepRunning = 0;
}

// Function to get current time as HH:MM:SS string
void getCurrentTime(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%H:%M:%S", t);
}

int main() {
    // Register Ctrl+C handler
    signal(SIGINT, handleSignal);

    HANDLE hPipe;
    char buffer[MAX_TEXT];
    DWORD bytesRead;
    int messageCount = 0;

    printf("Connecting to vehicle pipe...\n");

    // Open the named pipe for reading
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

    // Main loop: read messages until Ctrl+C or pipe disconnect
    while (keepRunning) {
        BOOL success = ReadFile(
            hPipe,
            buffer,
            MAX_TEXT - 1, // leave space for null terminator
            &bytesRead,
            NULL
        );

        if (!success || bytesRead == 0) {
            printf("Pipe read failed or generator disconnected. Exiting...\n");
            break;
        }

        buffer[bytesRead] = '\0'; // Null-terminate the string
        messageCount++;

        char timestamp[20];
        getCurrentTime(timestamp, sizeof(timestamp));

        printf("[%s] Received: %s | Total messages: %d\n", timestamp, buffer, messageCount);
    }

    // Clean up
    CloseHandle(hPipe);
    printf("\nPipe closed. Receiver exiting. Total messages received: %d\n", messageCount);

    return 0;
}

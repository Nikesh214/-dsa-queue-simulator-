#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

#define FILENAME "vehicles.data"

volatile sig_atomic_t keepRunning = 1;

/* Handle Ctrl+C gracefully */
void handleSignal(int signal) {
    (void)signal;
    keepRunning = 0;
}

/* Generate a random vehicle number (8 characters) */
void generateVehicleNumber(char *buffer) {
    buffer[0] = 'A' + rand() % 26;
    buffer[1] = 'A' + rand() % 26;
    buffer[2] = '0' + rand() % 10;
    buffer[3] = 'A' + rand() % 26;
    buffer[4] = 'A' + rand() % 26;
    buffer[5] = '0' + rand() % 10;
    buffer[6] = '0' + rand() % 10;
    buffer[7] = '0' + rand() % 10;
    buffer[8] = '\0';
}

/* Generate a random lane (A–D) */
char generateLane() {
    char lanes[] = { 'A', 'B', 'C', 'D' };
    return lanes[rand() % 4];
}

/* Generate a random speed (1–5) */
int generateSpeed() {
    return 1 + rand() % 5;
}

int main() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    /* Register Ctrl+C handler */
    signal(SIGINT, handleSignal);

    srand((unsigned int)time(NULL));

    printf("Vehicle logger started. Press Ctrl+C to stop.\n");

    while (keepRunning) {
        char vehicle[9];
        generateVehicleNumber(vehicle);
        char lane = generateLane();
        int speed = generateSpeed();

        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%H:%M:%S", t);

        /* Write to file: Vehicle:Lane:Speed:Timestamp */
        fprintf(file, "%s:%c:%d:%s\n", vehicle, lane, speed, timestamp);
        fflush(file);

        printf("[%s] Vehicle: %s | Lane: %c | Speed: %d\n",
               timestamp, vehicle, lane, speed);

        SLEEP_MS(1000);
    }

    printf("\nShutting down. File closed safely.\n");
    fclose(file);
    return 0;
}

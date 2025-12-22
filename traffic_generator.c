#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // For Sleep()

#define FILENAME "vehicles.data"

// Function to generate a random vehicle number
void generateVehicleNumber(char* buffer) {
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

// Function to generate a random lane
char generateLane() {
    char lanes[] = {'A', 'B', 'C', 'D'};
    return lanes[rand() % 4];
}

// Function to generate a random speed (1–5)
int generateSpeed() {
    return 1 + rand() % 5;
}

int main() {
    // Open file in append mode
    FILE* file = fopen(FILENAME, "a");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    srand((unsigned int)time(NULL)); // Initialize random seed

    while (1) {
        char vehicle[9];
        generateVehicleNumber(vehicle);
        char lane = generateLane();
        int speed = generateSpeed();

        // Get current timestamp
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%H:%M:%S", t);

        // Write to file: Vehicle:Lane:Speed:Timestamp
        fprintf(file, "%s:%c:%d:%s\n", vehicle, lane, speed, timestamp);
        fflush(file); // Ensure immediate writing

        // Print to console for monitoring
        printf("[%s] Generated: %s | Lane: %c | Speed: %d\n",
               timestamp, vehicle, lane, speed);

        Sleep(1000); // Wait 1 second
    }

    fclose(file);
    return 0;
}

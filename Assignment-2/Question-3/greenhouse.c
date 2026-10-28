/*
* Name: Ahmed Abbasi
* Student ID: 26K-0004
* Program Name: greenhouse.c
* Program Description: This program simulates a greenhouse temperature control system.
* Date: 2026-10-27 (YYYY-MM-DD)
*/

#include <stdio.h>
#include <stdlib.h>

// Inputs all temperature readings into the 2D array
void inputReadings(int **temp, int sensors, int hours) {
    int s, h;
    for (s = 0; s < sensors; s++) {
        printf("Sensor %d: \n", s + 1);
        for (h = 0; h < hours; h++){
            printf("Hour %d: ", h + 1);
            scanf("%d", &temp[s][h]);
        }
    }
} // end inputReadings()

// Analyzes one sensor's readings and prints its report
void analyzeSensor(int *readings, int hours, int sensorNo) {
    int h, total = 0;
    int max = readings[0], min = readings[0];
    int critical = 0, warning = 0;
    int streak = 0, longest = 0;
    float average;

    for (h = 0; h < hours; h++) {
        total += readings[h];
        if (readings[h] > max) max = readings[h];
        if (readings[h] < min) min = readings[h];

        if (readings[h] >= 40)                  // critical: 40 or above
            critical++;
        else if (readings[h] >= 35)             // warning: 35 to 39
            warning++;

        if (readings[h] >= 35) {                // hot streak: 35 or above
            streak++;
            if (streak > longest)
                longest = streak;
        } else {
            streak = 0;                         // a reading below 35 ends the streak
        }
    }
    average = (float)total / hours;

    printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n", sensorNo, total, average, max, min);
    printf("          Critical=%d Warning=%d Longest hot streak=%d\n", critical, warning, longest);
} // end analyzeSensor()

// Returns the index of the sensor with the highest average
int highestAverageSensor(int **temp, int sensors, int hours) {
    int s, h, sum, best = 0;
    float avg, bestAvg = 0;

    for (s = 0; s < sensors; s++) {
        sum = 0;
        for (h = 0; h < hours; h++)
            sum += temp[s][h];
        avg = (float)sum / hours;
        if (avg > bestAvg) {
            bestAvg = avg;
            best = s;
        }
    }
    return best;
} // end highestAverageSensor()

int main() {
    int sensors, hours, s, h, best, sum = 0;
    int **temp;

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    // allocate the matrix: one row per sensor, one column per hour
    temp = (int**)malloc(sensors * sizeof(int*));
    for (s = 0; s < sensors; s++)
        temp[s] = (int*)malloc(hours * sizeof(int));

    inputReadings(temp, sensors, hours);

    printf("\n");
    for (s = 0; s < sensors; s++)
        analyzeSensor(temp[s], hours, s + 1);   // temp[s] is the row of sensor s

    best = highestAverageSensor(temp, sensors, hours);
    for (h = 0; h < hours; h++)
        sum += temp[best][h];
    printf("\nHighest average: Sensor %d (%.2f)\n", best + 1, (float)sum / hours);

    // free the memory: rows first, then the row pointers
    for (s = 0; s < sensors; s++)
        free(temp[s]);
    free(temp);

    return 0;
} // end main()

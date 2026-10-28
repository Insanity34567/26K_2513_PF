#include <stdio.h>
/* 
 * Header: Greenhouse_Monitoring.c
 * Description: Greenhouse Temperature Monitoring System
 * Author: Aman Kumar
 */
#define MAX_HOURS 100
//Input Function: Stores all temperature readings into the 2D array
void inputReadings(int sensors, int readings, int temps[][MAX_HOURS]) {
    for (int r = 0; r < sensors; r++) {
        printf("Enter %d temperature readings for Sensor %d: ", readings, r + 1);
        for (int c = 0; c < readings; c++) {
            scanf("%d", &temps[r][c]);
        }
    }
}

//Sensor Analysis Function: Calculates stats for a single sensor and returns its average
float analyzeSensor(int sensorId, int readings, int row[]) {
    int total = 0;
    int max = row[0];
    int min = row[0];
    int critical = 0;
    int warning = 0;
    int current_streak = 0;
    int longest_streak = 0;

    for (int i = 0; i < readings; i++) {
        int temp = row[i];
        
        total += temp;
        if (temp > max) max = temp;
        if (temp < min) min = temp;

        if (temp >= 40) {
            critical++;
        } else if (temp >= 35 && temp <= 39) {
            warning++;
        }

        if (temp >= 35) {
            current_streak++;
            if (current_streak > longest_streak) {
                longest_streak = current_streak;
            }
        } else {
            current_streak = 0; // Reset streak if reading drops below 35
        }
    }

    float avg = (float)total / readings;

    printf("Sensor %d: Total=%d  Avg=%.2f  Max=%d  Min=%d\n", sensorId, total, avg, max, min);
    printf("          Critical=%d  Warning=%d  Longest hot streak=%d\n\n", critical, warning, longest_streak);

    return avg;
}

//Highest Average Function: Determines and returns the sensor number with the highest average
int getHighestAverageSensor(int sensors, float averages[]) {
    int max_index = 0;
    for (int i = 1; i < sensors; i++) {
        if (averages[i] > averages[max_index]) {
            max_index = i;
        }
    }
    return max_index + 1;
}

int main() {
    int sensors, readings;
    
    // Input dimensions
    printf("Enter the number of sensors: ");
    scanf("%d", &sensors);
    
    printf("Enter the number of hourly readings per sensor: ");
    scanf("%d", &readings);
    printf("\n");

    // Declare 2D array dynamically for rows
    int temps[sensors][MAX_HOURS];
    
    // Call input function
    inputReadings(sensors, readings, temps);

    // Process each sensor row
    float averages[sensors];
    printf("\nAnalysis Report\n\n");
    for (int i = 0; i < sensors; i++) {
        averages[i] = analyzeSensor(i + 1, readings, temps[i]);
    }

    int bestSensor = getHighestAverageSensor(sensors, averages);
    printf("Highest average: Sensor %d (%.2f)\n", bestSensor, averages[bestSensor - 1]);

    
    
    return 0;
}
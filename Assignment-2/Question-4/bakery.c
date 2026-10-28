/*
* Name: Ahmed Abbasi
* Student ID: 26K-0004
* Program Name: bakery.c
* Program Description: This program simulates a bakery festival sales management system.
* Date: 2026-10-28 (YYYY-MM-DD)
*/


#include <stdio.h>
#include <stdlib.h>

// Inputs and validates the number of festival days (1 to 7)
int getValidDays() {
    int days;
    printf("Enter number of festival days (1-7): ");
    scanf("%d", &days);
    while (days < 1 || days > 7) {
        printf("Invalid. Enter a value from 1 to 7: ");
        scanf("%d", &days);
    }
    return days;
} // end getValidDays()

// Inputs one day's orders, displays the day's statistics, returns the day's total sales
float calculateDailySales(int dayNumber) {
    int orders, i;
    float amount, total = 0, highest = 0, average;

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);
    while (orders < 1) {                        // avoids dividing by zero below
        printf("There must be at least one order. Enter again: ");
        scanf("%d", &orders);
    }

    for (i = 1; i <= orders; i++) {
        printf("  Order %d amount: ", i);
        scanf("%f", &amount);
        while (amount <= 0) {                   // ask again for the same order
            printf("  Amount must be greater than zero. Enter again: ");
            scanf("%f", &amount);
        }
        total += amount;
        if (amount > highest)
            highest = amount;
    }
    average = total / orders;

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", average);
    printf("Highest order: Rs. %.2f\n", highest);
    return total;
} // end calculateDailySales()

// Returns the day number (starting from 1) with the highest sales; earliest day on ties
int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int i, bestIndex = 0;
    for (i = 1; i < numberOfDays; i++)
        if (dailySales[i] > dailySales[bestIndex])      // strict >, so ties keep the earliest day
            bestIndex = i;
    return bestIndex + 1;                               // index to day number
} // end findHighestSalesDay()

// Prints one asterisk for every complete Rs. 100 of each day's sales
void displayBarChart(float dailySales[], int numberOfDays) {
    int i, j, stars;
    for (i = 0; i < numberOfDays; i++) {
        stars = (int)(dailySales[i] / 100);             // drop any remainder below Rs. 100
        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++)
            printf("*");
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
} // end displayBarChart()

int main() {
    int days, i, bestDay;
    float festivalTotal = 0;
    float *dailySales;

    days = getValidDays();
    dailySales = (float*)malloc(days * sizeof(float));  // one total per festival day

    for (i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    bestDay = findHighestSalesDay(dailySales, days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", bestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[bestDay - 1]);

    printf("\n===== DAILY SALES BAR CHART =====\n");
    displayBarChart(dailySales, days);

    free(dailySales);
    return 0;
} // end main()

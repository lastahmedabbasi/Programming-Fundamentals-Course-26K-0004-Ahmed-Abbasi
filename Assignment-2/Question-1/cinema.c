/*
* Name: Ahmed Abbasi
* Student ID: 26K-0004
* Program Name: cinema.c 
* Program Description: This program simulates a cinema hall seat booking system.
* Date: 2026-10-27 (YYYY-MM-DD)
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols, k;
    int r, c, d, t, row, mid;
    int freeCount, total = 0, count;
    int found = 0, startSeat = 0, allocRow = -1;
    int **seat;

    // 1. Input the seating plan 
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of seats per row: ");
    scanf("%d", &cols);

    // Malloc the matrix: an array of row pointers, then each row
    seat = (int**)malloc(rows * sizeof(int*));
    for (r = 0; r < rows; r++)
        seat[r] = (int*)malloc(cols * sizeof(int));

    // Input the seat status (0 = available, 1 = booked)
   
    for (r = 0; r < rows; r++)
        for (c = 0; c < cols; c++){
            printf("Enter seat status for row %d, seat %d (0 = available, 1 = booked):\n", r, c);
            scanf("%d", &seat[r][c]);
        }

    // 2. Display the seating arrangement 
    printf("\nSeating plan:\n   ");
    for (c = 0; c < cols; c++)
        printf("%d ", c);                       // seat numbers from 0
    printf("\n");
    for (r = 0; r < rows; r++) {
        printf("R%d ", r);                      // row numbers from 0
        for (c = 0; c < cols; c++) {
            if (seat[r][c] == 0) printf("_ ");  // available seat
            else                 printf("X ");  // booked seat
        }
        printf("\n");
    }

    // 3. Seat availability report
    printf("\nFree seats per row:");
    for (r = 0; r < rows; r++) {
        freeCount = 0;
        for (c = 0; c < cols; c++)
            if (seat[r][c] == 0)
                freeCount++;
        printf(" %d ", freeCount);
        total += freeCount;
    }
    printf("\nTotal free: %d\n", total);

    // 4. Group size with validation 
    printf("\nEnter number of customers (k): ");
    scanf("%d", &k);
    while (k <= 0 || k > cols) {
        printf("Invalid group size. Enter a value from 1 to %d: ", cols);
        scanf("%d", &k);
    }

    // 5. Search rows by distance from the middle row
    mid = rows / 2;                             // integer division
    for (d = 0; d <= mid && !found; d++) {
        for (t = 0; t < 2 && !found; t++) {
            if (t == 0) row = mid - d;          // row above first (smaller row number)
            else        row = mid + d;          // then the row below

            if (t == 1 && d == 0) continue;     // middle row is searched only once
            if (row < 0 || row >= rows) continue;   // row outside the hall

            // look for k consecutive free seats in this row
            count = 0;
            for (c = 0; c < cols && !found; c++) {
                if (seat[row][c] == 0) count++;
                else                   count = 0;

                if (count == k) {
                    found = 1;
                    allocRow = row;
                    startSeat = c - k + 1;
                    break; // exit the loop once found
                }
            }
        }
    }

    // 6 & 7. Confirm the booking or report failure 
    if (found) {
        for (c = startSeat; c < startSeat + k; c++)
            seat[allocRow][c] = 1;              // mark seats as booked

        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n",
               k, allocRow, startSeat, startSeat + k - 1);

        // display the updated plan
        printf("\nUpdated seating plan:\n   ");
        for (c = 0; c < cols; c++)
            printf("%d ", c);
        printf("\n");
        for (r = 0; r < rows; r++) {
            printf("R%d ", r);
            for (c = 0; c < cols; c++) {
                if (seat[r][c] == 0) printf("_ ");
                else                 printf("X ");
            }
            printf("\n");
        }
        printf("\nRemaining free seats: %d\n", total - k);
    } else {
        printf("\nNo row has %d consecutive available seats.\n", k);   // plan unchanged
    }

    // free the memory: rows first, then the row pointers
    for (r = 0; r < rows; r++)
        free(seat[r]);
    free(seat);

    return 0;
} // end main()

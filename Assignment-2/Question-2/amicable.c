/*
* Name: Ahmed Abbasi
* Student ID: 26K-0004
* Program Name: amicable.c
* Program Description: This program checks if two numbers are amicable.
* Date: 2026-10-27 (YYYY-MM-DD)
*/

#include <stdio.h>

// Returns the sum of the proper divisors of x (all divisors except x itself)
int sumProperDivisors(int x) {      // using sqr root method to find divisors
    int i, sum = 1;                 // 1 is a proper divisor of every x > 1
    if (x == 1)
        return 0;                   // 1 has no proper divisors

    for (i = 2; i * i <= x; i++) {  // startiing from i=2 because 1 is already included in sum
        if (x % i == 0) {
            sum += i;               // the smaller divisor
            if (x / i != i)
                sum += x / i;       // the partner divisor (not added twice for a square root)
        }
    }
    return sum;
} // end sumProperDivisors()

int main() {
    int n, a, b, count = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);
    for (a = 2; a <= n; a++) { // starting from 2 because 1 has no amicable pair
        b = sumProperDivisors(a);
        // b > a: numbers are different, smaller comes first, each pair shown once
        if (b > a && b <= n) {
            if (sumProperDivisors(b) == a) {
                printf("(%d, %d)\n", a, b);
                count++;
            }
        }
    }

    if (count == 0)
        printf("No amicable pairs found.\n");
    else
        printf("Total pairs: %d\n", count);

    return 0;
} // end main()

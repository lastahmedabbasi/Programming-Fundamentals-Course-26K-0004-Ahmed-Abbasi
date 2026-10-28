/*
* Name: Ahmed Abbasi
* Student ID: 26K-0004
* Program Name: library.c
* Program Description: This program simulates a library management system.
* Date: 2026-10-28 (YYYY-MM-DD)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Shows all menu options
void displayMenu() {
    printf("\n=====MENU OPTIONS=====");
    printf("\n1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
} //end displayMenu()

// Inputs the member's details and validates the membership type
void registerMember(char name[], int *studentID, int *memberType) {
    printf("Enter name: ");
    scanf(" %[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentID);
    printf("Enter membership type (1 = Student, 2 = Faculty): ");
    scanf("%d", memberType);
    while (*memberType != 1 && *memberType != 2) {
        printf("Invalid type. Enter 1 or 2: ");
        scanf("%d", memberType);
    }
} // end registerMember()

// Prints all books in a table
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    int i;
    printf("\n%-6s %-25s %-6s\n", "ID", "Title", "Copies");
    for (i = 0; i < totalBooks; i++)
        printf("%-6d %-25s %-6d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
} // end displayBooks()

// Validates and records a borrowed book
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType) {
    int id, days, i, index = -1;

    if (*borrowedCount >= 3) {                  // maximum of 3 books at a time
        printf("Borrowing limit of 3 books reached.\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &id);
    printf("Enter number of days you want to keep it: ");
    scanf("%d", &days);

    if (days <= 0) {
        printf("Days must be positive.\n");
        return;
    }

    int allowed;
    if (memberType == 1) allowed = 14;     // Student
    else                 allowed = 30;     // Faculty

    if (days > allowed) {
        printf("Your membership allows at most %d days.\n", allowed);
        return;
    }
        
    for (i = 0; i < totalBooks; i++)            // find the book in the inventory
        if (bookIDs[i] == id)
            index = i;
    if (index == -1) {
        printf("Invalid book ID.\n");
        return;
    }
    if (availableCopies[index] == 0) {
        printf("No copies available.\n");
        return;
    }
    borrowedBookIDs[*borrowedCount] = id;       // record the borrowing
    (*borrowedCount)++;
    availableCopies[index]--;
    printf("Book borrowed successfully.\n");
} // end borrowBook()

// Handles a return, calculates the fine, applies the waiver, returns the fine payable
float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    int id, actualDays, i, pos = -1, allowed, rate;
    float fine = 0, payable;
    char code[20];

    printf("Enter book ID to return: ");
    scanf("%d", &id);
    printf("Enter actual number of days kept: ");
    scanf("%d", &actualDays);
    if (actualDays <= 0) {
        printf("Days must be positive.\n");
        return 0;
    }
    for (i = 0; i < *borrowedCount; i++)        // check that the member borrowed this book
        if (borrowedBookIDs[i] == id)
            pos = i;
    if (pos == -1) {
        printf("You have not borrowed this book.\n");
        return 0;
    }
    for (i = 0; i < totalBooks; i++)            // put the copy back in stock
        if (bookIDs[i] == id)
            availableCopies[i]++;

    if (memberType == 1) { allowed = 14; rate = 20; }   // Student
    else                 { allowed = 30; rate = 10; }   // Faculty

    if (actualDays > allowed)
        fine = (actualDays - allowed) * rate;

    payable = fine;
    if (fine > 0) {
        printf("Enter membership code: ");
        scanf("%s", code);
        if (strcmp(code, "LIB2026") == 0)
            payable = fine * 0.5;               // 50% waiver
        else
            printf("Incorrect code. No waiver applied.\n");
    }
    *totalFine += fine;                         // cumulative fine before waiver

    for (i = pos; i < *borrowedCount - 1; i++)  // remove the book from the borrowed list
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    (*borrowedCount)--;

    printf("Fine: Rs. %.2f  Payable: Rs. %.2f\n", fine, payable);
    return payable;
} // end returnBook()

// Prints the member's details and borrowing record
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine, float fineAfterWaiver) {
    int i;
    printf("\nName: %s\nStudent ID: %d\n", name, studentID);
    if (memberType == 1) printf("Type: Student\n");
    else                 printf("Type: Faculty\n");
    printf("Currently borrowed books: ");
    if (borrowedCount == 0)
        printf("None");
    for (i = 0; i < borrowedCount; i++)
        printf("%d ", borrowedBookIDs[i]);
    printf("\nTotal fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable: Rs. %.2f\n", fineAfterWaiver);
} // end displayMemberRecord()

int main() {
    int totalBooks = 4;
    int studentID = 0, memberType = 0, borrowedCount = 0;
    int registered = 0, choice;
    float totalFine = 0, fineAfterWaiver = 0;

    // allocate all arrays dynamically
    int *bookIDs = (int*)malloc(totalBooks * sizeof(int));
    char (*bookTitles)[50] = (char(*)[50])malloc(totalBooks * sizeof(*bookTitles));
    int *availableCopies = (int*)malloc(totalBooks * sizeof(int));
    int *borrowedBookIDs = (int*)malloc(3 * sizeof(int));
    char *name = (char*)malloc(50 * sizeof(char));
    name[0] = '\0';

    // initialise the book inventory
    bookIDs[0] = 101; strcpy(bookTitles[0], "Programming in C");   availableCopies[0] = 5;
    bookIDs[1] = 102; strcpy(bookTitles[1], "Data Structures");    availableCopies[1] = 3;
    bookIDs[2] = 103; strcpy(bookTitles[2], "Database Systems");   availableCopies[2] = 0;
    bookIDs[3] = 104; strcpy(bookTitles[3], "Computer Networks");  availableCopies[3] = 4;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                registered = 1;
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                if (!registered) printf("Please register first.\n");
                else borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                                borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4:
                if (!registered) printf("Please register first.\n");
                else fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks,
                                borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                break;
            case 5:
                if (!registered) printf("Please register first.\n");
                else displayMemberRecord(name, studentID, memberType, borrowedBookIDs,
                                borrowedCount, totalFine, fineAfterWaiver);
                break;
            case 6:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    // release all dynamic memory
    free(bookIDs);
    free(bookTitles);
    free(availableCopies);
    free(borrowedBookIDs);
    free(name);
    return 0;
} // end main()

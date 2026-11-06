/* 
 * Header: University_Library.c
 * Description: University Library Management System
 * Author: Aman Kumar Panjwani
 */

#include <stdio.h>
#include <string.h>

void displayMenu() {
    printf("University Library Management System\n");
    printf("1. Register Member\n");
    printf("2. Display available books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}


void registerMember(char name[], int *studentID, int *memberType) {
    printf("Enter Member name: ");
    scanf("%[^\n]%*c", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);
    do {
        printf("Enter member type (1 for Student, 2 for Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2) {
            printf("Invalid member type. Please enter 1 for Student or 2 for Faculty.\n");
        }
    } while (*memberType != 1 && *memberType != 2);
    printf("Member registered successfully!!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks){
    printf("\nID         | Title                     | Copies\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < totalBooks; i++) {
        printf("%-10d | %-25s | %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void BorrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    if (*borrowedCount >= 3) {
        printf("Borrowing limit reached! A member can borrow a maximum of three books at a time.\n");
        return;
    }

    int id, days;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    
    int bookIndex = -1;
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1) {
        printf("Book ID not found.\n");
        return;
    }
    if (availableCopies[bookIndex] <= 0) {
        printf("No copies available for this book.\n");
        return;
    }
    printf("Enter number of days you intend to borrow the book: ");
    scanf("%d", &days);
    while (days <= 0) {
        printf("Number of days must be positive. Enter again: ");
        scanf("%d", &days);
    }
    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[bookIndex]--;
    printf("Book borrowed successfully! You have borrowed the book for %d days.\n", days);

}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFinebeforeWaiver) {
    if (*borrowedCount == 0) {
        printf("No books to return.\n");
        return 0.0;
    }

    int id, actualDays;
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    
    int borrowedIndex = -1;
    for (int i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == id) {
            borrowedIndex = i;
            break;
        }
    }
    
    if (borrowedIndex == -1) {
        printf("This book was not borrowed by you.\n");
        return 0.0;
    }

    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &actualDays);
    while (actualDays <= 0) {
        printf("Number of days must be positive. Enter again: ");
        scanf("%d", &actualDays);
    }
    int bookIndex = -1;
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            bookIndex = i;
            break;
        }
    }
    if (bookIndex != -1) {
        availableCopies[bookIndex]++; // Increase available copies
    }
    
    // Remove from borrowed list by shifting elements
    for (int i = borrowedIndex; i < *borrowedCount - 1; i++) {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;
    
    int allowedDays = (memberType == 1) ? 14 : 30; // Student = 14 days, Faculty = 30 days
    float currentFine = 0.0;
    
    if (actualDays > allowedDays) {
        int extraDays = actualDays - allowedDays;
        float rate = (memberType == 1) ? 20.0 : 10.0; // Student: Rs. 20/day, Faculty: Rs. 10/day 
        currentFine = extraDays * rate;
    }
    
    *totalFinebeforeWaiver += currentFine;
    float returnFinePayable = currentFine;
    
    if (currentFine > 0) {
        char code[20];
        printf("Late fine incurred: Rs. %.2f\n", currentFine);
        printf("Enter membership code (LIB2026) to check for waiver: ");
        scanf("%s", code);
        if (strcmp(code, "LIB2026") == 0) {
            returnFinePayable = currentFine * 0.5; // 50% waiver
            printf("Valid code! 50% waiver applied. Payable fine for this return: Rs. %.2f\n", returnFinePayable);
        } else {
            printf("Invalid code. No waiver applied.\n");
        }
    } else {
        printf("Book returned on time. No late fine.\n");
    }
    
    return returnFinePayable;

}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFineBeforeWaiver, float fineAfterWaiver) {
    printf("\n MEMBER RECORD \n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);
    printf("Membership Type: %s\n", (memberType == 1) ? "Student" : "Faculty");
    printf("Currently Borrowed Books (%d/3):\n", borrowedCount);
    if (borrowedCount == 0) {
        printf("  None\n");
    } else {
        for (int i = 0; i < borrowedCount; i++) {
            printf("  - Book ID: %d\n", borrowedBookIDs[i]);
        }
    }
    printf("Total Fine Charged Before Waiver: Rs. %.2f\n", totalFineBeforeWaiver);
    printf("Final Fine Payable After Waiver: Rs. %.2f\n", fineAfterWaiver);
}

int main(){
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    int totalBooks = 4;

    char name[100]= "Not Registered";
    int studentID = 0;
    int memberType = 1;
    int borrowedBookIDs[3] = {0};
    int borrowedCount = 0;
    float totalFineBeforeWaiver = 0.0;
    float cumulativeFineAfterWaiver = 0.0;
    
    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = 0;
        }
        
        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                BorrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4: {
                float fineForReturn = returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFineBeforeWaiver);
                cumulativeFineAfterWaiver += fineForReturn;
                break;
            }
            case 5:
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFineBeforeWaiver, cumulativeFineAfterWaiver);
                break;
            case 6:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please select between 1 and 6.\n");
        }
    } while (choice != 6);
    return 0;
}

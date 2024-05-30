#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define MAX_BOOKS 100

void printEmployeeBooks(int books[], int allocation[], int numBooks, const char* employeeName) {
    printf("%s: ", employeeName);
    int first = 1;
    for (int i = 0; i < numBooks; i++) {
        if (allocation[i]) {
            if (!first) {
                printf(", ");
            }
            printf("Book %d (%d pages)", i + 1, books[i]);
            first = 0;
        }
    }
    printf("\n");
}

void printDistribution(int books[], int numBooks, int allocationEmp1[], int allocationEmp2[], int allocationEmp3[]) {
    printf("\nDistribution of books:\n");
    printEmployeeBooks(books, allocationEmp1, numBooks, "Employee 1");
    printEmployeeBooks(books, allocationEmp2, numBooks, "Employee 2");
    printEmployeeBooks(books, allocationEmp3, numBooks, "Employee 3");
}

void findBestDistribution(int books[], int numBooks) {
    int totalSum = 0;
    for (int i = 0; i < numBooks; i++)
        totalSum += books[i];

    int bestMaxDiff = INT_MAX;  // Initialize with the largest possible integer to ensure any first found value is smaller.
    int bestAllocationEmp1[MAX_BOOKS] = { 0 }, bestAllocationEmp2[MAX_BOOKS] = { 0 }, bestAllocationEmp3[MAX_BOOKS] = { 0 };

    // Start bitmask from 1 to ensure at least one book is assigned to each employee
    for (int mask1 = 1; mask1 < (1 << numBooks); mask1++) {
        for (int mask2 = 1; mask2 < (1 << numBooks); mask2++) {
            // Ensure each mask is unique and they cover all books
            int mask3 = ((1 << numBooks) - 1) & ~(mask1 | mask2);
            if (!mask3 || (mask1 & mask2) || (mask1 & mask3) || (mask2 & mask3))
                continue; // Skip invalid or overlapping combinations.

            int allocationEmp1[MAX_BOOKS] = { 0 }, allocationEmp2[MAX_BOOKS] = { 0 }, allocationEmp3[MAX_BOOKS] = { 0 };
            int pagesEmp1 = 0, pagesEmp2 = 0, pagesEmp3 = 0;

            for (int book = 0; book < numBooks; book++) {
                if (mask1 & (1 << book)) {
                    pagesEmp1 += books[book];
                    allocationEmp1[book] = 1;
                }
                if (mask2 & (1 << book)) {
                    pagesEmp2 += books[book];
                    allocationEmp2[book] = 1;
                }
                if (mask3 & (1 << book)) {
                    pagesEmp3 += books[book];
                    allocationEmp3[book] = 1;
                }
            }

            int maxPages = pagesEmp1 > pagesEmp2 ? (pagesEmp1 > pagesEmp3 ? pagesEmp1 : pagesEmp3) : (pagesEmp2 > pagesEmp3 ? pagesEmp2 : pagesEmp3);

            if (maxPages < bestMaxDiff) {
                bestMaxDiff = maxPages;
                for (int l = 0; l < numBooks; l++) {
                    bestAllocationEmp1[l] = allocationEmp1[l];
                    bestAllocationEmp2[l] = allocationEmp2[l];
                    bestAllocationEmp3[l] = allocationEmp3[l];
                }
            }
        }
    }

    printDistribution(books, numBooks, bestAllocationEmp1, bestAllocationEmp2, bestAllocationEmp3);
}

int main() {
    int numBooks;
    printf("Enter number of books (up to 100): ");
    scanf("%d", &numBooks);

    if (numBooks <= 0 || numBooks > MAX_BOOKS || numBooks < 3) {
        printf("Invalid number of books, press any key to exit...\n");
        fflush(stdin);
        getchar();
        return 0;
    }

    int books[MAX_BOOKS];
    printf("Enter number of pages in each book:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Book %d: ", i + 1);
        scanf("%d", &books[i]);
    }

    findBestDistribution(books, numBooks);

    printf("\nPress any key to exit...");
    fflush(stdin);
    getchar();
    return 0;
}

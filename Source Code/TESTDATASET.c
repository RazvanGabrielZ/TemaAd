#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#define MAX_BOOKS 100

struct timespec start, end;

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
    clock_gettime(CLOCK_MONOTONIC, &start);

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

    clock_gettime(CLOCK_MONOTONIC, &end);

    printDistribution(books, numBooks, bestAllocationEmp1, bestAllocationEmp2, bestAllocationEmp3);
}

int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL)); // random seed for the number generator

    int numBooks = generateRandomNumber(4, 10);
    int books[MAX_BOOKS];

    // Generate random sizes of the books
    for (int i = 0; i < numBooks; i++) {
        int randomHigh = generateRandomNumber(0, 32767);
        int randomLow = generateRandomNumber(0, 32767);
        int pages = (randomHigh << 15) | randomLow;
        pages = (pages % (100000000 - 1000 + 1)) + 1000; // Ensuring the number is within the range 10^3 to 10^8
        books[i] = pages;

        printf("The number of pages for book %d: %d\n", i + 1, pages);
    }

    findBestDistribution(books, numBooks);

    double time_spent = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("\nExecution time for this dataset: %.6f seconds\n", time_spent);

    printf("\nPress any key to exit...");
    fflush(stdin);
    getchar();
    return 0;
}

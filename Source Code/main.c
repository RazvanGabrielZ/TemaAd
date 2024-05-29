#include <stdio.h>
#include <limits.h>

#define MAX_BOOKS 100 //Maxmimum number of books in the array

void findOptimalDivision(int books[], int n, int *minMaxLoad, int divisions[]) {
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += books[i];
    }

    int leftSum, midSum, rightSum, maxLoad;
    *minMaxLoad = INT_MAX;

    // Iterate over all possible divisions
    for (int i = 0; i < n; i++) {
        leftSum = 0;
        for (int j = 0; j <= i; j++) {
            leftSum += books[j];
        }
        for (int k = i+1; k < n-1; k++) {
            midSum = 0;
            for (int l = i+1; l <= k; l++) {
                midSum += books[l];
            }
            rightSum = totalSum - leftSum - midSum;

            maxLoad = 0;
            if (leftSum > midSum) {
              if (leftSum > rightSum)
                maxLoad = leftSum;
              else
                maxLoad = rightSum;
            } else {
              if (midSum > rightSum)
                maxLoad = midSum;
              else
                midSum = rightSum;
            }

            if (maxLoad < *minMaxLoad) {
                *minMaxLoad = maxLoad;
                divisions[0] = i;
                divisions[1] = k;
            }
        }
    }
}

int main() {
    int books[MAX_BOOKS];
    int n;

    printf("Enter the number of books: ");
    scanf("%d", &n);

    if (n < 3) {
        printf("There must be at least 3 books to divide among 3 employees.\n");
        return 1;
    }

    printf("Enter the sizes of the books: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &books[i]);
    }

    int minMaxLoad;
    int divisions[2];
    findOptimalDivision(books, n, &minMaxLoad, divisions);

    printf("Optimal division points are at indexes: %d and %d\n", divisions[0], divisions[1]);
    printf("The minimum possible maximum load is: %d\n", minMaxLoad);

    printf("Employee 1 will handle books from 0 to %d\n", divisions[0]);
    printf("Employee 2 will handle books from %d to %d\n", divisions[0] + 1, divisions[1]);
    printf("Employee 3 will handle books from %d to %d\n", divisions[1] + 1, n - 1);

    return 0;
}

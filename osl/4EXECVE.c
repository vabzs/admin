#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void bass(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nAscending Sorting\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bdsc(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nDescending Sorting\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void forkeg() {
    int arr[25], n, i;
    printf("Enter Size: ");
    scanf("%d", &n);

    if (n > 25) {
        printf("Error: Array size exceeds 25.\n");
        exit(1);
    }

    printf("Enter Array: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) { // Child process
        printf("\nChild Process (PID: %d) - Descending Sort\n", getpid());
        bdsc(arr, n); // Sort in descending order
    } else { // Parent process
        sleep(2); // Delay to simulate orphan state for the child
        printf("\nParent Process (PID: %d) - Ascending Sort\n", getpid());
        bass(arr, n); // Sort in ascending order
        printf("\nProcess List:\n");
        system("ps -x"); // Display processes
    }
}

int main() {
    forkeg();
    return 0;
}

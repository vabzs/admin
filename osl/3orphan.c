#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 100

// Bubble Sort function
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    int arr[MAX_SIZE];

    // Accepting the number of integers and the integers themselves
    printf("Enter the number of integers to be sorted: ");
    scanf("%d", &n);

    printf("Enter the integers:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Fork to create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("\nChild process (PID: %d) is sorting the array:\n", getpid());

        // Sorting in the child process
        bubbleSort(arr, n);

        // Displaying the sorted array
        printf("Child sorted array: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        printf("Child process (PID: %d) has completed sorting.\n", getpid());
    } else {
        // Parent process
        printf("\nParent process (PID: %d) is exiting, making child an orphan.\n", getpid());
        exit(0);  // Parent exits immediately, making the child an orphan
    }

    return 0;
}

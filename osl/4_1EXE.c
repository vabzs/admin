#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {

        bubble_sort(arr, n);

        // Prepare arguments for execve
        char *args[n + 2];
        args[0] = "./exe2";

        // Convert integers to strings for execve arguments
        for (int i = 0; i < n; i++) {
            char *arg = malloc(10);
            snprintf(arg, 10, "%d", arr[i]);
            args[i + 1] = arg;
        }
        args[n + 1] = NULL;

        // Execute reverse program
        execve(args[0], args, NULL);

        // Free memory if execve fails
        perror("execve failed");
        for (int i = 1; i <= n; i++) {
            free(args[i]);
        }
        exit(1);
    }
    else {
        // Parent process
        wait(NULL);  // Wait for child to complete
    }

    return 0;
}

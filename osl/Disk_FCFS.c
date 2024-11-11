#include <stdio.h>
#include <stdlib.h>

int main() {
    int numRequests, initialHeadPosition, totalHeadMovement = 0;

    // Input: Number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int requests[numRequests];

    // Input: Disk requests sequence
    printf("Enter the disk request sequence: ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Input: Initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &initialHeadPosition);

    // Starting position for the head
    int currentPosition = initialHeadPosition;

    // FCFS: Process each request in order
    for (int i = 0; i < numRequests; i++) {
        // Calculate movement distance
        int movement = abs(requests[i] - currentPosition);
        totalHeadMovement += movement;

        // Update current head position
        currentPosition = requests[i];

        printf("Moving from %d to %d, Movement: %d\n", currentPosition, requests[i], movement);
    }

    // Output the total head movement
    printf("Total Head Movement: %d\n", totalHeadMovement);

    return 0;
}

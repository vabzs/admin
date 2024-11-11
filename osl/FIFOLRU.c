#include <stdio.h>

// Function for FIFO page replacement
void fifoPageReplacement(int pages[], int pages_count, int frames_count) {
    int temp[frames_count];
    int pageFaults = 0;

    // Initialize all frames as empty
    for (int i = 0; i < frames_count; i++) {
        temp[i] = -1;
    }

    printf("\nFIFO Page Replacement\n");
    for (int i = 0; i < pages_count; i++) {
        int flag = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frames_count; j++) {
            if (temp[j] == pages[i]) {
                flag = 1;  // Page found in frame
                break;
            }
        }

        // If the page is not found in the frames, replace a page (page fault)
        if (!flag) {
            for (int j = 0; j < frames_count - 1; j++) {
                temp[j] = temp[j + 1];  // Shift frames to the left
            }
            temp[frames_count - 1] = pages[i];
            pageFaults++;
        }

        // Display the current state of frames
        printf("\n");
        for (int j = 0; j < frames_count; j++) {
            if (temp[j] != -1)
                printf("%d\t", temp[j]);
            else
                printf("-\t");
        }
    }
    printf("\nTotal Page Faults (FIFO): %d\n", pageFaults);
}

// Function for LRU page replacement
void lruPageReplacement(int pages[], int pages_count, int frames_count) {
    int frames[frames_count];
    int temp[frames_count];
    int page_faults = 0;

    // Initialize all frames as empty
    for (int i = 0; i < frames_count; i++) {
        frames[i] = -1;
    }

    printf("\nLRU Page Replacement\n");
    for (int i = 0; i < pages_count; i++) {
        int flag1 = 0, flag2 = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;  // Page found in frame
                break;
            }
        }

        // If the page is not found in the frames
        if (!flag1) {
            for (int j = 0; j < frames_count; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];  // Place page in empty frame
                    page_faults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty frame was found, we need to replace a page
        if (!flag2) {
            for (int j = 0; j < frames_count; j++) {
                temp[j] = -1;
                for (int k = i - 1; k >= 0; k--) {
                    if (frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            // Find the page with the smallest index in temp[] (least recently used)
            int min = temp[0], pos = 0;
            for (int j = 1; j < frames_count; j++) {
                if (temp[j] < min) {
                    min = temp[j];
                    pos = j;
                }
            }
            frames[pos] = pages[i];
            page_faults++;
        }

        // Display the current state of frames
        printf("\n");
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] != -1)
                printf("%d\t", frames[j]);
            else
                printf("-\t");
        }
    }
    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}

int main() {
    int pages[30], pages_count, frames_count;

    // Take user input for pages and frames
    printf("Enter the number of pages: ");
    scanf("%d", &pages_count);
    printf("Enter the page reference string:\n");
    for (int i = 0; i < pages_count; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }
    
    printf("Enter the number of frames: ");
    scanf("%d", &frames_count);

    // Run both FIFO and LRU page replacement algorithms
    fifoPageReplacement(pages, pages_count, frames_count);
    lruPageReplacement(pages, pages_count, frames_count);

    return 0;
}


#include <stdio.h>

// Optimal Page Replacement Function
void optimalPageReplacement(int pages[], int pages_number, int frames_number) {
    int frames[10], temp[10], page_faults = 0;
    
    // Initialize all frames as empty
    for(int i = 0; i < frames_number; i++) {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement\n");
    for(int i = 0; i < pages_number; i++) {
        int flag1 = 0, flag2 = 0;

        // Check if page is already in a frame
        for(int j = 0; j < frames_number; j++) {
            if(frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page is not found in frames, it's a page fault
        if(flag1 == 0) {
            // Place page in an empty frame if available
            for(int j = 0; j < frames_number; j++) {
                if(frames[j] == -1) {
                    frames[j] = pages[i];
                    page_faults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // Replace a page if no empty frame is found
        if(flag2 == 0) {
            int flag3 = 0;
            // Check next use of each page in frames
            for(int j = 0; j < frames_number; j++) {
                temp[j] = -1;
                for(int k = i + 1; k < pages_number; k++) {
                    if(frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            // Find page not used in the future (temp[j] == -1)
            int pos = 0;
            for(int j = 0; j < frames_number; j++) {
                if(temp[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            // If all pages will be used in future, replace the one used farthest in future
            if(flag3 == 0) {
                int max = temp[0];
                pos = 0;
                for(int j = 1; j < frames_number; j++) {
                    if(temp[j] > max) {
                        max = temp[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            page_faults++;
        }

        // Print the current frame status
        printf("\n");
        for(int j = 0; j < frames_number; j++) {
            printf("%d\t", frames[j]);
        }
    }

    printf("\nTotal Page Faults (Optimal): %d\n", page_faults);
}

// LRU Page Replacement Function
void lruPageReplacement(int pages[], int pages_number, int frames_number) {
    int frames[10], temp[10], page_faults = 0;

    // Initialize all frames as empty
    for(int i = 0; i < frames_number; i++) {
        frames[i] = -1;
    }

    printf("\nLRU Page Replacement\n");
    for(int i = 0; i < pages_number; i++) {
        int flag1 = 0, flag2 = 0;

        // Check if page is already in a frame
        for(int j = 0; j < frames_number; j++) {
            if(frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page is not found in frames, it's a page fault
        if(flag1 == 0) {
            // Place page in an empty frame if available
            for(int j = 0; j < frames_number; j++) {
                if(frames[j] == -1) {
                    frames[j] = pages[i];
                    page_faults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // Replace a page if no empty frame is found
        if(flag2 == 0) {
            // Check previous use of each page in frames
            for(int j = 0; j < frames_number; j++) {
                temp[j] = -1;
                for(int k = i - 1; k >= 0; k--) {
                    if(frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            // Find page with least recent use (smallest value in temp)
            int min = temp[0], pos = 0;
            for(int j = 1; j < frames_number; j++) {
                if(temp[j] < min) {
                    min = temp[j];
                    pos = j;
                }
            }

            frames[pos] = pages[i];
            page_faults++;
        }

        // Print the current frame status
        printf("\n");
        for(int j = 0; j < frames_number; j++) {
            printf("%d\t", frames[j]);
        }
    }

    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}

int main() {
    int pages[30], pages_number, frames_number;

    // Get user input for pages and frames
    printf("Enter number of frames: ");
    scanf("%d", &frames_number);

    printf("Enter number of pages: ");
    scanf("%d", &pages_number);

    printf("Enter page reference string: ");
    for(int i = 0; i < pages_number; ++i) {
        scanf("%d", &pages[i]);
    }

    // Run Optimal and LRU Page Replacement
    optimalPageReplacement(pages, pages_number, frames_number);
    lruPageReplacement(pages, pages_number, frames_number);

    return 0;
}


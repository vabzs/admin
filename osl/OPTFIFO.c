#include <stdio.h>

void fifoPageReplacement(int pages[], int pages_count, int frames_count) {
    int temp[frames_count], pageFaults = 0;
    for (int i = 0; i < frames_count; i++) {
        temp[i] = -1;  // Initialize all frames as empty
    }

    printf("\nFIFO Page Replacement\n");
    for (int i = 0; i < pages_count; i++) {
        int flag = 0;
        for (int j = 0; j < frames_count; j++) {
            if (pages[i] == temp[j]) {
                flag = 1;  // Page already in frame
                break;
            }
        }
        
        if (!flag) {  // Page fault occurs
            pageFaults++;
            for (int j = 0; j < frames_count - 1; j++) {
                temp[j] = temp[j + 1];  // Shift pages left
            }
            temp[frames_count - 1] = pages[i];
        }

        // Display frames after each iteration
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

void optimalPageReplacement(int pages[], int pages_count, int frames_count) {
    int frames[10], temp[10], page_faults = 0;

    for (int i = 0; i < frames_count; ++i) {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement\n");
    for (int i = 0; i < pages_count; ++i) {
        int flag1 = 0, flag2 = 0;
        
        for (int j = 0; j < frames_count; ++j) {
            if (frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (int j = 0; j < frames_count; ++j) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    page_faults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            int flag3 = 0, pos, max;

            for (int j = 0; j < frames_count; ++j) {
                temp[j] = -1;
                for (int k = i + 1; k < pages_count; ++k) {
                    if (frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            for (int j = 0; j < frames_count; ++j) {
                if (temp[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            if (flag3 == 0) {
                max = temp[0];
                pos = 0;
                for (int j = 1; j < frames_count; ++j) {
                    if (temp[j] > max) {
                        max = temp[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            page_faults++;
        }

        printf("\n");
        for (int j = 0; j < frames_count; ++j) {
            if (frames[j] != -1)
                printf("%d\t", frames[j]);
            else
                printf("-\t");
        }
    }
    printf("\nTotal Page Faults (Optimal): %d\n", page_faults);
}

int main() {
    int pages[30], pages_count, frames_count;

    printf("Enter the number of pages: ");
    scanf("%d", &pages_count);
    printf("Enter the page reference string:\n");
    for (int i = 0; i < pages_count; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }
    
    printf("Enter the number of frames: ");
    scanf("%d", &frames_count);

    fifoPageReplacement(pages, pages_count, frames_count);
    optimalPageReplacement(pages, pages_count, frames_count);

    return 0;
}


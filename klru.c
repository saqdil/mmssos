#include <stdio.h>

int main() {
    int pages[100], frames[10], temp[10];
    int n, f, i, j, k, pos, min, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frames[i] = -1;  // Initialize frames as empty (-1)

    for(i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frames (page hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            faults++; // Page fault occurs

            // Check if any frame is empty
            int empty = -1;
            for(j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if(empty != -1) {
                // If an empty frame was found, place the page there
                frames[empty] = pages[i];
            } else {
                // --- Frames are full, run LRU logic ---

                // 1. Find the last time each page in 'frames' was used
                for(j = 0; j < f; j++) {
                    temp[j] = -1; // Assume it was never used
                    for(k = i - 1; k >= 0; k--) {
                        if(frames[j] == pages[k]) {
                            temp[j] = k;  // Record the time 'k'
                            break;
                        }
                    }
                }

                // 2. Find the page with the smallest (oldest) time
                pos = 0;
                min = temp[0];
                for(j = 1; j < f; j++) {
                    if(temp[j] < min) {
                        min = temp[j];
                        pos = j;
                    }
                }
                
                // 3. Replace the victim
                frames[pos] = pages[i];
            }
        }

        // Print current frame contents
        printf("Frames after request %d: ", pages[i]);
        for(j = 0; j < f; j++) {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", faults);
    return 0;
}
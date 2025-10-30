#include <stdio.h>

int main() {
    int pages[100], frames[10], frequency[10];
    int n, f, i, j, pos, min, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++) {
        frames[i] = -1;     // Initialize frames as empty (-1)
        frequency[i] = 0;   // Initialize frequency counts to 0
    }

    for(i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frames (page hit)
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                frequency[j]++; // Increment its frequency
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
                frequency[empty] = 1; // Set initial frequency to 1
            } else {
                // --- Frames are full, run LFU logic ---

                // Find the frame with the lowest frequency
                pos = 0;
                min = frequency[0];
                for(j = 1; j < f; j++) {
                    if(frequency[j] < min) {
                        min = frequency[j];
                        pos = j;
                    }
                }
                
                // Replace the victim (at 'pos')
                frames[pos] = pages[i];
                frequency[pos] = 1; // Reset frequency for the new page
            }
        }

        // Print current frame contents
        printf("Frames after request %d: ", pages[i]);
        for(j = 0; j < f; j++) {
            if(frames[j] != -1)
                printf("%d(f=%d) ", frames[j], frequency[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", faults);
    return 0;
}
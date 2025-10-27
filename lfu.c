#include <stdio.h>

int main() {
    int n, f, i, j, faults = 0, time = 0, found, index, min_freq, min_time;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    int frames[f], freq[f], age[f];
    for (i = 0; i < f; i++) frames[i] = -1, freq[i] = 0, age[i] = -1;

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            faults++;
            // Find LFU victim
            min_freq = freq[0];
            min_time = age[0];
            index = 0;
            for (j = 1; j < f; j++) {
                if (freq[j] < min_freq ||
                   (freq[j] == min_freq && age[j] < min_time)) {
                    min_freq = freq[j];
                    min_time = age[j];
                    index = j;
                }
            }
            frames[index] = pages[i];
            freq[index] = 1;
            age[index] = time;
        }
        time++;
        printf("Frames: ");
        for (j = 0; j < f; j++) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total page faults: %d\n", faults);
    return 0;
}

#include <stdio.h>

int main() {
    int n, f, i, j, faults = 0, time = 0, found, lru, min, index;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    int frames[f], last_used[f];
    for (i = 0; i < f; i++) frames[i] = -1, last_used[i] = -1;

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                last_used[j] = time;
                break;
            }
        }
        if (!found) {
            faults++;
            min = last_used[0];
            index = 0;
            for (j = 1; j < f; j++)
                if (last_used[j] < min) {
                    min = last_used[j];
                    index = j;
                }
            frames[index] = pages[i];
            last_used[index] = time;
        }
        time++;
        printf("Frames: ");
        for (j = 0; j < f; j++) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total page faults: %d\n", faults);
    return 0;
}

#include <stdio.h>

int main() {
    int n, f, i, j, found, faults = 0, rear = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    int frames[f];
    for (i = 0; i < f; i++) frames[i] = -1;

    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = 1;
        if (!found) {
            faults++;
            frames[rear] = pages[i];
            rear = (rear + 1) % f;
        }
        printf("Frames: ");
        for (j = 0; j < f; j++) printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total page faults: %d\n", faults);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head, total_movement = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for (i = 0; i < n; i++) {
        total_movement += abs(head - req[i]);
        head = req[i];
    }

    printf("Total head movement: %d\n", total_movement);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

int main() {
    int n, head, disk_size, dir, i, total = 0, l=0, r=0;
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], left[n], right[n];
    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &dir);

    for (i = 0; i < n; i++) {
        if (req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    bubbleSort(left, l);
    bubbleSort(right, r);

    if (dir == 1) {
        for (i = 0; i < r; i++) {
            total += abs(head - right[i]);
            head = right[i];
        }
        total += abs(head - (disk_size-1));
        head = 0;
        total += disk_size-1;
        for (i = 0; i < l; i++) {
            total += abs(head - left[i]);
            head = left[i];
        }
    } else {
        for (i = l-1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
        }
        total += abs(head - 0);
        head = disk_size-1;
        total += disk_size-1;
        for (i = r-1; i >= 0; i--) {
            total += abs(head - right[i]);
            head = right[i];
        }
    }

    printf("Total head movement: %d\n", total);
    return 0;
}

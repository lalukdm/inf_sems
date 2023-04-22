#include <stdio.h>
#include <stdlib.h>

void ShellSort(int arr[], int n) {
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}


int main() {
    int lenth;
    
    scanf("%d", &lenth);

    int *arr = (int*) malloc(lenth * sizeof(int));
    
    for(int i = 0; i < lenth; i++){
        scanf("%d", &arr[i]);
    }

    ShellSort(arr, lenth);

    for (int i = 0; i < lenth; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    return 0;
}
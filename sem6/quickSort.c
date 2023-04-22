#include <stdio.h>

#define swap(arr, i, j)                   \
    {                                     \
        __typeof__(arr[0]) temp = arr[i]; \
        arr[i] = arr[j];                  \
        arr[j] = temp;                    \
    }


void qsort(int arr[], int left, int right){

    int i, j;
    int ltip, rtip;

    int lpart_arr[2048], rpart_arr[2048];

    int pos = 1;
    int ppos;
    int pivot;

    lpart_arr[1] = left;
    rpart_arr[1] = right;

    do {
        ltip = lpart_arr[pos];
        rtip = rpart_arr[pos];
        pos--;

        do {
            ppos = (ltip + rtip) >> 1;
            i = ltip;
            j = rtip;
            pivot = arr[ppos];

            do {
                for (; arr[i] < pivot; i++);
                for (; pivot < arr[j]; j--);

                if (i <= j) {
                    swap(arr, i, j);
                    i++;
                    j--;
                }

            } while (i <= j);

            if (i < ppos) {
                if (i < rtip) {
                    lpart_arr[++pos] = i;
                    rpart_arr[pos] = rtip;
                }
                rtip = j;
            }
            else {
                if (j > ltip) {
                    lpart_arr[++pos] = ltip;
                    rpart_arr[pos] = j;
                }
                ltip = i;
            }

        } while (ltip < rtip);
    } while (pos != 0);
}

int main() {
    int arr[] = {5, 2, 1, 3, 9, -100, 0, 10, 4, 6, 8};

    puts("start array: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", arr[i]);

    int n = sizeof(arr) / sizeof(arr[0]);

    int low = 0, high = n - 1;
    qsort(arr, low, high);

    puts("sorted array: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", arr[i]);

    return 0;
}
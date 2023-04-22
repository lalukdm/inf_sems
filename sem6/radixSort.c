#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void radixSort(int arr[], int rang, int len_arr){
    int depth = 0;
    int figure; 

    int max_num = arr[0]; 
    int min_num = arr[0];

    for (int i = 1; i < len_arr; i++) {
        max_num = (max_num < arr[i]) ? arr[i] : max_num;
        min_num = (min_num > arr[i]) ? (arr[i] - 1) : min_num;
    }

    if (min_num < 0) {
        for (int i = 0; i < len_arr; i++)
            arr[i] -= min_num;
        max_num -= min_num;
    }

    for (; max_num != 0; max_num /= 10) 
        depth++; 

    int ** buf_arr = (int **)calloc(rang, sizeof(int *));
    for (int i = 0; i < rang; i++)
        buf_arr[i] = (int *)calloc(len_arr, sizeof(int));

    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rang; j++) {
            for (int k = 0; k < len_arr; k++) {
                figure = (arr[k] / (int)pow(10, i)) % 10;
                buf_arr[figure][k] = arr[k];
            }                
        }

        int p = 0;
        for (int j = 0; j < rang; j++) {
            for (int k = 0; k < len_arr; k++) {
                if (buf_arr[j][k] != 0) {
                    arr[p++] = buf_arr[j][k];
                    buf_arr[j][k] = 0;
                }
            }    
        }
    }

    if (min_num < 0) {
        for (int i = 0; i < len_arr; i++)
            arr[i] += min_num;
    }

    for (int i = 0; i < rang; i++)
        free(buf_arr[i]);
    free(buf_arr);
}



int main() {
    int arr[] = {12, 5, 664, 63, -100, 0, 73, 93, 127, 432, 64, 34};
    
    int len_arr = sizeof(arr) / sizeof(int);

    printf("start array:\n\t\t");
    for(int i = 0; i < len_arr; ++i)
        printf("%d ", arr[i]); 

    radixSort(arr, 10, len_arr);
    
    printf("\nradix sort result:\n\t\t");
    for(int i = 0; i < len_arr; ++i)
        printf("%d ", arr[i]); 

    return 0;
}
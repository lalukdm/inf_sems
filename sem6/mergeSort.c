#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) { 
    int i, j; 
    int len_l = mid - left + 1; 
    int len_r = right - mid; 

    int left_arr[len_l], right_arr[len_r]; 
  
    for (i = 0; i < len_l; i++) 
        left_arr[i] = arr[left + i]; 
    for (j = 0; j < len_r; j++) 
        right_arr[j] = arr[mid + 1 + j]; 
  
    i = j = 0; 
    while (i < len_l && j < len_r) { 
        if (left_arr[i] <= right_arr[j])
            arr[left++] = left_arr[i++]; 
        else
            arr[left++] = right_arr[j++];
    } 
  
    while (i < len_l)
        arr[left++] = left_arr[i++]; 

    while (j < len_r)
        arr[left++] = right_arr[j++]; 
} 

void mergeSort(int arr[], int left, int right) { 
    if (left < right) { 
        int mid = left + (right - left) / 2; 
  
        mergeSort(arr, left, mid); 
        mergeSort(arr, mid + 1, right); 
  
        merge(arr, left, mid, right); 
    } 
} 



int main() {
    int arr[] = {12, 5, 664, 63, -100, 0, 73, 93, 127, 432, 64, 34};
    
    int len_arr = sizeof(arr) / sizeof(int);

    printf("start array:\n\t\t");
    for(int i = 0; i < len_arr; ++i)
        printf("%d ", arr[i]);     

    mergeSort(arr, 0, len_arr - 1);

    printf("\nmerge sort result:\n\t\t");
    for(int i = 0; i < len_arr; i++)
        printf("%d ", arr[i]);

    return 0;
}
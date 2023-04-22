#include <stdio.h>
 
int binSearch(int nums[], int low, int high, int target){

    if (low > high) return -1;
 
    int mid = low + (high - low)/2;
 
    if (target == nums[mid])
        return mid;
    else if (target < nums[mid])
        return binSearch(nums, low, mid - 1, target);
    else 
        return binSearch(nums, mid + 1, high, target);
}
 
int main(){
    int arr[] = {-100, 0, 2, 5, 6, 8, 9, 10 };

    int target;

    puts("input number for search:");
    scanf("%d", &target);
 
    int n = sizeof(arr) / sizeof(arr[0]);
 
    int low = 0, high = n - 1;
    int index = binSearch(arr, low, high, target);
 
    if (index != -1)
        printf("index of %d: %d", arr[index], index);
    else
        printf("not found");
 
    return 0;
}
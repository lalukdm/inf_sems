#include <stdio.h>

#define swap(arr, i, j) {           \
  __typeof__(arr[0]) temp = arr[i]; \
  arr[i] = arr[j];                  \
  arr[j] = temp;                    \
}
 
int main(){
 
    int int_arr[] = {1, 2, 3, 4, 5};
    float float_arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    char char_arr[] = {'A', 'B', 'C', 'D', 'E'};

    swap(char_arr, 2, 3);
    for(int i = 0; i < 5; i++)
        printf("%c ", char_arr[i]);
    
    return 0;
}

#include <stdio.h>
#include <limits.h>

int maxSubArray(int arr[], int size) {
    int max_sum = INT_MIN, current_sum = 0;
    
    for (int i = 0; i < size; i++) {
        current_sum += arr[i];
        if (current_sum > max_sum)
            max_sum = current_sum;
        if (current_sum < 0)
            current_sum = 0;
    }
    
    return max_sum;
}

int main() {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Maximum Subarray Sum = %d\n", maxSubArray(arr, size));
    
    return 0;
}

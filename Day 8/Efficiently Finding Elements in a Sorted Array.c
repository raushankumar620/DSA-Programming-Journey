#include <stdio.h>

// Function for Binary Search (Iterative)
int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if the key is present at mid
        if (arr[mid] == key) {
            return mid;
        }

        // If the key is greater, ignore the left half
        if (arr[mid] < key) {
            low = mid + 1;
        }
        // If the key is smaller, ignore the right half
        else {
            high = mid - 1;
        }
    }

    return -1;  // Return -1 if key is not found
}

int main() {
    // Array must be sorted for binary search
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 7;

    int result = binarySearch(arr, 0, n - 1, key);

    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    } else {
        printf("Element %d not found in the array\n", key);
    }

    return 0;
}

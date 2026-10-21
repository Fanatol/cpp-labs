#include <cstdlib>

int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

int countDigits(int n) {
    n = abs(n);
    if (n < 10)
        return 1;
    else
        return 1 + countDigits(n / 10);
}

int binarySearch(int arr[], int left, int right, int target) {
    if (left > right) return -1;
    int mid = (left + right) / 2;
    if (arr[mid] == target)
        return mid;
    else if (arr[mid] < target)
        return binarySearch(arr, mid + 1, right, target);
    else
        return binarySearch(arr, left, mid - 1, target);
}
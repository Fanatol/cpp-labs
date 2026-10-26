// рекурсивный бинарный поиск
int binSearchRec(int arr[], int left, int right, int target) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (arr[mid] == target)
        return mid;
    else if (arr[mid] > target)
        return binSearchRec(arr, left, mid - 1, target);
    else
        return binSearchRec(arr, mid + 1, right, target);
}

// итеративный бинарный поиск
int binSearchIte(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
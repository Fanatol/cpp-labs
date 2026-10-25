#pragma once
#include <utility>

// Медиана из трёх
void medianOfThree(int arr[], int low, int high) {
    int mid = (low + high) / 2;
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
    std::swap(arr[mid], arr[high]);
}

// Разделение вокруг опорного
int partition(int arr[], int low, int high) {
    medianOfThree(arr, low, high);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Быстрая сортировка
void quickSort(int arr[], int low, int high) {
    if (low >= high) return;
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

// Слияние двух отсортированных половин
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    int i = 0, j = 0, k = left;
    for (int a = 0; a < n1; a++) L[a] = arr[left + a];
    for (int b = 0; b < n2; b++) R[b] = arr[mid + 1 + b];

    while (i < n1 and j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

// Сортировка слиянием
void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Опускание узла вниз (восстановление кучи)
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1, right = 2 * i + 2;
    if (left < n and arr[left] > arr[largest]) largest = left;
    if (right < n and arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Пирамидальная сортировка
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
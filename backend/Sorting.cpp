
#include "../include/ShopSmart.h"

void merge(Product products[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Product* L = new Product[n1];
    Product* R = new Product[n2];

    for (int i = 0; i < n1; i++)
        L[i] = products[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = products[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].price <= R[j].price)
            products[k++] = L[i++];
        else
            products[k++] = R[j++];
    }

    while (i < n1)
        products[k++] = L[i++];

    while (j < n2)
        products[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Product products[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(products, left, mid);
    mergeSort(products, mid + 1, right);
    merge(products, left, mid, right);
}

int partitionByRating(Product products[], int low, int high) {
    double pivot = products[high].rating;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (products[j].rating >= pivot) {
            i++;

            Product temp = products[i];
            products[i] = products[j];
            products[j] = temp;
        }
    }

    Product temp = products[i + 1];
    products[i + 1] = products[high];
    products[high] = temp;

    return i + 1;
}

void quickSortByRating(Product products[], int low, int high) {
    if (low < high) {
        int pivotIndex = partitionByRating(products, low, high);

        quickSortByRating(products, low, pivotIndex - 1);
        quickSortByRating(products, pivotIndex + 1, high);
    }
}

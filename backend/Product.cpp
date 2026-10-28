
#include "../include/ShopSmart.h"

void displayProducts(Product products[], int totalProducts) {
    cout << left
         << setw(6) << "ID"
         << setw(20) << "Product"
         << setw(16) << "Category"
         << setw(12) << "Price"
         << setw(10) << "Rating"
         << "Stock\n";

    cout << string(75, '-') << '\n';

    for (int i = 0; i < totalProducts; i++) {
        cout << left
             << setw(6) << products[i].id
             << setw(20) << products[i].name
             << setw(16) << products[i].category
             << setw(12) << fixed << setprecision(2)
             << products[i].price
             << setw(10) << products[i].rating
             << products[i].stock << '\n';
    }
}

// Linear Search
int linearSearch(Product products[], int totalProducts, int searchId) {
    for (int i = 0; i < totalProducts; i++) {
        if (products[i].id == searchId)
            return i;
    }

    return -1;
}

// Binary Search (array must be sorted by ID)
int binarySearch(Product products[], int totalProducts, int searchId) {
    int left = 0;
    int right = totalProducts - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].id == searchId)
            return mid;
        else if (products[mid].id < searchId)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

// Sort products by ID for Binary Search
void sortById(Product products[], int totalProducts) {
    for (int i = 0; i < totalProducts - 1; i++) {
        for (int j = 0; j < totalProducts - i - 1; j++) {
            if (products[j].id > products[j + 1].id) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

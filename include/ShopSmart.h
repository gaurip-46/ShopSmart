
#ifndef SHOPSMART_H
#define SHOPSMART_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Product details
struct Product {
    int id;
    string name;
    string category;
    double price;
    double rating;
    int stock;
};

// Shopping cart item
struct CartItem {
    Product product;
    int quantity;
};

// Hash table size
const int TABLE_SIZE = 10;

// Inventory linked-list node
struct InventoryNode {
    Product product;
    InventoryNode* next;
};

// Product display and searching
void displayProducts(Product products[], int totalProducts);
int linearSearch(Product products[], int totalProducts, int searchId);
int binarySearch(Product products[], int totalProducts, int searchId);
void sortById(Product products[], int totalProducts);

// Sorting algorithms
void merge(Product products[], int left, int mid, int right);
void mergeSort(Product products[], int left, int right);
int partitionByRating(Product products[], int low, int high);
void quickSortByRating(Product products[], int low, int high);

// Inventory management
int hashFunction(int productId);
void insertInventory(InventoryNode* table[], Product product);
InventoryNode* searchInventory(InventoryNode* table[], int productId);
bool updateStock(InventoryNode* table[], int productId, int quantity);

// Shopping cart
void addToCart(
    CartItem cart[],
    int &cartSize,
    Product products[],
    int totalProducts,
    int productId,
    int quantity,
    InventoryNode* inventory[]
);

void displayCart(CartItem cart[], int cartSize);

void removeFromCart(
    CartItem cart[],
    int &cartSize,
    int productId,
    Product products[],
    int totalProducts,
    InventoryNode* inventory[]
);

#endif


#include "../include/ShopSmart.h"

// Hash function
int hashFunction(int productId) {
    return productId % TABLE_SIZE;
}

// Insert product into hash table using linked list
void insertInventory(InventoryNode* table[], Product product) {
    int index = hashFunction(product.id);

    InventoryNode* newNode = new InventoryNode;
    newNode->product = product;
    newNode->next = table[index];

    table[index] = newNode;
}

// Search product in inventory
InventoryNode* searchInventory(
    InventoryNode* table[],
    int productId
) {
    int index = hashFunction(productId);
    InventoryNode* current = table[index];

    while (current != nullptr) {
        if (current->product.id == productId)
            return current;

        current = current->next;
    }

    return nullptr;
}

// Update inventory stock
bool updateStock(
    InventoryNode* table[],
    int productId,
    int quantity
) {
    InventoryNode* item = searchInventory(table, productId);

    if (item == nullptr) {
        cout << "Product not found in inventory!\n";
        return false;
    }

    if (quantity < 0) {
        cout << "Invalid stock quantity!\n";
        return false;
    }

    item->product.stock = quantity;

    cout << "Stock updated successfully!\n";
    cout << "Product: " << item->product.name << '\n';
    cout << "New Stock: " << item->product.stock << '\n';

    return true;
}

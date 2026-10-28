
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
    double rating;
    int stock;
};

struct CartItem {
    Product product;
    int quantity;
};


const int TABLE_SIZE = 10;

struct InventoryNode {
    Product product;
    InventoryNode* next;
};


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

// Search by product ID
int linearSearch(Product products[], int totalProducts, int searchId) {
    for (int i = 0; i < totalProducts; i++) {
        if (products[i].id == searchId) {
            return i;
        }
    }
    return -1;
}


int binarySearch(Product products[], int totalProducts, int searchId) {
    int left = 0;
    int right = totalProducts - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].id == searchId) {
            return mid;
        }
        else if (products[mid].id < searchId) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}


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

   void addToCart(
    CartItem cart[],
    int &cartSize,
    Product products[],
    int totalProducts,
    int productId,
    int quantity,
    InventoryNode* inventory[]
) {
    int productIndex = linearSearch(
        products, totalProducts, productId
    );

    if (productIndex == -1) {
        cout << "Product not found!\n";
        return;
    }

    if (quantity <= 0) {
        cout << "Quantity must be at least 1.\n";
        return;
    }

    if (quantity > products[productIndex].stock) {
        cout << "Not enough stock available!\n";
        return;
    }

    for (int i = 0; i < cartSize; i++) {
        if (cart[i].product.id == productId) {
            if (cart[i].quantity + quantity >
                products[productIndex].stock)
                 {
                cout << "Not enough stock available!\n";
                return;
            }

            cart[i].quantity += quantity;
            cout << "Cart quantity updated successfully!\n";
            return;
        }
    }


cart[cartSize].product = products[productIndex];
cart[cartSize].quantity = quantity;
cartSize++;

// Update stock in the main product array
products[productIndex].stock -= quantity;
// Update stock in the hash table too
InventoryNode* inventoryItem =
    searchInventory(inventory, productId);

if (inventoryItem != nullptr) {
    inventoryItem->product.stock =
        products[productIndex].stock;
}
cout << "Product added to cart successfully!\n";
cout << "Remaining stock: "
     << products[productIndex].stock << '\n';

}

void displayCart(CartItem cart[], int cartSize) {
    if (cartSize == 0) {
        cout << "\nYour cart is empty!\n";
        return;
    }

    double totalBill = 0;

    cout << "\n========== YOUR SHOPPING CART ==========\n";

    cout << left
         << setw(20) << "Product"
         << setw(12) << "Price"
         << setw(10) << "Quantity"
         << "Subtotal\n";

    cout << string(55, '-') << '\n';

    for (int i = 0; i < cartSize; i++) {
        double subtotal =
            cart[i].product.price * cart[i].quantity;

        totalBill += subtotal;

        cout << left
             << setw(20) << cart[i].product.name
             << setw(12) << fixed << setprecision(2)
             << cart[i].product.price
             << setw(10) << cart[i].quantity
             << subtotal << '\n';
    }

    cout << string(55, '-') << '\n';
    cout << "TOTAL BILL: Rs. "
         << fixed << setprecision(2)
         << totalBill << '\n';
}


void removeFromCart(CartItem cart[], int &cartSize, int productId) {
    int index = -1;

    for (int i = 0; i < cartSize; i++) {
        if (cart[i].product.id == productId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Product not found in cart!\n";
        return;
    }

    for (int i = index; i < cartSize - 1; i++) {
        cart[i] = cart[i + 1];
    }

    cartSize--;

    cout << "Product removed from cart successfully!\n";
}


int hashFunction(int productId) {
    return productId % TABLE_SIZE;
}

void insertInventory(InventoryNode* table[], Product product) {
    int index = hashFunction(product.id);

    InventoryNode* newNode = new InventoryNode;
    newNode->product = product;
    newNode->next = table[index];

    table[index] = newNode;
}

InventoryNode* searchInventory(InventoryNode* table[], int productId) {
    int index = hashFunction(productId);

    InventoryNode* current = table[index];

    while (current != nullptr) {
        if (current->product.id == productId) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool updateStock(InventoryNode* table[], int productId, int quantity) {
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


int main() {
    Product products[] = {
        {101, "Headphones", "Electronics", 1499.00, 4.5, 20},
        {102, "Smart Watch", "Electronics", 2299.00, 4.2, 15},
        {103, "Running Shoes", "Fashion", 1799.00, 4.7, 12},
        {104, "Backpack", "Accessories", 899.00, 4.1, 25},
        {105, "Keyboard", "Electronics", 1199.00, 4.4, 18}
    };

    int totalProducts = sizeof(products) / sizeof(products[0]);
 
    
InventoryNode* inventory[TABLE_SIZE] = {};

for (int i = 0; i < totalProducts; i++) {
    insertInventory(inventory, products[i]);
}


    int inventoryId;

    cout << "\n===== INVENTORY SEARCH =====\n";
    cout << "Enter Product ID to find in inventory: ";
    cin >> inventoryId;

    InventoryNode* foundItem =
        searchInventory(inventory, inventoryId);

    if (foundItem != nullptr) {
        cout << "\nInventory Product Found!\n";
        cout << "Name: " << foundItem->product.name << '\n';
        cout << "Stock: " << foundItem->product.stock << '\n';
        cout << "Price: Rs. "
             << fixed << setprecision(2)
             << foundItem->product.price << '\n';
    } else {
        cout << "Product not found in inventory!\n";
    }

    
    cout << "\n===== UPDATE INVENTORY STOCK =====\n";

    updateStock(inventory, 101, 14);

    InventoryNode* updatedItem =
        searchInventory(inventory, 101);

    if (updatedItem != nullptr) {
        cout << "Verified Stock: "
             << updatedItem->product.stock << '\n';
    }

CartItem cart[5];
int cartSize = 0;

    cout << "\n===== SHOPSMART: BEFORE SORTING =====\n\n";
    displayProducts(products, totalProducts);

    mergeSort(products, 0, totalProducts - 1);

    Product ratingSortedProducts[5];

for (int i = 0; i < totalProducts; i++) {
    ratingSortedProducts[i] = products[i];
}

quickSortByRating(ratingSortedProducts, 0, totalProducts - 1);

cout << "\n===== PRODUCTS SORTED BY RATING (HIGH TO LOW) =====\n";
displayProducts(ratingSortedProducts, totalProducts);

    cout << "\n===== PRODUCTS SORTED BY PRICE =====\n\n";
    displayProducts(products, totalProducts);

    int searchId;
    cout << "\nEnter Product ID to search: ";
    cin >> searchId;

    
    // Linear Search
    int index = linearSearch(products, totalProducts, searchId);

    if (index != -1) {
        cout << "\nLinear Search: Product Found!\n";
        cout << "Name: " << products[index].name << '\n';
    } else {
        cout << "\nLinear Search: Product not found!\n";
    }

    // Create a separate array for Binary Search
    Product idSortedProducts[5];

    for (int i = 0; i < totalProducts; i++) {
        idSortedProducts[i] = products[i];
    }

    // Sort products by ID
    sortById(idSortedProducts, totalProducts);

    // Binary Search
    int binaryIndex = binarySearch(
        idSortedProducts, totalProducts, searchId
    );

    if (binaryIndex != -1) {
        cout << "\nBinary Search: Product Found!\n";
        cout << "Name: "
             << idSortedProducts[binaryIndex].name << '\n';
        cout << "Category: "
             << idSortedProducts[binaryIndex].category << '\n';
        cout << "Price: Rs. "
             << idSortedProducts[binaryIndex].price << '\n';
        cout << "Rating: "
             << idSortedProducts[binaryIndex].rating << '\n';
        cout << "Stock: "
             << idSortedProducts[binaryIndex].stock << '\n';
    } else {
        cout << "\nBinary Search: Product not found!\n";
    }


    int cartProductId;
    int quantity;

    cout << "\n===== SHOPSMART SHOPPING CART =====\n";
    cout << "Enter Product ID to add to cart: ";
    cin >> cartProductId;

    cout << "Enter quantity: ";
    cin >> quantity;

    addToCart(
    cart, cartSize, products,
    totalProducts, cartProductId, quantity,
    inventory
);

    cout << "\nProducts currently in cart: "
         << cartSize << '\n';
     displayCart(cart, cartSize);

     
    char removeChoice;
    cout << "\nDo you want to remove a product? (y/n): ";
    cin >> removeChoice;

    if (removeChoice == 'y' || removeChoice == 'Y') {
        int removeId;

        cout << "Enter Product ID to remove: ";
        cin >> removeId;

        removeFromCart(cart, cartSize, removeId);

        displayCart(cart, cartSize);
    }


    return 0;
}

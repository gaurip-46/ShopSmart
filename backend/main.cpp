
#include "../include/ShopSmart.h"

int main() {
    const int totalProducts = 5;

    Product products[5] = {
        {101, "Headphones", "Electronics", 1499.00, 4.5, 20},
        {102, "Smart Watch", "Electronics", 2299.00, 4.2, 15},
        {103, "Running Shoes", "Fashion", 1799.00, 4.7, 12},
        {104, "Backpack", "Accessories", 899.00, 4.1, 25},
        {105, "Keyboard", "Electronics", 1199.00, 4.4, 18}
    };

    // Initialize inventory hash table
    InventoryNode* inventory[TABLE_SIZE] = {};

    for (int i = 0; i < totalProducts; i++) {
        insertInventory(inventory, products[i]);
    }

    // Initialize shopping cart
    CartItem cart[5];
    int cartSize = 0;
    int choice = 0;

    do {
        cout << "\n================================\n";
        cout << "       WELCOME TO SHOPSMART\n";
        cout << "================================\n";
        cout << "1. View All Products\n";
        cout << "2. Search Product by ID\n";
        cout << "3. Sort Products by Price\n";
        cout << "4. Sort Products by Rating\n";
        cout << "5. Add Product to Cart\n";
        cout << "6. View Cart and Bill\n";
        cout << "7. Remove Product from Cart\n";
        cout << "8. Exit\n";
        cout << "--------------------------------\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            choice = 0;
            continue;
        }

        switch (choice) {

            case 1: {
                cout << "\n--- AVAILABLE PRODUCTS ---\n";
                displayProducts(products, totalProducts);
                break;
            }

            case 2: {
                int id;

                cout << "\nEnter Product ID to search: ";

                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid Product ID!\n";
                    break;
                }

                int index = linearSearch(
                    products, totalProducts, id
                );

                if (index != -1) {
                    cout << "\nProduct found:\n";
                    displayProducts(&products[index], 1);
                } else {
                    cout << "Product not found!\n";
                }

                break;
            }

            case 3: {
                mergeSort(products, 0, totalProducts - 1);

                cout << "\n--- PRODUCTS SORTED BY PRICE ---\n";
                displayProducts(products, totalProducts);
                break;
            }

            case 4: {
                quickSortByRating(
                    products, 0, totalProducts - 1
                );

                cout << "\n--- PRODUCTS SORTED BY RATING ---\n";
                displayProducts(products, totalProducts);
                break;
            }

            case 5: {
                int id, quantity;

                cout << "\n--- AVAILABLE PRODUCTS ---\n";
                displayProducts(products, totalProducts);

                cout << "\nEnter Product ID to add: ";

                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid Product ID!\n";
                    break;
                }

                cout << "Enter quantity: ";

                if (!(cin >> quantity)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid quantity!\n";
                    break;
                }

                addToCart(
                    cart,
                    cartSize,
                    products,
                    totalProducts,
                    id,
                    quantity,
                    inventory
                );

                break;
            }

            case 6: {
                displayCart(cart, cartSize);
                break;
            }

            case 7: {
                int id;

                cout << "\nEnter Product ID to remove: ";

                if (!(cin >> id)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid Product ID!\n";
                    break;
                }

                removeFromCart(
                    cart,
                    cartSize,
                    id,
                    products,
                    totalProducts,
                    inventory
                );

                break;
            }

            case 8: {
                cout << "\nThank you for shopping with ShopSmart!\n";
                break;
            }

            default: {
                cout << "Invalid choice! Please select 1 to 8.\n";
            }
        }

    } while (choice != 8);

    // Free inventory linked-list memory
    for (int i = 0; i < TABLE_SIZE; i++) {
        InventoryNode* current = inventory[i];

        while (current != nullptr) {
            InventoryNode* temp = current;
            current = current->next;
            delete temp;
        }
    }

    return 0;
}

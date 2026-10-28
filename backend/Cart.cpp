
#include "../include/ShopSmart.h"

// Add product to cart
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

    int cartIndex = -1;

    for (int i = 0; i < cartSize; i++) {
        if (cart[i].product.id == productId) {
            cartIndex = i;
            break;
        }
    }

    if (cartIndex != -1) {
        cart[cartIndex].quantity += quantity;
    } else {
        if (cartSize >= 5) {
            cout << "Cart is full!\n";
            return;
        }

        cart[cartSize].product = products[productIndex];
        cart[cartSize].quantity = quantity;
        cartIndex = cartSize;
        cartSize++;
    }

    // Reduce stock
    products[productIndex].stock -= quantity;

    InventoryNode* item = searchInventory(inventory, productId);

    if (item != nullptr) {
        item->product.stock = products[productIndex].stock;
    }

    cout << "Product added to cart successfully!\n";
    cout << "Remaining stock: "
         << products[productIndex].stock << '\n';
}

// Display cart and calculate bill
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

// Remove product and restore stock
void removeFromCart(
    CartItem cart[],
    int &cartSize,
    int productId,
    Product products[],
    int totalProducts,
    InventoryNode* inventory[]
) {
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

    int productIndex =
        linearSearch(products, totalProducts, productId);

    if (productIndex != -1) {
        products[productIndex].stock += cart[index].quantity;

        InventoryNode* item =
            searchInventory(inventory, productId);

        if (item != nullptr) {
            item->product.stock = products[productIndex].stock;
        }
    }

    for (int i = index; i < cartSize - 1; i++) {
        cart[i] = cart[i + 1];
    }

    cartSize--;

    cout << "Product removed successfully!\n";
    cout << "Stock restored successfully!\n";
}

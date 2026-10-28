# ShopSmart — E-Commerce Cart & Inventory Management System

ShopSmart is a C++ based project that simulates an e-commerce shopping cart and inventory management system. It demonstrates important Data Structures and Algorithms (DSA) through product searching, sorting, inventory management, and cart operations.

## Features

- View all available products
- Search products by ID
- Sort products by price using Merge Sort
- Sort products by rating using Quick Sort
- Manage product inventory using a hash table
- Add products to the shopping cart
- Remove products from the cart
- Generate a bill with the total amount

## Technologies Used

- C++
- Data Structures and Algorithms
- Hash Table
- Linked List
- Merge Sort
- Quick Sort
- Linear Search and Binary Search

## Project Structure

```text
ShopSmart/
├── backend/
│   ├── main.cpp
│   ├── Product.cpp
│   ├── Sorting.cpp
│   ├── Inventory.cpp
│   └── Cart.cpp
├── include/
│   └── ShopSmart.h
└── README.md
```

## How to Run

Compile the project:

```bash
g++ backend/main.cpp backend/Product.cpp backend/Sorting.cpp backend/Inventory.cpp backend/Cart.cpp -o shopsmart.exe
```

Run on Windows PowerShell:

```powershell
.\shopsmart.exe
```

## Objective

The objective of ShopSmart is to understand how data structures and algorithms can be applied to a practical e-commerce application.

## Future Improvements

- Develop a web-based frontend
- Connect the frontend with the C++ backend
- Add product-name search
- Save inventory data permanently
- Improve checkout and billing functionality

## Author

Developed as a college DSA project.

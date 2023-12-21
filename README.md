# Supermarket-Inventory-Management-System
This project, developed in C++, implements a comprehensive Supermarket Inventory Management System. The primary objective is to efficiently manage the stock of items in a supermarket, including CRUD functionalities. It also includes specialized features for monitoring items low in stock and items nearing their expiration date.

## Features
- Data File Handling: Utilizes a text file (Supermarket System Database.txt) for persistent storage of item data.
- Item Structure: Each item in the inventory is represented with attributes like name, expiration date, quantity, price, and type.
- Load and Save Functionality: Items can be loaded from and saved to the data file, ensuring data persistence.
- Listing Items: Displays all items in the inventory in a formatted manner.
- Insertion and Deletion: Allows the user to add new items to the inventory and delete existing ones.
- Editing Items: Provides the functionality to edit the details of existing items.
- Searching Items: Enables searching for items by name and displays matching results.
- Stock Monitoring: Features a function to list items that are low in stock.
- Expiration Alert: Includes a function to print items that are about to expire in the next five days.
## Technical Implementation
- Exception Handling: Includes robust error handling for file operations and data validity.
- Data Manipulation: Employs standard C++ libraries for file I/O, strings, vectors, and stream manipulations.
- User Interface: Implements a simple console-based menu for user interaction.

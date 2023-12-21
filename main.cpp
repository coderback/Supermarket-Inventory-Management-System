#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// name of the data file
const std::string FILENAME = "Supermarket System Database.txt";

struct Item {
  std::string name;
  std::string date;
  int quantity;
  double price;
  std::string type;
};

// function to load the items from the data file
std::vector<Item> loadItems() {
  std::vector<Item> items;
  std::ifstream file(FILENAME);
  if (!file) {
    throw std::runtime_error("Unable to open file.");
  }
  if (file) {
    std::string line;

    while (getline(file, line)) {
      Item item;

      std::istringstream iss(line);
      // sequence is important!
      if (!(iss >> item.name >> item.date >> item.quantity >> item.price >>
            item.type))
        throw std::runtime_error("invalid data");
      iss >> item.name >> item.date >> item.quantity >> item.price >> item.type;

      /*std::stringstream ss(line);
      getline(ss, item.name, '\t');
      getline(ss, item.date, '\t');
      ss >> item.quantity;
      ss.ignore();
      ss >> item.price;
      ss.ignore();
      getline(ss, item.type);*/
      items.push_back(item);
    }
    file.close();
  }
  return items;
}

// function to save the items to the data file
void saveItems(const std::vector<Item> &items) {
  std::ofstream file(FILENAME);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open file.");
  }
  for (const auto &item : items) {
    file << item.name << '\t' << item.date << '\t' << item.quantity << '\t'
         << item.price << '\t' << item.type << '\n';
  }
  file.close();
}

// function to list the items to the data file
void listItem() {
  const std::string &filename = FILENAME;
  std::ifstream file(filename);
  try {
    if (!file.is_open()) {
      throw std::runtime_error("Unable to open file.");
    }

    // print the data in a formatted manner
    std::string line;
    std::cout << '\n'
              << std::left << std::setw(20) << "Name" << std::setw(15) << "Date"
              << std::setw(10) << "Quantity" << std::setw(10) << "Price"
              << std::setw(10) << "Type" << std::endl;
    while (getline(file, line)) {
      std::stringstream ss(line);
      std::string name, date, type;
      int quantity;
      double price;
      ss >> name >> date >> quantity >> price >> type;
      std::cout << std::left << std::setw(20) << name << std::setw(15) << date
                << std::setw(10) << quantity << std::setw(10) << price
                << std::setw(10) << type << std::endl;
    }

    file.close();
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
  }
}

// function to insert items to the data file
std::vector<Item> insertItem(std::vector<Item> items) {
  Item item;
  std::cout << "Enter item name: ";
  // getline(std::cin, item.name);
  std::cin >> item.name;
  std::cout << "Enter expiration date (dd/mm/yyyy): ";
  // getline(std::cin, item.date);
  std::cin >> item.date;
  std::cout << "Enter quantity: ";
  std::cin >> item.quantity;
  std::cout << "Enter price: ";
  std::cin >> item.price;
  std::cout << "Enter item type: ";
  // std::cin.ignore();
  // getline(std::cin, item.type);
  std::cin >> item.type;
  std::cout << item.name << '\t' << item.date << '\t' << item.quantity << '\t'
            << item.price << '\t' << item.type << std::endl;
  items.push_back(item);

  return items;
}

// function to delete items to the data file
void deleteItem(std::vector<Item> &items) {
  std::string name;
  std::cout << "Enter name of item to delete: ";
  getline(std::cin, name);
  if (name.empty()) {
    std::cout << "Error: Item name cannot be empty.\n";
    return;
  }
  auto it = remove_if(items.begin(), items.end(),
                      [&](const Item &item) { return item.name == name; });
  if (it != items.end()) {
    items.erase(it, items.end());
    std::cout << "Item deleted successfully.\n";
    saveItems(items); // update original.txt file
  } else {
    std::cout << "Error: Item \"" << name << "\" not found.\n";
  }
}

// function to edit existing items in the data file
void editItem(std::vector<Item> &items) {
  std::string name;
  std::cout << "Enter name of item to edit: ";
  getline(std::cin, name);
  auto it = find_if(items.begin(), items.end(),
                    [&](const Item &item) { return item.name == name; });
  if (it != items.end()) {
    std::cout << "Enter new name: ";
    getline(std::cin, it->name);
    std::cout << "Enter new date (dd/mm/yyyy): ";
    getline(std::cin, it->date);
    std::cout << "Enter new quantity: ";
    std::cin >> it->quantity;
    std::cout << "Enter new price: ";
    std::cin >> it->price;
    std::cin.ignore(); // consume the newline character left in the input stream
    std::cout << "Enter new type: ";
    getline(std::cin, it->type);
  }
}

// function to search for an item in the data file
void searchItem(const std::vector<Item> &items) {
  std::string searchName;
  std::cout << "Enter the name of the item to search for: ";
  std::cin.ignore();
  getline(std::cin, searchName);

  std::vector<Item> filteredItems;
  for (const Item &item : items) {
    if (item.name.find(searchName) != std::string::npos) {
      filteredItems.push_back(item);
    }
  }

  if (filteredItems.empty()) {
    std::cout << "No items found with the name \"" << searchName << "\""
              << std::endl;
    return;
  }

  std::cout << "\nMatching items:\n";
  for (const Item &item : filteredItems) {
    std::cout << "Name: " << item.name << std::endl;
    std::cout << "Date: " << item.date << std::endl;
    std::cout << "Quantity: " << item.quantity << std::endl;
    std::cout << "Price: " << item.price << std::endl;
    std::cout << "Type: " << item.type << std::endl;
    std::cout << std::endl;
  }

  std::cout
      << "Do you want to save the filtered results to a text file? (Y/N): ";
  std::string saveOption;
  std::cin >> saveOption;

  if (saveOption == "Y" || saveOption == "y") {
    std::string filename;
    std::cout << "Enter the name of the file to save the filtered results: ";
    std::cin >> filename;
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
      std::cout << "Unable to open file for writing." << std::endl;
      return;
    }

    for (const Item &item : filteredItems) {
      outfile << item.name << "\t" << item.date << "\t" << item.quantity << "\t"
              << item.price << "\t" << item.type << std::endl;
    }

    std::cout << "Filtered results saved to file \"" << filename << "\"."
              << std::endl;
  }
}

// Function to print items low in stock
void printItemsLowInStock(const std::vector<Item> &items) {
  std::cout << "\nItems low in stock:" << std::endl;
  std::cout << std::setw(20) << std::left << "Name" << std::setw(10)
            << "Quantity" << std::endl;
  for (const auto &item : items) {
    if (item.quantity < 10) {
      std::cout << std::setw(20) << std::left << item.name << std::setw(10)
                << item.quantity << std::endl;
    }
  }
}

// function to print items about to expire in the next 5 days

void printExpiringItems(const std::vector<Item> &items) {
  std::string input_date;
  std::cout << "\nEnter today's date (dd/mm/yyyy): ";
  std::cin >> input_date;

  std::tm tm = {};
  std::istringstream iss(input_date);
  iss >> std::get_time(&tm, "%d/%m/%Y");
  if (iss.fail()) {
    std::cout << "Invalid date format.\n";
    return;
  }

  std::time_t date = std::mktime(&tm);

  for (const Item &item : items) {
    std::tm item_tm = {};
    std::istringstream item_iss(item.date);
    item_iss >> std::get_time(&item_tm, "%d/%m/%Y");
    if (item_iss.fail()) {
      std::cout << "Invalid date format for item " << item.name << "\n";
      continue;
    }
    std::time_t item_date = std::mktime(&item_tm);
    if (item_date < date) {
      std::cout << "Item " << item.name << " expired (on " << item.date
                << ")\n";
    } else if (item_date <= date + 5 * 24 * 60 * 60) {
      std::cout << "Item " << item.name << " is expiring soon (on " << item.date
                << ")\n";
    }
  }
}

int main() {
  std::vector<Item> items = loadItems();
  int choice;

  // Display menu and prompt user for input until they choose to exit
  do {
    std::cout << "\n1. List item\n"
              << "2. Insert item\n"
              << "3. Delete item\n"
              << "4. Edit item\n"
              << "5. Search item\n"
              << "6. Print items low in stock\n"
              << "7. Print items about to expire in the next 5 days\n"
              << "8. Exit\n"
              << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    // Processes users choice
    switch (choice) {
    case 1:
      listItem();
      break;
    case 2:
      items = insertItem(items);
      saveItems(items);
      break;
    case 3:
      deleteItem(items);
      saveItems(items);
      break;
    case 4:
      editItem(items);
      saveItems(items);
      break;
    case 5:
      searchItem(items);
      break;
    case 6:
      printItemsLowInStock(items);
      break;
    case 7:
      printExpiringItems(items);
      break;
    case 8:
      std::cout << "Exiting...\n";
      break;
    default:
      std::cout << "Invalid choice.\n";
      break;
    }
  } while (choice != 8);

  return 0;
}

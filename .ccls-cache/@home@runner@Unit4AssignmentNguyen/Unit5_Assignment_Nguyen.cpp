// Thien Nguyen
// COSC-1437
// Professor: Dr. T
// Unit 5 Assignment Nguyen
// 4/28/2024
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Define colors for output
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

class MenuItem {
private:
  string name;
  double itemCost;
  string desc;
  char addLetter;
  char removeLetter;
  int count;

public:
  MenuItem(string n, double cost, string d, char add, char remove)
      : name(n), itemCost(cost), desc(d), addLetter(add), removeLetter(remove),
        count(0) {}

  string getName() const { return name; }
  double getItemCost() const { return itemCost; }
  string getDesc() const { return desc; }
  char getAddLetter() const { return addLetter; }
  char getRemoveLetter() const { return removeLetter; }
  int getCount() const { return count; }
  void incrementCount() { count++; }
  void decrementCount() { count--; }
};

void populateMenu(vector<MenuItem> &entireMenu) {
  entireMenu.push_back(
      MenuItem("Green Tea", 3.00, "Refreshing green tea", 'A', 'a'));
  entireMenu.push_back(
      MenuItem("Burrito", 4.50, "Delicious beef burrito", 'B', 'b'));
  entireMenu.push_back(
      MenuItem("Pizza", 5.50, "Cheesy pepperoni pizza", 'C', 'c'));
  entireMenu.push_back(
      MenuItem("Salad", 4.00, "Healthy garden salad", 'D', 'd'));
  entireMenu.push_back(
      MenuItem("Burger", 6.00, "Juicy beef burger with fries", 'E', 'e'));
  entireMenu.push_back(
      MenuItem("Soda", 1.50, "Refreshing soda drink", 'F', 'f'));
}

void showMenu(const vector<MenuItem> &m) {
  cout << RESET << fixed
       << setprecision(2); // Reset color and set doubles to 2 decimal places
  cout << GREEN << "ADD  \t" << CYAN << "NAME \t" << YELLOW << "COST \t" << RED
       << "REMOVE\t" << MAGENTA << "COUNT\t" << BLUE << "DESC" << endl;
  for (const auto &item : m) {
    cout << GREEN << item.getAddLetter() << ")" << RESET << setw(10) << CYAN
         << item.getName() << RESET << setw(5) << YELLOW << "$"
         << item.getItemCost() << RESET << setw(5) << RED << "("
         << item.getRemoveLetter() << ")" << RESET << setw(7) << MAGENTA
         << item.getCount() << RESET << setw(13) << BLUE << item.getDesc()
         << endl;
  }
}

void acceptOrder(vector<MenuItem> &m) {
  char option = '\0'; // The user-selected menu item
  double subtotal = 0.0;
  double taxRate = 0.1; // 10% tax rate
  double tipAmount;

  // Accept orders until 'x' or 'X' is entered
  do {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option;

    for (auto &item : m) {
      if (option == item.getAddLetter()) {
        cout << "\nMenu Item " << item.getAddLetter() << " selected.";
        item.incrementCount();
        cout << "\033[2J\033[1;1H"; // Clear screen
        cout << "\n1 UP on " << item.getName() << endl;
        subtotal += item.getItemCost();
        showMenu(m); // Show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;
      } else if (option == item.getRemoveLetter()) {
        cout << "\nRemove Item " << item.getRemoveLetter() << " selected.";
        if (item.getCount() > 0) {
          item.decrementCount();
          cout << "\033[2J\033[1;1H"; // Clear screen
          cout << "\n1 DOWN on " << item.getName() << endl;
          subtotal -= item.getItemCost();
          showMenu(m); // Show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;
        } else {
          cout << "\nItem count must be > 0 to remove: " << item.getName()
               << endl;
        }
      } else if (option != item.getAddLetter() &&
                 option != item.getRemoveLetter() && option != 'x' &&
                 option != 'X') {
        if (&item == &m.front()) {
          cout << "\nInvalid input (" << option << "). Please try again."
               << endl;
        }
      }
    }
  } while (option != 'x' && option != 'X');

  double tax = subtotal * taxRate;
  double total = subtotal + tax;

  cout << "\nSubtotal: $" << subtotal << endl;
  cout << "Tax (10%): $" << tax << endl;
  cout << "Total: $" << total << endl;

  cout << "Enter the tip amount: $";
  cin >> tipAmount;
  double tip = tipAmount;

  cout << "Tip: $" << tip << endl;
  cout << "Grand Total: $" << total + tip << endl;
  cout << "\nThank you for placing your order." << endl;
  // Handle receipt generation here
}

int main() {
  vector<MenuItem> wholeMenu;
  populateMenu(wholeMenu); // Put some default values in the menu
  showMenu(wholeMenu);     // Print the current data of the menu on the screen
  acceptOrder(wholeMenu);

  return 0;
}

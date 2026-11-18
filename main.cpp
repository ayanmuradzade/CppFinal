
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
using namespace std;

// ==================== DRINK CLASS ====================

class Drink {
private:
    string name;
    double price;
    int calories;

public:
    Drink(string n, double p, int c) {
        name = n;
        price = p;
        calories = c;
    }

    void display() const {
        cout << name << " | Price: " << price
             << " AZN | Calories: " << calories << " kcal" << endl;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getCalories() const {
        return calories;
    }
};

// ==================== INGREDIENT CLASS ====================

class Ingredient {
private:
    string name;
    double quantity;
    string unit;

public:
    Ingredient(string n, double q, string u) {
        name = n;
        quantity = q;
        unit = u;
    }

    bool hasEnough(double amount) const {
        return quantity >= amount;
    }

    void use(double amount) {
        quantity -= amount;
    }

    void addQuantity(double amount) {
        quantity += amount;
    }

    void display() const {
        cout << name << ": " << quantity << " " << unit << endl;
    }
};

// ==================== INVENTORY CLASS ====================

class Inventory {
private:
    Ingredient coffeeBeans;
    Ingredient water;
    Ingredient regularMilk;
    Ingredient oatMilk;
    Ingredient almondMilk;
    Ingredient lactoseMilk;
    Ingredient sugar;
    Ingredient vanilla;
    Ingredient caramel;
    Ingredient hazelnut;
    Ingredient cups;

public:
    Inventory()
        : coffeeBeans("Coffee Beans", 500, "g"),
          water("Water", 2000, "ml"),
          regularMilk("Regular Milk", 1000, "ml"),
          oatMilk("Oat Milk", 1000, "ml"),
          almondMilk("Almond Milk", 1000, "ml"),
          lactoseMilk("Lactose-Free Milk", 1000, "ml"),
          sugar("Sugar", 500, "g"),
          vanilla("Vanilla Syrup", 500, "ml"),
          caramel("Caramel Syrup", 500, "ml"),
          hazelnut("Hazelnut Syrup", 500, "ml"),
          cups("Cups", 20, "pcs") {
    }

    bool canPrepare(
        int milkChoice,
        int syrupChoice,
        double coffeeUsed,
        double waterUsed,
        double milkUsed,
        double sugarUsed,
        double syrupUsed
    ) const {

        if (!coffeeBeans.hasEnough(coffeeUsed)) return false;
        if (!water.hasEnough(waterUsed)) return false;
        if (!cups.hasEnough(1)) return false;
        if (!sugar.hasEnough(sugarUsed)) return false;

        if (milkChoice == 1 && !regularMilk.hasEnough(milkUsed))
            return false;

        if (milkChoice == 2 && !oatMilk.hasEnough(milkUsed))
            return false;

        if (milkChoice == 3 && !almondMilk.hasEnough(milkUsed))
            return false;

        if (milkChoice == 4 && !lactoseMilk.hasEnough(milkUsed))
            return false;

        if (syrupChoice == 1 && !vanilla.hasEnough(syrupUsed))
            return false;

        if (syrupChoice == 2 && !caramel.hasEnough(syrupUsed))
            return false;

        if (syrupChoice == 3 && !hazelnut.hasEnough(syrupUsed))
            return false;

        return true;
    }

    void useIngredients(
        int milkChoice,
        int syrupChoice,
        double coffeeUsed,
        double waterUsed,
        double milkUsed,
        double sugarUsed,
        double syrupUsed
    ) {
        coffeeBeans.use(coffeeUsed);
        water.use(waterUsed);
        cups.use(1);
        sugar.use(sugarUsed);

        if (milkChoice == 1) regularMilk.use(milkUsed);
        if (milkChoice == 2) oatMilk.use(milkUsed);
        if (milkChoice == 3) almondMilk.use(milkUsed);
        if (milkChoice == 4) lactoseMilk.use(milkUsed);

        if (syrupChoice == 1) vanilla.use(syrupUsed);
        if (syrupChoice == 2) caramel.use(syrupUsed);
        if (syrupChoice == 3) hazelnut.use(syrupUsed);
    }

    void displayInventory() const {
        cout << "\n===== CURRENT INVENTORY =====" << endl;

        coffeeBeans.display();
        water.display();
        regularMilk.display();
        oatMilk.display();
        almondMilk.display();
        lactoseMilk.display();
        sugar.display();
        vanilla.display();
        caramel.display();
        hazelnut.display();
        cups.display();
    }

    void restockIngredient(int choice) {
        double amount;

        cout << "Enter quantity to add: ";
        cin >> amount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!" << endl;
            return;
        }

        if (amount <= 0) {
            cout << "Quantity must be greater than zero!" << endl;
            return;
        }

        switch (choice) {
            case 1: coffeeBeans.addQuantity(amount); break;
            case 2: water.addQuantity(amount); break;
            case 3: regularMilk.addQuantity(amount); break;
            case 4: oatMilk.addQuantity(amount); break;
            case 5: almondMilk.addQuantity(amount); break;
            case 6: lactoseMilk.addQuantity(amount); break;
            case 7: sugar.addQuantity(amount); break;
            case 8: vanilla.addQuantity(amount); break;
            case 9: caramel.addQuantity(amount); break;
            case 10: hazelnut.addQuantity(amount); break;
            case 11: cups.addQuantity(amount); break;
            default:
                cout << "Invalid ingredient choice!" << endl;
                return;
        }

        cout << "Stock updated successfully!" << endl;
    }
};

// ==================== ORDER STRUCT ====================

struct Order {
    string drinkName;
    string customizations;
    double totalPrice;
    int totalCalories;
    double payment;
    double change;
};

// ==================== INPUT FUNCTIONS ====================

int getInt(string message, int minValue, int maxValue) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number!" << endl;
            continue;
        }

        if (value < minValue || value > maxValue) {
            cout << "Invalid choice. Try again!" << endl;
            continue;
        }

        return value;
    }
}

double getPositiveAmount(string message) {
    double amount;

    while (true) {
        cout << message;
        cin >> amount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid amount!" << endl;
            continue;
        }

        if (amount <= 0) {
            cout << "Amount must be greater than zero!" << endl;
            continue;
        }

        return amount;
    }
}

// ==================== ORDER HISTORY ====================

void displayOrderHistory(const vector<Order> &orderHistory) {
    cout << "\n===== ORDER HISTORY =====" << endl;

    if (orderHistory.empty()) {
        cout << "No completed orders yet." << endl;
        return;
    }

    for (int i = 0; i < orderHistory.size(); i++) {
        cout << "\nOrder #" << i + 1 << endl;
        cout << "Drink: " << orderHistory[i].drinkName << endl;
        cout << "Customizations: " << orderHistory[i].customizations << endl;
        cout << "Price: " << orderHistory[i].totalPrice << " AZN" << endl;
        cout << "Calories: " << orderHistory[i].totalCalories << " kcal" << endl;
        cout << "Payment: " << orderHistory[i].payment << " AZN" << endl;
        cout << "Change: " << orderHistory[i].change << " AZN" << endl;
    }
}

// ==================== SALES STATISTICS ====================

void displaySalesStatistics(const vector<Order> &orderHistory) {
    double totalRevenue = 0;

    for (int i = 0; i < orderHistory.size(); i++) {
        totalRevenue += orderHistory[i].totalPrice;
    }

    cout << "\n===== SALES STATISTICS =====" << endl;
    cout << "Total completed orders: " << orderHistory.size() << endl;
    cout << "Total revenue: " << totalRevenue << " AZN" << endl;
}

// ==================== CLIENT ORDER FUNCTION ====================

void processOrder(const Drink menu[], Inventory &inventory,
                  vector<Order> &orderHistory) {

    cout << "\n===== COFFEE MENU =====" << endl;

    for (int i = 0; i < 6; i++) {
        cout << i + 1 << ". ";
        menu[i].display();
    }

    int drinkChoice = getInt("\nChoose your coffee (1-6): ", 1, 6);

    Drink selectedDrink = menu[drinkChoice - 1];

    double totalPrice = selectedDrink.getPrice();
    int totalCalories = selectedDrink.getCalories();

    string customizations = "";

    // MILK SELECTION

    cout << "\n===== MILK OPTIONS =====" << endl;
    cout << "0. No Milk" << endl;
    cout << "1. Regular Milk (+0.50 AZN, +40 kcal)" << endl;
    cout << "2. Oat Milk (+0.80 AZN, +50 kcal)" << endl;
    cout << "3. Almond Milk (+1.00 AZN, +25 kcal)" << endl;
    cout << "4. Lactose-Free Milk (+0.70 AZN, +45 kcal)" << endl;

    int milkChoice = getInt("Choose milk: ", 0, 4);

    switch (milkChoice) {
        case 0: customizations += "No milk"; break;
        case 1:
            totalPrice += 0.50;
            totalCalories += 40;
            customizations += "Regular milk";
            break;
        case 2:
            totalPrice += 0.80;
            totalCalories += 50;
            customizations += "Oat milk";
            break;
        case 3:
            totalPrice += 1.00;
            totalCalories += 25;
            customizations += "Almond milk";
            break;
        case 4:
            totalPrice += 0.70;
            totalCalories += 45;
            customizations += "Lactose-free milk";
            break;
    }

    // SUGAR SELECTION

    cout << "\n===== SUGAR OPTIONS =====" << endl;
    cout << "0. No Sugar" << endl;
    cout << "1. Low Sugar (+10 kcal)" << endl;
    cout << "2. Normal Sugar (+20 kcal)" << endl;
    cout << "3. Extra Sugar (+40 kcal)" << endl;

    int sugarChoice = getInt("Choose sugar: ", 0, 3);

    switch (sugarChoice) {
        case 0: customizations += ", No sugar"; break;
        case 1:
            totalCalories += 10;
            customizations += ", Low sugar";
            break;
        case 2:
            totalCalories += 20;
            customizations += ", Normal sugar";
            break;
        case 3:
            totalCalories += 40;
            customizations += ", Extra sugar";
            break;
    }

    // SYRUP SELECTION

    cout << "\n===== SYRUP OPTIONS =====" << endl;
    cout << "0. No Syrup" << endl;
    cout << "1. Vanilla (+0.60 AZN, +30 kcal)" << endl;
    cout << "2. Caramel (+0.60 AZN, +35 kcal)" << endl;
    cout << "3. Hazelnut (+0.70 AZN, +40 kcal)" << endl;

    int syrupChoice = getInt("Choose syrup: ", 0, 3);

    switch (syrupChoice) {
        case 0: customizations += ", No syrup"; break;
        case 1:
            totalPrice += 0.60;
            totalCalories += 30;
            customizations += ", Vanilla syrup";
            break;
        case 2:
            totalPrice += 0.60;
            totalCalories += 35;
            customizations += ", Caramel syrup";
            break;
        case 3:
            totalPrice += 0.70;
            totalCalories += 40;
            customizations += ", Hazelnut syrup";
            break;
    }

    // EXTRA ESPRESSO SHOT

    int extraShot = getInt(
        "\nAdd extra espresso shot? (1 = Yes, 0 = No): ", 0, 1
    );

    if (extraShot == 1) {
        totalPrice += 1.00;
        totalCalories += 5;
        customizations += ", Extra espresso shot";
    }

    // CALORIE LIMIT

    int calorieLimit = getInt("\nEnter your calorie limit: ", 0, 10000);

    if (totalCalories > calorieLimit) {
        cout << "\nWarning! Your drink contains "
             << totalCalories << " kcal." << endl;

        cout << "It exceeds your limit of "
             << calorieLimit << " kcal." << endl;

        char choice;
        cout << "Continue with this order? (y/n): ";
        cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            cout << "Order cancelled." << endl;
            return;
        }
    }

    // ORDER SUMMARY

    cout << "\n===== ORDER SUMMARY =====" << endl;
    cout << "Drink: " << selectedDrink.getName() << endl;
    cout << "Customizations: " << customizations << endl;
    cout << "Total Price: " << totalPrice << " AZN" << endl;
    cout << "Total Calories: " << totalCalories << " kcal" << endl;

    // INGREDIENT REQUIREMENTS

    double coffeeUsed = 18;
    double waterUsed = 30;
    double milkUsed = 0;
    double sugarUsed = 0;
    double syrupUsed = 0;

    if (drinkChoice == 2) {
        waterUsed = 150;
    }

    if (extraShot == 1) {
        coffeeUsed += 18;
    }

    if (milkChoice != 0) {
        milkUsed = 150;
    }

    if (sugarChoice == 1) sugarUsed = 5;
    if (sugarChoice == 2) sugarUsed = 10;
    if (sugarChoice == 3) sugarUsed = 20;

    if (syrupChoice != 0) {
        syrupUsed = 15;
    }

    // CHECK INVENTORY

    if (!inventory.canPrepare(
        milkChoice, syrupChoice,
        coffeeUsed, waterUsed, milkUsed, sugarUsed, syrupUsed
    )) {
        cout << "\nInsufficient inventory!" << endl;
        cout << "Your order cannot be completed." << endl;
        return;
    }

    // PAYMENT

    double payment = 0;

    cout << "\n===== PAYMENT =====" << endl;
    cout << "Amount to pay: " << totalPrice << " AZN" << endl;

    while (payment < totalPrice) {
        double amount = getPositiveAmount("Insert money: ");

        payment += amount;

        if (payment < totalPrice) {
            cout << "Insufficient payment!" << endl;
            cout << "Remaining amount: "
                 << totalPrice - payment << " AZN" << endl;
        }
    }

    double change = payment - totalPrice;

    cout << "\nPayment successful!" << endl;
    cout << "Your change: " << change << " AZN" << endl;

    // UPDATE INVENTORY

    inventory.useIngredients(
        milkChoice, syrupChoice,
        coffeeUsed, waterUsed, milkUsed, sugarUsed, syrupUsed
    );

    // SAVE ORDER

    Order newOrder;

    newOrder.drinkName = selectedDrink.getName();
    newOrder.customizations = customizations;
    newOrder.totalPrice = totalPrice;
    newOrder.totalCalories = totalCalories;
    newOrder.payment = payment;
    newOrder.change = change;

    orderHistory.push_back(newOrder);

    cout << "\nYour coffee is being prepared..." << endl;
    cout << "Enjoy your coffee!" << endl;
}

// ==================== CLIENT INTERFACE ====================

void clientInterface(const Drink menu[], Inventory &inventory,
                     vector<Order> &orderHistory) {

    int choice;

    do {
        cout << "\n========== CLIENT INTERFACE ==========" << endl;
        cout << "1. Place an Order" << endl;
        cout << "0. Return to Main Menu" << endl;

        choice = getInt("Enter your choice: ", 0, 1);

        if (choice == 1) {
            processOrder(menu, inventory, orderHistory);
        }

    } while (choice != 0);
}

// ==================== ADMIN INTERFACE ====================

void adminInterface(Inventory &inventory,
                    const vector<Order> &orderHistory) {

    const string ADMIN_PASSWORD = "admin123";
    string password;

    cout << "\n===== ADMIN LOGIN =====" << endl;
    cout << "Enter admin password: ";
    cin >> password;

    if (password != ADMIN_PASSWORD) {
        cout << "Incorrect password! Access denied." << endl;
        return;
    }

    cout << "Admin login successful!" << endl;

    int choice;

    do {
        cout << "\n========== ADMIN INTERFACE ==========" << endl;
        cout << "1. View Inventory" << endl;
        cout << "2. Restock Ingredient" << endl;
        cout << "3. View Order History" << endl;
        cout << "4. View Sales Statistics" << endl;
        cout << "0. Return to Main Menu" << endl;

        choice = getInt("Enter your choice: ", 0, 4);

        switch (choice) {
            case 1:
                inventory.displayInventory();
                break;

            case 2: {
                cout << "\n===== RESTOCK MENU =====" << endl;
                cout << "1. Coffee Beans" << endl;
                cout << "2. Water" << endl;
                cout << "3. Regular Milk" << endl;
                cout << "4. Oat Milk" << endl;
                cout << "5. Almond Milk" << endl;
                cout << "6. Lactose-Free Milk" << endl;
                cout << "7. Sugar" << endl;
                cout << "8. Vanilla Syrup" << endl;
                cout << "9. Caramel Syrup" << endl;
                cout << "10. Hazelnut Syrup" << endl;
                cout << "11. Cups" << endl;

                int ingredientChoice = getInt(
                    "Choose ingredient: ", 1, 11
                );

                inventory.restockIngredient(ingredientChoice);
                break;
            }

            case 3:
                displayOrderHistory(orderHistory);
                break;

            case 4:
                displaySalesStatistics(orderHistory);
                break;

            case 0:
                cout << "Leaving Admin Interface..." << endl;
                break;
        }

    } while (choice != 0);
}

// ==================== MAIN FUNCTION ====================

int main() {

    cout << fixed << setprecision(2);

    Drink menu[6] = {
        Drink("Espresso", 3.00, 5),
        Drink("Americano", 3.50, 10),
        Drink("Cappuccino", 5.00, 90),
        Drink("Latte", 5.50, 130),
        Drink("Mocha", 6.00, 180),
        Drink("Flat White", 5.50, 120)
    };

    Inventory inventory;

    vector<Order> orderHistory;

    int choice;

    cout << "======================================" << endl;
    cout << "       SMART COFFEE MACHINE           " << endl;
    cout << "======================================" << endl;

    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Client Interface" << endl;
        cout << "2. Admin Interface" << endl;
        cout << "0. Exit System" << endl;

        choice = getInt("Select interface: ", 0, 2);

        switch (choice) {
            case 1:
                clientInterface(menu, inventory, orderHistory);
                break;

            case 2:
                adminInterface(inventory, orderHistory);
                break;

            case 0:
                cout << "\nThank you for using Smart Coffee Machine!" << endl;
                break;
        }

    } while (choice != 0);

    return 0;
}

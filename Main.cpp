#include <bits/stdc++.h>
using namespace std;

class Pizza {
private:
    string base;
    string sauce;
    string topping;
    int basePrice;
    int toppingPrice;
    int totalPrice;

public:
    void setBase(string base, int basePrice) {
        this->base = base;
        this->basePrice = basePrice;
    }
    void setSauce(string sauce) {
        this->sauce = sauce;
    }
    void setTopping(string topping, int toppingPrice) {
        this->topping = topping;
        this->toppingPrice = toppingPrice;
    }
    void setTotalPrice() {
        this->totalPrice = basePrice + toppingPrice;
    }
    int getTotalPrice() const {
        return totalPrice;
    }
};

class Product {
private:
    string name;
    string type;
    int price;

public:
    Product(string name, int price, string type) : name(name), price(price), type(type) {}
    string getName() const { return name; }
    string getType() const { return type; }
    int getPrice() const { return price; }
};

class Menu {
private:
    map<string, vector<Product*>> itemsList;
    map<string, int> basesList;
    vector<string> saucesList;
    map<string, int> toppingsList;

public:
    void addItem(string name, int price, string type) {
        itemsList[type].emplace_back(new Product(name, price, type));
    }
    void addBase(string name, int price) {
        basesList[name] = price;
    }
    void addSauce(string name) {
        saucesList.push_back(name);
    }
    void addTopping(string name, int price) {
        toppingsList[name] = price;
    }
    void display() {
        cout << "Menu:\n";

        cout << "Bases:\n";
        for (const auto& base : basesList) {
            cout << base.first << "\t" << base.second << " Rs\n";
        }

        cout << "\nSauces:\n";
        for (const auto& sauce : saucesList) {
            cout << sauce << "\n";
        }

        cout << "\nToppings:\n";
        for (const auto& topping : toppingsList) {
            cout << topping.first << "\t" << topping.second << " Rs\n";
        }

        cout << "\nDrinks and Desserts:\n";
        for (const auto& category : itemsList) {
            cout << "Category: " << category.first << "\n";
            for (const auto& product : category.second) {
                cout << product->getName() << "\t" << product->getPrice() << " Rs\n";
            }
        }
    }

    int getBasePrice(string name) {
        return basesList.count(name) ? basesList[name] : 0;
    }
    int getToppingPrice(string name) {
        return toppingsList.count(name) ? toppingsList[name] : 0;
    }
    vector<Product*> getItems(string category) {
        return itemsList[category];
    }
};

class Bill {
private:
    vector<Product> products;
    vector<Pizza> pizzas;
    int discountPercentage = 5;
    int totalPrice = 0;
    int amountPayable = 0;
    bool discount = false;
    bool payment = false;

public:
    void addItem(Product& item) {
        products.push_back(item);
        totalPrice += item.getPrice();
        amountPayable = totalPrice;
    }

    void addPizza(Pizza& pizza) {
        pizzas.push_back(pizza);
        totalPrice += pizza.getTotalPrice();
        amountPayable = totalPrice;
    }

    void applyDiscount() {
        discount = true;
        amountPayable = amountPayable * (100 - discountPercentage) / 100;
    }

    void display() {
        cout << "Bill:\n";

        for (const auto& product : products) {
            cout << product.getName() << "\t" << product.getPrice() << " Rs\n";
        }

        int pizzaCount = 1;
        for (const auto& pizza : pizzas) {
            cout << "Pizza " << pizzaCount++ << "\t" << pizza.getTotalPrice() << " Rs\n";
        }

        cout << "Total Price: " << totalPrice << " Rs\n";
        if (discount) {
            cout << "Discount Applied: " << discountPercentage << "%\n";
        }
        cout << "Amount Payable: " << amountPayable << " Rs\n";
    }

    void makePayment() {
        if (payment) {
            cout << "Payment already made.\n";
        } else {
            payment = true;
            cout << "Payment successful.\n";
        }
    }

    bool isPaid() {
        return payment;
    }

    int getNumItems() {
        return products.size() + pizzas.size();
    }
};

void initializeMenu(Menu& menu) {
    menu.addBase("Regular", 50);
    menu.addBase("Whole wheat", 75);

    menu.addSauce("Marinara sauce");
    menu.addSauce("Pesto sauce");

    menu.addTopping("Mozzarella cheese", 30);
    menu.addTopping("Cheddar cheese", 35);
    menu.addTopping("Spinach", 20);
    menu.addTopping("Corn", 15);
    menu.addTopping("Mushroom", 15);
    menu.addTopping("Chicken", 50);
    menu.addTopping("Pepperoni", 45);

    menu.addItem("Pepsi", 17, "drink");
    menu.addItem("7-up", 19, "drink");
    menu.addItem("Coke", 20, "drink");
    menu.addItem("Lava cake", 95, "dessert");
    menu.addItem("Chocolate brownie", 86, "dessert");
}

void choose(Menu& menu, Bill& bill) {
    while (true) {
        cout << "\nEnter Your Choice:\n";
        cout << "1. Display Menu\n";
        cout << "2. Make an Order\n";
        cout << "3. Display Cart\n";
        cout << "4. Make Payment\n";
        cout << "5. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            menu.display();
            break;

        case 2: {
            cout << "Order Type (Pizza/Other): ";
            string type;
            cin >> type;

            if (type == "Pizza") {
                string base, sauce, topping;

                cout << "Choose Base: ";
                cin >> base;
                cout << "Choose Sauce: ";
                cin >> sauce;
                cout << "Choose Topping: ";
                cin >> topping;

                if (menu.getBasePrice(base) == 0 || menu.getToppingPrice(topping) == 0) {
                    cout << "Invalid base or topping!\n";
                    break;
                }

                Pizza pizza;
                pizza.setBase(base, menu.getBasePrice(base));
                pizza.setSauce(sauce);
                pizza.setTopping(topping, menu.getToppingPrice(topping));
                pizza.setTotalPrice();
                bill.addPizza(pizza);
                cout << "Pizza added to the cart.\n";
            } else {
                cout << "Enter Category: ";
                string category;
                cin >> category;

                vector<Product*> items = menu.getItems(category);
                if (items.empty()) {
                    cout << "No items found in this category.\n";
                    break;
                }

                cout << "Available Items:\n";
                for (const auto& item : items) {
                    cout << item->getName() << "\t" << item->getPrice() << " Rs\n";
                }

                cout << "Enter Item Name: ";
                string itemName;
                cin >> itemName;

                bool found = false;
                for (const auto& item : items) {
                    if (item->getName() == itemName) {
                        bill.addItem(*item);
                        cout << itemName << " added to the cart.\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Item not found.\n";
                }
            }
            break;
        }

        case 3:
            bill.display();
            break;

        case 4:
            if (bill.getNumItems() == 0) {
                cout << "Cart is empty.\n";
            } else {
                bill.makePayment();
            }
            break;

        case 5:
            cout << "Thank you! Visit again.\n";
            return;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    Menu menu;
    Bill bill;

    initializeMenu(menu);
    choose(menu, bill);

    return 0;
}

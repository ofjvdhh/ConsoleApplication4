#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;

class Item {
public:
    string name;
    double price;

    Item(string n, double p) : name(n), price(p) {}
};

class Order {
private:
    vector<Item> pizzas;
    vector<Item> snacks;
    vector<Item> drinks;

public:
    void addPizza(const Item& pizza) {
        pizzas.push_back(pizza);
    }

    void addSnack(const Item& snack) {
        snacks.push_back(snack);
    }

    void addDrink(const Item& drink) {
        drinks.push_back(drink);
    }

    double calculateTotal() {
        double total = 0.0;

        // Считаем стоимость пицц
        total += pizzas.size() / 5 * 0; // Каждая 5-я пицца в подарок
        for (const auto& pizza : pizzas) {
            total += pizza.price;
        }

        // Считаем стоимость закусок
        for (const auto& snack : snacks) {
            total += snack.price;
        }

        // Считаем стоимость напитков
        int drinkCount = drinks.size();
        for (const auto& drink : drinks) {
            total += drink.price;
        }

        // Скидка на напитки
        if (drinkCount > 4) {
            total -= drinks[0].price; // Одна напиток в подарок
        }

        // Скидка 15% на весь заказ, если сумма заказа превышает 1000 рублей
        if (total > 1000) {
            total *= 0.85; // Применяем скидку 15%
        }

        return total;
    }

    void printOrder() {
        cout << "Ваш заказ:" << endl;
        cout << "Пиццы:" << endl;
        for (const auto& pizza : pizzas) {
            cout << " - " << pizza.name << ": " << fixed << setprecision(2) << pizza.price << " руб." << endl;
        }

        cout << "Закуски:" << endl;
        for (const auto& snack : snacks) {
            cout << " - " << snack.name << ": " << fixed << setprecision(2) << snack.price << " руб." << endl;
        }

        cout << "Напитки:" << endl;
        for (const auto& drink : drinks) {
            cout << " - " << drink.name << ": " << fixed << setprecision(2) << drink.price << " руб." << endl;
        }

        cout << "Итого к оплате: " << fixed << setprecision(2) << calculateTotal() << " руб." << endl;
    }
};

void displayMenu(const vector<Item>& items, const string& type) {
    cout << type << ":" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].name << " - " << fixed << setprecision(2) << items[i].price << " руб." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<Item> pizzas = { {"Маргарита", 500}, {"Пепперони", 600}, {"Гавайская", 550}, {"Четыре сыра", 650},
                            {"Мясная", 700}, {"Вегетарианская", 480}, {"С морепродуктами", 800} };

    vector<Item> snacks = { {"Крылышки", 300}, {"Чипсы", 150}, {"Салат", 250}, {"Наггетсы", 350} };

    vector<Item> drinks = { {"Кола", 100}, {"Сок", 120}, {"Минеральная вода", 80}, {"Пиво", 150}, {"Лимонад", 130} };

    while (true) {
        Order order;
        char choice;

        // Выбор пиццы
        while (true) {
            displayMenu(pizzas, "Выберите пиццу (или введите 'q' для завершения выбора):");
            cin >> choice;

            if (choice == 'q') break;

            int index = choice - '1';
            if (index >= 0 && index < pizzas.size()) {
                order.addPizza(pizzas[index]);
            }
            else {
                cout << "Некорректный ввод. Попробуйте снова." << endl;
            }
        }

        // Выбор закусок
        while (true) {
            displayMenu(snacks, "Выберите закуску (или введите 'q' для завершения выбора):");
            cin >> choice;

            if (choice == 'q') break;

            int index = choice - '1';
            if (index >= 0 && index < snacks.size()) {
                order.addSnack(snacks[index]);
            }
            else {
                cout << "Некорректный ввод. Попробуйте снова." << endl;
            }
        }

        // Выбор напитков
        while (true) {
            displayMenu(drinks, "Выберите напиток (или введите 'q' для завершения выбора):");
            cin >> choice;

            if (choice == 'q') break;

            int index = choice - '1';
            if (index >= 0 && index < drinks.size()) {
                order.addDrink(drinks[index]);
            }
            else {
                cout << "Некорректный ввод. Попробуйте снова." << endl;
            }
        }

        // Печать заказа
        order.printOrder();

        // Запрос на продолжение
        cout << "Хотите сделать еще один заказ? (y/n): ";
        cin >> choice;

        if (choice != 'y') break;

        system("cls"); // Очищаем экран
    }

    return 0;
}

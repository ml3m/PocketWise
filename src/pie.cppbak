#include <iostream>
#include <vector>
#include <matplot/matplot.h>
#include <cstdlib> 

void clearScreen() {
    system("clear");
}

class Expense {
    public:
        double amount;
        std::string category;

        Expense(double _amount, std::string _category) : amount(_amount), category(_category) {}
};

std::vector<Expense> expenses;
double balance = 0;

void addExpense(double amount, std::string category) {
    bool categoryExists = false;
    for (auto& expense : expenses) {
        if (expense.category == category) {
            expense.amount += amount;
            balance -= amount;
            categoryExists = true;
            break;
        }
    }
    if (!categoryExists) {
        expenses.push_back(Expense(amount, category));
        balance -= amount;
    }
}

void addIncome(double amount) {
    balance += amount;
}

void updatePieChart() {
    std::vector<double> amounts;
    std::vector<std::string> categories;
    for (const auto& expense : expenses) {
        amounts.push_back(expense.amount);
        categories.push_back(expense.category);
    }
    matplot::pie(amounts);
    matplot::legend(categories);
    matplot::show();
}

int main() {
    char choice;
    double amount;
    std::string category;

    while (true) {
        clearScreen();
        std::cout << "Expense App Menu:" << std::endl;
        std::cout << "1. Add Expense" << std::endl;
        std::cout << "2. Add Income" << std::endl;
        std::cout << "3. View Pie Chart" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter expense amount: ";
                std::cin >> amount;
                std::cout << "Enter expense category: ";
                std::cin >> category;
                addExpense(amount, category);
                break;
            case '2':
                std::cout << "Enter income amount: ";
                std::cin >> amount;
                addIncome(amount);
                break;
            case '3':
                updatePieChart();
                break;
            case '4':
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <matplot/matplot.h>
#include <cstdlib> 

void clearScreen() {
    system("clear");
}

using namespace std;
using namespace matplot;

class Expense {
    public:
        double amount;
        string category;

        Expense(double _amount, string _category) : amount(_amount), category(_category) {}
};

vector<Expense> expenses;
double balance = 0;

void addExpense(double amount, string category) {
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
    vector<double> amounts;
    vector<string> categories;
    for (const auto& expense : expenses) {
        amounts.push_back(expense.amount);
        categories.push_back(expense.category);
    }
    pie(amounts);
    legend(categories);
    show();
}

int main() {
    char choice;
    double amount;
    string category;

    while (true) {
        clearScreen();
        cout << "Expense App Menu:" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. Add Income" << endl;
        cout << "3. View Pie Chart" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Enter expense amount: ";
                cin >> amount;
                cout << "Enter expense category: ";
                cin >> category;
                addExpense(amount, category);
                break;
            case '2':
                cout << "Enter income amount: ";
                cin >> amount;
                addIncome(amount);
                break;
            case '3':
                updatePieChart();
                break;
            case '4':
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

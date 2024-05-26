#include <matplot/axes_objects/labels.h>
#include <matplot/matplot.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cctype>
#include <string>
#include <cstdio>
#include <vector>
#include <ctime>

#include "../include/Analysis.h"
#include "../include/ExpenseRevenue.h"

void Analysis::monthAnalysis(const std::string& username) {
    int month;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;
    
    if (month < 1 || month > 12) {
        std::cout << "Invalid month. Please enter a number between 1 and 12." << std::endl;
        return;
    }

    std::ifstream expensesFile("data/expenses.txt");
    std::string line;
    bool foundExpenses = false;
    std::cout << "Expenses for user " << username << " in month " << month << ":" << std::endl;
    while (getline(expensesFile, line)) {
        std::istringstream iss(line);
        std::string usr, description;
        double amount;
        int expMonth, category;
        if (iss >> usr >> amount >> expMonth >> category >> description) {
            if (usr == username && expMonth == month) {
                std::cout << "Amount: " << amount << ", Category: " << category << ", Description: " << description << std::endl;
                foundExpenses = true;
            }
        }
    }
    expensesFile.close();

    if (!foundExpenses) {
        std::cout << "No expenses found for user " << username << " in month " << month << "." << std::endl;
    }
}

void Analysis::updatePieChart(const std::string& username) {
    std::vector<double> amounts;
    std::vector<std::string> categories;

    std::ifstream expensesFile("data/expenses.txt");
    if (!expensesFile.is_open()) {
        std::cout << "Error: Unable to open expenses file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(expensesFile, line)) {
        std::istringstream iss(line);
        std::string usr, description;
        double amount;
        int category, month;
        if (iss >> usr >> amount >> month >> category >> description && usr == username) {
            std::string categoryName = ExpenseRevenue::getCategoryName(category);
            amounts.push_back(amount);
            categories.push_back(categoryName);
        }
    }
    expensesFile.close();

    const int maxLegendEntries = 10; 
    if (categories.size() > maxLegendEntries) {
        std::cout << "Warning: Too many categories to display in the legend. Only the first "
                  << maxLegendEntries << " categories will be shown." << std::endl;
        categories.resize(maxLegendEntries);
        amounts.resize(maxLegendEntries);
    }

    matplot::pie(amounts);
    matplot::legend(categories);
    matplot::show();
}

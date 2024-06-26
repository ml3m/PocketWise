#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <ostream>
#include <cctype>
#include <string>
#include <ctime>

/************** header files import **************/
#include "../include/Analysis.h"

void Analysis::monthAnalysis(const std::string& username) {
    // File handling + Expenses/Revenues + month Analysis for months 1-12 
    int month;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;

    if (month < 1 || month > 12) {
        std::cout << "Invalid month. Please enter a number between 1 and 12." << std::endl;
        return;
    }

    // Processing expenses
    std::ifstream expensesFile("data/expenses.txt");
    std::string line;
    bool foundExpenses = false;
    std::cout << "Expenses for user " << username << " in month " << month << ":" << std::endl;
    while (getline(expensesFile, line)) {
        std::istringstream iss(line);
        std::string usr;
        double amount;
        int expMonth, category;
        if (iss >> usr >> amount >> expMonth >> category) {
            std::string description;
            getline(iss, description);
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
    std::cout << std::endl;

    // Processing revenues
    std::ifstream revenueFile("data/revenues.txt");
    std::string line_revenue;
    bool foundRevenue = false;
    std::cout << "Revenues for user " << username << " in month " << month << ":" << std::endl;
    while (getline(revenueFile, line_revenue)) {
        std::istringstream iss(line_revenue);
        std::string user;
        double amount;
        int revMonth;
        if (iss >> user >> amount >> revMonth) {
            std::string user_description;
            getline(iss, user_description);  // Read the rest of the line as description
            if (user == username && revMonth == month) {
                std::cout << "Amount: " << amount << ", Description: " << user_description << std::endl;
                foundRevenue = true;
            }
        }
    }
    revenueFile.close();
    if (!foundRevenue) {
        std::cout << "No Revenues found for user " << username << " in month " << month << "." << std::endl;
    }
    std::cout << std::endl;

}

/*
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
*/

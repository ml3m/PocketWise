#ifndef BUDGETMANAGEMENT_H
#define BUDGETMANAGEMENT_H

#include <string>

class BudgetManagement {
public:
    BudgetManagement();
    void budgetsTab(const std::string& username);
    void writeBudget(const std::string& username, int month, double budget);
    void writeGeneralBudget(const std::string& username, double budget);
    double readBudget(const std::string& username, int month);
    void printBudgets(const std::string& username);
};

#endif 

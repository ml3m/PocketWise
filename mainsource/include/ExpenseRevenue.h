#ifndef EXPENSEREVENUE_H
#define EXPENSEREVENUE_H

#include <string>

class ExpenseRevenue {
    public:
        void writeExpense(const std::string& username, double amount, int category, const std::string& description, int month);
        void writeRevenue(const std::string& username, double amount, const std::string& description, int month);
        void addExpense(const std::string& username);
        void addRevenue(const std::string& username);
        void readExpenses(const std::string& username);
        void readRevenues(const std::string& username);
        static std::string getCategoryName(int category);
        void writeGoal(const std::string& username, double amount, const std::string& goalTitle, int month, double amountLeft, double amountPaid);
};

#endif 

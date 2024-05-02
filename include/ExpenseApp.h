#ifndef EXPENSEAPP_H
#define EXPENSEAPP_H

#include <vector>
#include <string>
#include "Account.h"

class ExpenseApp {
    private:
        std::string accountDatabaseFile = "data/accounts.txt";
        std::string loggedInUser;

        void loadAccounts();
        void saveAccount(const Account& acc);

    public:
        ExpenseApp();
        void signUp(const std::string& uname, const std::string& pwd);
        bool login(const std::string& uname, const std::string& pwd);
        void showLoggedInMenu(const Account& acc);
        void modifyBudget(const Account& acc, int user_month, float user_budget);
        std::vector<Account> accounts;
};

#endif // EXPENSEAPP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct Month {
    int month;
    float budget;
    float total_expenses;
    float total_savings;
    float month_overall;
    void setBudget(float);
};

class Account {
private:
    std::string username;
    std::string password;

public:
    Account(const std::string& uname, const std::string& pwd);
    std::string getUsername() const;
    std::string getPassword() const;
    bool authenticate(const std::string& pwd) const;
    Month cls_user_months[12];
};

class ExpenseApp {
private:
    std::string accountDatabaseFile = "data/accounts.txt";
    std::string budgetDataFile = "data/appdata.txt";
    std::string loggedInUser;

    void loadAccounts();
    void saveAccount(const Account& acc);
    void modifyBudget(const Account& acc, int user_month, float user_budget);
    void print_months() const;
    void loadBudgetData();
    void saveBudgetData(const std::string& uname, int month, float budget);

public:
    ExpenseApp();
    void signUp(const std::string& uname, const std::string& pwd);
    bool login(const std::string& uname, const std::string& pwd);
    void showLoggedInMenu(const Account& acc);
    std::vector<Account> accounts;
};

void Month::setBudget(float given_budget) {
    budget = given_budget;
}

void ExpenseApp::print_months() const {
    std::cout << "1.  January  " << std::endl;
    std::cout << "2.  February " << std::endl;
    std::cout << "3.  March    " << std::endl;
    std::cout << "4.  April    " << std::endl;
    std::cout << "5.  May      " << std::endl;
    std::cout << "6.  June     " << std::endl;
    std::cout << "7.  July     " << std::endl;
    std::cout << "8.  August   " << std::endl;
    std::cout << "9.  September" << std::endl;
    std::cout << "10. October  " << std::endl;
    std::cout << "11. November " << std::endl;
    std::cout << "12. December " << std::endl;
}

Account::Account(const std::string& uname, const std::string& pwd) : username(uname), password(pwd) {}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

bool Account::authenticate(const std::string& pwd) const {
    return password == pwd;
}

ExpenseApp::ExpenseApp() {
    loadAccounts();
    loadBudgetData();
}

void ExpenseApp::loadAccounts() {
    std::ifstream infile(accountDatabaseFile);
    std::string uname, pwd;

    while (infile >> uname >> pwd) {
        accounts.push_back(Account(uname, pwd));
    }

    infile.close();
}

void ExpenseApp::saveAccount(const Account& acc) {
    std::ofstream outfile(accountDatabaseFile, std::ios_base::app);
    outfile << acc.getUsername() << " " << acc.getPassword() << std::endl;
    outfile.close();
}

void ExpenseApp::modifyBudget(const Account& acc, int user_month, float user_budget) {
    if (user_month < 1 || user_month > 12) {
        std::cout << "Invalid month." << std::endl;
        return;
    }

    // Update budget in memory
    // Assuming months are 1-based index
    acc.cls_user_months[user_month].setBudget(user_budget);

    // Save budget data to file
    saveBudgetData(acc.getUsername(), user_month, user_budget);
}

void ExpenseApp::loadBudgetData() {
    std::ifstream infile(budgetDataFile);
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string uname;
        int month;
        float budget;

        if (iss >> uname >> month >> budget) {
            // Update budget in memory
            // Assuming months are 1-based index
            for (auto& acc : accounts) {
                if (acc.getUsername() == uname) {
                    acc.cls_user_months[month - 1].setBudget(budget);
                    break;
                }
            }
        }
    }

    infile.close();
}

void ExpenseApp::saveBudgetData(const std::string& uname, int month, float budget) {
    std::ofstream outfile(budgetDataFile, std::ios_base::app);
    outfile << uname << " " << month << " " << budget << std::endl;
    outfile.close();
}

void ExpenseApp::signUp(const std::string& uname, const std::string& pwd) {
    for (const Account& acc : accounts) {
        if (acc.getUsername() == uname) {
            std::cout << "Username already exists. Please choose a different one." << std::endl;
            return;
        }
    }
    Account newAccount(uname, pwd);
    accounts.push_back(newAccount);
    saveAccount(newAccount);
    std::cout << "Account created successfully!" << std::endl;
}

bool ExpenseApp::login(const std::string& uname, const std::string& pwd) {
    for (const Account& acc : accounts) {
        if (acc.getUsername() == uname && acc.authenticate(pwd)) {
            std::cout << "Login successful! Welcome, " << uname << "!" << std::endl;
            loggedInUser = uname; 
            return true;
        }
    }
    std::cout << "Invalid username or password." << std::endl;
    return false;
}

void ExpenseApp::showLoggedInMenu(const Account& acc) {
    std::cout << "Logged in as: " << loggedInUser << std::endl;
    std::cout << "1. Modify budget" << std::endl;
    std::cout << "2. See expenses" << std::endl;
    std::cout << "3. See balance" << std::endl;
    std::cout << "4. Logout" << std::endl;
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            float user_budget;
            int user_month;
            print_months();
            std::cout << "Enter Month: ";
            std::cin >> user_month;
            std::cout << "Enter wanted budget: ";
            std::cin >> user_budget;
            modifyBudget(acc, user_month, user_budget);
            break;
        case 2:
            // See expenses function
            break;
        case 3:
            // See balance function
            break;
        case 4:
            std::cout << "Logging out..." << std::endl;
            loggedInUser.clear(); // Clear logged-in user
            break;
        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            break;
    }
}

int main() {
    ExpenseApp app;

    int choice;
    std::string username, password;

    do {
        std::cout << "Welcome to the Finance App" << std::endl;
        std::cout << "1. Sign Up" << std::endl;
        std::cout << "2. Log In" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                app.signUp(username, password);
                break;
            case 2:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (app.login(username, password)) {
                    app.showLoggedInMenu(Account(username, password));
                }
                break;
            case 3:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
                break;
        }
    } while (choice != 3);

    return 0;
}

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "sha256.h"
#include <vector>

class User {
public:
    User(const std::string& username, const std::string& password)
        : username(username), passwordHash(hashPassword(password)) {}

    static bool login(const std::string& username, const std::string& password);
    static bool createUser(const std::string& username, const std::string& password);
    static bool authenticateUser(const std::string& username, const std::string& password);

private:
    std::string username;
    std::string passwordHash;
    static std::unordered_map<std::string, std::string> users;

    static std::string hashPassword(const std::string& password) {
        sha256 algorithm;
        std::string small_salt = "mlematikus";
        return algorithm.doSha256(password + small_salt);
    }
};

std::unordered_map<std::string, std::string> User::users;

bool User::createUser(const std::string& username, const std::string& password) {
    std::ifstream infile("users.txt");
    std::string storedUsername;
    while (infile >> storedUsername) {
        if (storedUsername == username) {
            std::cout << "Username already exists. Please choose a different one." << std::endl;
            return false;
        }
    }

    std::ofstream outfile("users.txt", std::ios::app);
    if (outfile.is_open()) {
        std::string hashPassword = User::hashPassword(password);
        outfile << username << " " << hashPassword << std::endl;
        std::cout << "Account created successfully!" << std::endl;
        return true;
    } else {
        std::cout << "Error: Unable to create account." << std::endl;
        return false;
    }
}

bool User::login(const std::string& username, const std::string& password) {
    std::string hashedPassword = User::hashPassword(password);

    std::ifstream infile("users.txt");
    if (infile.is_open()) {
        std::string storedUsername, storedHashedPassword;
        while (infile >> storedUsername >> storedHashedPassword) {
            if (storedUsername == username && storedHashedPassword == hashedPassword) {
                std::cout << "Login successful!" << std::endl;
                return true;
            }
        }
        std::cout << "Login failed. Please try again." << std::endl;
        return false;
    } else {
        std::cout << "Error: Unable to open users.txt." << std::endl;
        return false;
    }
}

bool User::authenticateUser(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) {
        std::string hashedPassword = User::hashPassword(password);
        if (hashedPassword == users[username]) {
            std::cout << "User " << username << " authenticated successfully." << std::endl;
            return true;
        } else {
            std::cout << "Invalid password for user " << username << "." << std::endl;
            return false;
        }
    } else {
        std::cout << "User " << username << " not found." << std::endl;
        return false;
    }
}


class Budget {
public:
    Budget(const std::string& username) : username(username) {}

    void writeBudget(int month, double budget);
    void writeGeneralBudget(double budget);
    double readBudget(int month);
    void printBudgets();

private:
    std::string username;
    std::unordered_map<int, double> budgets;
};

void Budget::writeBudget(int month, double budget) {
    budgets[month] = budget;
    // Write to file or database
}

void Budget::writeGeneralBudget(double budget) {
    // Write general budget
}

double Budget::readBudget(int month) {
    if (budgets.find(month) != budgets.end()) {
        return budgets[month];
    } else {
        std::cout << "Budget for month " << month << " not found." << std::endl;
        return 0.0;
    }
}

void Budget::printBudgets() {
    for (const auto& [month, budget] : budgets) {
        std::cout << "Month: " << month << ", Budget: " << budget << std::endl;
    }
}

class Transaction {
public:
    Transaction(const std::string& username, double amount, const std::string& description)
        : username(username), amount(amount), description(description) {}

    virtual void writeTransaction() = 0;
    virtual void readTransaction() = 0;

protected:
    std::string username;
    double amount;
    std::string description;
};

class Expense : public Transaction {
public:
    Expense(const std::string& username, double amount, const std::string& description, int category, int month)
        : Transaction(username, amount, description), category(category), month(month) {}

    void writeTransaction() override;
    void readTransaction() override;

private:
    int category;
    int month;
};

class Revenue : public Transaction {
public:
    Revenue(const std::string& username, double amount, const std::string& description, int month)
        : Transaction(username, amount, description), month(month) {}

    void writeTransaction() override;
    void readTransaction() override;

private:
    int month;
};

void Expense::writeTransaction() {
    // Write expense to file or database
}

void Expense::readTransaction() {
    // Read expense from file or database
}

void Revenue::writeTransaction() {
    // Write revenue to file or database
}

void Revenue::readTransaction() {
    // Read revenue from file or database
}


class Goal {
public:
    Goal(const std::string& username) : username(username) {}

    void updateGoal(int goalIndex, double additionalAmount);
    void deleteGoal(int goalIndex);
    void printGoals();

private:
    std::string username;
    std::vector<double> goals;
};

void Goal::updateGoal(int goalIndex, double additionalAmount) {
    if (goalIndex >= 0 && goalIndex < goals.size()) {
        goals[goalIndex] += additionalAmount;
    } else {
        std::cout << "Invalid goal index." << std::endl;
    }
}

void Goal::deleteGoal(int goalIndex) {
    if (goalIndex >= 0 && goalIndex < goals.size()) {
        goals.erase(goals.begin() + goalIndex);
    } else {
        std::cout << "Invalid goal index." << std::endl;
    }
}

void Goal::printGoals() {
    for (size_t i = 0; i < goals.size(); ++i) {
        std::cout << "Goal " << i << ": " << goals[i] << std::endl;
    }
}

class Investment {
public:
    Investment(const std::string& username) : username(username) {}

    void investInStock(double investmentAmount, const std::string& stockName);
    void displayInvestments();

private:
    std::string username;
    std::vector<std::string> investments;
};

void Investment::investInStock(double investmentAmount, const std::string& stockName) {
    investments.push_back(stockName + ": " + std::to_string(investmentAmount));
}

void Investment::displayInvestments() {
    for (const auto& investment : investments) {
        std::cout << investment << std::endl;
    }
}

int main() {
    int choice;
    std::string username, password;

    do {
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Create Account" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice) {
            case 1:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (User::login(username, password)) {
                    // Proceed to main menu
                }
                break;
            case 2:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                User::createUser(username, password);
                break;
            case 3:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    } while(choice != 3);

    return 0;
}

#include <iostream>
#include <fstream>
#include "../include/ExpenseApp.h"
#include "../include/cli.h"

ExpenseApp::ExpenseApp() {
    loadAccounts();
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



void ExpenseApp::showLoggedInMenu() {
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
            // Modify budget function 
            print_months();
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

#include <iostream>
#include <string>
#include "../include/ExpenseApp.h"

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
                    app.showLoggedInMenu();
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

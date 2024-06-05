#include <sys/ioctl.h>
#include <limits>  // Add this include for std::numeric_limits
#include <termios.h>
#include <fstream>
#include <sstream>  // Add this include for std::istringstream
#include <unistd.h>
#include <iostream>
#include <ostream>
#include <cctype>
#include <string>
#include <cstdio>
#include <ctime>
#include "../include/ExpenseRevenue.h"
#include "../include/terminal_utils.h"
#include <iostream>

void ExpenseRevenue::writeExpense(const std::string& username, double amount, int category, const std::string& description, int month) {
    std::ofstream outfile("data/expenses.txt", std::ios::app); // Create or open the expenses file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << month << " " << category << " " << description << std::endl;
        std::cout << "Expense added successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to add expense..." << std::endl;
    }
}

void ExpenseRevenue::writeRevenue(const std::string& username, double amount, const std::string& description, int month) {
    std::ofstream outfile("data/revenues.txt", std::ios::app); // Create or open the revenues file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << month << " " << description << std::endl;
        std::cout << "Revenue added successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to add revenue." << std::endl;
    }
}

void ExpenseRevenue::addExpense(const std::string& username) {
    double amount;
    int category, month;
    std::string description;
    
    //beauty
    clear_screen();
    print_topClock();
    int printing_height = 11;
    int terminal_width = central_print_prepare_terminal(printing_height);
    
    std::cout << center_text("Enter amount: ",terminal_width);
    std::cin >> amount;
    std::cout << center_text("Chose one of the following categories: \n", terminal_width);
    std::cout<<center_text("1. Housing\n",terminal_width);
    std::cout<<center_text("2. Transportation\n",terminal_width);
    std::cout<<center_text("3. Food\n",terminal_width);
    std::cout<<center_text("4. Healthcare\n",terminal_width);
    std::cout<<center_text("5. Utilities\n",terminal_width);
    std::cout<<center_text("6. Debt Payments\n" ,terminal_width);
    std::cout<<center_text("7. Entertainment\n",terminal_width);
    std::cout<<center_text("8. Personal Care\n",terminal_width);
    std::cout<<center_text("> ",terminal_width);
    std::cin >> category;

    if (category>8 || category<0) {
        std::cout << "category doesn't exist, try again: \n";
        std::cout<<"1. Housing\n";
        std::cout<<"2. Transportation\n";
        std::cout<<"3. Food\n";
        std::cout<<"4. Healthcare\n";
        std::cout<<"5. Utilities\n";
        std::cout<<"6. Debt Payments\n";
        std::cout<<"7. Entertainment\n";
        std::cout<<"8. Personal Care\n";
        std::cin >> category;
    }
    std::cout << "Enter month (1-12): ";
    std::cin >> month;

    std::cin.ignore(); 
    std::cout << "Enter description: ";
    getline(std::cin, description);
    writeExpense(username, amount, category, description, month);
    std::cout<< "successfully added expense...\n";
    clear_screen();
}

void ExpenseRevenue::addRevenue(const std::string& username) {
    double amount;
    int month;

    //beauty
    clear_screen();
    print_topClock();
    int printing_height = 3;
    int terminal_width = central_print_prepare_terminal(printing_height);

    std::string description;
    std::cout << center_text("Enter amount: ",terminal_width);
    std::cin >> amount;
    std::cout << center_text("Enter month (1-12): ",terminal_width);
    std::cin >> month;
    std::cin.ignore(); 
    std::cout << center_text("Enter description: ",terminal_width);
    getline(std::cin, description);
    writeRevenue(username, amount, description, month);
}

void ExpenseRevenue::readExpenses(const std::string& username) {
    std::ifstream infile("data/expenses.txt");
    std::string line;
    std::cout << "Expenses for user " << username << ":" << std::endl;
    while (getline(infile, line)) {
        std::string usr, description;
        double amount;
        int category;
        std::istringstream iss(line);
        if (iss >> usr >> amount >> category >> description) {
            if (usr == username) {
                std::cout << "Amount: " << amount << ", Category: " << category << ", Description: " << description << std::endl;
            }
        }
    }
    std::cout << std::endl;
    infile.close();
}

void ExpenseRevenue::readRevenues(const std::string& username) {
    std::ifstream infile("data/revenues.txt");
    std::string line;
    std::cout << "Revenues for user " << username << ":" << std::endl;
    while (getline(infile, line)) {
        std::string usr, description;
        double amount;
        int category;
        std::istringstream iss(line);
        if (iss >> usr >> amount >> category >> description) {
            if (usr == username) {
                std::cout << "Amount: " << amount << ", Category: " << category << ", Description: " << description << std::endl;
            }
        }
    }
    std::cout << std::endl;
    infile.close();
}

std::string ExpenseRevenue::getCategoryName(int category) {
    switch(category) {
        case 1:
            return "Housing";
        case 2:
            return "Transportation";
        case 3:
            return "Food";
        case 4:
            return "Healthcare";
        case 5:
            return "Utilities";
        case 6:
            return "Debt Payments";
        case 7:
            return "Entertainment";
        case 8:
            return "Personal Care";
        default:
            return "Other";
    }
}

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
#include <ctime>

#include "../include/BudgetManagement.h"
#include "../include/terminal_utils.h"
BudgetManagement::BudgetManagement(){}

void BudgetManagement::budgetsTab(const std::string& username) {
    int choice, need_menu = 0;
    clear_screen();
    do {
        if (need_menu) {
            clear_screen();
        }
        print_topClock();
        int printing_height = 6;
        int terminal_width = central_print_prepare_terminal(printing_height);


        std::cout << center_text("Budgets Tab\n",terminal_width);
        std::cout << center_text("1. Set General Budget\n", terminal_width);
        std::cout << center_text("2. Set Month Budget\n", terminal_width);
        std::cout << center_text("3. Print Budgets\n" ,terminal_width);
        std::cout << center_text("4. Back to Main Menu\n", terminal_width);
        std::cout << center_text("Enter your choice: ", terminal_width);
        std::cin >> choice;
        std::cin.ignore();



        switch(choice) {
            case 1:
                double budget;
                std::cout << std::endl <<center_text("Enter budget: ", terminal_width);
                std::cin >> budget;
                writeGeneralBudget(username, budget);
                need_menu = 1;
                break;
            case 2: {
                int month;
                double budget;
                std::cout << std::endl <<center_text("Enter month (1-12): ", terminal_width);
                std::cin >> month;
                std::cout << center_text("Enter budget: ", terminal_width);
                std::cin >> budget;
                writeBudget(username, month, budget);
                need_menu = 1;
                break;
            }
            case 3:{
                printBudgets(username);
                need_menu = 1;
                break;
            }
            case 4:
                std::cout << "Returning to Main Menu..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    } while(choice != 4);
}


void BudgetManagement::writeGeneralBudget(const std::string& username, double budget) {
    std::ifstream infile("data/budgets.txt");
    std::ofstream tempfile("data/temp.txt");
    
    bool entryExists = false;
    std::string line;
    char choice = 'n';
    
    while (getline(infile, line)) {
        std::istringstream iss(line);
        std::string usr;
        int m;
        double b;
        int terminal_width, terminal_height;
        get_terminal_size(terminal_width, terminal_height);
        
        if (iss >> usr >> m >> b) {
            if (usr == username) {
                entryExists = true;
                if (toupper(choice) != 'Y') {
                    std::cout << center_text("Another budget entry for the same username already exists.\n",terminal_width);
                    std::cout << center_text("Do you want to overwrite it? (Y/N): ",terminal_width);
                    std::cin >> choice;
                }
                if (toupper(choice) != 'Y') {
                    std::cout << "Operation cancelled..." << std::endl;
                    return;
                }
            } else {
                tempfile << line << std::endl;
            }
        }
    }
    infile.close();
    tempfile.close();
    
    remove("data/budgets.txt");
    rename("data/temp.txt", "data/budgets.txt");
    
    std::ofstream outfile("data/budgets.txt", std::ios::app);
    if (outfile.is_open()) {
        for (int i = 1; i <= 12; ++i) {
            outfile << username << " " << i << " " << budget << std::endl;
        }
        std::cout << "Budget set successfully! press enter to go back..." << std::endl;
        outfile.close();
        std::cin.ignore();
        if (entryExists) {
            std::cin.ignore();
            return;
        }
    } else {
        std::cout << "Error: Unable to set budget! press enter to go back..." << std::endl;
        std::cin.ignore();
        if (entryExists) {
            std::cin.ignore();
            return;
        }
    }
}

void BudgetManagement::writeBudget(const std::string& username, int month, double budget) {
    std::ifstream infile("data/budgets.txt");
    std::ofstream tempfile("data/temp.txt");
    
    bool entryExists = false;
    std::string line;
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);
    
    while (getline(infile, line)) {
        std::istringstream iss(line);
        std::string usr;
        int m;
        double b;
        if (iss >> usr >> m >> b) {
            if (usr == username && m == month) {
                entryExists = true;
                char choice;
                std::cout << center_text("Another budget entry for the same username already exists.\n",terminal_width);
                std::cout << center_text("Do you want to overwrite it? (Y/N): ",terminal_width);
                std::cin >> choice;
                if (toupper(choice) != 'Y') {
                    std::cout << "Operation cancelled." << std::endl;
                    return;
                }
            } else {
                tempfile << line << std::endl;
            }
        }
    }
    infile.close();
    tempfile.close();
    
    remove("data/budgets.txt");
    rename("data/temp.txt", "data/budgets.txt");
    
    std::ofstream outfile("data/budgets.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << username << " " << month << " " << budget << std::endl;
        std::cout << "Budget set successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to set budget." << std::endl;
    }
}

double BudgetManagement::readBudget(const std::string& username, int month) {
    std::ifstream infile("data/budgets.txt");
    double budget = 0.0;
    std::string line;
    while (getline(infile, line)) {
        std::string usr;
        int m;
        double b;
        std::istringstream iss(line);
        if (iss >> usr >> m >> b) {
            if (usr == username && m == month) {
                budget = b;
                break;
            }
        }
    }
    infile.close();
    return budget;
}

void BudgetManagement::printBudgets(const std::string& username){
    //beauty
    clear_screen();
    print_topClock();
    int printing_height = 12;
    central_print_prepare_terminal(printing_height);
    std::ifstream infile("data/budgets.txt");
    double budget = 0.0;
    std::string line;
    std::cout<<"\t\tuser: mlem\t"<<"month\t"<<"budget\t"<<std::endl;
    while (getline(infile, line)) {
        std::string usr;
        int m;
        double b;
        std::istringstream iss(line);
        if (iss >> usr >> m >> b) {
            if (usr == username) {
                std::cout<<"\t\t          \t"<<m<<"\t"<<b<<"\t"<<std::endl;
            }
        }
    }
    std::cout << "Press Enter to go back..." << std::endl;
    std::cin.ignore();

    infile.close();
    return;
}

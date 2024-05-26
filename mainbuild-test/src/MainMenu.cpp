#include <matplot/axes_objects/labels.h>
#include <matplot/matplot.h>
#include <unordered_map>
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

#include "../include/Goals.h"
#include "../include/Analysis.h"
#include "../include/MainMenu.h"
#include "../include/Investments.h"
#include "../include/ExpenseRevenue.h"
#include "../include/BudgetManagement.h"
#include "../include/terminal_utils.h"

MainMenu::MainMenu(){}

void MainMenu::mainMenu(const std::string& username) {
    int choice;
    int need_menu = 0;
    do {
        BudgetManagement mybudget;
        ExpenseRevenue myEx_Rev;
        Analysis myanalysis;
        Goals mygoals;
        Investments myinvestments;
        MainMenu repeating_menu;

        if (need_menu) {
            clear_screen();
            std::cout << repeating_menu;
        }
        std::cin >> choice;
        std::cin.ignore();


        switch(choice) {

            case 1:
                mybudget.budgetsTab(username);
                need_menu = 1;
                break;
            case 2:
                myEx_Rev.addExpense(username);
                need_menu = 1;
                break;
            case 3:
                myEx_Rev.addRevenue(username);
                need_menu = 1;
                break;
            case 4:
                std::cout << "Goal Tab" << std::endl;
                mygoals.GoalTab(username);
                need_menu = 1;
                break;
            case 5:
                std::cout << "Investments Tab" << std::endl;
                myinvestments.investmentTab(username);
                need_menu = 1;
                break;
            case 6:
                std::cout << "Dashboard" << std::endl;
                myanalysis.monthAnalysis(username);
                dashboard(username);
                // annoying thingy 
                //myanalysis.updatePieChart(username);
                need_menu = 1;
                break;
            case 7:
                std::cout << "Logging out..." << std::endl;
                break;
            case 8:
                std::cout << "Exiting..." << std::endl;
                exit(0); 
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    } while(choice != 7 && choice != 8);
}

void MainMenu::printmenu() const {
    // this is the only one for mainMenu
    print_topClock();
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);

    int menu_height = 10; // Number of lines in the menu

    // Calculate the vertical positions
    int half_height = terminal_height / 2;

    for (int i = 0; i < half_height - menu_height/2; ++i) {
        std::cout << std::endl;
    }

    std::cout << center_text("Main Menu\n"        , terminal_width);
    std::cout << center_text("1. Budgets Tab\n"     , terminal_width);
    std::cout << center_text("2. Add Expense\n"     , terminal_width);
    std::cout << center_text("3. Add Revenue\n"     , terminal_width);
    std::cout << center_text("4. Goal Tab\n"        , terminal_width);
    std::cout << center_text("5. Investments Tab\n" , terminal_width);
    std::cout << center_text("6. Dashboard\n"       , terminal_width);
    std::cout << center_text("7. Log Out\n"         , terminal_width);
    std::cout << center_text("8. Quit\n"            , terminal_width);
    std::cout << center_text("Enter your choice: ", terminal_width);
}

void MainMenu::dashboard(const std::string& username) {
    std::ifstream revenuesFile("data/revenues.txt");
    std::unordered_map<int, double> revenuesPerMonth;
    std::string line;
    while (getline(revenuesFile, line)) {
        std::istringstream iss(line);
        std::string usr, description;
        double amount;
        int month;
        if (iss >> usr >> amount >> month >> description) {
            if (usr == username) {
                revenuesPerMonth[month] += amount;
            }
        }
    }
    revenuesFile.close();

    std::ifstream expensesFile("data/expenses.txt");
    std::unordered_map<int, double> expensesPerMonth; 
    while (getline(expensesFile, line)) {
        std::istringstream iss(line);
        std::string usr, description;
        double amount;
        int month;
        int category; 
        if (iss >> usr >> amount >> month >> category >> description) {
            if (usr == username) {
                expensesPerMonth[month] += amount;
            }
        }
    }
    expensesFile.close();

    std::ifstream budgetsFile("data/budgets.txt");
    std::unordered_map<int, double> budgetsPerMonth; // Month -> Budget
    while (getline(budgetsFile, line)) {
        std::istringstream iss(line);
        std::string usr;
        int month;
        double amount;
        if (iss >> usr >> month >> amount) {
            if (usr == username) {
                budgetsPerMonth[month] = amount;
            }
        }
    }
    budgetsFile.close();

    std::cout << "Dashboard for user: " << username << std::endl;
    std::cout << "Month\tTotal Revenue\tTotal Expenses\tbudget\t\tprofit\t\toverspend" << std::endl;
    for (int month = 1; month <= 12; ++month) {
        double totalRevenue = revenuesPerMonth[month];
        double totalExpenses = expensesPerMonth[month];
        double budget = budgetsPerMonth[month];
        double profit = totalRevenue - totalExpenses; 
        if (profit<0) {profit = 0;}
        double overspend = totalExpenses - budget;
        if (overspend<0) {overspend = 0;}
        std::cout << month << "\t" << totalRevenue << "\t\t" << totalExpenses << "\t\t" << budget << "\t\t" << profit << "\t\t" << overspend << std::endl;
    }
    std::cin.ignore();
    std::cout << "Press Enter to go back..." << std::endl;
    std::cin.ignore();
    return;
}

std::ostream& operator<<(std::ostream& os, const MainMenu& mymenu) {
    mymenu.printmenu();
    return os;
}

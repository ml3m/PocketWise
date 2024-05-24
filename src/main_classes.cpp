#include <cctype>
#include <ios>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <matplot/matplot.h>

#include "sha256.h"


std::unordered_map<std::string, std::string> users;


//User Authentication:
void login();
void createUser();
bool authenticateUser(const std::string& username, const std::string& password, sha256& algorithm);

//Main Menu and Navigation:
void mainMenu(const std::string& username);
void dashboard(const std::string& username);

//Budget Management:
void budgetsTab(const std::string& username);
void writeBudget(const std::string& username, int month, double budget);
void writeGeneralBudget(const std::string& username, double budget);
double readBudget(const std::string& username, int month);
void printBudgets(const std::string& username);

//Transaction Management:
void writeTransaction(const std::string& username, int type, double amount, int category, const std::string& description);
void readTransactions(const std::string& username);
std::string getCategoryName(int category);

//Expense and Revenue Management:
void writeExpense(const std::string& username, double amount, int category, const std::string& description, int month);
void writeRevenue(const std::string& username, double amount, const std::string& description, int month);
void addExpense(const std::string& username);
void addRevenue(const std::string& username);
void readExpenses(const std::string& username);
void readRevenues(const std::string& username);

//Analysis and Visualization:
void monthAnalysis(const std::string& username);
void updatePieChart(const std::string& username);

//Goal Management:
void GoalTab(const std::string& username);
void dashboard_component_Goals(const std::string& username);
void updateGoalTab(const std::string& username);
void updateGoal(const std::string& username, int goalIndex, double additionalAmount);
void deleteGoal(const std::string& username);

// Investment Tab;
void investmentTab(const std::string& username);
void displayInvestments(const std::vector<std::string>& investmentData);
void investInStock(const std::string& username, double investmentAmount, const std::string& stockName, std::vector<std::string>& investmentData);
void writeInvestmentData(const std::string& filename, const std::vector<std::string>& data);
void readInvestmentData(const std::string& filename, std::vector<std::string>& data);


int main() {
    int choice;
    do {
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Create Account" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice) {
            case 1:
                login();
                break;
            case 2:
                createUser();
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

void createUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::ifstream infile("users.txt");
    std::string storedUsername;
    while (infile >> storedUsername) {
        if (storedUsername == username) {
            std::cout << "Username already exists. Please choose a different one." << std::endl;
            infile.close();
            return;
        }
    }
    infile.close();

    std::cout << "Enter password: ";
    std::cin >> password;

    std::string small_salt = "mlematikus";
    password += small_salt; // salt aplication
    std::ofstream outfile("users.txt", std::ios::app);
    if (outfile.is_open()) {
        sha256 algorithm;
        std::string hashPassword = algorithm.doSha256(password);

        outfile << username << " " << hashPassword << std::endl;
        outfile.close();
        std::cout << "Account created successfully!" << std::endl;
    } else {
        std::cout << "Error: Unable to create account." << std::endl;
    }
}

void login() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string small_salt = "mlematikus";
    sha256 algorithm;
    password += small_salt; //salt aplication
    std::string hashedPassword = algorithm.doSha256(password);

    std::ifstream infile("users.txt");
    if (infile.is_open()) {
        std::string storedUsername, storedHashedPassword;
        bool userFound = false;
        while (infile >> storedUsername >> storedHashedPassword) {
            if (storedUsername == username) {
                userFound = true;
                if (hashedPassword == storedHashedPassword) {
                    std::cout << "Login successful!" << std::endl;
                    mainMenu(username);
                    return;
                } else {
                    std::cout << "Login failed. Please try again." << std::endl;
                    return; 
                }
            }
        }
        if (!userFound) {
            std::cout << "User not found. Please try again." << std::endl;
        }
        infile.close();
    } else {
        std::cout << "Error: Unable to open users.txt." << std::endl;
    }
}

bool authenticateUser(const std::string& username, const std::string& password, sha256& algorithm) {
    if (users.find(username) != users.end()) {
        std::string hashedPassword = algorithm.doSha256(password);
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

std::string getCategoryName(int category) {
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

void mainMenu(const std::string& username) {
    int choice;
    do {
        std::cout << "\nMain Menu" << std::endl;
        std::cout << "1. Budgets Tab" << std::endl;
        std::cout << "2. Add Expense" << std::endl;
        std::cout << "3. Add Revenue" << std::endl;
        std::cout << "4. Goal Tab" << std::endl;
        std::cout << "5. Investments Tab" << std::endl;
        std::cout << "6. Dashboard" << std::endl;
        std::cout << "7. Log Out" << std::endl;
        std::cout << "8. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice) {
            case 1:
                budgetsTab(username);
                break;
            case 2:
                addExpense(username);
                break;
            case 3:
                addRevenue(username);
                break;
            case 4:
                std::cout << "Goal Tab" << std::endl;
                GoalTab(username);
                break;
            case 5:
                std::cout << "Investments Tab" << std::endl;
                investmentTab(username);
                break;
            case 6:
                std::cout << "Dashboard" << std::endl;
                monthAnalysis(username);
                dashboard(username);
                updatePieChart(username);
                break;
            case 7:
                std::cout << "Logging out..." << std::endl;
                break;
            case 8:
                std::cout << "Exiting..." << std::endl;
                exit(0); // Exit the program immediately
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    } while(choice != 7 && choice != 8);
}

void budgetsTab(const std::string& username) {
    int choice;
    do {
        std::cout << "\nBudgets Tab" << std::endl;
        std::cout << "1. Set General Budget" << std::endl;
        std::cout << "2. Set Month Budget" << std::endl;
        std::cout << "3. Print Budgets" << std::endl;
        std::cout << "4. Back to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice) {
            case 1:
                double budget;
                std::cout << "Enter budget: ";
                std::cin >> budget;
                writeGeneralBudget(username, budget);
                break;
            case 2: {
                int month;
                double budget;
                std::cout << "Enter month (1-12): ";
                std::cin >> month;
                std::cout << "Enter budget: ";
                std::cin >> budget;
                writeBudget(username, month, budget);
                break;
            }
            case 3:{
                printBudgets(username);
            }
            case 4:
                std::cout << "Returning to Main Menu..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    } while(choice != 4);
}


void writeGeneralBudget(const std::string& username, double budget) {
    std::ifstream infile("budgets.txt");
    std::ofstream tempfile("temp.txt");
    
    bool entryExists = false;
    std::string line;
    char choice = 'n';
    
    while (getline(infile, line)) {
        std::istringstream iss(line);
        std::string usr;
        int m;
        double b;
        
        if (iss >> usr >> m >> b) {
            if (usr == username) {
                entryExists = true;
                if (toupper(choice) != 'Y') {
                    std::cout << "Another budget entry for the same username already exists. Do you want to overwrite it? (Y/N): ";
                    std::cin >> choice;
                }
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
    
    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");
    
    std::ofstream outfile("budgets.txt", std::ios::app);
    if (outfile.is_open()) {
        for (int i = 1; i <= 12; ++i) {
            outfile << username << " " << i << " " << budget << std::endl;
        }
        std::cout << "Budget set successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to set budget." << std::endl;
    }
}

void writeBudget(const std::string& username, int month, double budget) {
    std::ifstream infile("budgets.txt");
    std::ofstream tempfile("temp.txt");
    
    bool entryExists = false;
    std::string line;
    
    while (getline(infile, line)) {
        std::istringstream iss(line);
        std::string usr;
        int m;
        double b;
        
        if (iss >> usr >> m >> b) {
            if (usr == username && m == month) {
                entryExists = true;
                char choice;
                std::cout << "Another budget entry for the same username and month already exists. Do you want to overwrite it? (Y/N): ";
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
    
    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");
    
    std::ofstream outfile("budgets.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << username << " " << month << " " << budget << std::endl;
        std::cout << "Budget set successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to set budget." << std::endl;
    }
}

double readBudget(const std::string& username, int month) {
    std::ifstream infile("budgets.txt");
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

void printBudgets(const std::string& username){
    std::ifstream infile("budgets.txt");
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
    infile.close();
}

void writeExpense(const std::string& username, double amount, int category, const std::string& description, int month) {
    std::ofstream outfile("expenses.txt", std::ios::app); // Create or open the expenses file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << month << " " << category << " " << description << std::endl;
        std::cout << "Expense added successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to add expense." << std::endl;
    }
}

void writeRevenue(const std::string& username, double amount, const std::string& description, int month) {
    std::ofstream outfile("revenues.txt", std::ios::app); // Create or open the revenues file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << month << " " << description << std::endl;
        std::cout << "Revenue added successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to add revenue." << std::endl;
    }
}

void addExpense(const std::string& username) {
    double amount;
    int category, month;
    std::string description;
    std::cout << "Enter amount: ";
    std::cin >> amount;
    std::cout << "Chose one of the following categories: \n";
    std::cout<<"1. Housing\n";
    std::cout<<"2. Transportation\n";
    std::cout<<"3. Food\n";
    std::cout<<"4. Healthcare\n";
    std::cout<<"5. Utilities\n";
    std::cout<<"6. Debt Payments\n";
    std::cout<<"7. Entertainment\n";
    std::cout<<"8. Personal Care\n";
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
}

void addRevenue(const std::string& username) {
    double amount;
    int month;
    std::string description;
    std::cout << "Enter amount: ";
    std::cin >> amount;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;
    std::cin.ignore(); 
    std::cout << "Enter description: ";
    getline(std::cin, description);
    writeRevenue(username, amount, description, month);
}

void readExpenses(const std::string& username) {
    std::ifstream infile("expenses.txt");
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
    infile.close();
}

void readRevenues(const std::string& username) {
    std::ifstream infile("revenues.txt");
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
    infile.close();
}

void dashboard(const std::string& username) {
    std::ifstream revenuesFile("revenues.txt");
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

    std::ifstream expensesFile("expenses.txt");
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

    std::ifstream budgetsFile("budgets.txt");
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
}

void monthAnalysis(const std::string& username) {
    int month;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;
    
    if (month < 1 || month > 12) {
        std::cout << "Invalid month. Please enter a number between 1 and 12." << std::endl;
        return;
    }

    std::ifstream expensesFile("expenses.txt");
    std::string line;
    bool foundExpenses = false;
    std::cout << "Expenses for user " << username << " in month " << month << ":" << std::endl;
    while (getline(expensesFile, line)) {
        std::istringstream iss(line);
        std::string usr, description;
        double amount;
        int expMonth, category;
        if (iss >> usr >> amount >> expMonth >> category >> description) {
            if (usr == username && expMonth == month) {
                std::cout << "Amount: " << amount << ", Category: " << category << ", Description: " << description << std::endl;
                foundExpenses = true;
            }
        }
    }
    expensesFile.close();

    if (!foundExpenses) {
        std::cout << "No expenses found for user " << username << " in month " << month << "." << std::endl;
    }
}

void writeGoal(const std::string& username, double amount, const std::string& goalTitle, int month, double amountLeft, double amountPaid) {
    std::ofstream outfile("goals.txt", std::ios::app); // Create or open the expenses file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << amountLeft << " " << amountPaid << " " << month << " " << goalTitle <<std::endl;
        std::cout << "Goal '" <<goalTitle << "' added successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to add goal." << std::endl;
    }
}

void dashboard_component_Goals(const std::string& username) {
    std::ifstream infile("goals.txt");
    if (!infile.is_open()) {
        std::cout << "Error: Unable to open goals file." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> userGoals;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string goalUsername;
        iss >> goalUsername;

        if (goalUsername == username) {
            userGoals.push_back(line);
        }
    }

    infile.close();

    if (userGoals.empty()) {
        std::cout << "No goals found for " << username << std::endl;
        return;
    }

    std::cout << "Goals for " << username << ":" << std::endl;
    std::cout << std::setw(5) << "Index"
              << std::setw(20) << std::left << "Goal Title"
              << std::setw(15) << "Amount"
              << std::setw(15) << "Amount Left"
              << std::setw(15) << "Amount Paid"
              << std::setw(10) << "Month"
              << std::setw(15) << "Completion %" // Added column for completion percentage
              << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    for (size_t i = 0; i < userGoals.size(); ++i) {
        std::istringstream iss(userGoals[i]);
        std::string goalUsername, goalTitle;
        double amount, amountLeft, amountPaid;
        int month;

        iss >> goalUsername >> amount >> amountLeft >> amountPaid >> month >> goalTitle;

        // Calculate completion percentage
        double completionPercentage = ((amount - amountLeft) / amount) * 100;

        std::cout << std::setw(5) << i + 1 // Index starts from 1
                  << std::setw(20) << std::left << goalTitle
                  << std::setw(15) << amount
                  << std::setw(15) << amountLeft
                  << std::setw(15) << amountPaid
                  << std::setw(10) << month
                  << std::setw(15) << std::fixed << std::setprecision(2) << completionPercentage // Display completion percentage with 2 decimal places
                  << std::endl;
    }
}

void GoalTab(const std::string& username) {
    bool exitGoalTab = false;

    while (!exitGoalTab) {
        int month, user_goal_choice;
        std::string title;
        double amount, leftA = 0, paidA = 0;

        std::cout << "1. Create Goal\n";
        std::cout << "2. See Goal/s\n";
        std::cout << "3. Update Goal\n";
        std::cout << "4. Delete Goal\n";
        std::cout << "5. Exit Goal Tab\n";

        std::cin >> user_goal_choice;

        switch (user_goal_choice) {
            case 1:
                std::cin.ignore();
                std::cout << "Enter Goal Title:";
                getline(std::cin, title);
                std::cout << "\nEnter required goal amount:";
                std::cin >> amount;
                std::cout << "\nEnter deadline month:";
                std::cin >> month;
                leftA = amount;
                writeGoal(username, amount, title, month, leftA, paidA);
                break;
            case 2:
                dashboard_component_Goals(username);
                break;
            case 3:
                updateGoalTab(username);
                break;
            case 4:
                deleteGoal(username);
                break;
            case 5:
                std::cout << "Exiting Goal Tab..." << std::endl;
                exitGoalTab = true;   // Set exit flag 
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    }
}


void updateGoal(const std::string& username, int goalIndex, double additionalAmount) {
    std::ifstream infile("goals.txt");
    if (!infile.is_open()) {
        std::cout << "Error: Unable to open goals file." << std::endl;
        return;
    }

    std::vector<std::string> goals;
    std::string line;
    while (std::getline(infile, line)) {
        goals.push_back(line);
    }
    infile.close();

    if (goalIndex < 1 || goalIndex > goals.size()) {
        std::cout << "Invalid goal number. Please try again." << std::endl;
        return;
    }

    std::istringstream iss(goals[goalIndex - 1]);
    std::string goalUsername, goalTitle;
    double amount, amountLeft, amountPaid;
    int month;
    iss >> goalUsername >> amount >> amountLeft >> amountPaid >> month >> std::ws;
    std::getline(iss, goalTitle);

    amountLeft -= additionalAmount;
    amountPaid += additionalAmount;

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2); // Set precision for doubles
    oss << username << " " << amount << " " << amountLeft << " " << amountPaid << " " << month << " " << goalTitle;

    goals[goalIndex - 1] = oss.str();

    std::ofstream outfile("goals.txt");
    if (outfile.is_open()) {
        for (const auto& goal : goals) {
            outfile << goal << std::endl;
        }
        outfile.close();
        
        if (amountPaid == amount) {
            std::cout << "Goal accomplished! Congratulations, " << username << "!" << std::endl;
        } else {
            std::cout << "Goal updated successfully!" << std::endl;
        }
    } else {
        std::cout << "Error: Unable to update goal." << std::endl;
    }
}

void updateGoalTab(const std::string& username) {
    dashboard_component_Goals(username);
    std::cout << "goals are numbered starting from 1.\n";

    int goalIndex;
    std::cout << "\tEnter the number of the goal you want to update: ";
    std::cin >> goalIndex;

    double additionalAmount;
    std::cout << "\tEnter the additional amount to add to the goal: ";
    std::cin >> additionalAmount;

    updateGoal(username, goalIndex, additionalAmount);
}


void deleteGoal(const std::string& username) {
    dashboard_component_Goals(username);
    std::cout << "Goals are numbered starting from 1." << std::endl;

    int goalIndex;
    std::cout << "Enter the number of the goal you want to delete: ";
    std::cin >> goalIndex;

    std::ifstream infile("goals.txt");
    if (!infile.is_open()) {
        std::cout << "Error: Unable to open goals file." << std::endl;
        return;
    }

    std::vector<std::string> goals;
    std::string line;
    while (std::getline(infile, line)) {
        goals.push_back(line);
    }
    infile.close();

    if (goalIndex < 1 || goalIndex > goals.size()) {
        std::cout << "Invalid goal number. Please try again." << std::endl;
        return;
    }

    goals.erase(goals.begin() + goalIndex - 1);

    std::ofstream outfile("goals.txt");
    if (outfile.is_open()) {
        for (const auto& goal : goals) {
            outfile << goal << std::endl;
        }
        outfile.close();
        
        std::cout << "Goal deleted successfully!" << std::endl;
    } else {
        std::cout << "Error: Unable to delete goal." << std::endl;
    }
}



void readInvestmentData(const std::string& filename, std::vector<std::string>& data) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        data.push_back(line);
    }

    infile.close();
}

void writeInvestmentData(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    for (const auto& line : data) {
        outfile << line << std::endl;
    }

    outfile.close();
}

// Investment Functions

void investInStock(const std::string& username, double investmentAmount, const std::string& stockName, std::vector<std::string>& investmentData) {
    // Code for investing in a stock
    // You can add more functionality here, such as updating user's investment portfolio, etc.
    std::string investmentRecord = username + " " + std::to_string(investmentAmount) + " " + stockName;
    investmentData.push_back(investmentRecord);
    std::cout << "Invested $" << investmentAmount << " in " << stockName << std::endl;
}

void displayInvestments(const std::vector<std::string>& investmentData) {
    std::cout << "Investment History:" << std::endl;
    std::cout << std::setw(15) << "Username"
              << std::setw(15) << "Amount"
              << std::setw(15) << "Stock" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    for (const auto& record : investmentData) {
        std::istringstream iss(record);
        std::string username, stock;
        double amount;
        iss >> username >> amount >> stock;
        std::cout << std::setw(15) << username
                  << std::setw(15) << amount
                  << std::setw(15) << stock << std::endl;
    }
}

// Investment Tab Function

void investmentTab(const std::string& username) {
    std::vector<std::string> investmentData;
    readInvestmentData("investment_data.txt", investmentData);

    bool exitInvestmentTab = false;
    while (!exitInvestmentTab) {
        int user_choice;
        std::cout << "\nInvestment Tab" << std::endl;
        std::cout << "1. Invest in a Stock" << std::endl;
        std::cout << "2. View Investment History" << std::endl;
        std::cout << "3. Exit Investment Tab" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> user_choice;

        switch(user_choice) {
            case 1: {
                double investmentAmount;
                std::string stockName;
                std::cout << "Enter the amount you want to invest: ";
                std::cin >> investmentAmount;
                std::cin.ignore();
                std::cout << "Enter the name of the stock: ";
                std::getline(std::cin, stockName);
                investInStock(username, investmentAmount, stockName, investmentData);
                break;
            }
            case 2:
                displayInvestments(investmentData);
                break;
            case 3:
                std::cout << "Exiting Investment Tab..." << std::endl;
                exitInvestmentTab = true;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    }

    writeInvestmentData("investment_data.txt", investmentData);
}


void updatePieChart(const std::string& username) {
    std::vector<double> amounts;
    std::vector<std::string> categories;

    std::ifstream expensesFile("expenses.txt");
    if (!expensesFile.is_open()) {
        std::cout << "Error: Unable to open expenses file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(expensesFile, line)) {
        std::istringstream iss(line);
        std::string usr, description;
        double amount;
        int category, month;
        if (iss >> usr >> amount >> month >> category >> description && usr == username) {
            std::string categoryName = getCategoryName(category);
            amounts.push_back(amount);
            categories.push_back(categoryName);
        }
    }
    expensesFile.close();

    const int maxLegendEntries = 10; 
    if (categories.size() > maxLegendEntries) {
        std::cout << "Warning: Too many categories to display in the legend. Only the first "
                  << maxLegendEntries << " categories will be shown." << std::endl;
        categories.resize(maxLegendEntries);
        amounts.resize(maxLegendEntries);
    }

    matplot::pie(amounts);
    matplot::legend(categories);
    matplot::show();
}

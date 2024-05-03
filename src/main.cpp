#include <cctype>
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

using namespace std;
unordered_map<string, string> users;

void login();
void createUser();
void mainMenu(const string& username);
void budgetsTab(const string& username);
void writeBudget(const string& username, int month, double budget);
void writeGeneralBudget(const string& username, double budget);
double readBudget(const string& username, int month);
void writeTransaction(const string& username, int type, double amount, int category, const string& description);
void readTransactions(const string& username);
string getCategoryName(int category);
bool authenticateUser(const string& username, const string& password, sha256& algorithm);
void printBudgets(const string& username);

void writeExpense(const string& username, double amount, int category, const string& description, int month);
void writeRevenue(const string& username, double amount, const string& description, int month);
void addExpense(const string& username);
void addRevenue(const string& username);
void readExpenses(const string& username);
void readRevenues(const string& username);
void dashboard(const string& username);
void monthAnalysis(const string& username);

void updatePieChart(const string& username);

int main() {
    int choice;
    do {
        cout << "1. Login" << endl;
        cout << "2. Create Account" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                login();
                break;
            case 2:
                createUser();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter again." << endl;
        }
    } while(choice != 3);

    return 0;
}

void createUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    ifstream infile("users.txt");
    string storedUsername;
    while (infile >> storedUsername) {
        if (storedUsername == username) {
            cout << "Username already exists. Please choose a different one." << endl;
            infile.close();
            return;
        }
    }
    infile.close();

    cout << "Enter password: ";
    cin >> password;

    string small_salt = "mlematikus";
    password += small_salt; // salt aplication
    ofstream outfile("users.txt", ios::app);
    if (outfile.is_open()) {
        sha256 algorithm;
        std::string hashPassword = algorithm.doSha256(password);

        outfile << username << " " << hashPassword << endl;
        outfile.close();
        cout << "Account created successfully!" << endl;
    } else {
        cout << "Error: Unable to create account." << endl;
    }
}

void login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string small_salt = "mlematikus";
    sha256 algorithm;
    password += small_salt; //salt aplication
    string hashedPassword = algorithm.doSha256(password);

    ifstream infile("users.txt");
    if (infile.is_open()) {
        string storedUsername, storedHashedPassword;
        bool userFound = false;
        while (infile >> storedUsername >> storedHashedPassword) {
            if (storedUsername == username) {
                userFound = true;
                if (hashedPassword == storedHashedPassword) {
                    cout << "Login successful!" << endl;
                    mainMenu(username);
                    return;
                } else {
                    cout << "Login failed. Please try again." << endl;
                    return; 
                }
            }
        }
        if (!userFound) {
            cout << "User not found. Please try again." << endl;
        }
        infile.close();
    } else {
        cout << "Error: Unable to open users.txt." << endl;
    }
}

bool authenticateUser(const string& username, const string& password, sha256& algorithm) {
    if (users.find(username) != users.end()) {
        string hashedPassword = algorithm.doSha256(password);
        if (hashedPassword == users[username]) {
            cout << "User " << username << " authenticated successfully." << endl;
            return true; 
        } else {
            cout << "Invalid password for user " << username << "." << endl;
            return false; 
        }
    } else {
        cout << "User " << username << " not found." << endl;
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

void mainMenu(const string& username) {
    int choice;
    do {
        cout << "\nMain Menu" << endl;
        cout << "1. Budgets Tab" << endl;
        cout << "2. Add Expense" << endl;
        cout << "3. Add Revenue" << endl;
        cout << "4. Goal Tab" << endl;
        cout << "5. Investments Tab" << endl;
        cout << "6. Dashboard" << endl;
        cout << "7. Log Out" << endl;
        cout << "8. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

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
                cout << "Goal Tab" << endl;
                break;
            case 5:
                cout << "Investments Tab" << endl;
                break;
            case 6:
                cout << "Dashboard" << endl;
                monthAnalysis(username);
                dashboard(username);
                updatePieChart(username);
                break;
            case 7:
                cout << "Logging out..." << endl;
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter again." << endl;
        }
    } while(choice != 7 && choice != 8);
}

void budgetsTab(const string& username) {
    int choice;
    do {
        cout << "\nBudgets Tab" << endl;
        cout << "1. Set General Budget" << endl;
        cout << "2. Set Month Budget" << endl;
        cout << "3. Print Budgets" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                double budget;
                cout << "Enter budget: ";
                cin >> budget;
                writeGeneralBudget(username, budget);
                break;
            case 2: {
                int month;
                double budget;
                cout << "Enter month (1-12): ";
                cin >> month;
                cout << "Enter budget: ";
                cin >> budget;
                writeBudget(username, month, budget);
                break;
            }
            case 3:{
                printBudgets(username);
            }
            case 4:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter again." << endl;
        }
    } while(choice != 4);
}


void writeGeneralBudget(const string& username, double budget) {
    ifstream infile("budgets.txt");
    ofstream tempfile("temp.txt");
    
    bool entryExists = false;
    string line;
    char choice = 'n';
    
    while (getline(infile, line)) {
        istringstream iss(line);
        string usr;
        int m;
        double b;
        
        if (iss >> usr >> m >> b) {
            if (usr == username) {
                entryExists = true;
                if (toupper(choice) != 'Y') {
                    cout << "Another budget entry for the same username already exists. Do you want to overwrite it? (Y/N): ";
                    cin >> choice;
                }
                if (toupper(choice) != 'Y') {
                    cout << "Operation cancelled." << endl;
                    return;
                }
            } else {
                tempfile << line << endl;
            }
        }
    }
    infile.close();
    tempfile.close();
    
    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");
    
    ofstream outfile("budgets.txt", ios::app);
    if (outfile.is_open()) {
        for (int i = 1; i <= 12; ++i) {
            outfile << username << " " << i << " " << budget << endl;
        }
        cout << "Budget set successfully!" << endl;
        outfile.close();
    } else {
        cout << "Error: Unable to set budget." << endl;
    }
}

void writeBudget(const string& username, int month, double budget) {
    ifstream infile("budgets.txt");
    ofstream tempfile("temp.txt");
    
    bool entryExists = false;
    string line;
    
    while (getline(infile, line)) {
        istringstream iss(line);
        string usr;
        int m;
        double b;
        
        if (iss >> usr >> m >> b) {
            if (usr == username && m == month) {
                entryExists = true;
                char choice;
                cout << "Another budget entry for the same username and month already exists. Do you want to overwrite it? (Y/N): ";
                cin >> choice;
                if (toupper(choice) != 'Y') {
                    cout << "Operation cancelled." << endl;
                    return;
                }
            } else {
                tempfile << line << endl;
            }
        }
    }
    infile.close();
    tempfile.close();
    
    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");
    
    ofstream outfile("budgets.txt", ios::app);
    if (outfile.is_open()) {
        outfile << username << " " << month << " " << budget << endl;
        cout << "Budget set successfully!" << endl;
        outfile.close();
    } else {
        cout << "Error: Unable to set budget." << endl;
    }
}

double readBudget(const string& username, int month) {
    ifstream infile("budgets.txt");
    double budget = 0.0;
    string line;
    while (getline(infile, line)) {
        string usr;
        int m;
        double b;
        istringstream iss(line);
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

void printBudgets(const string& username){
    ifstream infile("budgets.txt");
    double budget = 0.0;
    string line;
    cout<<"\t\tuser: mlem\t"<<"month\t"<<"budget\t"<<endl;
    while (getline(infile, line)) {
        string usr;
        int m;
        double b;
        istringstream iss(line);
        if (iss >> usr >> m >> b) {
            if (usr == username) {
                cout<<"\t\t          \t"<<m<<"\t"<<b<<"\t"<<endl;
            }
        }
    }
    infile.close();
}

void writeExpense(const string& username, double amount, int category, const string& description, int month) {
    ofstream outfile("expenses.txt", ios::app); // Create or open the expenses file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << month << " " << category << " " << description << endl;
        cout << "Expense added successfully!" << endl;
        outfile.close();
    } else {
        cout << "Error: Unable to add expense." << endl;
    }
}

void writeRevenue(const string& username, double amount, const string& description, int month) {
    ofstream outfile("revenues.txt", ios::app); 
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << month << " " << description << endl;
        cout << "Revenue added successfully!" << endl;
        outfile.close();
    } else {
        cout << "Error: Unable to add revenue." << endl;
    }
}

void addExpense(const string& username) {
    double amount;
    int category, month;
    string description;
    cout << "Enter amount: ";
    cin >> amount;
    cout << "Chose one of the following categories: \n";
    cout<<"1. Housing\n";
    cout<<"2. Transportation\n";
    cout<<"3. Food\n";
    cout<<"4. Healthcare\n";
    cout<<"5. Utilities\n";
    cout<<"6. Debt Payments\n";
    cout<<"7. Entertainment\n";
    cout<<"8. Personal Care\n";
    cin >> category;

    if (category>8 || category<0) {
        cout << "category doesn't exist, try again: \n";
        cout<<"1. Housing\n";
        cout<<"2. Transportation\n";
        cout<<"3. Food\n";
        cout<<"4. Healthcare\n";
        cout<<"5. Utilities\n";
        cout<<"6. Debt Payments\n";
        cout<<"7. Entertainment\n";
        cout<<"8. Personal Care\n";
        cin >> category;
    }
    cout << "Enter month (1-12): ";
    cin >> month;

    cin.ignore(); 
    cout << "Enter description: ";
    getline(cin, description);
    writeExpense(username, amount, category, description, month);
}

void addRevenue(const string& username) {
    double amount;
    int month;
    string description;
    cout << "Enter amount: ";
    cin >> amount;
    cout << "Enter month (1-12): ";
    cin >> month;
    cin.ignore(); 
    cout << "Enter description: ";
    getline(cin, description);
    writeRevenue(username, amount, description, month);
}

void readExpenses(const string& username) {
    ifstream infile("expenses.txt");
    string line;
    cout << "Expenses for user " << username << ":" << endl;
    while (getline(infile, line)) {
        string usr, description;
        double amount;
        int category;
        istringstream iss(line);
        if (iss >> usr >> amount >> category >> description) {
            if (usr == username) {
                cout << "Amount: " << amount << ", Category: " << category << ", Description: " << description << endl;
            }
        }
    }
    infile.close();
}

void readRevenues(const string& username) {
    ifstream infile("revenues.txt");
    string line;
    cout << "Revenues for user " << username << ":" << endl;
    while (getline(infile, line)) {
        string usr, description;
        double amount;
        int category;
        istringstream iss(line);
        if (iss >> usr >> amount >> category >> description) {
            if (usr == username) {
                cout << "Amount: " << amount << ", Category: " << category << ", Description: " << description << endl;
            }
        }
    }
    infile.close();
}

void dashboard(const string& username) {
    ifstream revenuesFile("revenues.txt");
    unordered_map<int, double> revenuesPerMonth;
    string line;
    while (getline(revenuesFile, line)) {
        istringstream iss(line);
        string usr, description;
        double amount;
        int month;
        if (iss >> usr >> amount >> month >> description) {
            if (usr == username) {
                revenuesPerMonth[month] += amount;
            }
        }
    }
    revenuesFile.close();

    ifstream expensesFile("expenses.txt");
    unordered_map<int, double> expensesPerMonth; 
    while (getline(expensesFile, line)) {
        istringstream iss(line);
        string usr, description;
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

    ifstream budgetsFile("budgets.txt");
    unordered_map<int, double> budgetsPerMonth; // Month -> Budget
    while (getline(budgetsFile, line)) {
        istringstream iss(line);
        string usr;
        int month;
        double amount;
        if (iss >> usr >> month >> amount) {
            if (usr == username) {
                budgetsPerMonth[month] = amount;
            }
        }
    }
    budgetsFile.close();

    cout << "Dashboard for user: " << username << endl;
    cout << "Month\tTotal Revenue\tTotal Expenses\tbudget\t\tprofit\t\toverspend" << endl;
    for (int month = 1; month <= 12; ++month) {
        double totalRevenue = revenuesPerMonth[month];
        double totalExpenses = expensesPerMonth[month];
        double budget = budgetsPerMonth[month];
        double profit = totalRevenue - totalExpenses; 
        if (profit<0) {profit = 0;}
        double overspend = totalExpenses - budget;
        if (overspend<0) {overspend = 0;}
        cout << month << "\t" << totalRevenue << "\t\t" << totalExpenses << "\t\t" << budget << "\t\t" << profit << "\t\t" << overspend << endl;
    }
}

void monthAnalysis(const string& username) {
    int month;
    cout << "Enter month (1-12): ";
    cin >> month;
    
    if (month < 1 || month > 12) {
        cout << "Invalid month. Please enter a number between 1 and 12." << endl;
        return;
    }

    ifstream expensesFile("expenses.txt");
    string line;
    bool foundExpenses = false;
    cout << "Expenses for user " << username << " in month " << month << ":" << endl;
    while (getline(expensesFile, line)) {
        istringstream iss(line);
        string usr, description;
        double amount;
        int expMonth, category;
        if (iss >> usr >> amount >> expMonth >> category >> description) {
            if (usr == username && expMonth == month) {
                cout << "Amount: " << amount << ", Category: " << category << ", Description: " << description << endl;
                foundExpenses = true;
            }
        }
    }
    expensesFile.close();

    if (!foundExpenses) {
        cout << "No expenses found for user " << username << " in month " << month << "." << endl;
    }
}

void updatePieChart(const string& username) {
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

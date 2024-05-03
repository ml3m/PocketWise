#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>
#include "sha256.h"
#include <unordered_map>

using namespace std;

unordered_map<string, string> users;

// Function prototypes
void login();
void createUser();
void mainMenu(const string& username);
void budgetsTab(const string& username);
void addExpense(const string& username);
void addRevenue(const string& username);
void writeBudget(const string& username, int month, double budget);
void writeGeneralBudget(const string& username, double budget);
double readBudget(const string& username, int month);
void writeTransaction(const string& username, int type, double amount, int category, const string& description);
void readTransactions(const string& username);
string getCategoryName(int category);
void createUser();
bool authenticateUser(const string& username, const string& password, sha256& algorithm);

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

    // Check if the username already exists
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
    // Save username and password to the users.txt file
    ofstream outfile("users.txt", ios::app);
    if (outfile.is_open()) {
        // Hash the password
        sha256 algorithm;
        std::string hashPassword = algorithm.doSha256(password);

        // Write username and hashed password to the file
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

    // Hash the input password
    string small_salt = "mlematikus";
    sha256 algorithm;
    password += small_salt; //salt aplication
    string hashedPassword = algorithm.doSha256(password);

    // Authenticate user by checking the users.txt file
    ifstream infile("users.txt");
    if (infile.is_open()) {
        string storedUsername, storedHashedPassword;
        bool userFound = false;
        // Read each line from the file
        while (infile >> storedUsername >> storedHashedPassword) {
            // Check if the provided username matches any in the file
            if (storedUsername == username) {
                userFound = true;
                // Compare the hashed input password with the stored hashed password
                if (hashedPassword == storedHashedPassword) {
                    cout << "Login successful!" << endl;
                    mainMenu(username);
                    return; // Exit the function after successful login
                } else {
                    cout << "Login failed. Please try again." << endl;
                    return; // Exit the function after failed login
                }
            }
        }
        // If the provided username was not found in the file
        if (!userFound) {
            cout << "User not found. Please try again." << endl;
        }
        infile.close();
    } else {
        cout << "Error: Unable to open users.txt." << endl;
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
        cout << "3. Back to Main Menu" << endl;
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
            case 3:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter again." << endl;
        }
    } while(choice != 3);
}

void addExpense(const string& username) {
    // Implement add expense functionality
}

void addRevenue(const string& username) {
    // Implement add revenue functionality
}

void writeGeneralBudget(const string& username, double budget) {
    ifstream infile("budgets.txt");
    ofstream tempfile("temp.txt");
    
    bool entryExists = false;
    string line;
    
    // Read the input file line by line
    while (getline(infile, line)) {
        istringstream iss(line);
        string usr;
        int m;
        double b;
        
        // Parse the line into username, month, and budget
        if (iss >> usr >> m >> b) {
            // Check if the entry matches the given username
            if (usr == username) {
                entryExists = true;
                // Prompt user to confirm overwrite
                char choice;
                cout << "Another budget entry for the same username already exists. Do you want to overwrite it? (Y/N): ";
                cin >> choice;
                if (toupper(choice) != 'Y') {
                    cout << "Operation cancelled." << endl;
                    return;
                }
            } else {
                // Write the line to the temporary file if it doesn't match the username
                tempfile << line << endl;
            }
        }
    }
    infile.close();
    tempfile.close();
    
    // Remove the original file and rename the temporary file to the original filename
    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");
    
    // Write the new entries to the file
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
    
    // Read the input file line by line
    while (getline(infile, line)) {
        istringstream iss(line);
        string usr;
        int m;
        double b;
        
        // Parse the line into username, month, and budget
        if (iss >> usr >> m >> b) {
            // Check if the entry matches the given username and month
            if (usr == username && m == month) {
                entryExists = true;
                // Prompt user to confirm overwrite
                char choice;
                cout << "Another budget entry for the same username and month already exists. Do you want to overwrite it? (Y/N): ";
                cin >> choice;
                if (toupper(choice) != 'Y') {
                    cout << "Operation cancelled." << endl;
                    return;
                }
            } else {
                // Write the line to the temporary file if it doesn't match the username and month
                tempfile << line << endl;
            }
        }
    }
    infile.close();
    tempfile.close();
    
    // Remove the original file and rename the temporary file to the original filename
    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");
    
    // Write the new entry to the file
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

void writeTransaction(const string& username, int type, double amount, int category, const string& description) {
    // Implement write transaction functionality
}

void readTransactions(const string& username) {
    // Implement read transactions functionality
}

/*
string getCategoryName(int category) {
    // Implement get category name functionality
}

*/

// Function to authenticate a user
bool authenticateUser(const string& username, const string& password, sha256& algorithm) {
    // Check if the username exists in the map
    if (users.find(username) != users.end()) {
        // Hash the input password
        string hashedPassword = algorithm.doSha256(password);
        // Compare the hashed input password with the stored hashed password
        if (hashedPassword == users[username]) {
            cout << "User " << username << " authenticated successfully." << endl;
            return true; // Authentication successful
        } else {
            cout << "Invalid password for user " << username << "." << endl;
            return false; // Incorrect password
        }
    } else {
        cout << "User " << username << " not found." << endl;
        return false; // User not found
    }
}


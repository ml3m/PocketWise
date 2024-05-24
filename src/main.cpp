#include <matplot/axes_objects/labels.h>
#include <matplot/matplot.h>
#include <unordered_map>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <cstdio>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>

#include "sha256.h"

std::unordered_map<std::string, std::string> users;
void print_topClock();

std::string getCurrentTimeAndDay() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *ltm = std::localtime(&now_time);

    char timeBuffer[6]; 
    char dayBuffer[10];

    std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M", ltm);
    std::strftime(dayBuffer, sizeof(dayBuffer), "%A", ltm);

    std::string timeDayStr = std::string(timeBuffer) + " " + std::string(dayBuffer);
    return timeDayStr;
}
std::string get_password() {
    // Disable echoing
    termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    std::string password;
    std::cin >> password;

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    return password;
}
// Function to get the dimensions of the terminal
void get_terminal_size(int &width, int &height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
}

// Function to center text horizontally
std::string center_text(const std::string &text, int width) {
    int pad = (width - text.size()) / 2;
    return std::string(pad, ' ') + text;
}
int central_print_prepare_terminal(int printing_height){
        int terminal_width, terminal_height;
        get_terminal_size(terminal_width, terminal_height);
        int half_height = terminal_height / 2;

        for (int i = 0; i < half_height - printing_height/2; ++i) {
            std::cout << std::endl;
        }
        return terminal_width;
}

// this is very cool
void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}

class UserAuthentication{
    public:
        UserAuthentication();
        void login();
        void createUser();
        bool authenticateUser(const std::string& username, const std::string& password, sha256& algorithm);
    private:
        std::string username;
        std::string password;
};

UserAuthentication::UserAuthentication(){}

class MainMenu {
public:
    MainMenu();
    void mainMenu(const std::string& username);
    void dashboard(const std::string& username);
    void printmenu() const;
    friend std::ostream& operator<<(std::ostream&, const MainMenu&);
};
MainMenu::MainMenu(){}

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

std::ostream& operator<<(std::ostream& os, const MainMenu& mymenu) {
    mymenu.printmenu();
    return os;
}

class BudgetManagement{
    public:
        BudgetManagement();
        void budgetsTab(const std::string& username);
        void writeBudget(const std::string& username, int month, double budget);
        void writeGeneralBudget(const std::string& username, double budget);
        double readBudget(const std::string& username, int month);
        void printBudgets(const std::string& username);
};
BudgetManagement::BudgetManagement(){}

class TransactionManagement{
    public:
        //Transaction Management:
        void writeTransaction(const std::string& username, int type, double amount, int category, const std::string& description);
        void readTransactions(const std::string& username);
        std::string getCategoryName(int category);
};

class ExpenseRevenue{
    public:
        void writeExpense(const std::string& username, double amount, int category, const std::string& description, int month);
        void writeRevenue(const std::string& username, double amount, const std::string& description, int month);
        void addExpense(const std::string& username);
        void addRevenue(const std::string& username);
        void readExpenses(const std::string& username);
        void readRevenues(const std::string& username);
};

class Analysis{
    public:
        void monthAnalysis(const std::string& username);
        void updatePieChart(const std::string& username);
};

class Goals{
    public:
        void GoalTab(const std::string& username);
        void dashboard_component_Goals(const std::string& username);
        void updateGoalTab(const std::string& username);
        void updateGoal(const std::string& username, int goalIndex, double additionalAmount);
        void deleteGoal(const std::string& username);
};

class Investments{
    public:
        void investmentTab(const std::string& username);
        void displayInvestments(const std::vector<std::string>& investmentData);
        void investInStock(const std::string& username, double investmentAmount, const std::string& stockName, std::vector<std::string>& investmentData);
        void writeInvestmentData(const std::string& filename, const std::vector<std::string>& data);
        void readInvestmentData(const std::string& filename, std::vector<std::string>& data);
};


void print_topClock(){
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);

    int clock_start = 2;
    int clock_height = 1;

    for (int i = 0; i < clock_height; ++i) {
        std::cout << std::endl;
    }

    std::string currentTimeAndDay = getCurrentTimeAndDay();
    std::cout << "\r" << std::setw(15) << std::left << center_text(currentTimeAndDay, terminal_width) << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

/************************* MAIN ******************************/ 

int main() {

    int choice;
    UserAuthentication loger;
    do {
        int terminal_width, terminal_height;
        get_terminal_size(terminal_width, terminal_height);
        clear_screen();

        print_topClock();

        std::string art[] = {
            " ____            _        _ __        ___          ",
            "|  _ \\ ___   ___| | _____| |\\ \\      / (_)___  ___ ",
            "| |_) / _ \\ / __| |/ / _ \\ __\\ \\ /\\ / /| / __|/ _ \\",
            "|  __/ (_) | (__|   <  __/ |_ \\ V  V / | \\__ \\  __/",
            "|_|   \\___/ \\___|_|\\_\\___|\\__| \\_/\\_/  |_|___/\\___|"
        };

        // Menu options
        std::string login = "1. Login";
        std::string create_account = "2. Create Account";
        std::string quit = "3. Quit";
        std::string enter_choice = "Enter your choice: ";

        // Center each line of the ASCII art horizontally
        for (std::string &line : art) {
            line = center_text(line, terminal_width);
        }

        // Center each line of the menu horizontally
        login = center_text(login, terminal_width);
        create_account = center_text(create_account, terminal_width);
        quit = center_text(quit, terminal_width);
        enter_choice = center_text(enter_choice, terminal_width);

        // Calculate the total number of lines in the ASCII art and menu
        int art_height = sizeof(art) / sizeof(art[0]);
        int menu_height = 4; // Number of lines in the menu

        // Calculate the vertical positions
        int half_height = terminal_height / 2;
        int art_start = half_height - (art_height / 2 + menu_height + 1); // Add extra space between the art and the menu
        int menu_start = art_start + art_height + 2; // Add extra space between the art and the menu

        // Print blank lines to position the ASCII art
        for (int i = 0; i < art_start; ++i) {
            std::cout << std::endl;
        }

        // Print the ASCII art
        for (const std::string &line : art) {
            std::cout << line << std::endl;
        }

        // Print blank lines to position the menu
        for (int i = art_start + art_height; i < menu_start; ++i) {
            std::cout << std::endl;
        }

        // Print the centered menu
        std::cout << login << std::endl;
        std::cout << create_account << std::endl;
        std::cout << quit << std::endl;
        std::cout << enter_choice;
        std::cin >> choice;

        std::cin.ignore();



        switch(choice) {
            case 1:
                clear_screen();
                loger.login();
                break;
            case 2:
                loger.createUser();
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

void UserAuthentication::createUser() {
    
    std::string username, password;

    clear_screen();
    print_topClock();
    int printing_height  = 3; 
    int terminal_width = central_print_prepare_terminal(printing_height);

    std::cout << center_text("Enter username: ", terminal_width);
    std::cin >> username;

    std::ifstream infile("users.txt");
    std::string storedUsername;
    while (infile >> storedUsername) {
        if (storedUsername == username) {
            std::cout << center_text("Username already exists. Please choose a different one.\n", terminal_width);
            infile.close();
            std::cout << center_text("Press Enter to continue...\n", terminal_width);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input
            std::cin.get(); // Wait for Enter key press
            return;
        }
    }
    infile.close();

    std::cout << center_text("Enter password: ", terminal_width);
    password = get_password();

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


void UserAuthentication::login() {
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);
    int menu_height = 2; 
    int half_height = terminal_height / 2;
    int printing_height = 2;
    
    print_topClock();
    int clock_height = 3;

    for (int i = clock_height; i<half_height-menu_height+clock_height; ++i) {
        std::cout << std::endl;
    }

    std::cout << center_text("Enter username: ", terminal_width);
    std::string username;
    std::cin >> username;

    std::cout << center_text("Enter password: ", terminal_width);
    std::string password = get_password();
    std::cout << std::endl; 

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
                    this->username = username;
                    this->password = password;
                    MainMenu mymenu;
                    clear_screen();
                    std::cout<<mymenu;
                    mymenu.mainMenu(username);
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

bool UserAuthentication::authenticateUser(const std::string& username, const std::string& password, sha256& algorithm) {
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
    
    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");
    
    std::ofstream outfile("budgets.txt", std::ios::app);
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
    std::ifstream infile("budgets.txt");
    std::ofstream tempfile("temp.txt");
    
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

double BudgetManagement::readBudget(const std::string& username, int month) {
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

void BudgetManagement::printBudgets(const std::string& username){
    //beauty
    clear_screen();
    print_topClock();
    int printing_height = 12;
    central_print_prepare_terminal(printing_height);
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
    std::cout << "Press Enter to go back..." << std::endl;
    std::cin.ignore();

    infile.close();
    return;
}

void ExpenseRevenue::writeExpense(const std::string& username, double amount, int category, const std::string& description, int month) {
    std::ofstream outfile("expenses.txt", std::ios::app); // Create or open the expenses file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << month << " " << category << " " << description << std::endl;
        std::cout << "Expense added successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to add expense..." << std::endl;
    }
}

void ExpenseRevenue::writeRevenue(const std::string& username, double amount, const std::string& description, int month) {
    std::ofstream outfile("revenues.txt", std::ios::app); // Create or open the revenues file
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

void ExpenseRevenue::readRevenues(const std::string& username) {
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

void MainMenu::dashboard(const std::string& username) {
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
    std::cin.ignore();
    std::cout << "Press Enter to go back..." << std::endl;
    std::cin.ignore();
    return;
}

void Analysis::monthAnalysis(const std::string& username) {
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

void Goals::dashboard_component_Goals(const std::string& username) {
    // clear scree + setup for space before menu
    // for each item in menu do the thingy with need_menu.
    // center print for all, maybe add spaces   
    clear_screen();
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
    std::cout << "Press Enter to Go back...";
    std::cin.ignore();
}

void Goals::GoalTab(const std::string& username) {
    bool exitGoalTab = false;
    int need_menu = 0;

    clear_screen();
    print_topClock();
    int printing_height = 7;
    int terminal_width = central_print_prepare_terminal(printing_height);

    while (!exitGoalTab) {
        int month, user_goal_choice;
        std::string title;
        double amount, leftA = 0, paidA = 0;
        if (need_menu) {
            clear_screen();
        }

        std::cout << center_text("Goals Tab\n", terminal_width);
        std::cout << center_text("1. Create Goal\n", terminal_width);
        std::cout << center_text("2. See Goal/s\n", terminal_width);
        std::cout << center_text("3. Update Goal\n",terminal_width);
        std::cout << center_text("4. Delete Goal\n", terminal_width);
        std::cout << center_text("5. Exit Goal Tab\n", terminal_width);
        std::cout << center_text("Enter your choice: ", terminal_width);
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
                need_menu = 1;
                break;
            case 2:
                dashboard_component_Goals(username);
                need_menu = 1;
                break;
            case 3:
                updateGoalTab(username);
                need_menu = 1;
                break;
            case 4:
                deleteGoal(username);
                need_menu = 1;
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


void Goals::updateGoal(const std::string& username, int goalIndex, double additionalAmount) {
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

void Goals::updateGoalTab(const std::string& username) {
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


void Goals::deleteGoal(const std::string& username) {
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



void Investments::readInvestmentData(const std::string& filename, std::vector<std::string>& data) {
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

void Investments::writeInvestmentData(const std::string& filename, const std::vector<std::string>& data) {
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

void Investments::investInStock(const std::string& username, double investmentAmount, const std::string& stockName, std::vector<std::string>& investmentData) {
    // Code for investing in a stock
    // You can add more functionality here, such as updating user's investment portfolio, etc.
    std::string investmentRecord = username + " " + std::to_string(investmentAmount) + " " + stockName;
    investmentData.push_back(investmentRecord);
    std::cout << "Invested $" << investmentAmount << " in " << stockName << std::endl;
}

void Investments::displayInvestments(const std::vector<std::string>& investmentData) {
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

void Investments::investmentTab(const std::string& username) {
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


void Analysis::updatePieChart(const std::string& username) {
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

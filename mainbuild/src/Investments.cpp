#include "../include/precompiled.h"

#include "../include/Investments.h"

void Investments::investmentTab(const std::string& username) {
    std::vector<std::string> investmentData;
    readInvestmentData("data/investment_data.txt", investmentData);

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

    writeInvestmentData("data/investment_data.txt", investmentData);
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

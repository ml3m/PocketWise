#include "../include/precompiled.h"

#include "../include/Stocks.h"

void Investments::investmentTab(const std::string& username) {
    readInvestmentData("data/investment_data.txt");
    loadAvailableStocks();
    parseInvestmentData();

    bool exitInvestmentTab = false;
    while (!exitInvestmentTab) {
        int user_choice;
        std::cout << "\nInvestment Tab" << std::endl;
        std::cout << "1. Invest in a Stock" << std::endl;
        std::cout << "2. View Investment Portfolio" << std::endl;
        std::cout << "3. Sell Shares" << std::endl;
        std::cout << "4. Exit Investment Tab" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> user_choice;

        switch(user_choice) {
            case 1:
                investInStock(username);
                break;
            case 2:
                displayInvestments(username);
                break;
            case 3:
                sellShares(username);
                break;
            case 4:
                std::cout << "Exiting Investment Tab..." << std::endl;
                exitInvestmentTab = true;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    }

    updateInvestmentData();
    writeInvestmentData("data/investment_data.txt");
}

void Investments::readInvestmentData(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        investmentData.push_back(line);
    }

    infile.close();
}

void Investments::writeInvestmentData(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    for (const auto& line : investmentData) {
        outfile << line << std::endl;
    }

    outfile.close();
}

void Investments::loadAvailableStocks() {
    // Predefined list of stocks and their prices
    availableStocks = {
        {"AAPL", 156.80}, {"GOOGL", 2821.30}, {"AMZN", 3401.46},
        {"MSFT", 299.35}, {"TSLA", 759.49}, {"FB", 345.89},
        {"NFLX", 590.65}, {"NVDA", 195.55}, {"DIS", 175.18},
        {"V", 223.50}
    };
}

void Investments::parseInvestmentData() {
    for (const auto& record : investmentData) {
        std::istringstream iss(record);
        Investment investment;
        iss >> investment.username >> investment.shares >> investment.stockName >> investment.initialPrice;
        userInvestments.push_back(investment);
    }
}

void Investments::updateInvestmentData() {
    investmentData.clear();
    for (const auto& investment : userInvestments) {
        investmentData.push_back(investment.username + " " + std::to_string(investment.shares) + " " + investment.stockName + " " + std::to_string(investment.initialPrice));
    }
}

void Investments::investInStock(const std::string& username) {
    std::cout << "\nAvailable Stocks:\n";
    for (size_t i = 0; i < availableStocks.size(); ++i) {
        std::cout << i + 1 << ". " << availableStocks[i].name << " - $" << availableStocks[i].price << " per share\n";
    }

    int stockChoice, shares;
    std::cout << "Select the Stock (1-10): ";
    std::cin >> stockChoice;
    if (stockChoice < 1 || stockChoice > 10) {
        std::cout << "Invalid choice. Returning to menu.\n";
        return;
    }

    Stock& chosenStock = availableStocks[stockChoice - 1];
    std::cout << "How many shares do you want to buy? ";
    std::cin >> shares;

    double totalCost = shares * chosenStock.price;
    std::cout << "Your receipt is: buy " << shares << " * $" << chosenStock.price << " = $" << totalCost << "\nAre you sure you want to proceed with this action? (Y/N): ";
    char confirmation;
    std::cin >> confirmation;

    if (confirmation == 'Y' || confirmation == 'y') {
        Investment newInvestment = {username, chosenStock.name, shares, chosenStock.price};
        userInvestments.push_back(newInvestment);
        std::cout << "Invested $" << totalCost << " in " << chosenStock.name << std::endl;
    } else {
        std::cout << "Investment cancelled.\n";
    }
}

void Investments::displayInvestments(const std::string& username) {
    std::cout << "\nInvestment Portfolio:\n";
    std::cout << std::setw(15) << "Username" << std::setw(15) << "Stock" << std::setw(15) << "Shares"
              << std::setw(15) << "Price" << std::setw(15) << "Total" << std::setw(20) << "Difference"
              << std::setw(20) << "Dividends" << std::endl;
    std::cout << std::string(95, '-') << std::endl;

    for (const auto& investment : userInvestments) {
        if (investment.username == username) {
            double currentPrice = 0.0;
            for (const auto& stock : availableStocks) {
                if (stock.name == investment.stockName) {
                    currentPrice = stock.price;
                    break;
                }
            }
            double totalValue = investment.shares * currentPrice;
            double difference = (currentPrice - investment.initialPrice) * investment.shares;
            double dividends = totalValue * 0.042;

            std::cout << std::setw(15) << investment.username << std::setw(15) << investment.stockName
                      << std::setw(15) << investment.shares << std::setw(15) << currentPrice
                      << std::setw(15) << totalValue << std::setw(20) << (difference >= 0 ? "+" : "") << difference
                      << std::setw(20) << dividends << std::endl;
        }
    }
}

void Investments::sellShares(const std::string& username) {
    std::cout << "\nYour Stocks:\n";
    int count = 1;
    std::vector<Investment*> userStocks;
    for (auto& investment : userInvestments) {
        if (investment.username == username) {
            userStocks.push_back(&investment);
            double currentPrice = 0.0;
            for (const auto& stock : availableStocks) {
                if (stock.name == investment.stockName) {
                    currentPrice = stock.price;
                    break;
                }
            }
            std::cout << count++ << ". " << investment.stockName << " - " << investment.shares << " shares @ $" << currentPrice << " per share\n";
        }
    }

    int stockChoice, shares;
    std::cout << "Select the Stock to sell (1-" << count - 1 << "): ";
    std::cin >> stockChoice;
    if (stockChoice < 1 || stockChoice >= count) {
        std::cout << "Invalid choice. Returning to menu.\n";
        return;
    }

    Investment* chosenInvestment = userStocks[stockChoice - 1];

    std::cout << "How many shares do you want to sell? ";
    std::cin >> shares;
    if (shares > chosenInvestment->shares) {
        std::cout << "You don't own that many shares. Returning to menu.\n";
        return;
    }

    double currentPrice = 0.0;
    for (const auto& stock : availableStocks) {
        if (stock.name == chosenInvestment->stockName) {
            currentPrice = stock.price;
            break;
        }
    }

    double totalSale = shares * currentPrice;
    double profit = (currentPrice - chosenInvestment->initialPrice) * shares;

    std::cout << "Your receipt is: sell " << shares << " * $" << currentPrice << " = $" << totalSale << "\nAre you sure you want to proceed with this action? (Y/N): ";
    char confirmation;
    std::cin >> confirmation;

    if (confirmation == 'Y' || confirmation == 'y') {
        chosenInvestment->shares -= shares;
        if (chosenInvestment->shares == 0) {
            userInvestments.erase(std::remove(userInvestments.begin(), userInvestments.end(), *chosenInvestment), userInvestments.end());
        }
        std::cout << "Sold " << shares << " shares of " << chosenInvestment->stockName << " for $" << totalSale << ".\n";
        std::cout << "Profit/Loss: $" << profit << "\n";
    } else {
        std::cout << "Sale cancelled.\n";
    }
}

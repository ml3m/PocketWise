#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

struct Stock {
    std::string name;
    double price;
};

struct Investment {
    std::string username;
    std::string stockName;
    int shares;
    double initialPrice; 
    bool operator==(const Investment& other) const {
        return username == other.username &&
               stockName == other.stockName &&
               shares == other.shares &&
               initialPrice == other.initialPrice;
    }
};

struct Transaction {
    std::string username;
    std::string stockName;
    int shares;
    double price;
    std::string type; // "buy" or "sell"
};

class Investments {
public:
    void investmentTab(const std::string& username);

private:
    std::vector<Stock> availableStocks;
    std::vector<Investment> userInvestments;
    std::vector<std::string> investmentData;
    std::vector<Transaction> transactionHistory;

    void readInvestmentData(const std::string& filename);
    void writeInvestmentData(const std::string& filename);
    void loadAvailableStocks();
    void investInStock(const std::string& username);
    void displayInvestments(const std::string& username);
    void sellShares(const std::string& username);
    void parseInvestmentData();
    void updateInvestmentData();
    void logTransaction(const std::string& username, const std::string& stockName, int shares, double price, const std::string& type);
    void writeTransactionHistory(const std::string& filename);
};

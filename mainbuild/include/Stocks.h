#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Stock {
    std::string name;
    double price;
};

struct Investment {
    std::string username;
    std::string stockName;
    int shares;
    double initialPrice; 
    // def of operator == for comparing objects by all means
    bool operator==(const Investment& other) const {
        return username == other.username &&
               stockName == other.stockName &&
               shares == other.shares &&
               initialPrice == other.initialPrice;
    }
};

class Investments {
public:
    void investmentTab(const std::string& username);

private:
    std::vector<Stock> availableStocks;
    std::vector<Investment> userInvestments;
    std::vector<std::string> investmentData; // Original data from file

    void readInvestmentData(const std::string& filename);
    void writeInvestmentData(const std::string& filename);
    void loadAvailableStocks();
    void investInStock(const std::string& username);
    void displayInvestments(const std::string& username);
    void sellShares(const std::string& username);
    void parseInvestmentData();
    void updateInvestmentData();
};

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>


// structs that are used trough the Investment Tab of the app.

struct Stock {
    std::string name;
    double price;
};


struct Transaction {
    std::string username;
    std::string stockName;
    std::string type;
    int shares;
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


/* thought with the idea of having one accesable public class that controls internally all the private stuff*/
class Investments {
    public:
        void investmentTab(const std::string& username);

    private:
        std::vector<Stock> availableStocks;
        std::vector<Investment> userInvestments;
        std::vector<std::string> investmentData;
        std::vector<Transaction> transactionHistory;

        void logTransaction(const std::string& username, const std::string& stockName, int shares, double price, const std::string& type);
        void writeTransactionHistory(const std::string& filename);
        void writeInvestmentData(const std::string& filename);
        void readInvestmentData(const std::string& filename);
        void displayInvestments(const std::string& username);
        void investInStock(const std::string& username);
        void sellShares(const std::string& username);
        void updateInvestmentData();
        void loadAvailableStocks();
        void parseInvestmentData();
};

#ifndef INVESTMENTS_H
#define INVESTMENTS_H

#include <string>
#include <vector>

class Investments {
public:
    void investmentTab(const std::string& username);
    void displayInvestments(const std::vector<std::string>& investmentData);
    void investInStock(const std::string& username, double investmentAmount, const std::string& stockName, std::vector<std::string>& investmentData);
    void writeInvestmentData(const std::string& filename, const std::vector<std::string>& data);
    void readInvestmentData(const std::string& filename, std::vector<std::string>& data);
};

#endif 

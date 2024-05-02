#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

struct Month{
    int month;
    float budget;
    float total_expenses;
    float total_savings;
    float month_overall;
    void setBudget(float) const;
};


class Account {
    private:
        std::string username;
        std::string password;

    public:
        Account(const std::string& uname, const std::string& pwd);
        std::string getUsername() const;
        std::string getPassword() const;
        bool authenticate(const std::string& pwd) const;
        std::vector<Month> cls_user_months; 
};

#endif // ACCOUNT_H

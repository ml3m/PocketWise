#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Month{
    private:
        int month;
        float budget;
        float total_expenses;
        float total_savings;
        float month_overall;
    public:
        Month(int, float, float, float, float);
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
};

#endif // ACCOUNT_H

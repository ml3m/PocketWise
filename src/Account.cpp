#include "../include/Account.h"

Account::Account(const std::string& uname, const std::string& pwd) : username(uname), password(pwd) {}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

bool Account::authenticate(const std::string& pwd) const {
    return password == pwd;
}

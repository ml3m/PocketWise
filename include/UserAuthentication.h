#ifndef USERAUTHENTICATION_H
#define USERAUTHENTICATION_H

#include <string>
#include "sha256.h"

class UserAuthentication {
    public:
        UserAuthentication();
        void login();
        void createUser();
        bool authenticateUser(const std::string& username, const std::string& password, sha256& algorithm);
    private:
        std::string username;
        std::string password;
};

#endif 

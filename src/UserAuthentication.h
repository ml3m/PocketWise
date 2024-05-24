#include <iostream>
#include "sha256.h"

class UserAuthentication{
    public:
        void login();
        void createUser();
        bool authenticateUser(const std::string& username, const std::string& password, sha256& algorithm);
};

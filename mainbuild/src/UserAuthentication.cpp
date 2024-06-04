#include <sys/ioctl.h>
#include <termios.h>
#include <fstream>
#include <sstream>  // Add this include for std::istringstream
#include <unistd.h>
#include <iostream>
#include <ostream>
#include <cctype>
#include <string>
#include <cstdio>
#include <ctime>
#include "../include/sha256.h"
#include "../include/MainMenu.h"
#include "../include/terminal_utils.h"
#include "../include/UserAuthentication.h"
#include <limits>

#include "../include/global.h"

UserAuthentication::UserAuthentication(){}

void UserAuthentication::createUser() {
    
    std::string username, password;

    clear_screen();
    print_topClock();
    int printing_height  = 3; 
    int terminal_width = central_print_prepare_terminal(printing_height);

    std::cout << center_text("Enter username: ", terminal_width);
    std::cin >> username;

    std::ifstream infile("data/users.txt");
    std::string storedUsername;
    while (infile >> storedUsername) {
        if (storedUsername == username) {
            std::cout << center_text("Username already exists. Please choose a different one.\n", terminal_width);
            infile.close();
            std::cout << center_text("Press Enter to continue...\n", terminal_width);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input
            std::cin.get(); // Wait for Enter key press
            return;
        }
    }
    infile.close();

    std::cout << center_text("Enter password: ", terminal_width);
    password = get_password();

    std::string small_salt = "mlematikus";
    password += small_salt; // salt aplication
    std::ofstream outfile("data/users.txt", std::ios::app);
    if (outfile.is_open()) {
        sha256 algorithm;
        std::string hashPassword = algorithm.doSha256(password);

        outfile << username << " " << hashPassword << std::endl;
        outfile.close();
        std::cout << "Account created successfully!" << std::endl;
    } else {
        std::cout << "Error: Unable to create account." << std::endl;
    }
}


void UserAuthentication::login() {
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);
    int menu_height = 2; 
    int half_height = terminal_height / 2;
    int printing_height = 2;
    
    print_topClock();
    int clock_height = 3;

    for (int i = clock_height; i<half_height-menu_height+clock_height; ++i) {
        std::cout << std::endl;
    }

    std::cout << center_text("Enter username: ", terminal_width);
    std::string username;
    std::cin >> username;

    std::cout << center_text("Enter password: ", terminal_width);
    std::string password = get_password();
    std::cout << std::endl; 

    std::string small_salt = "mlematikus";
    sha256 algorithm;
    password += small_salt; //salt aplication
    std::string hashedPassword = algorithm.doSha256(password);

    std::ifstream infile("data/users.txt");
    if (infile.is_open()) {
        std::string storedUsername, storedHashedPassword;
        bool userFound = false;
        while (infile >> storedUsername >> storedHashedPassword) {
            if (storedUsername == username) {
                userFound = true;
                if (hashedPassword == storedHashedPassword) {
                    std::cout << "Login successful!" << std::endl;
                    this->username = username;
                    this->password = password;
                    MainMenu mymenu;
                    mymenu.set_menu_username(username);
                    clear_screen();
                    std::cout<<mymenu;
                    mymenu.mainMenu(username);
                    return;
                } else {
                    std::cout << "Login failed. Please try again." << std::endl;
                    return; 
                }
            }
        }
        if (!userFound) {
            std::cout << "User not found. Please try again." << std::endl;
        }
        infile.close();
    } else {
        std::cout << "Error: Unable to open users.txt." << std::endl;
    }
}

bool UserAuthentication::authenticateUser(const std::string& username, const std::string& password, sha256& algorithm) {
    if (users.find(username) != users.end()) {
        std::string hashedPassword = algorithm.doSha256(password);
        if (hashedPassword == users[username]) {
            std::cout << "User " << username << " authenticated successfully." << std::endl;
            return true; 
        } else {
            std::cout << "Invalid password for user " << username << "." << std::endl;
            return false; 
        }
    } else {
        std::cout << "User " << username << " not found." << std::endl;
        return false;
    }
}


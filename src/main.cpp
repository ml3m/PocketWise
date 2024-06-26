#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <ostream>
#include <cctype>
#include <string>
#include <ctime>


/************** header files import **************/
#include "../include/terminal_utils.h"
#include "../include/UserAuthentication.h"


/************************* MAIN ******************************/ 
int main() {
    // the main functionality that goes to the login + ascii art formating + pedding math

    int choice;
    UserAuthentication loger;
    do {
        int terminal_width, terminal_height;
        get_terminal_size(terminal_width, terminal_height);
        clear_screen();

        print_topClock();

        std::string art[] = {
            " ____            _        _ __        ___          ",
            "|  _ \\ ___   ___| | _____| |\\ \\      / (_)___  ___ ",
            "| |_) / _ \\ / __| |/ / _ \\ __\\ \\ /\\ / /| / __|/ _ \\",
            "|  __/ (_) | (__|   <  __/ |_ \\ V  V / | \\__ \\  __/",
            "|_|   \\___/ \\___|_|\\_\\___|\\__| \\_/\\_/  |_|___/\\___|"
        };

        // Menu options
        std::string login = "1. Login";
        std::string create_account = "2. Create Account";
        std::string quit = "3. Quit";
        std::string enter_choice = "Enter your choice: ";

        // Center each line of the ASCII art horizontally
        for (std::string &line : art) {
            line = center_text(line, terminal_width);
        }

        // center each line on horizontal side 
        login = center_text(login, terminal_width);
        create_account = center_text(create_account, terminal_width);
        quit = center_text(quit, terminal_width);
        enter_choice = center_text(enter_choice, terminal_width);

        // total number of lines in the ASCII art and menu
        int art_height = sizeof(art) / sizeof(art[0]);
        int menu_height = 4; // Number of lines in the menu

        // Calculate the vertical positions
        int half_height = terminal_height / 2;
        int art_start = half_height - (art_height / 2 + menu_height + 1); // Add extra space between the art and the menu
        int menu_start = art_start + art_height + 2; // Add extra space between the art and the menu

        // Print blank lines for right distance in ascii art 
        for (int i = 0; i < art_start; ++i) {
            std::cout << std::endl;
        }

        //printing of the ASCII art
        for (const std::string &line : art) {
            std::cout << line << std::endl;
        }

        // Print blank lines to position the menu
        for (int i = art_start + art_height; i < menu_start; ++i) {
            std::cout << std::endl;
        }

        // Print the centered menu
        std::cout << login << std::endl;
        std::cout << create_account << std::endl;
        std::cout << quit << std::endl;
        std::cout << enter_choice;
        std::cin >> choice;
        std::cin.ignore();


        switch(choice) {
            case 1:
                clear_screen();
                loger.login();
                break;
            case 2:
                loger.createUser();
                break;
            case 3:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    } while(choice != 3);

    return 0;
}

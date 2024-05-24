#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

// Function to get the dimensions of the terminal
void get_terminal_size(int &width, int &height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
}

// Function to center text horizontally
std::string center_text(const std::string &text, int width) {
    int pad = (width - text.size()) / 2;
    return std::string(pad, ' ') + text;
}

// Function to clear the screen
void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}

int main() {
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);

    // Clear the screen
    clear_screen();

    // Menu options
    std::string login = "1. Login";
    std::string create_account = "2. Create Account";
    std::string quit = "3. Quit";
    std::string enter_choice = "Enter your choice: ";

    // Center each line of the menu horizontally
    login = center_text(login, terminal_width);
    create_account = center_text(create_account, terminal_width);
    quit = center_text(quit, terminal_width);
    enter_choice = center_text(enter_choice, terminal_width);

    // Calculate the total number of lines in the menu
    int menu_height = 4; // Number of lines in the menu
    int top_padding = (terminal_height - menu_height) / 2;

    // Print blank lines to center the menu vertically
    for (int i = 0; i < top_padding; ++i) {
        std::cout << std::endl;
    }

    // Print the centered menu
    std::cout << login << std::endl;
    std::cout << create_account << std::endl;
    std::cout << quit << std::endl;
    std::cout << enter_choice;

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    return 0;
}

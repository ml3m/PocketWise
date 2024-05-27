#include "../include/precompiled.h"
#include <iostream>
#include <matplot/axes_objects/labels.h>
#include <string>
#include "../include/terminal_utils.h"

// this is very cool
void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}
void get_terminal_size(int &width, int &height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
}
std::string center_text(const std::string &text, int width) {
    int pad = (width - text.size()) / 2;
    return std::string(pad, ' ') + text;
}
int central_print_prepare_terminal(int printing_height){
        int terminal_width, terminal_height;
        get_terminal_size(terminal_width, terminal_height);
        int half_height = terminal_height / 2;

        for (int i = 0; i < half_height - printing_height/2; ++i) {
            std::cout << std::endl;
        }
        return terminal_width;
}
void print_topClock(){
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);

    int clock_start = 2;
    int clock_height = 1;

    for (int i = 0; i < clock_height; ++i) {
        std::cout << std::endl;
    }

    std::string currentTimeAndDay = getCurrentTimeAndDay();
    std::cout << "\r" << std::setw(15) << std::left << center_text(currentTimeAndDay, terminal_width) << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
void print_topName(const std::string username){
    /*bruv Idek abof this func idkidkidk*/
    int terminal_width, terminal_height;
    get_terminal_size(terminal_width, terminal_height);

    int Name_height = 2;

    for (int i = 0; i < Name_height; ++i) {
        std::cout << std::endl;
    }
    std::cout << center_text("Logged in as " + username,terminal_width);
}

std::string getCurrentTimeAndDay() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *ltm = std::localtime(&now_time);

    char timeBuffer[6]; 
    char dayBuffer[10];

    std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M", ltm);
    std::strftime(dayBuffer, sizeof(dayBuffer), "%A", ltm);

    std::string timeDayStr = std::string(timeBuffer) + " " + std::string(dayBuffer);
    return timeDayStr;
}
std::string get_password() {
    // Disable echoing
    termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    std::string password;
    std::cin >> password;

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    return password;
}

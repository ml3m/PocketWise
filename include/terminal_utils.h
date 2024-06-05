#ifndef TERMINAL_UTILS_H
#define TERMINAL_UTILS_H

#include <string>

void clear_screen();
void get_terminal_size(int &width, int &height);
std::string center_text(const std::string &text, int width);
int central_print_prepare_terminal(int printing_height);
void print_topClock();
std::string getCurrentTimeAndDay();
std::string get_password();
void print_topName(const std::string username);

#endif // TERMINAL_UTILS_H

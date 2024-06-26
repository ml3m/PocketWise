#ifndef TERMINAL_UTILS_H
#define TERMINAL_UTILS_H

#include <string>

void get_terminal_size(int &width, int &height);
void print_topName(const std::string username);
void print_topClock();
void clear_screen();

int central_print_prepare_terminal(int printing_height);

std::string center_text(const std::string &text, int width);
std::string getCurrentTimeAndDay();
std::string get_password();

#endif 

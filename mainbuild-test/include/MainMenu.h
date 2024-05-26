#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>
#include <ostream>

class MainMenu {
public:
    MainMenu();
    void mainMenu(const std::string& username);
    void dashboard(const std::string& username);
    void printmenu() const;
    friend std::ostream& operator<<(std::ostream&, const MainMenu&);
};

#endif 

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
        void set_menu_username(const std::string& username);
        friend std::ostream& operator<<(std::ostream&, const MainMenu&);
    private:
        std::string username;
};

#endif 

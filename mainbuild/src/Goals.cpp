#include "../include/precompiled.h"

#include "../include/Goals.h"
#include "../include/terminal_utils.h"

void Goals::writeGoal(const std::string& username, double amount, const std::string& goalTitle, int month, double amountLeft, double amountPaid) {
    std::ofstream outfile("data/goals.txt", std::ios::app); // Create or open the expenses file
    if (outfile.is_open()) {
        outfile << username << " " << amount << " " << amountLeft << " " << amountPaid << " " << month << " " << goalTitle <<std::endl;
        std::cout << "Goal '" <<goalTitle << "' added successfully!" << std::endl;
        outfile.close();
    } else {
        std::cout << "Error: Unable to add goal." << std::endl;
    }
}

void Goals::GoalTab(const std::string& username) {
    bool exitGoalTab = false;
    int need_menu = 0;

    clear_screen();
    print_topClock();
    int printing_height = 7;
    int terminal_width = central_print_prepare_terminal(printing_height);

    while (!exitGoalTab) {
        int month, user_goal_choice;
        std::string title;
        double amount, leftA = 0, paidA = 0;
        if (need_menu) {
            clear_screen();
        }

        std::cout << center_text("Goals Tab\n", terminal_width);
        std::cout << center_text("1. Create Goal\n", terminal_width);
        std::cout << center_text("2. See Goal/s\n", terminal_width);
        std::cout << center_text("3. Update Goal\n",terminal_width);
        std::cout << center_text("4. Delete Goal\n", terminal_width);
        std::cout << center_text("5. Exit Goal Tab\n", terminal_width);
        std::cout << center_text("Enter your choice: ", terminal_width);
        std::cin >> user_goal_choice;

        switch (user_goal_choice) {
            case 1:
                std::cin.ignore();
                std::cout << "Enter Goal Title:";
                getline(std::cin, title);
                std::cout << "\nEnter required goal amount:";
                std::cin >> amount;
                std::cout << "\nEnter deadline month:";
                std::cin >> month;
                leftA = amount;
                writeGoal(username, amount, title, month, leftA, paidA);
                need_menu = 1;
                break;
            case 2:
                dashboard_component_Goals(username);
                need_menu = 1;
                break;
            case 3:
                updateGoalTab(username);
                need_menu = 1;
                break;
            case 4:
                deleteGoal(username);
                need_menu = 1;
                break;
            case 5:
                std::cout << "Exiting Goal Tab..." << std::endl;
                exitGoalTab = true;   // Set exit flag 
                break;
            default:
                std::cout << "Invalid choice. Please enter again." << std::endl;
        }
    }
}


void Goals::updateGoal(const std::string& username, int goalIndex, double additionalAmount) {
    std::ifstream infile("data/goals.txt");
    if (!infile.is_open()) {
        std::cout << "Error: Unable to open goals file." << std::endl;
        return;
    }

    std::vector<std::string> goals;
    std::string line;
    while (std::getline(infile, line)) {
        goals.push_back(line);
    }
    infile.close();

    if (goalIndex < 1 || goalIndex > goals.size()) {
        std::cout << "Invalid goal number. Please try again." << std::endl;
        return;
    }

    std::istringstream iss(goals[goalIndex - 1]);
    std::string goalUsername, goalTitle;
    double amount, amountLeft, amountPaid;
    int month;
    iss >> goalUsername >> amount >> amountLeft >> amountPaid >> month >> std::ws;
    std::getline(iss, goalTitle);

    amountLeft -= additionalAmount;
    amountPaid += additionalAmount;

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2); // Set precision for doubles
    oss << username << " " << amount << " " << amountLeft << " " << amountPaid << " " << month << " " << goalTitle;

    goals[goalIndex - 1] = oss.str();

    std::ofstream outfile("data/goals.txt");
    if (outfile.is_open()) {
        for (const auto& goal : goals) {
            outfile << goal << std::endl;
        }
        outfile.close();
        
        if (amountPaid == amount) {
            std::cout << "Goal accomplished! Congratulations, " << username << "!" << std::endl;
        } else {
            std::cout << "Goal updated successfully!" << std::endl;
        }
    } else {
        std::cout << "Error: Unable to update goal." << std::endl;
    }
}

void Goals::updateGoalTab(const std::string& username) {
    dashboard_component_Goals(username);
    std::cout << "goals are numbered starting from 1.\n";

    int goalIndex;
    std::cout << "\tEnter the number of the goal you want to update: ";
    std::cin >> goalIndex;

    double additionalAmount;
    std::cout << "\tEnter the additional amount to add to the goal: ";
    std::cin >> additionalAmount;

    updateGoal(username, goalIndex, additionalAmount);
}


void Goals::deleteGoal(const std::string& username) {
    dashboard_component_Goals(username);
    std::cout << "Goals are numbered starting from 1." << std::endl;

    int goalIndex;
    std::cout << "Enter the number of the goal you want to delete: ";
    std::cin >> goalIndex;

    std::ifstream infile("data/goals.txt");
    if (!infile.is_open()) {
        std::cout << "Error: Unable to open goals file." << std::endl;
        return;
    }

    std::vector<std::string> goals;
    std::string line;
    while (std::getline(infile, line)) {
        goals.push_back(line);
    }
    infile.close();

    if (goalIndex < 1 || goalIndex > goals.size()) {
        std::cout << "Invalid goal number. Please try again." << std::endl;
        return;
    }

    goals.erase(goals.begin() + goalIndex - 1);

    std::ofstream outfile("data/goals.txt");
    if (outfile.is_open()) {
        for (const auto& goal : goals) {
            outfile << goal << std::endl;
        }
        outfile.close();
        
        std::cout << "Goal deleted successfully!" << std::endl;
    } else {
        std::cout << "Error: Unable to delete goal." << std::endl;
    }
}

void Goals::dashboard_component_Goals(const std::string& username) {
    // clear scree + setup for space before menu
    // for each item in menu do the thingy with need_menu.
    // center print for all, maybe add spaces   
    clear_screen();
    std::ifstream infile("data/goals.txt");

    if (!infile.is_open()) {
        std::cout << "Error: Unable to open goals file." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> userGoals;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string goalUsername;
        iss >> goalUsername;

        if (goalUsername == username) {
            userGoals.push_back(line);
        }
    }

    infile.close();

    if (userGoals.empty()) {
        std::cout << "No goals found for " << username << std::endl;
        return;
    }

    std::cout << "Goals for " << username << ":" << std::endl;
    std::cout << std::setw(5) << "Index"
              << std::setw(20) << std::left << "Goal Title"
              << std::setw(15) << "Amount"
              << std::setw(15) << "Amount Left"
              << std::setw(15) << "Amount Paid"
              << std::setw(10) << "Month"
              << std::setw(15) << "Completion %" // Added column for completion percentage
              << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    for (size_t i = 0; i < userGoals.size(); ++i) {
        std::istringstream iss(userGoals[i]);
        std::string goalUsername, goalTitle;
        double amount, amountLeft, amountPaid;
        int month;

        iss >> goalUsername >> amount >> amountLeft >> amountPaid >> month >> goalTitle;

        // Calculate completion percentage
        double completionPercentage = ((amount - amountLeft) / amount) * 100;

        std::cout << std::setw(5) << i + 1 // Index starts from 1
                  << std::setw(20) << std::left << goalTitle
                  << std::setw(15) << amount
                  << std::setw(15) << amountLeft
                  << std::setw(15) << amountPaid
                  << std::setw(10) << month
                  << std::setw(15) << std::fixed << std::setprecision(2) << completionPercentage // Display completion percentage with 2 decimal places
                  << std::endl;
    }
    std::cout << "Press Enter to Go back...";
    std::cin.ignore();
}


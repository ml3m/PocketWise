#ifndef GOALS_H
#define GOALS_H

#include <string>

class Goals {
public:
    void GoalTab(const std::string& username);
    void dashboard_component_Goals(const std::string& username);
    void updateGoalTab(const std::string& username);
    void updateGoal(const std::string& username, int goalIndex, double additionalAmount);
    void deleteGoal(const std::string& username);
    void writeGoal(const std::string& username, double amount, const std::string& goalTitle, int month, double amountLeft, double amountPaid);
};

#endif // GOALS_H

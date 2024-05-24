#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>

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
/*
    while (true) {
        std::string currentTimeAndDay = getCurrentTimeAndDay();
        std::cout << "\r" << std::setw(15) << std::left << currentTimeAndDay << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

*/

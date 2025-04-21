#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

struct Process {
    std::string name;
    int pid;
    std::string status;
    std::string owner;
};

void printProcessTable(const std::vector<Process>& processes) {
    constexpr int nameWidth = 20;
    constexpr int pidWidth = 10;
    constexpr int statusWidth = 15;
    constexpr int ownerWidth = 15;

    std::cout << std::left
              << std::setw(nameWidth) << "Name"
              << std::setw(pidWidth) << "PID"
              << std::setw(statusWidth) << "Status"
              << std::setw(ownerWidth) << "Owner" << "\n";

    std::cout << std::string(nameWidth + pidWidth + statusWidth + ownerWidth, '-') << "\n";

    for (const auto& p : processes) {
        std::cout << std::left
                  << std::setw(nameWidth) << p.name
                  << std::setw(pidWidth) << p.pid
                  << std::setw(statusWidth) << p.status
                  << std::setw(ownerWidth) << p.owner << "\n";
    }
}

int main() {
    std::vector<Process> processes = {
        {"chrome.exe",  1234, "Running",    "user1"},
        {"explorer.exe", 567, "Sleeping",   "user1"},
        {"mysqld",      4321, "Running",    "mysql"},
        {"python",      3141, "Stopped",    "dev"},
        {"nginx",       8080, "Zombie",     "root"},
        {"code",        2025, "Running",    "user1"}
    };

    printProcessTable(processes);

    return 0;
}

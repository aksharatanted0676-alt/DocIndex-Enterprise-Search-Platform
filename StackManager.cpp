// ============================================================
// StackManager.cpp — Correction Trail Module
// ============================================================

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>

// ----------------------------------------------------------
// ConfigChange
// ----------------------------------------------------------
struct ConfigChange {
    std::string changeType;
    std::string description;
    std::string timestamp;

    ConfigChange(const std::string& type, const std::string& desc,
                 const std::string& ts)
        : changeType(type), description(desc), timestamp(ts) {}
};

// ----------------------------------------------------------
// StackManager
// ----------------------------------------------------------
class StackManager {
private:
    std::stack<ConfigChange> changeStack;
    std::vector<ConfigChange> undoneItems;
    int totalPushed;

    std::string getCurrentTimestamp() const;

public:
    StackManager();

    void addChange(const std::string& changeType, const std::string& description, bool silent = false, const std::string& overrideTime = "");
    bool undoLastChange(bool silent = false);
    void viewTopChange() const;
    void displayHistory() const;
    int getPendingCount() const;
    int getTotalPushed() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

// ============================================================
// Implementation
// ============================================================

StackManager::StackManager() : totalPushed(0) {}

std::string StackManager::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

void StackManager::addChange(const std::string& changeType, const std::string& description, bool silent, const std::string& overrideTime) {
    if (changeType.empty() || description.empty()) {
        if (!silent) std::cout << "  [ERROR] Change type and description cannot be empty.\n";
        return;
    }
    std::string ts = overrideTime.empty() ? getCurrentTimestamp() : overrideTime;
    ConfigChange change(changeType, description, ts);
    changeStack.push(change);
    totalPushed++;
    if (!silent) {
        std::cout << "  Configuration saved:\n";
        std::cout << "  " << description << "\n";
    }
}

bool StackManager::undoLastChange(bool silent) {
    if (changeStack.empty()) {
        if (!silent) std::cout << "  [INFO] No changes to undo. Stack is empty.\n";
        return false;
    }
    ConfigChange top = changeStack.top();
    changeStack.pop();
    undoneItems.push_back(top);
    if (!silent) {
        std::cout << "  Configuration undone:\n";
        std::cout << "  " << top.description << "\n";
    }
    return true;
}

void StackManager::viewTopChange() const {
    if (changeStack.empty()) {
        std::cout << "  No configuration changes on record.\n";
        return;
    }
    const ConfigChange& top = changeStack.top();
    std::cout << "  Latest Configuration Change:\n";
    std::cout << "  Description : " << top.description << "\n";
    std::cout << "  Type        : " << top.changeType << "\n";
    std::cout << "  Timestamp   : " << top.timestamp << "\n";
}

void StackManager::displayHistory() const {
    if (changeStack.empty()) {
        std::cout << "  No configuration changes on record.\n";
        return;
    }
    std::stack<ConfigChange> temp = changeStack;
    int index = 1;
    std::cout << "  Configuration Change History:\n\n";
    while (!temp.empty()) {
        const ConfigChange c = temp.top();
        temp.pop();
        std::cout << "  " << index++ << ". [" << c.changeType << "] " << c.description << " (" << c.timestamp << ")\n";
    }
    if (!undoneItems.empty()) {
        std::cout << "\n  Previously Undone Changes:\n";
        for (int i = (int)undoneItems.size() - 1; i >= 0; i--) {
            const ConfigChange& c = undoneItems[i];
            std::cout << "  - [" << c.changeType << "] " << c.description << "\n";
        }
    }
}

int StackManager::getPendingCount() const { return (int)changeStack.size(); }
int StackManager::getTotalPushed() const { return totalPushed; }

void StackManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    
    // Save Stack (Bottom to Top)
    std::stack<ConfigChange> temp = changeStack;
    std::vector<ConfigChange> bottomUp;
    while (!temp.empty()) {
        bottomUp.push_back(temp.top());
        temp.pop();
    }
    for (int i = bottomUp.size() - 1; i >= 0; i--) {
        outFile << "STACK|" << bottomUp[i].changeType << "|" 
                << bottomUp[i].description << "|" << bottomUp[i].timestamp << "\n";
    }
    
    // Save Undone Items
    for (const auto& item : undoneItems) {
        outFile << "UNDONE|" << item.changeType << "|" 
                << item.description << "|" << item.timestamp << "\n";
    }
    
    // Save totalPushed
    outFile << "TOTAL|" << totalPushed << "\n";
    outFile.close();
}

void StackManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string tag;
        std::getline(ss, tag, '|');
        
        if (tag == "STACK" || tag == "UNDONE") {
            std::string type, desc, ts;
            std::getline(ss, type, '|');
            std::getline(ss, desc, '|');
            std::getline(ss, ts, '|');
            if (tag == "STACK") {
                addChange(type, desc, true, ts); // Note: addChange increments totalPushed
            } else {
                undoneItems.push_back(ConfigChange(type, desc, ts));
            }
        } else if (tag == "TOTAL") {
            std::string tot;
            std::getline(ss, tot);
            totalPushed = std::stoi(tot);
        }
    }
    inFile.close();
}

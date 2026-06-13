// ============================================================
// HashManager.cpp — Checksum Lookup Module
// ============================================================

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <functional>
#include <algorithm>
#include <fstream>

// ----------------------------------------------------------
// ChecksumEntry
// ----------------------------------------------------------
struct ChecksumEntry {
    std::string fileName;
    std::string checksum;
    long long   fileSizeBytes;
    std::string registeredAt;

    ChecksumEntry() : fileSizeBytes(0) {}
    ChecksumEntry(const std::string& name, const std::string& cs,
                  long long size, const std::string& ts)
        : fileName(name), checksum(cs), fileSizeBytes(size), registeredAt(ts) {}
};

// ----------------------------------------------------------
// HashManager
// ----------------------------------------------------------
class HashManager {
private:
    std::unordered_map<std::string, ChecksumEntry> checksumTable;
    std::unordered_map<std::string, std::string> fileToChecksum;
    int duplicatesDetected;

    std::string getCurrentTimestamp() const;
    std::string generateSimulatedChecksum(const std::string& fileName, long long size) const;

public:
    HashManager();

    bool registerChecksum(const std::string& fileName, const std::string& checksum, long long fileSizeBytes, bool silent = false, const std::string& overrideTime = "");
    bool autoRegister(const std::string& fileName, long long fileSizeBytes, bool silent = false);
    bool verifyChecksum(const std::string& checksum) const;
    void lookupByChecksum(const std::string& checksum) const;
    void lookupByFileName(const std::string& fileName) const;
    bool removeChecksum(const std::string& checksum, bool silent = false);
    void displayAll() const;

    int getTotalRegistered()    const;
    int getDuplicatesDetected() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

// ============================================================
// Implementation
// ============================================================

HashManager::HashManager() : duplicatesDetected(0) {}

std::string HashManager::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

std::string HashManager::generateSimulatedChecksum(const std::string& fileName, long long size) const {
    std::string seed = fileName + std::to_string(size);
    std::hash<std::string> hasher;
    size_t h1 = hasher(seed);
    size_t h2 = hasher(seed + "_salt_enterprise");
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(16) << h1 << std::setw(16) << h2;
    return oss.str();
}

bool HashManager::registerChecksum(const std::string& fileName, const std::string& checksum, long long fileSizeBytes, bool silent, const std::string& overrideTime) {
    if (fileName.empty() || checksum.empty()) {
        if (!silent) std::cout << "  [ERROR] File name and checksum cannot be empty.\n";
        return false;
    }
    if (checksumTable.count(checksum)) {
        duplicatesDetected++;
        if (!silent) {
            const ChecksumEntry& existing = checksumTable[checksum];
            std::cout << "  Duplicate document detected.\n";
            std::cout << "  File \"" << fileName << "\" matches existing file \"" << existing.fileName << "\".\n";
        }
        return false;
    }
    if (fileToChecksum.count(fileName)) {
        if (!silent) {
            std::cout << "  File \"" << fileName << "\" already has a registered checksum.\n";
        }
        return false;
    }
    
    std::string ts = overrideTime.empty() ? getCurrentTimestamp() : overrideTime;
    ChecksumEntry entry(fileName, checksum, fileSizeBytes, ts);
    checksumTable[checksum]    = entry;
    fileToChecksum[fileName]   = checksum;

    if (!silent) {
        std::cout << "  Checksum registered successfully:\n";
        std::cout << "  File: " << fileName << "\n";
    }
    return true;
}

bool HashManager::autoRegister(const std::string& fileName, long long fileSizeBytes, bool silent) {
    std::string cs = generateSimulatedChecksum(fileName, fileSizeBytes);
    if (!silent) std::cout << "  Generated Checksum: " << cs << "\n";
    return registerChecksum(fileName, cs, fileSizeBytes, silent);
}

bool HashManager::verifyChecksum(const std::string& checksum) const {
    bool found = (checksumTable.count(checksum) > 0);
    if (found) {
        std::cout << "  Document already exists in system.\n";
        std::cout << "  Checksum verified successfully.\n";
    } else {
        std::cout << "  Document is unique (not found in checksum registry).\n";
    }
    return found;
}

void HashManager::lookupByChecksum(const std::string& checksum) const {
    if (!checksumTable.count(checksum)) {
        std::cout << "  No registry entry found for checksum: " << checksum << "\n";
        return;
    }
    const ChecksumEntry& e = checksumTable.at(checksum);
    std::cout << "  Checksum Lookup Result:\n";
    std::cout << "  File      : " << e.fileName      << "\n";
    std::cout << "  Size      : " << e.fileSizeBytes << " bytes\n";
    std::cout << "  Registered: " << e.registeredAt  << "\n";
}

void HashManager::lookupByFileName(const std::string& fileName) const {
    if (!fileToChecksum.count(fileName)) {
        std::cout << "  No registry entry found for file: " << fileName << "\n";
        return;
    }
    lookupByChecksum(fileToChecksum.at(fileName));
}

bool HashManager::removeChecksum(const std::string& checksum, bool silent) {
    if (!checksumTable.count(checksum)) {
        if (!silent) std::cout << "  Checksum not found: " << checksum << "\n";
        return false;
    }
    const std::string& fname = checksumTable[checksum].fileName;
    fileToChecksum.erase(fname);
    checksumTable.erase(checksum);
    if (!silent) std::cout << "  Checksum removed for file: " << fname << "\n";
    return true;
}

void HashManager::displayAll() const {
    if (checksumTable.empty()) {
        std::cout << "  Checksum registry is empty.\n";
        return;
    }
    std::cout << "  Registered Checksums:\n\n";
    for (const auto& pair : checksumTable) {
        const ChecksumEntry& e = pair.second;
        std::cout << "  - File: " << e.fileName << "\n";
        std::cout << "    Checksum: " << e.checksum << "\n";
        std::cout << "    Size    : " << e.fileSizeBytes << " B\n\n";
    }
    std::cout << "  Duplicates detected: " << duplicatesDetected << "\n";
}

int HashManager::getTotalRegistered()    const { return (int)checksumTable.size(); }
int HashManager::getDuplicatesDetected() const { return duplicatesDetected; }

void HashManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    for (const auto& pair : checksumTable) {
        const ChecksumEntry& e = pair.second;
        outFile << e.fileName << "|" << e.checksum << "|" << e.fileSizeBytes << "|" << e.registeredAt << "\n";
    }
    outFile.close();
}

void HashManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string fname, cs, ssize, ts;
        std::getline(ss, fname, '|');
        std::getline(ss, cs, '|');
        std::getline(ss, ssize, '|');
        std::getline(ss, ts, '|');
        if (!fname.empty() && !cs.empty()) {
            registerChecksum(fname, cs, std::stoll(ssize), true, ts);
        }
    }
    inFile.close();
}

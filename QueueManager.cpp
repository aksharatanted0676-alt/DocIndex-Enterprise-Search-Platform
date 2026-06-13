// ============================================================
// QueueManager.cpp — Compute Line Module
// ============================================================

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

// ----------------------------------------------------------
// ScanJob
// ----------------------------------------------------------
struct ScanJob {
    int     jobId;
    std::string fileName;
    std::string jobType;
    int     priority;

    ScanJob(int id, const std::string& file,
            const std::string& type, int prio)
        : jobId(id), fileName(file), jobType(type), priority(prio) {}
};

// ----------------------------------------------------------
// QueueManager
// ----------------------------------------------------------
class QueueManager {
private:
    std::queue<ScanJob> jobQueue;
    std::vector<ScanJob> processedJobs;
    int nextJobId;

public:
    QueueManager();

    void addJob(const std::string& fileName, const std::string& jobType, int priority = 1, bool silent = false, int overrideId = -1);
    bool processNextJob(bool silent = false);
    void viewNextJob() const;
    void displayPendingJobs() const;
    void displayProcessedJobs() const;
    int getPendingCount() const;
    int getProcessedCount() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

// ============================================================
// Implementation
// ============================================================

QueueManager::QueueManager() : nextJobId(1001) {}

void QueueManager::addJob(const std::string& fileName, const std::string& jobType, int priority, bool silent, int overrideId) {
    if (fileName.empty()) {
        if (!silent) std::cout << "  [ERROR] File name cannot be empty.\n";
        return;
    }
    int safePriority = (priority < 1) ? 1 : (priority > 5) ? 5 : priority;
    
    int id = (overrideId != -1) ? overrideId : nextJobId++;
    ScanJob job(id, fileName, jobType, safePriority);
    jobQueue.push(job);

    if (!silent) {
        std::cout << "  Job added to queue:\n";
        std::cout << "  File: " << job.fileName << " (" << job.jobType << ")\n";
    }
}

bool QueueManager::processNextJob(bool silent) {
    if (jobQueue.empty()) {
        if (!silent) std::cout << "  [INFO] Compute Line is empty — no pending jobs.\n";
        return false;
    }
    ScanJob job = jobQueue.front();
    jobQueue.pop();
    processedJobs.push_back(job);

    if (!silent) {
        std::cout << "  Processing document:\n";
        std::cout << "  " << job.fileName << "\n\n";
        std::cout << "  Processing completed.\n";
    }
    return true;
}

void QueueManager::viewNextJob() const {
    if (jobQueue.empty()) {
        std::cout << "  Compute Line is empty.\n";
        return;
    }
    const ScanJob& job = jobQueue.front();
    std::cout << "  Next Pending Job:\n";
    std::cout << "  File     : " << job.fileName << "\n";
    std::cout << "  Type     : " << job.jobType << "\n";
    std::cout << "  Priority : " << job.priority << "/5\n";
}

void QueueManager::displayPendingJobs() const {
    if (jobQueue.empty()) {
        std::cout << "  No pending jobs in Compute Line.\n";
        return;
    }
    std::queue<ScanJob> temp = jobQueue;
    int pos = 1;
    std::cout << "  Pending Scan Jobs:\n\n";
    while (!temp.empty()) {
        const ScanJob j = temp.front();
        temp.pop();
        std::cout << "  " << pos++ << ". " << j.fileName << " [" << j.jobType << "] (Priority: " << j.priority << "/5)\n";
    }
}

void QueueManager::displayProcessedJobs() const {
    if (processedJobs.empty()) {
        std::cout << "  No jobs have been processed yet.\n";
        return;
    }
    std::cout << "  Completed Scan Jobs:\n\n";
    for (int i = 0; i < (int)processedJobs.size(); i++) {
        const ScanJob& j = processedJobs[i];
        std::cout << "  " << (i + 1) << ". " << j.fileName << " [" << j.jobType << "] - Completed\n";
    }
}

int QueueManager::getPendingCount()   const { return (int)jobQueue.size(); }
int QueueManager::getProcessedCount() const { return (int)processedJobs.size(); }

void QueueManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    
    std::queue<ScanJob> temp = jobQueue;
    while (!temp.empty()) {
        const ScanJob& j = temp.front();
        outFile << "PENDING|" << j.jobId << "|" << j.fileName << "|" << j.jobType << "|" << j.priority << "\n";
        temp.pop();
    }
    for (const auto& j : processedJobs) {
        outFile << "PROCESSED|" << j.jobId << "|" << j.fileName << "|" << j.jobType << "|" << j.priority << "\n";
    }
    outFile << "NEXTID|" << nextJobId << "\n";
    outFile.close();
}

void QueueManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string tag;
        std::getline(ss, tag, '|');
        
        if (tag == "PENDING" || tag == "PROCESSED") {
            std::string sid, file, type, sprio;
            std::getline(ss, sid, '|');
            std::getline(ss, file, '|');
            std::getline(ss, type, '|');
            std::getline(ss, sprio, '|');
            
            ScanJob j(std::stoi(sid), file, type, std::stoi(sprio));
            if (tag == "PENDING") {
                jobQueue.push(j);
            } else {
                processedJobs.push_back(j);
            }
        } else if (tag == "NEXTID") {
            std::string nxt;
            std::getline(ss, nxt);
            nextJobId = std::stoi(nxt);
        }
    }
    inFile.close();
}

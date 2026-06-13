// ============================================================
// HeapManager.cpp — Hit Sorter & Compression Balancer Modules
// ============================================================

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

// ===========================================================
// ---- MODULE A : HIT SORTER --------------------------------
// ===========================================================

struct SearchResult {
    std::string docName;
    int         hitCount;
    std::string snippet;

    SearchResult(const std::string& name, int hits, const std::string& snip)
        : docName(name), hitCount(hits), snippet(snip) {}

    bool operator<(const SearchResult& other) const {
        return hitCount < other.hitCount;
    }
};

class HitSorter {
private:
    std::priority_queue<SearchResult> resultHeap;
    int totalAdded;

public:
    HitSorter();

    void addResult(const std::string& docName, int hitCount, const std::string& snippet = "", bool silent = false);
    void displayRankedResults() const;
    bool getTopResult(bool silent = false);

    int getTotalAdded() const;
    int getCurrentSize() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

HitSorter::HitSorter() : totalAdded(0) {}

void HitSorter::addResult(const std::string& docName, int hitCount, const std::string& snippet, bool silent) {
    if (docName.empty()) {
        if (!silent) std::cout << "  [ERROR] Document name cannot be empty.\n";
        return;
    }
    if (hitCount < 0) {
        if (!silent) std::cout << "  [ERROR] Hit count cannot be negative.\n";
        return;
    }
    SearchResult result(docName, hitCount, snippet);
    resultHeap.push(result);
    totalAdded++;
    if (!silent) {
        std::cout << "  Result added to Hit Sorter:\n";
        std::cout << "  Document : " << docName << " (" << hitCount << " hits)\n";
    }
}

void HitSorter::displayRankedResults() const {
    if (resultHeap.empty()) {
        std::cout << "  No search results in Hit Sorter.\n";
        return;
    }
    std::priority_queue<SearchResult> temp = resultHeap;
    int rank = 1;

    std::cout << "  Most Relevant Documents:\n\n";
    while (!temp.empty()) {
        const SearchResult& r = temp.top();
        std::cout << "  " << rank++ << ". " << r.docName << " (" << r.hitCount << " keyword matches)\n";
        if (!r.snippet.empty()) {
            std::cout << "     Snippet: \"" << r.snippet << "\"\n";
        }
        temp.pop();
    }
}

bool HitSorter::getTopResult(bool silent) {
    if (resultHeap.empty()) {
        if (!silent) std::cout << "  Hit Sorter is empty.\n";
        return false;
    }
    const SearchResult& top = resultHeap.top();
    if (!silent) {
        std::cout << "  Top-ranked document retrieved:\n";
        std::cout << "  " << top.docName << " (" << top.hitCount << " hits)\n";
    }
    resultHeap.pop();
    return true;
}

int HitSorter::getTotalAdded()   const { return totalAdded; }
int HitSorter::getCurrentSize()  const { return (int)resultHeap.size(); }

void HitSorter::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    std::priority_queue<SearchResult> temp = resultHeap;
    while (!temp.empty()) {
        const SearchResult& r = temp.top();
        outFile << r.docName << "|" << r.hitCount << "|" << r.snippet << "\n";
        temp.pop();
    }
    outFile.close();
}

void HitSorter::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string doc, shits, snip;
        std::getline(ss, doc, '|');
        std::getline(ss, shits, '|');
        std::getline(ss, snip, '|'); // snippet might contain spaces, read until | or end
        if (!doc.empty() && !shits.empty()) {
            addResult(doc, std::stoi(shits), snip, true);
        }
    }
    inFile.close();
}

// ===========================================================
// ---- MODULE B : COMPRESSION BALANCER ---------------------
// ===========================================================

struct DataBlock {
    std::string blockName;
    long long   sizeBytes;
    double      compressionScore;
    double      estimatedRatio;

    DataBlock(const std::string& name, long long size,
              double score, double ratio)
        : blockName(name), sizeBytes(size),
          compressionScore(score), estimatedRatio(ratio) {}

    bool operator<(const DataBlock& other) const {
        return compressionScore < other.compressionScore;
    }
};

class CompressionBalancer {
private:
    std::priority_queue<DataBlock> blockHeap;
    int totalAdded;
    long long totalBytesManaged;

public:
    CompressionBalancer();

    void addBlock(const std::string& blockName, long long sizeBytes, double compressionScore, double estimatedRatio = 0.5, bool silent = false);
    void displayCompressionQueue() const;
    bool compressTopBlock(bool silent = false);

    int getTotalAdded()        const;
    int getCurrentQueueSize()  const;
    long long getTotalBytes()  const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

CompressionBalancer::CompressionBalancer() : totalAdded(0), totalBytesManaged(0) {}

void CompressionBalancer::addBlock(const std::string& blockName, long long sizeBytes, double compressionScore, double estimatedRatio, bool silent) {
    if (blockName.empty()) {
        if (!silent) std::cout << "  [ERROR] Block name cannot be empty.\n";
        return;
    }
    if (sizeBytes <= 0) {
        if (!silent) std::cout << "  [ERROR] Block size must be positive.\n";
        return;
    }
    if (compressionScore < 0.0) {
        if (!silent) std::cout << "  [ERROR] Compression score cannot be negative.\n";
        return;
    }

    DataBlock block(blockName, sizeBytes, compressionScore, estimatedRatio);
    blockHeap.push(block);
    totalAdded++;
    totalBytesManaged += sizeBytes;

    if (!silent) {
        long long savings = (long long)(sizeBytes * (1.0 - estimatedRatio));
        long long savingsMB = (savings + 524288) / (1024 * 1024);
        std::cout << "  Block added to compression balancer:\n";
        std::cout << "  " << blockName << " (Potential saving: " << savingsMB << " MB)\n";
    }
}

void CompressionBalancer::displayCompressionQueue() const {
    if (blockHeap.empty()) {
        std::cout << "  Compression queue is empty.\n";
        return;
    }

    std::priority_queue<DataBlock> temp = blockHeap;
    int rank = 1;

    std::cout << "  Compression Priority List:\n\n";
    while (!temp.empty()) {
        const DataBlock& b = temp.top();
        long long savings = (long long)(b.sizeBytes * (1.0 - b.estimatedRatio));
        long long savingsMB = (savings + 524288) / (1024 * 1024);
        std::cout << "  " << rank++ << ". " << b.blockName << "\n";
        std::cout << "     Potential Saving: " << savingsMB << " MB\n\n";
        temp.pop();
    }
}

bool CompressionBalancer::compressTopBlock(bool silent) {
    if (blockHeap.empty()) {
        if (!silent) std::cout << "  No blocks in compression queue.\n";
        return false;
    }
    const DataBlock& top = blockHeap.top();
    if (!silent) {
        long long savings = (long long)(top.sizeBytes * (1.0 - top.estimatedRatio));
        long long savingsMB = (savings + 524288) / (1024 * 1024);
        std::cout << "  Compressing top-priority block:\n";
        std::cout << "  Block Name: " << top.blockName << "\n";
        std::cout << "  Potential Saving: " << savingsMB << " MB\n\n";
        std::cout << "  Compression completed successfully.\n";
    }
    blockHeap.pop();
    return true;
}

int       CompressionBalancer::getTotalAdded()       const { return totalAdded; }
int       CompressionBalancer::getCurrentQueueSize() const { return (int)blockHeap.size(); }
long long CompressionBalancer::getTotalBytes()       const { return totalBytesManaged; }

void CompressionBalancer::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    std::priority_queue<DataBlock> temp = blockHeap;
    while (!temp.empty()) {
        const DataBlock& b = temp.top();
        outFile << b.blockName << "|" << b.sizeBytes << "|" << b.compressionScore << "|" << b.estimatedRatio << "\n";
        temp.pop();
    }
    outFile.close();
}

void CompressionBalancer::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string bname, ssize, sscore, sratio;
        std::getline(ss, bname, '|');
        std::getline(ss, ssize, '|');
        std::getline(ss, sscore, '|');
        std::getline(ss, sratio, '|');
        if (!bname.empty() && !ssize.empty()) {
            addBlock(bname, std::stoll(ssize), std::stod(sscore), std::stod(sratio), true);
        }
    }
    inFile.close();
}

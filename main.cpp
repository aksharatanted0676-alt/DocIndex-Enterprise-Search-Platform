// ============================================================
// main.cpp — Enterprise Search Engine Documentation Hub
// ============================================================

// ---- Standard library includes ---------------------------
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <ctime>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

// ============================================================
// ---- CLASS & STRUCT DECLARATIONS (no .h files needed) -----
// ============================================================

// ----------------------------------------------------------
// MODULE 1 — Trie (Naming Registry)
// ----------------------------------------------------------
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
    int totalNames;
    void collectWords(TrieNode* node, const std::string& prefix,
                      std::vector<std::string>& results) const;
    bool deleteHelper(TrieNode* node, const std::string& word, int depth);
public:
    Trie();
    ~Trie();
    void insert(const std::string& name, bool silent = false);
    bool search(const std::string& name) const;
    bool remove(const std::string& name, bool silent = false);
    std::vector<std::string> autocomplete(const std::string& prefix) const;
    int getTotalNames() const;
    void displayAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

// ----------------------------------------------------------
// MODULE 2 — Stack (Correction Trail)
// ----------------------------------------------------------
struct ConfigChange {
    std::string changeType;
    std::string description;
    std::string timestamp;
    ConfigChange(const std::string& type, const std::string& desc,
                 const std::string& ts)
        : changeType(type), description(desc), timestamp(ts) {}
};

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

// ----------------------------------------------------------
// MODULE 3 — Queue (Compute Line)
// ----------------------------------------------------------
struct ScanJob {
    int jobId;
    std::string fileName;
    std::string jobType;
    int priority;
    ScanJob(int id, const std::string& file,
            const std::string& type, int prio)
        : jobId(id), fileName(file), jobType(type), priority(prio) {}
};

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

// ----------------------------------------------------------
// MODULE 4 — Hash Table (Checksum Lookup)
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

class HashManager {
private:
    std::unordered_map<std::string, ChecksumEntry> checksumTable;
    std::unordered_map<std::string, std::string>   fileToChecksum;
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

// ----------------------------------------------------------
// MODULE 5 — Max Heap (Hit Sorter)
// ----------------------------------------------------------
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

// ----------------------------------------------------------
// MODULE 8 — Max Heap (Compression Balancer)
// ----------------------------------------------------------
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

// ----------------------------------------------------------
// MODULE 6 & 7 — Directed Graph (Citation Map + BFS)
// ----------------------------------------------------------
class GraphManager {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> adjList;
    std::unordered_map<std::string, std::string> docDescriptions;
    bool docExists(const std::string& docName) const;
public:
    GraphManager();
    void addDocument(const std::string& docName, const std::string& description = "", bool silent = false);
    bool addCitation(const std::string& fromDoc, const std::string& toDoc, bool silent = false);
    bool removeCitation(const std::string& fromDoc, const std::string& toDoc, bool silent = false);
    void displayCitationMap() const;
    void displayOutgoingCitations(const std::string& docName) const;
    void displayIncomingCitations(const std::string& docName) const;
    std::vector<std::string> bfsShortestPath(const std::string& source, const std::string& target) const;
    void displayShortestPath(const std::string& source, const std::string& target) const;
    int getDocumentCount()  const;
    int getCitationCount()  const;
    void traverseDFS(const std::string& startNode) const;
    void traverseDFSIterative(const std::string& startNode) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

// ============================================================
// Helper: display a decorative section banner
// ============================================================
static void printBanner(const std::string& title) {
    int width = 54;
    std::string border(width, '=');
    int padding = (width - (int)title.size() - 2) / 2;
    std::cout << "\n  " << border << "\n";
    std::cout << "  |" << std::string(padding, ' ')
              << title
              << std::string(width - padding - (int)title.size() - 2, ' ')
              << "|\n";
    std::cout << "  " << border << "\n";
}

// ============================================================
// Helper: clear cin state and discard bad input
// ============================================================
static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ============================================================
// Helper: trim leading/trailing whitespace from a string
// ============================================================
static std::string trim(const std::string& s) {
    int start = 0, end = (int)s.size() - 1;
    while (start <= end && std::isspace((unsigned char)s[start])) start++;
    while (end >= start && std::isspace((unsigned char)s[end]))   end--;
    return (start <= end) ? s.substr(start, end - start + 1) : "";
}

// ============================================================
// Helper: safe integer read with validation
// ============================================================
static int readInt(const std::string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= minVal && val <= maxVal) {
            clearInput();
            return val;
        }
        std::cout << "  [ERROR] Please enter a number between "
                  << minVal << " and " << maxVal << ".\n";
        clearInput();
    }
}

// ============================================================
// Helper: read a non-empty line of text
// ============================================================
static std::string readLine(const std::string& prompt) {
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        line = trim(line);
        if (!line.empty()) return line;
        std::cout << "  [ERROR] Input cannot be empty. Try again.\n";
    }
}

// ============================================================
// MODULE 1 — Naming Registry sub-menu
// ============================================================
static void menuNamingRegistry(Trie& trie) {
    while (true) {
        printBanner("Naming Registry  [Trie]");
        std::cout << "\n  1. Add file name\n"
                     "  2. Delete file name\n"
                     "  3. Search exact file name\n"
                     "  4. Prefix search / Autocomplete\n"
                     "  5. Display all names\n"
                     "  0. Back to main menu\n";
        int choice = readInt("\n  Enter choice: ", 0, 5);

        if (choice == 0) break;

        std::string input;
        switch (choice) {
        case 1:
            input = readLine("  Enter file name to add: ");
            trie.insert(input);
            trie.saveToFile("data/files.txt");
            break;
        case 2:
            input = readLine("  Enter file name to delete: ");
            if (trie.remove(input)) {
                trie.saveToFile("data/files.txt");
            }
            break;
        case 3:
            input = readLine("  Enter exact file name to search: ");
            if (trie.search(input))
                std::cout << "  [FOUND] \"" << input << "\" exists in registry.\n";
            else
                std::cout << "  [NOT FOUND] \"" << input << "\" is not in registry.\n";
            break;
        case 4: {
            input = readLine("  Enter prefix for autocomplete: ");
            std::vector<std::string> results = trie.autocomplete(input);
            if (results.empty()) {
                std::cout << "  [INFO] No names found with prefix \"" << input << "\".\n";
            } else {
                std::cout << "  Autocomplete results (" << results.size() << "):\n";
                for (int i = 0; i < (int)results.size(); i++)
                    std::cout << "    " << (i+1) << ". " << results[i] << "\n";
            }
            break;
        }
        case 5:
            trie.displayAll();
            break;
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 2 — Correction Trail sub-menu
// ============================================================
static void menuCorrectionTrail(StackManager& stack) {
    while (true) {
        printBanner("Correction Trail  [Stack]");
        std::cout << "\n  1. Add configuration change\n"
                     "  2. Undo last change\n"
                     "  3. View top (latest) change\n"
                     "  4. View full change history\n"
                     "  0. Back to main menu\n";
        int choice = readInt("\n  Enter choice: ", 0, 4);

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            std::string type = readLine("  Enter change type (e.g. INDEX_UPDATE): ");
            std::string desc = readLine("  Enter description: ");
            stack.addChange(type, desc);
            stack.saveToFile("data/config_history.txt");
            break;
        }
        case 2:
            if (stack.undoLastChange()) {
                stack.saveToFile("data/config_history.txt");
            }
            break;
        case 3:
            stack.viewTopChange();
            break;
        case 4:
            stack.displayHistory();
            break;
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 3 — Compute Line sub-menu
// ============================================================
static void menuComputeLine(QueueManager& queue) {
    while (true) {
        printBanner("Compute Line  [Queue]");
        std::cout << "\n  1. Add scan job\n"
                     "  2. Process next job\n"
                     "  3. View next pending job\n"
                     "  4. View all pending jobs\n"
                     "  5. View processed jobs\n"
                     "  0. Back to main menu\n";
        int choice = readInt("\n  Enter choice: ", 0, 5);

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            std::string file = readLine("  Enter file name: ");
            std::cout << "  Job types: FULL_SCAN | INDEX | CHECKSUM | METADATA\n";
            std::string type = readLine("  Enter job type: ");
            std::transform(type.begin(), type.end(), type.begin(), ::toupper);
            int prio = readInt("  Enter priority (1-5): ", 1, 5);
            queue.addJob(file, type, prio);
            queue.saveToFile("data/compute_line.txt");
            break;
        }
        case 2:
            if (queue.processNextJob()) {
                queue.saveToFile("data/compute_line.txt");
            }
            break;
        case 3:
            queue.viewNextJob();
            break;
        case 4:
            queue.displayPendingJobs();
            break;
        case 5:
            queue.displayProcessedJobs();
            break;
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 4 — Checksum Lookup sub-menu
// ============================================================
static void menuChecksumLookup(HashManager& hash) {
    while (true) {
        printBanner("Checksum Lookup  [Hash Table]");
        std::cout << "\n  1. Register file checksum (manual)\n"
                     "  2. Auto-generate & register checksum\n"
                     "  3. Verify if checksum exists\n"
                     "  4. Lookup by checksum\n"
                     "  5. Lookup by file name\n"
                     "  6. Remove a checksum\n"
                     "  7. Display all checksums\n"
                     "  0. Back to main menu\n";
        int choice = readInt("\n  Enter choice: ", 0, 7);

        if (choice == 0) break;

        std::string input;
        switch (choice) {
        case 1: {
            std::string fname = readLine("  Enter file name: ");
            std::string cs    = readLine("  Enter checksum (hex string): ");
            int size = readInt("  Enter file size in bytes: ", 1, 2000000000);
            if (hash.registerChecksum(fname, cs, (long long)size)) {
                hash.saveToFile("data/checksums.txt");
            }
            break;
        }
        case 2: {
            std::string fname = readLine("  Enter file name: ");
            int size = readInt("  Enter file size in bytes: ", 1, 2000000000);
            if (hash.autoRegister(fname, (long long)size)) {
                hash.saveToFile("data/checksums.txt");
            }
            break;
        }
        case 3:
            input = readLine("  Enter checksum to verify: ");
            hash.verifyChecksum(input);
            break;
        case 4:
            input = readLine("  Enter checksum to lookup: ");
            hash.lookupByChecksum(input);
            break;
        case 5:
            input = readLine("  Enter file name to lookup: ");
            hash.lookupByFileName(input);
            break;
        case 6:
            input = readLine("  Enter checksum to remove: ");
            if (hash.removeChecksum(input)) {
                hash.saveToFile("data/checksums.txt");
            }
            break;
        case 7:
            hash.displayAll();
            break;
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 5 — Hit Sorter sub-menu
// ============================================================
static void menuHitSorter(HitSorter& hitSorter) {
    while (true) {
        printBanner("Hit Sorter  [Max Heap]");
        std::cout << "\n  1. Add document result with hit count\n"
                     "  2. Display results (highest hits first)\n"
                     "  3. Pop top-ranked result\n"
                     "  0. Back to main menu\n";
        int choice = readInt("\n  Enter choice: ", 0, 3);

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            std::string doc  = readLine("  Enter document name: ");
            int hits = readInt("  Enter keyword hit count: ", 0, 1000000);
            std::cout << "  Enter short snippet (or press ENTER to skip): ";
            std::string snip;
            std::getline(std::cin, snip);
            hitSorter.addResult(doc, hits, trim(snip));
            hitSorter.saveToFile("data/hits.txt");
            break;
        }
        case 2:
            hitSorter.displayRankedResults();
            break;
        case 3:
            if (hitSorter.getTopResult()) {
                hitSorter.saveToFile("data/hits.txt");
            }
            break;
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 6 — Citation Map sub-menu
// ============================================================
static void menuCitationMap(GraphManager& graph) {
    while (true) {
        printBanner("Citation Map  [Directed Graph]");
        std::cout << "\n  1. Add document node\n"
                     "  2. Add citation (edge)\n"
                     "  3. Remove citation (edge)\n"
                     "  4. Display full citation map\n"
                     "  5. View outgoing citations for a document\n"
                     "  6. View incoming citations for a document\n"
                     "  0. Back to main menu\n";
        int choice = readInt("\n  Enter choice: ", 0, 6);

        if (choice == 0) break;

        std::string a, b;
        switch (choice) {
        case 1: {
            a = readLine("  Enter document name: ");
            std::cout << "  Enter description (or ENTER to skip): ";
            std::string desc;
            std::getline(std::cin, desc);
            graph.addDocument(a, trim(desc));
            graph.saveToFile("data/citations.txt");
            break;
        }
        case 2:
            a = readLine("  Enter citing document (source): ");
            b = readLine("  Enter cited document (target): ");
            if (graph.addCitation(a, b)) {
                graph.saveToFile("data/citations.txt");
            }
            break;
        case 3:
            a = readLine("  Enter citing document (source): ");
            b = readLine("  Enter cited document to remove: ");
            if (graph.removeCitation(a, b)) {
                graph.saveToFile("data/citations.txt");
            }
            break;
        case 4:
            graph.displayCitationMap();
            break;
        case 5:
            a = readLine("  Enter document name: ");
            graph.displayOutgoingCitations(a);
            break;
        case 6:
            a = readLine("  Enter document name: ");
            graph.displayIncomingCitations(a);
            break;
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 7 — Validation & Traversal sub-menu (BFS/DFS)
// ============================================================
static void menuValidationPath(GraphManager& graph) {
    while (true) {
        printBanner("Validation & Traversal");
        std::cout << "\n  1. View Citation Map\n"
                     "  2. Find Shortest Citation Path (BFS)\n"
                     "  3. Traverse Citation Network (DFS)\n"
                     "  4. Back\n";
        int choice = readInt("\n  Enter choice: ", 1, 4);

        if (choice == 4) break;

        switch (choice) {
        case 1:
            graph.displayCitationMap();
            break;
        case 2: {
            std::string src = readLine("  Enter source document: ");
            std::string tgt = readLine("  Enter target document: ");
            graph.displayShortestPath(src, tgt);
            break;
        }
        case 3: {
            std::string start = readLine("  Enter starting document: ");
            std::cout << "\n  DFS Traversal Mode:\n";
            std::cout << "  1. Recursive DFS\n";
            std::cout << "  2. Iterative DFS (using Stack)\n";
            int dfsChoice = readInt("\n  Enter choice (1-2): ", 1, 2);
            if (dfsChoice == 1) {
                graph.traverseDFS(start);
            } else {
                graph.traverseDFSIterative(start);
            }
            break;
        }
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 8 — Compression Balancer sub-menu
// ============================================================
static void menuCompressionBalancer(CompressionBalancer& compressor) {
    while (true) {
        printBanner("Compression Balancer  [Max Heap]");
        std::cout << "\n  1. Add data block\n"
                     "  2. View compression queue (by priority)\n"
                     "  3. Compress top-priority block\n"
                     "  0. Back to main menu\n";
        int choice = readInt("\n  Enter choice: ", 0, 3);

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            std::string name = readLine("  Enter block name: ");
            int size  = readInt("  Enter block size in bytes: ", 1, 2000000000);
            std::cout << "  Enter compression score (0.0 - 10.0): ";
            double score;
            std::cin >> score;
            clearInput();
            if (score < 0.0) score = 0.0;
            if (score > 10.0) score = 10.0;
            std::cout << "  Enter estimated compression ratio (0.0 - 1.0): ";
            double ratio;
            std::cin >> ratio;
            clearInput();
            if (ratio < 0.01) ratio = 0.01;
            if (ratio > 0.99) ratio = 0.99;
            compressor.addBlock(name, (long long)size, score, ratio);
            compressor.saveToFile("data/compression.txt");
            break;
        }
        case 2:
            compressor.displayCompressionQueue();
            break;
        case 3:
            if (compressor.compressTopBlock()) {
                compressor.saveToFile("data/compression.txt");
            }
            break;
        }
        std::cout << "\n  Press ENTER to continue...";
        clearInput();
    }
}

// ============================================================
// MODULE 9 — Display Statistics
// ============================================================
static void displayStatistics(const Trie& trie,
                               const StackManager& stack,
                               const QueueManager& queue,
                               const HashManager& hash,
                               const HitSorter& hitSorter,
                               const CompressionBalancer& compressor,
                               const GraphManager& graph) {
    printBanner("Enterprise Hub — Statistics");

    std::cout << "\n  " << std::string(52, '-') << "\n";
    std::cout << "  " << std::left
              << std::setw(32) << "Module"
              << std::setw(10) << "Count"
              << "Data Structure\n";
    std::cout << "  " << std::string(52, '-') << "\n";

    auto row = [](const std::string& mod, int cnt, const std::string& ds) {
        std::cout << "  " << std::left
                  << std::setw(32) << mod
                  << std::setw(10) << cnt
                  << ds << "\n";
    };

    row("Naming Registry",          trie.getTotalNames(),            "Trie");
    row("Correction Trail (total)", stack.getTotalPushed(),          "Stack (LIFO)");
    row("Correction Trail (active)",stack.getPendingCount(),         "Stack (LIFO)");
    row("Compute Line (pending)",   queue.getPendingCount(),         "Queue (FIFO)");
    row("Compute Line (processed)", queue.getProcessedCount(),       "Queue (FIFO)");
    row("Checksum Registry",        hash.getTotalRegistered(),       "Hash Table");
    row("Duplicates Detected",      hash.getDuplicatesDetected(),    "Hash Table");
    row("Hit Sorter (results)",     hitSorter.getCurrentSize(),      "Max Heap");
    row("Citation Documents",       graph.getDocumentCount(),        "Adj-List Graph");
    row("Citations (edges)",        graph.getCitationCount(),        "Adj-List Graph");
    row("Compression Queue",        compressor.getCurrentQueueSize(),"Max Heap");

    std::cout << "  " << std::string(52, '-') << "\n";
    std::cout << "\n  Total bytes under compression management: "
              << compressor.getTotalBytes() << " bytes\n";

    std::cout << "\n  Data Structure Summary:\n";
    std::cout << "  Trie        — O(L) insert/search/delete, O(P+K) prefix search\n";
    std::cout << "  Stack       — O(1) push/pop/peek operations\n";
    std::cout << "  Queue       — O(1) enqueue/dequeue operations\n";
    std::cout << "  Hash Table  — O(1) average insert/search/delete\n";
    std::cout << "  Max Heap    — O(log N) insert/extract, O(1) peek\n";
    std::cout << "  Graph (BFS) — O(V+E) traversal and shortest path\n";
}

// ============================================================
// printMainMenu: Display the top-level menu
// ============================================================
static void printMainMenu() {
    std::cout << "\n";
    std::cout << "  ==========================================\n";
    std::cout << "     Enterprise Search Engine Hub v1.0\n";
    std::cout << "  ==========================================\n";
    std::cout << "\n";
    std::cout << "    1.  Naming Registry        [Trie]\n";
    std::cout << "    2.  Correction Trail        [Stack]\n";
    std::cout << "    3.  Compute Line            [Queue]\n";
    std::cout << "    4.  Checksum Lookup         [Hash Table]\n";
    std::cout << "    5.  Hit Sorter              [Max Heap]\n";
    std::cout << "    6.  Citation Map            [Graph]\n";
    std::cout << "    7.  Validation Path & DFS   [BFS/DFS]\n";
    std::cout << "    8.  Compression Balancer    [Max Heap]\n";
    std::cout << "    9.  Display Statistics\n";
    std::cout << "    0.  Exit\n";
    std::cout << "\n  ==========================================\n";
}

// ============================================================
// main: Application entry point
// ============================================================
int main() {
    // Instantiate all modules
    Trie                trie;
    StackManager        stack;
    QueueManager        queue;
    HashManager         hash;
    HitSorter           hitSorter;
    CompressionBalancer compressor;
    GraphManager        graph;

    // Ensure data directory exists
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0777);
    }

    // Load persisted data silently
    trie.loadFromFile("data/files.txt");
    stack.loadFromFile("data/config_history.txt");
    queue.loadFromFile("data/compute_line.txt");
    hash.loadFromFile("data/checksums.txt");
    hitSorter.loadFromFile("data/hits.txt");
    compressor.loadFromFile("data/compression.txt");
    graph.loadFromFile("data/citations.txt");

    std::cout << "Enterprise Search Engine Hub - Ready\n";

    // Main event loop
    bool running = true;
    while (running) {
        printMainMenu();
        int choice = readInt("  Enter choice: ", 0, 9);

        switch (choice) {
        case 1:  menuNamingRegistry(trie);                                   break;
        case 2:  menuCorrectionTrail(stack);                                  break;
        case 3:  menuComputeLine(queue);                                       break;
        case 4:  menuChecksumLookup(hash);                                     break;
        case 5:  menuHitSorter(hitSorter);                                     break;
        case 6:  menuCitationMap(graph);                                       break;
        case 7:  menuValidationPath(graph);                                    break;
        case 8:  menuCompressionBalancer(compressor);                          break;
        case 9:
            displayStatistics(trie, stack, queue, hash,
                              hitSorter, compressor, graph);
            std::cout << "\n  Press ENTER to continue...";
            clearInput();
            break;
        case 0:
            std::cout << "\n  ==========================================\n";
            std::cout << "    Thank you for using Enterprise Hub!\n";
            std::cout << "    Goodbye.\n";
            std::cout << "  ==========================================\n\n";
            running = false;
            break;
        }
    }
    return 0;
}

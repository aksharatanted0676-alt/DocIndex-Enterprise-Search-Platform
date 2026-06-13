// ============================================================
// GraphManager.cpp — Citation Map & Validation Path Modules
// ============================================================

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

// ----------------------------------------------------------
// GraphManager
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
private:
    void dfsHelper(const std::string& node, std::unordered_set<std::string>& visited, int& order) const;
};

// ============================================================
// Implementation
// ============================================================

GraphManager::GraphManager() {}

bool GraphManager::docExists(const std::string& docName) const {
    return adjList.count(docName) > 0;
}

void GraphManager::addDocument(const std::string& docName, const std::string& description, bool silent) {
    if (docName.empty()) {
        if (!silent) std::cout << "  [ERROR] Document name cannot be empty.\n";
        return;
    }
    if (docExists(docName)) {
        if (!silent) std::cout << "  [INFO] Document \"" << docName << "\" already in graph.\n";
        return;
    }
    adjList[docName] = std::unordered_set<std::string>();
    docDescriptions[docName] = description.empty() ? "No description" : description;

    if (!silent) {
        std::cout << "  Document added successfully:\n";
        std::cout << "  " << docName << "\n";
    }
}

bool GraphManager::addCitation(const std::string& fromDoc, const std::string& toDoc, bool silent) {
    if (fromDoc == toDoc) {
        if (!silent) std::cout << "  [ERROR] A document cannot cite itself.\n";
        return false;
    }
    if (!docExists(fromDoc)) {
        if (!silent) std::cout << "  [INFO] Auto-creating node: \"" << fromDoc << "\"\n";
        addDocument(fromDoc, "", silent);
    }
    if (!docExists(toDoc)) {
        if (!silent) std::cout << "  [INFO] Auto-creating node: \"" << toDoc << "\"\n";
        addDocument(toDoc, "", silent);
    }
    if (adjList[fromDoc].count(toDoc)) {
        if (!silent) std::cout << "  [INFO] Citation \"" << fromDoc << "\" -> \"" << toDoc << "\" already exists.\n";
        return false;
    }
    adjList[fromDoc].insert(toDoc);
    if (!silent) std::cout << "  Citation added:\n  " << fromDoc << " -> " << toDoc << "\n";
    return true;
}

bool GraphManager::removeCitation(const std::string& fromDoc, const std::string& toDoc, bool silent) {
    if (!docExists(fromDoc) || !adjList[fromDoc].count(toDoc)) {
        if (!silent) std::cout << "  [ERROR] Citation not found: \"" << fromDoc << "\" -> \"" << toDoc << "\"\n";
        return false;
    }
    adjList[fromDoc].erase(toDoc);
    if (!silent) std::cout << "  [OK] Citation removed: \"" << fromDoc << "\" -> \"" << toDoc << "\"\n";
    return true;
}

void GraphManager::displayCitationMap() const {
    if (adjList.empty()) {
        std::cout << "  [INFO] Citation map is empty.\n";
        return;
    }
    std::vector<std::string> docs;
    for (const auto& pair : adjList) docs.push_back(pair.first);
    std::sort(docs.begin(), docs.end());

    std::cout << "  ===== Citation Network =====\n\n";
    for (const std::string& doc : docs) {
        const auto& citations = adjList.at(doc);
        std::vector<std::string> sortedCites(citations.begin(), citations.end());
        std::sort(sortedCites.begin(), sortedCites.end());

        std::cout << "  Document: " << doc << "\n";
        if (sortedCites.empty()) {
            std::cout << "  References: None\n\n";
        } else {
            std::cout << "  References:\n";
            for (const std::string& cited : sortedCites) {
                std::cout << "  -> " << cited << "\n";
            }
            std::cout << "\n";
        }
    }
}

void GraphManager::displayOutgoingCitations(const std::string& docName) const {
    if (!docExists(docName)) {
        std::cout << "  [ERROR] Document \"" << docName << "\" not in graph.\n";
        return;
    }
    const auto& citations = adjList.at(docName);
    std::cout << "  Documents cited by \"" << docName << "\" (" << citations.size() << "):\n";
    if (citations.empty()) {
        std::cout << "    (none)\n";
        return;
    }
    for (const std::string& c : citations) std::cout << "    --> " << c << "\n";
}

void GraphManager::displayIncomingCitations(const std::string& docName) const {
    if (!docExists(docName)) {
        std::cout << "  [ERROR] Document \"" << docName << "\" not in graph.\n";
        return;
    }
    std::vector<std::string> incomers;
    for (const auto& pair : adjList) {
        if (pair.second.count(docName)) incomers.push_back(pair.first);
    }
    std::sort(incomers.begin(), incomers.end());
    std::cout << "  Documents citing \"" << docName << "\" (" << incomers.size() << "):\n";
    if (incomers.empty()) {
        std::cout << "    (none)\n";
        return;
    }
    for (const std::string& inc : incomers) std::cout << "    <-- " << inc << "\n";
}

std::vector<std::string> GraphManager::bfsShortestPath(const std::string& source, const std::string& target) const {
    if (!docExists(source) || !docExists(target)) return {};
    if (source == target) return {source};

    std::queue<std::string> bfsQueue;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> parent;

    bfsQueue.push(source);
    visited.insert(source);
    parent[source] = "";

    while (!bfsQueue.empty()) {
        std::string current = bfsQueue.front();
        bfsQueue.pop();

        for (const std::string& neighbour : adjList.at(current)) {
            if (!visited.count(neighbour)) {
                visited.insert(neighbour);
                parent[neighbour] = current;
                bfsQueue.push(neighbour);

                if (neighbour == target) {
                    std::vector<std::string> path;
                    std::string step = target;
                    while (!step.empty()) {
                        path.push_back(step);
                        step = parent[step];
                    }
                    std::reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }
    return {};
}

void GraphManager::displayShortestPath(const std::string& source, const std::string& target) const {
    if (!docExists(source)) {
        std::cout << "  Document not found in system.\n";
        return;
    }
    if (!docExists(target)) {
        std::cout << "  Document not found in system.\n";
        return;
    }
    std::cout << "  Finding shortest citation path...\n\n";

    std::vector<std::string> path = bfsShortestPath(source, target);

    if (path.empty()) {
        std::cout << "  No path found.\n";
        return;
    }
    std::cout << "  Path Found:\n";
    for (int i = 0; i < (int)path.size(); i++) {
        std::cout << "  " << path[i] << "\n";
        if (i < (int)path.size() - 1) {
            std::cout << "  ↓\n";
        }
    }
    std::cout << "\n";
}

int GraphManager::getDocumentCount() const { return (int)adjList.size(); }

int GraphManager::getCitationCount() const {
    int total = 0;
    for (const auto& pair : adjList) total += (int)pair.second.size();
    return total;
}

void GraphManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    
    // Save nodes
    for (const auto& pair : docDescriptions) {
        outFile << "NODE|" << pair.first << "|" << pair.second << "\n";
    }
    // Save edges
    for (const auto& pair : adjList) {
        for (const std::string& target : pair.second) {
            outFile << "EDGE|" << pair.first << "|" << target << "\n";
        }
    }
    outFile.close();
}

void GraphManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string tag;
        std::getline(ss, tag, '|');
        
        if (tag == "NODE") {
            std::string docName, desc;
            std::getline(ss, docName, '|');
            std::getline(ss, desc, '|');
            if (!docName.empty()) {
                addDocument(docName, desc, true);
            }
        } else if (tag == "EDGE") {
            std::string fromDoc, toDoc;
            std::getline(ss, fromDoc, '|');
            std::getline(ss, toDoc, '|');
            if (!fromDoc.empty() && !toDoc.empty()) {
                addCitation(fromDoc, toDoc, true);
            }
        }
    }
    inFile.close();
}

void GraphManager::dfsHelper(const std::string& node, std::unordered_set<std::string>& visited, int& order) const {
    visited.insert(node);
    std::cout << "  " << order++ << ". " << node << "\n";
    
    if (adjList.count(node)) {
        std::vector<std::string> neighbors(adjList.at(node).begin(), adjList.at(node).end());
        std::sort(neighbors.begin(), neighbors.end());
        for (const std::string& next : neighbors) {
            if (!visited.count(next)) {
                dfsHelper(next, visited, order);
            }
        }
    }
}

void GraphManager::traverseDFS(const std::string& startNode) const {
    if (!docExists(startNode)) {
        std::cout << "  Document not found in system.\n";
        return;
    }
    
    std::cout << "  Exploring citation network using DFS...\n\n";
    std::cout << "  Visit Order:\n\n";
    
    std::unordered_set<std::string> visited;
    int order = 1;
    dfsHelper(startNode, visited, order);
    
    std::cout << "\n  DFS Traversal Complete.\n";
}

void GraphManager::traverseDFSIterative(const std::string& startNode) const {
    if (!docExists(startNode)) {
        std::cout << "  Document not found in system.\n";
        return;
    }
    
    std::cout << "  Exploring citation network using Iterative DFS (Stack)...\n\n";
    std::cout << "  Visit Order:\n\n";
    
    std::unordered_set<std::string> visited;
    std::vector<std::string> stack;
    stack.push_back(startNode);
    int order = 1;
    
    while (!stack.empty()) {
        std::string current = stack.back();
        stack.pop_back();
        
        if (visited.count(current) == 0) {
            visited.insert(current);
            std::cout << "  " << order++ << ". " << current << "\n";
            
            if (adjList.count(current)) {
                std::vector<std::string> neighbors(adjList.at(current).begin(), adjList.at(current).end());
                std::sort(neighbors.begin(), neighbors.end());
                for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
                    if (visited.count(*it) == 0) {
                        stack.push_back(*it);
                    }
                }
            }
        }
    }
    std::cout << "\n  Iterative DFS Traversal Complete.\n";
}



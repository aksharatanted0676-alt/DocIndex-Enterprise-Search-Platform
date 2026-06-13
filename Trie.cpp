// ============================================================
// Trie.cpp — Naming Registry Module
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>

// ----------------------------------------------------------
// TrieNode
// ----------------------------------------------------------
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// ----------------------------------------------------------
// Trie
// ----------------------------------------------------------
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

// ============================================================
// Implementation
// ============================================================

Trie::Trie() : root(new TrieNode()), totalNames(0) {}

Trie::~Trie() {
    std::vector<TrieNode*> stack;
    stack.push_back(root);
    while (!stack.empty()) {
        TrieNode* node = stack.back();
        stack.pop_back();
        for (auto& pair : node->children) {
            stack.push_back(pair.second);
        }
        delete node;
    }
}

void Trie::insert(const std::string& name, bool silent) {
    if (name.empty()) {
        if (!silent) std::cout << "  [WARNING] Cannot insert an empty name.\n";
        return;
    }
    TrieNode* current = root;
    for (char ch : name) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    if (!current->isEndOfWord) {
        current->isEndOfWord = true;
        totalNames++;
        if (!silent) {
            std::cout << "  File added successfully:\n";
            std::cout << "  " << name << "\n";
        }
    } else {
        if (!silent) std::cout << "  File already exists in registry.\n";
    }
}

bool Trie::search(const std::string& name) const {
    TrieNode* current = root;
    for (char ch : name) {
        if (current->children.find(ch) == current->children.end()) {
            return false;
        }
        current = current->children[ch];
    }
    return current->isEndOfWord;
}

bool Trie::deleteHelper(TrieNode* node, const std::string& word, int depth) {
    if (depth == (int)word.size()) {
        if (!node->isEndOfWord) return false;
        node->isEndOfWord = false;
        return node->children.empty();
    }
    char ch = word[depth];
    if (node->children.find(ch) == node->children.end()) return false;

    bool shouldDeleteChild = deleteHelper(node->children[ch], word, depth + 1);

    if (shouldDeleteChild) {
        delete node->children[ch];
        node->children.erase(ch);
        return (!node->isEndOfWord && node->children.empty());
    }
    return false;
}

bool Trie::remove(const std::string& name, bool silent) {
    if (!search(name)) {
        if (!silent) std::cout << "  File not found in registry.\n";
        return false;
    }
    deleteHelper(root, name, 0);
    totalNames--;
    if (!silent) {
        std::cout << "  File deleted successfully:\n";
        std::cout << "  " << name << "\n";
    }
    return true;
}

void Trie::collectWords(TrieNode* node, const std::string& prefix,
                         std::vector<std::string>& results) const {
    if (node->isEndOfWord) {
        results.push_back(prefix);
    }
    for (auto& pair : node->children) {
        collectWords(pair.second, prefix + pair.first, results);
    }
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) const {
    std::vector<std::string> results;
    TrieNode* current = root;
    for (char ch : prefix) {
        if (current->children.find(ch) == current->children.end()) {
            return results;
        }
        current = current->children[ch];
    }
    collectWords(current, prefix, results);
    std::sort(results.begin(), results.end());
    return results;
}

int Trie::getTotalNames() const { return totalNames; }

void Trie::displayAll() const {
    std::vector<std::string> all = autocomplete("");
    if (all.empty()) {
        std::cout << "  Registry is empty.\n";
        return;
    }
    std::cout << "  Stored Names (" << all.size() << " total):\n";
    for (int i = 0; i < (int)all.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << all[i] << "\n";
    }
}

void Trie::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    std::vector<std::string> all = autocomplete("");
    for (const auto& name : all) {
        outFile << name << "\n";
    }
    outFile.close();
}

void Trie::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;
    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) insert(line, true);
    }
    inFile.close();
}

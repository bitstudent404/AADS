#include <iostream>
#include <string>
using namespace std;

// Trie Node
struct TrieNode {
    TrieNode* child[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;

        for (int i = 0; i < 26; i++) {
            child[i] = NULL;
        }
    }
};

// Insert a word into Trie
void insert(TrieNode* root, string word) {
    TrieNode* current = root;

    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';

        if (current->child[index] == NULL) {
            current->child[index] = new TrieNode();
        }

        current = current->child[index];
    }

    current->isEnd = true;
}

// Search a pattern in Suffix Trie
bool search(TrieNode* root, string pattern) {
    TrieNode* current = root;

    for (int i = 0; i < pattern.length(); i++) {
        int index = pattern[i] - 'a';

        if (current->child[index] == NULL) {
            return false;
        }

        current = current->child[index];
    }

    return true;
}

int main() {
    string text, pattern;

    cout << "Enter text: ";
    cin >> text;

    // Create root
    TrieNode* root = new TrieNode();

    // Generate and insert all suffixes
    for (int i = 0; i < text.length(); i++) {
        string suffix = text.substr(i);
        insert(root, suffix);
    }

    cout << "Enter pattern to search: ";
    cin >> pattern;

    if (search(root, pattern))
        cout << "Pattern found" << endl;
    else
        cout << "Pattern not found" << endl;

    return 0;
}
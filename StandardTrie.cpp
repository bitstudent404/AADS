#include <iostream>
#include <string>
using namespace std;

class TrieNode {
public:
    TrieNode* child[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            child[i] = NULL;
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - 'a';

            if (current->child[index] == NULL)
                current->child[index] = new TrieNode();

            current = current->child[index];
        }

        current->isEnd = true;
    }

    bool search(string word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - 'a';

            if (current->child[index] == NULL)
                return false;

            current = current->child[index];
        }

        return current->isEnd;
    }

    bool startsWith(string prefix) {
        TrieNode* current = root;

        for (char c : prefix) {
            int index = c - 'a';

            if (current->child[index] == NULL)
                return false;

            current = current->child[index];
        }

        return true;
    }
};

int main() {
    Trie trie;
    int n;
    string word;

    cout << "Enter number of words: ";
    cin >> n;

    cout << "Enter words:\n";
    for (int i = 0; i < n; i++) {
        cin >> word;
        trie.insert(word);
    }

    cout << "\nEnter word to search: ";
    cin >> word;

    if (trie.search(word))
        cout << "Word found"<<endl;
    else
        cout << "Word not found"<<endl;

    cout << "\n\nEnter prefix to search: ";
    cin >> word;

    if (trie.startsWith(word))
        cout << "Prefix exists"<<endl;
    else
        cout << "Prefix does not exist"<<endl;

    return 0;
}
#include <iostream>
using namespace std;

class BTreeNode {
public:
    int *keys;              // Stores keys
    BTreeNode **child;      // Stores child pointers
    int n;                  // Current number of keys
    bool leaf;              // True if node is leaf
    int m;                  // Order of B-Tree

    BTreeNode(int order, bool isLeaf) {
        m = order;
        leaf = isLeaf;
        n = 0;

        // Maximum keys = m - 1
        keys = new int[m];

        // Maximum children = m
        child = new BTreeNode*[m + 1];

        for (int i = 0; i <= m; i++)
            child[i] = nullptr;
    }

    // Traverse the tree
    void traverse() {
        int i;

        for (i = 0; i < n; i++) {
            if (!leaf)
                child[i]->traverse();

            cout << keys[i] << " ";
        }

        if (!leaf)
            child[i]->traverse();
    }

    // Search for a key
    BTreeNode* search(int k) {
        int i = 0;

        while (i < n && k > keys[i])
            i++;

        if (i < n && keys[i] == k)
            return this;

        if (leaf)
            return nullptr;

        return child[i]->search(k);
    }

    // Insert key into a non-full node
    void insertNonFull(int k) {
        int i = n - 1;

        if (leaf) {
            // Shift keys to make space
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
            n++;
        }
        else {
            // Find child where key should go
            while (i >= 0 && keys[i] > k)
                i--;

            i++;

            // If child is full
            if (child[i]->n == m - 1) {
                splitChild(i, child[i]);

                if (keys[i] < k)
                    i++;
            }

            child[i]->insertNonFull(k);
        }
    }

    // Split a full child
    void splitChild(int i, BTreeNode* y) {
        int mid = (m - 1) / 2;

        BTreeNode* z = new BTreeNode(m, y->leaf);

        // Number of keys going to new node
        int rightKeys = y->n - mid - 1;

        // Copy right half keys
        for (int j = 0; j < rightKeys; j++)
            z->keys[j] = y->keys[mid + 1 + j];

        // Copy children if not leaf
        if (!y->leaf) {
            for (int j = 0; j <= rightKeys; j++)
                z->child[j] = y->child[mid + 1 + j];
        }

        z->n = rightKeys;

        // Reduce number of keys in old node
        y->n = mid;

        // Shift children of current node
        for (int j = n; j >= i + 1; j--)
            child[j + 1] = child[j];

        child[i + 1] = z;

        // Shift keys of current node
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        // Move middle key to parent
        keys[i] = y->keys[mid];

        n++;
    }
};


class BTree {
public:
    BTreeNode* root;
    int m;

    BTree(int order) {
        root = nullptr;
        m = order;
    }

    // Insert a key
    void insert(int k) {
        // If tree is empty
        if (root == nullptr) {
            root = new BTreeNode(m, true);
            root->keys[0] = k;
            root->n = 1;
            return;
        }

        // If root is full
        if (root->n == m - 1) {
            BTreeNode* newRoot = new BTreeNode(m, false);

            newRoot->child[0] = root;

            // Split old root
            newRoot->splitChild(0, root);

            int i = 0;

            if (newRoot->keys[0] < k)
                i++;

            newRoot->child[i]->insertNonFull(k);

            root = newRoot;
        }
        else {
            root->insertNonFull(k);
        }
    }

    // Display B-Tree
    void display() {
        if (root != nullptr)
            root->traverse();
        cout << endl;
    }

    // Search
    bool search(int k) {
        if (root == nullptr)
            return false;

        return root->search(k) != nullptr;
    }
};


int main() {
    int m, n, value;

    cout << "Enter order of B-Tree (m): ";
    cin >> m;

    if (m < 3) {
        cout << "Order of B-Tree should be at least 3." << endl;
        return 0;
    }

    BTree tree(m);

    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter " << n << " keys:\n";

    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insert(value);
    }

    cout << "\nB-Tree traversal: ";
    tree.display();

    cout << "\nEnter key to search: ";
    cin >> value;

    if (tree.search(value))
        cout << value << " found in B-Tree." << endl;
    else
        cout << value << " not found in B-Tree." << endl;

    return 0;
}
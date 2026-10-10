#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_LEVEL = 4;

struct Node {
    int data;
    Node* next[MAX_LEVEL + 1];

    Node(int value) {
        data = value;
        for (int i = 0; i <= MAX_LEVEL; i++)
            next[i] = NULL;
    }
};

class SkipList {
    Node* head;
    int level;

    int randomLevel() {
        int lvl = 0;
        while (rand() % 2 && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

public:
    SkipList() {
        head = new Node(-1);
        level = 0;
    }

    void insert(int value) {
        Node* update[MAX_LEVEL + 1];
        Node* current = head;

        for (int i = level; i >= 0; i--) {
            while (current->next[i] != NULL &&
                   current->next[i]->data < value)
                current = current->next[i];

            update[i] = current;
        }

        current = current->next[0];

        if (current != NULL && current->data == value) {
            cout << "Element already exists\n";
            return;
        }

        int newLevel = randomLevel();

        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++)
                update[i] = head;

            level = newLevel;
        }

        Node* newNode = new Node(value);

        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }

        cout << "Element inserted\n";
    }

    void search(int value) {
        Node* current = head;

        for (int i = level; i >= 0; i--) {
            while (current->next[i] != NULL &&
                   current->next[i]->data < value)
                current = current->next[i];
        }

        current = current->next[0];

        if (current != NULL && current->data == value)
            cout << "Element found\n";
        else
            cout << "Element not found\n";
    }

    void display() {
        cout << "Skip List:\n";

        for (int i = level; i >= 0; i--) {
            Node* current = head->next[i];
            cout << "Level " << i << ": ";

            while (current != NULL) {
                cout << current->data << " ";
                current = current->next[i];
            }

            cout << endl;
        }
    }

    ~SkipList() {
        Node* current = head;

        while (current != NULL) {
            Node* nextNode = current->next[0];
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    srand(time(0));

    SkipList s;
    int choice, value;

    do {
        cout << "\n1. Insert\n2. Search\n3. Display\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                s.insert(value);
                break;

            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                s.search(value);
                break;

            case 3:
                s.display();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}
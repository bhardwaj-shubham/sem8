#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

class Node {
public:
    Node *left, *right;
    int data;

    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class Breadthfs {

public:
    Node *insert(Node *, int);
    void bfs(Node *);
};

// inserts a Node in tree
Node *insert(Node *root, int data) {

    if (!root) {

        root = new Node(data);
        return root;
    }

    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {

        Node *temp = q.front();
        q.pop();

        if (temp->left == NULL) {
            temp->left = new Node(data);
            return root;
        }
        else {
            q.push(temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new Node(data);
            return root;
        }
        else {
            q.push(temp->right);
        }
    }

    return NULL;
}

void bfs(Node *head) {

    queue<Node *> q;
    q.push(head);

    int qSize;

    while (!q.empty()) {
        qSize = q.size();
        
        #pragma omp parallel for
        // creates parallel threads
        for (int i = 0; i < qSize; i++) {
            Node *currNode;
            
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();

                // prints parent Node
                cout << "\t" << currNode->data;

            } 
            
            #pragma omp critical
            {
                // push parent's left Node in queue
                if (currNode->left) 
                    q.push(currNode->left);

                // push parent's right Node in queue
                if (currNode->right)
                    q.push(currNode->right);
            } 
        }
    }
}

int main() {

    Node *root = NULL;
    int data;
    char ans;

    do {
        cout << "Enter node's data: ";
        cin >> data;

        root = insert(root, data);

        cout << "Do you want insert one more Node? ('y' | 'n'): ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    bfs(root);

    return 0;
}
// question :
// http://practice.geeksforgeeks.org/problems/leftmost-and-rightmost-nodes-of-binary-tree/1

#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class Node {
public:
  int key;
  Node* left;
  Node* right;

  Node(int key) {
    this->key = key;
    left = nullptr;
    right = nullptr;
  }

  string toString() { return std::to_string(key); }
};

void printCornerInner(vector<Node*>& nodes) {
  if (nodes.size() <= 0) {
    return;
  }

  vector<Node*> nextNodes;
  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    if (it == nodes.begin() || it == nodes.end() - 1) {
      cout << (*it)->key << " ";
    }

    if ((*it)->left != nullptr) {
      nextNodes.push_back((*it)->left);
    }
    if ((*it)->right != nullptr) {
      nextNodes.push_back((*it)->right);
    }
  }

  printCornerInner(nextNodes);
}

void printCorner(Node* root) {
  if (root == nullptr) {
    return;
  }

  vector<Node*> nextNodes;
  nextNodes.push_back(root);

  printCornerInner(nextNodes);
}

void insert(struct Node* root, int n1, int n2, char lr) {
  if (root == NULL)
    return;
  if (root->key == n1) {
    switch (lr) {
    case 'L':
      root->left = new Node(n2);
      break;
    case 'R':
      root->right = new Node(n2);
      break;
    }
  } else {
    insert(root->left, n1, n2, lr);
    insert(root->right, n1, n2, lr);
  }
}

Node* parse(string& target) {
  stringstream stream(target);
  string temp;
  vector<string> list;

  while (getline(stream, temp, ' ')) {
    list.push_back(temp);
  }

  int n1 = -1, n2 = -1;

  Node* root = nullptr;

  int count = 0;
  for (auto item : list) {
    ++count;

    switch (count % 3) {
    case 0:
      if (root == nullptr) {
        root = new Node(n1);
      }

      insert(root, n1, n2, item[0]);
      break;

    case 1:
      n1 = stoi(item);
      break;

    case 2:
      n2 = stoi(item);
      break;
    }
  }

  return root;
}

int main(int argc, char* argv[]) {
  string testcases[] = {"15 10 L 10 8 L 10 12 R 15 20 R 20 16 L 20 25 R",
                        "4 1 L 4 2 R 1 6 L 1 10 R 2 2 L 2 3 R 6 9 L 6 1 R 10 "
                        "10 L 10 3 R 2 5 L 2 10 R 3 1 L 3 10 R"};

  for (auto item : testcases) {
    printCorner(parse(item));
    cout << endl;
  }

  return 0;
}
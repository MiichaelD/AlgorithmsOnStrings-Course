#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

const char ROOT_NODE_CHAR = '.';

struct Node {
  char c;
  unordered_map<char, Node*> children;
  bool isLeaf = false;
  Node *parent = nullptr;
  Node(char ch, Node *p = nullptr) : c{ch}, parent{p} {};
  ~Node(){
    for (auto entry : children) {
      if (entry.second != nullptr) {
        delete entry.second;
      }
    }
  }
};

Node * buildTrie(const string& text) {
  Node *root = new Node(ROOT_NODE_CHAR);
  for (int i = 0; i < text.length(); ++i) {
    Node *aux = root;
    for (int j = i; j < text.length(); ++j) {
      if (aux->children[text[j]] == nullptr) {
        aux->children[text[j]] = new Node(text[j], aux);
      }
      aux = aux->children[text[j]];
    }
    aux->isLeaf = true;
  }
  return root;
}

void printTrie(Node *root, int depth = 0) {
  if (root == nullptr) {
    return;
  }
  for (int i = 0 ; i < depth; ++i) {
    cout << "  ";
  }
  cout << root->c << (root->isLeaf ? " <END>" : "" ) << endl;
  for (auto entry : root->children) {
    printTrie(entry.second, depth + 1);
  }
}

deque<char> getString(Node *root) {
  deque<char> result;
  while (root != nullptr && root->c != ROOT_NODE_CHAR) {
    result.push_front(root->c);
    root = root->parent;
    if (root->children.size() > 1) {
      break;
    }
  }
  return result;
}

void fillSuffixTree(vector<deque<char>> &suffixTree, Node *root) {
  if (root == nullptr) {
    return;
  }
  if (root->isLeaf || root->children.size() > 1) {
    suffixTree.push_back(getString(root));
  }
  for (auto entry : root->children) {
    fillSuffixTree(suffixTree, entry.second);
  }
}

// Build a suffix tree of the string text and return a vector with all of the labels of its edges
// (the corresponding substrings of the text) in any order.
vector<deque<char>> ComputeSuffixTreeEdges(const string& text) {
  vector<deque<char>> result;
  Node *root = buildTrie(text);
  printTrie(root);
  fillSuffixTree(result, root);
  delete root;
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<deque<char>> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    for (int j = 0; j < edges[i].size(); ++j) {
      cout << edges[i][j];
    }
    cout << endl;
  }
  return 0;
}

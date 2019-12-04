#include <iostream>
#include <string>
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

bool find(const Node *root, const string &term, int start, int end) {
  if (start >= end) {
    return true;
  }
  auto child = root->children.find(term[start]);
  if (child == root->children.end()) {
    return false;
  }
  return find(child->second, term, start + 1, end);
}

string solve (string p, string q) {
  Node *root = buildTrie(q);
  printTrie(root);
	string result = p;

  for (int i = 1; i < p.length(); ++i) {
    for (int j = 0; (j + i) <= p.length(); ++j) {
      if (!find(root, p, j, j + i)) {
        return p.substr(j, i);
      }
    }
  }

  delete root;
	return result;
}

int main (void) {
	string p, q;
	cin >> p >> q;
	string ans = solve(p, q);
	cout << ans << endl;
	return 0;
}

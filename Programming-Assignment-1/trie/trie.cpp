#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  t.emplace_back(); // Adding root;
  for (const string &pattern : patterns) {
    int aux = 0;
    for (int i = 0 ; i < pattern.size(); ++i) {
      char c = pattern.at(i);
      if (t[aux].find(c) == t[aux].end()) {
        t[aux][c] = t.size();
        t.emplace_back(); // Adding new node;
      }
      aux = t[aux][c];
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & entry : t[i]) {
      std::cout << i << "->" << entry.second << ":" << entry.first << "\n";
    }
  }

  return 0;
}
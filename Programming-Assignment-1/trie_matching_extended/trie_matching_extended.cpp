#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node {
	int next [Letters] = {NA, NA, NA, NA};
	bool patternEnd = false;
};

int letterToIndex (char letter) {
	switch (letter) {
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}


vector<Node> createTrie(const vector <string>& patterns) {
  vector<Node> result;
  result.emplace_back();
  for (const string &pattern : patterns) {
    int aux = 0;
    for (char c : pattern) {
      if (result[aux].next[letterToIndex(c)] == NA) {
        result[aux].next[letterToIndex(c)] = result.size();
        result.emplace_back();
      }
      aux = result[aux].next[letterToIndex(c)];
    }
    result[aux].patternEnd = true;
  }
  return result;
}

vector <int> solve(const string& text, const vector <string>& patterns) {
	vector <int> result;
  vector<Node> trie = createTrie(patterns);
  for (int i = 0 ; i < text.size(); ++i) {
    int aux = 0;
    for (int j = i; j < text.size(); ++j) {
      char c = text.at(j);
      int next = trie[aux].next[letterToIndex(c)];
      if (next == NA) {
        break;
      }
      if (trie[next].patternEnd) {
        result.push_back(i);
        break;
      }
      aux = next;
    }
  }
	return result;
}
int main (void) {
	string text;
	int n;
	cin >> text;
	cin >> n;

	vector <string> patterns(n);
	for (int i = 0; i < n; i++) {
		cin >> patterns[i];
	}

	vector <int> ans = solve(text, patterns);
  if (!ans.empty()) {
    cout << ans[0];
    for (int i = 1; i < (int) ans.size (); i++) {
      cout << " " << ans[i];
    }
    cout << endl;
  }
	return 0;
}

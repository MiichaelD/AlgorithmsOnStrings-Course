#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void printMatrix(const vector<string> &matrix) {
  for (const string &row : matrix) {
    cout << row << endl;
  }
}

string getLastColumn(const vector<string> &matrix) {
  std::stringstream result;
  for (const string &row : matrix) {
    result << row.back();
  }
  return result.str();
}

int safeIndex(const string &text, int index) {
  int textLen = text.size();
  if (index >= textLen) {
    return (index - textLen);
  }
  if (index < 0) {
    return (textLen + index);
  }
  return index;
}

string BWT(const string& text) {
  vector<string> matrix;
  int startIndex = text.find('$');
  for (int i = 0; i < text.size(); ++i) {
    std::stringstream ss;
    for (int j = 0; j < text.size(); ++j) {
      ss << text.at(safeIndex(text, j + startIndex));
    }
    matrix.emplace_back(ss.str());
    ss.clear();
    --startIndex;
  }
  sort(matrix.begin(), matrix.end());
  printMatrix(matrix);
  return getLastColumn(matrix);
}

int main() {
  string text;
  cin >> text;
  string bwt = BWT(text);
  cout << "BWT: " << bwt << endl;
  return 0;
}
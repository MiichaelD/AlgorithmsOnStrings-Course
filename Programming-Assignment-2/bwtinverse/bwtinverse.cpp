#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef vector<deque<char>> Matrix;

void printMatrix(Matrix& matrix) {
  for (int r = 0; r < matrix.size(); ++r) {
    for (char c : matrix[r]) {
      cout << c;
    }
    cout << endl;
  }
  cout << endl;
}

string getOriginalStringFromMatrix(Matrix& matrix) {
  for (auto& row : matrix) {
    if (row.back() == '$') {
      stringstream ss;
      for (char c : row) {
        ss << c;
      }
      return ss.str();
    }
  }
  return "NOT_FOUND";
}

string InverseBWT(const string& bwt) {
  size_t textLen = bwt.size();
  string sortedBwt = bwt;
  sort(sortedBwt.begin(), sortedBwt.end());
  Matrix matrix(bwt.size());
  for (int r = 0; r < bwt.size(); ++r) {
    matrix[r].push_back(sortedBwt.at(r));
    matrix[r].push_back(bwt.at(r));
  }
  // printMatrix(matrix);
  // Matrix has first and last row. On each iteration insert before last column
  for (int i = 1; i < textLen - 1; ++i) {
    vector<string> nMer;
    nMer.reserve(textLen);

    for (int r = 0; r < matrix.size(); ++ r) {
      stringstream ss;
      // Always start with last character first
      ss << matrix[r].back();
      for (int c = 0; c < matrix[r].size() - 1; ++c) {
        ss << matrix[r][c];
      }
      // cout << "inserting: " << ss.str() << endl;
      nMer.emplace_back(ss.str());
    }
    // Sorting gives us the next column
    sort(nMer.begin(), nMer.end());
    
    // Insert new column
    for (int r = 0; r < textLen; ++r) {
      matrix[r].insert((matrix[r].begin() + i), nMer[r].back());
    }
    // printMatrix(matrix);
  }

  return getOriginalStringFromMatrix(matrix);
}

void printMapping(vector<pair<int,int>>& mapping) {
  for (int i = 0; i < mapping.size(); ++i) {
    cout << i << ".-  " << mapping.at(i).first << " - " << mapping.at(i).second << endl;
  }
  cout << endl;
}

string InverseBWTImproved(const string& bwt) {
  size_t textLen = bwt.size();
  string sortedBwt = bwt;
  sort(sortedBwt.begin(), sortedBwt.end());
  vector<pair<int,int>> mapping(textLen);

  int repeats;
  for (int i = 0 ; i < textLen; ++i) {
    char c = sortedBwt.at(i);
    if (i > 0 && sortedBwt.at(i - 1) == c) {
      ++repeats;
    } else {
      repeats = 0;
    }
    int tmpRepeats = repeats;
    for (int j = 0; j < textLen; ++j) {
      if (c == bwt.at(j)) {
        if (tmpRepeats) {
          --tmpRepeats;
        } else {
          mapping.at(i).first = j;
          mapping.at(j).second = i;
          break;
        }
      }
    }
  }
  // printMapping(mapping);
  stringstream output;
  int index = 0;
  for (int i = 0; i < textLen; ++i) {
    const auto& entry = mapping.at(index);
    output << sortedBwt.at(entry.first);
    index = entry.first;
  }
  return output.str();;
}

int main() {
  string bwt;
  cin >> bwt;
  // string inverseBwt = InverseBWT(bwt);
  string inverseBwt = InverseBWTImproved(bwt);
  cout << "Inverse BWT(" << bwt << ") = " << inverseBwt << endl;
  return 0;
}

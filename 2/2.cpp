#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isSequenceSafe(const std::vector<unsigned>& seq) {
  if (seq.size() < 2) return true;

  bool is_increasing = seq[1] > seq[0];

  for (size_t i = 1; i < seq.size(); i++) {
    int diff = seq[i] - seq[i - 1];
    if ((is_increasing && diff <= 0) || (!is_increasing && diff >= 0) ||
        abs(diff) < 1 || abs(diff) > 3) {
      return false;
    }
  }
  return true;
}

bool checkWithDampener(std::vector<unsigned>& levels) {
  // First check if safe without dampener
  if (isSequenceSafe(levels)) return true;

  // Try removing each number one at a time
  for (size_t i = 0; i < levels.size(); i++) {
    unsigned removed = levels[i];
    levels.erase(levels.begin() + i);

    if (isSequenceSafe(levels)) {
      levels.insert(levels.begin() + i, removed);
      return true;
    }

    levels.insert(levels.begin() + i, removed);
  }
  return false;
}

int main() {
  std::ifstream inFile("in.txt", std::ios::in);
  std::string line;
  unsigned safe_count = 0;
  unsigned count = 0;

  while (std::getline(inFile, line)) {
    std::vector<unsigned> levels;
    unsigned num;
    std::istringstream iss(line);
    while (iss >> num) {
      levels.push_back(num);
    }

    if (isSequenceSafe(levels)) {
      count++;
    }
    if (checkWithDampener(levels)) {
      safe_count++;
    }
  }

  std::cout << count << " " << safe_count << std::endl;
  return 0;
}

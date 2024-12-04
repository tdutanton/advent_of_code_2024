#include <fstream>
#include <iostream>
#include <string>

unsigned long long xmas_count_horizon(const std::string& s1, size_t ptr) {
  unsigned long long count = 0;
  if (s1.substr(ptr, 4) == "XMAS") count++;
  if (s1.substr(ptr, 4) == "SAMX") count++;
  return count;
}

unsigned long long xmas_count_vertical(const std::string& s1,
                                       const std::string& s2,
                                       const std::string& s3,
                                       const std::string& s4, size_t ptr) {
  unsigned long long count = 0;
  if (s1.at(ptr) == 'X' && s2.at(ptr) == 'M' && s3.at(ptr) == 'A' &&
      s4.at(ptr) == 'S')
    count++;
  if (s1.at(ptr) == 'S' && s2.at(ptr) == 'A' && s3.at(ptr) == 'M' &&
      s4.at(ptr) == 'X')
    count++;
  return count;
}

unsigned long long xmas_count_diagonal(const std::string& s1,
                                       const std::string& s2,
                                       const std::string& s3,
                                       const std::string& s4, size_t ptr) {
  unsigned long long count = 0;
  if (s1.at(ptr) == 'X' && s2.at(ptr + 1) == 'M' && s3.at(ptr + 2) == 'A' &&
      s4.at(ptr + 3) == 'S')
    count++;
  if (s1.at(ptr) == 'S' && s2.at(ptr + 1) == 'A' && s3.at(ptr + 2) == 'M' &&
      s4.at(ptr + 3) == 'X')
    count++;
  if (s1.at(ptr + 3) == 'S' && s2.at(ptr + 2) == 'A' && s3.at(ptr + 1) == 'M' &&
      s4.at(ptr) == 'X')
    count++;
  if (s1.at(ptr + 3) == 'X' && s2.at(ptr + 2) == 'M' && s3.at(ptr + 1) == 'A' &&
      s4.at(ptr) == 'S')
    count++;
  return count;
}

unsigned long long xmas_like_big_x(const std::string& s1, const std::string& s2,
                                   const std::string& s3, size_t ptr) {
  unsigned long long count = 0;
  if (ptr + 2 >= s1.size()) return 0;
  if (s2.at(ptr + 1) != 'A') return 0;

  bool left_mas = (s1.at(ptr) == 'M' && s3.at(ptr + 2) == 'S');
  bool left_sam = (s1.at(ptr) == 'S' && s3.at(ptr + 2) == 'M');

  bool right_mas = (s1.at(ptr + 2) == 'M' && s3.at(ptr) == 'S');
  bool right_sam = (s1.at(ptr + 2) == 'S' && s3.at(ptr) == 'M');

  if (left_mas && right_mas) count++;
  if (left_mas && right_sam) count++;
  if (left_sam && right_mas) count++;
  if (left_sam && right_sam) count++;

  return count;
}

int main() {
  std::ifstream inFile("input.txt", std::ios::in);
  std::string s1, s2, s3, s4;
  unsigned long long res = 0;
  unsigned long long x_res = 0;
  std::getline(inFile, s1);
  std::getline(inFile, s2);
  std::getline(inFile, s3);
  for (size_t i = 0; i < s1.size() - 3; i++) {
    res += xmas_count_horizon(s1, i);
    res += xmas_count_horizon(s2, i);
    res += xmas_count_horizon(s3, i);
  }
  for (size_t i = 0; i < s1.size(); i++) {
    x_res += xmas_like_big_x(s1, s2, s3, i);
  }
  while (std::getline(inFile, s4)) {
    size_t length = s1.size();
    for (size_t i = 0; i < length; i++) {
      res += xmas_count_vertical(s1, s2, s3, s4, i);
    }
    for (size_t i = 0; i < length - 3; i++) {
      res += xmas_count_horizon(s4, i);
      res += xmas_count_diagonal(s1, s2, s3, s4, i);
    }
    s1 = s2;
    s2 = s3;
    s3 = s4;
    for (size_t i = 0; i < length; i++) {
      x_res += xmas_like_big_x(s1, s2, s3, i);
    }
  }

  std::cout << "Number of XMAS word: " << res << std::endl;
  std::cout << "Number of MAS like X: " << x_res << std::endl;

  return 0;
}
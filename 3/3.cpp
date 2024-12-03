#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int process_mul_instructions(const std::string& text) {
  std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
  std::smatch matches;
  std::string::const_iterator searchStart(text.cbegin());
  int total = 0;

  while (std::regex_search(searchStart, text.cend(), matches, pattern)) {
    int num1 = std::stoi(matches[1]);
    int num2 = std::stoi(matches[2]);
    total += num1 * num2;
    searchStart = matches.suffix().first;
  }

  return total;
}

int main() {
  int result = 0;
  std::ifstream file("in.txt");
  if (file.is_open()) {
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    result = process_mul_instructions(content);
    std::cout << "Total sum from file: " << result << std::endl;
  }

  return 0;
}

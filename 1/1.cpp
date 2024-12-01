#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

unsigned distance_between_lists(std::vector<unsigned>& first,
                                std::vector<unsigned>& second);
void create_repeat_count(std::map<unsigned, unsigned>& list,
                         const std::vector<unsigned>& second);
unsigned second_task(std::map<unsigned, unsigned>& list,
                     const std::vector<unsigned>& first);

int main() {
  std::vector<unsigned> a, b;
  std::ifstream inFile("in.txt", std::ios::in);
  unsigned num1, num2;

  while (inFile >> num1 >> num2) {
    a.push_back(num1);
    b.push_back(num2);
  }

  unsigned result = distance_between_lists(a, b);

  std::map<unsigned, unsigned> list_with_repeats_count;
  create_repeat_count(list_with_repeats_count, b);

  unsigned result_2 = second_task(list_with_repeats_count, a);

  std::cout << "First answer - " << result << std::endl;
  std::cout << "Second answer - " << result_2 << std::endl;

  return 0;
}

unsigned distance_between_lists(std::vector<unsigned>& first,
                                std::vector<unsigned>& second) {
  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());
  unsigned result = 0;
  for (int i = 0; i < first.size(); i++) {
    result += abs(first[i] - second[i]);
  }
  return result;
}

void create_repeat_count(std::map<unsigned, unsigned>& list,
                         const std::vector<unsigned>& second) {
  for (const auto& i : second) {
    if (auto search = list.find(i); search == list.end()) {
      list[i] = 1;
    } else
      list[i] += 1;
  }
}

unsigned second_task(std::map<unsigned, unsigned>& list,
                     const std::vector<unsigned>& first) {
  unsigned result = 0;
  for (const auto& i : first) {
    if (auto search = list.find(i); search != list.end()) {
      result += i * list[i];
    }
  }
  return result;
}
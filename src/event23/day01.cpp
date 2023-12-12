#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>
#include <aoc.h>

namespace event23::day01 {

const std::vector<std::string> DIGITS {
  "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
};

int calculate_calibration(std::string &line) {
  line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) {
    return !std::isdigit(c);
  }), line.end());

  auto line_len = line.length();

  if (!line_len) {
    return 0;
  }

  if (line_len == 1) {
    line.append(line);
  } else if (line_len > 2) {
    char last = line.at(line_len - 1);
    line = line.at(0);
    line += last;
  }

  return std::stoi(line);
}

aoc::Answer solve() {
  int part1 = 0;
  int part2 = 0;

  std::ifstream input("inputs/event23/day01/input.txt");

  if (!input) {
    return aoc::Answer { 2023, 01, "", "" };
  }

  for (std::string line; std::getline(input, line);) {
    std::string sline = line;

    part1 += calculate_calibration(line);

    for (int idx = 0; idx < DIGITS.size(); idx++) {
      const auto &digit = DIGITS.at(idx);
      auto pos = sline.find(digit);

      if (pos == std::string::npos) {
        continue;
      }

      sline[pos + 1] = idx + 1 + '0';
      idx--;
    }

    part2 += calculate_calibration(sline);
  }

  return aoc::Answer {
    2023,
    01,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

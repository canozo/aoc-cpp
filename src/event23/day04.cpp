#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <aoc.h>

namespace event23::day04 {

constexpr int EVENT = 2023;
constexpr int DAY = 4;

constexpr int id_begin = 5;

aoc::Answer solve(const std::string &filename = "input.txt") {
  int part1 = 0;
  int part2 = 0;

  std::ifstream input("inputs/event23/day04/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  for (std::string line; std::getline(input, line);) {
    int card_num = 0;
    int winners = 0;
    int pos = 0;

    bool crossed = false;
    std::vector<int> winning;

    for (int idx = id_begin; idx < line.length(); idx++) {
      const char curr = line[idx];
      int parsed;

      switch (curr) {
      case ':':
        card_num = std::stoi(line.substr(id_begin, idx - id_begin));
        idx++;
        break;

      case '|':
        crossed = true;
        idx++;
        break;

      case ' ':
        if (!pos) {
          continue;
        }

        parsed = std::stoi(line.substr(pos, idx - pos));

        if (crossed) {
          bool found = std::find(
            winning.begin(), winning.end(), parsed) != winning.end();

          if (found) {
            winners++;
          }
        } else {
          winning.push_back(parsed);
        }

        pos = 0;
        break;

      default:
        if (card_num && !pos && std::isdigit(curr)) {
          pos = idx;
        }
        break;
      }
    }

    if (pos) {
      int parsed = std::stoi(line.substr(pos, line.length() - pos));

      bool found = std::find(
          winning.begin(), winning.end(), parsed) != winning.end();

      if (found) {
        winners++;
      }
    }

    if (winners) {
      part1 += std::pow(2, winners - 1);
    }
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

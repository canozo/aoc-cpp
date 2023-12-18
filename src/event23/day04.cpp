#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <map>
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

  std::map<int, int> copies;

  for (std::string line; std::getline(input, line);) {
    line += ' ';

    int card_num = 0;
    int winners = 0;
    int pos = 0;
    bool crossed = false;
    std::vector<int> winning;

    int matches = 0;

    for (int idx = id_begin; idx < line.length(); idx++) {
      const char curr = line[idx];
      int parsed;

      switch (curr) {
      case ':':
        card_num = std::stoi(line.substr(id_begin, idx - id_begin));

        {
          const auto it = copies.find(card_num);

          if (it == copies.end()) {
            copies.insert({ card_num, ++matches });
          } else {
            matches = ++it->second;
          }
        }

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

    if (winners) {
      part1 += std::pow(2, winners - 1);
    }

    part2 += matches;

    for (int card = card_num + 1; card <= card_num + winners; card++) {
      const auto it = copies.find(card);

      if (it == copies.end()) {
        copies.insert({ card, matches });
      } else {
        it->second += matches;
      }
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

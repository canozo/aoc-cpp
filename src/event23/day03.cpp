#include <array>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <aoc.h>

namespace event23::day03 {

constexpr int EVENT = 2023;
constexpr int DAY = 3;

constexpr int npos = -1;

struct PartNumber {
  int number;
  bool seen;
};

const std::array<std::pair<int, int>, 8> BORDERS {
  std::make_pair(-1, -1),
  std::make_pair(-1,  0),
  std::make_pair(-1,  1),

  std::make_pair(0, -1),
  std::make_pair(0,  1),

  std::make_pair(1, -1),
  std::make_pair(1,  0),
  std::make_pair(1,  1),
};

aoc::Answer solve(const std::string &filename = "input.txt") {
  int part1 = 0;
  int part2 = 0;

  std::ifstream input("inputs/event23/day03/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  std::vector<std::string> schematic;

  for (std::string line; std::getline(input, line);) {
    schematic.push_back(line + '.');
  }

  std::vector<std::pair<int, int>> symbols;
  std::map<std::pair<int, int>, std::shared_ptr<PartNumber>> part_numbers;

  for (std::size_t lidx = 0; lidx < schematic.size(); lidx++) {
    const std::string &line = schematic.at(lidx);

    std::shared_ptr<PartNumber> part_number;
    int num_begin = npos;

    for (std::size_t cidx = 0; cidx < line.length(); cidx++) {
      const char curr = line[cidx];
      const bool is_digit = std::isdigit(curr);

      if (is_digit && num_begin == npos) {
        part_number = std::make_shared<PartNumber>();
        part_numbers.insert({ std::make_pair(lidx, cidx), part_number });

        num_begin = cidx;
        continue;
      }

      if (is_digit) {
        part_numbers.insert({ std::make_pair(lidx, cidx), part_number });
        continue;
      }

      if (num_begin != npos) {
        int num = std::stoi(line.substr(num_begin, cidx - num_begin));

        part_number->number = num;
        part_number->seen = false;

        num_begin = npos;
      }

      if (curr != '.') {
        symbols.push_back(std::make_pair(lidx, cidx));
      }
    }
  }

  for (const auto &[sline, scol] : symbols) {
    const bool gear_symbol = schematic[sline][scol] == '*';
    int part_number_count = 0;
    int gear_ratio = 1;

    for (const auto &[bline, bcol] : BORDERS) {
      const auto pair = std::make_pair(sline + bline, scol + bcol);
      const auto it = part_numbers.find(pair);

      if (it == part_numbers.end()) {
        continue;
      }

      const std::shared_ptr<PartNumber> part_number = it->second;

      if (part_number->seen) {
        continue;
      }

      part1 += part_number->seen ? 0 : part_number->number;
      part_number->seen = true;

      if (gear_symbol) {
        part_number_count++;
        gear_ratio *= part_number->number;
      }
    }

    if (part_number_count == 2) {
      part2 += gear_ratio;
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

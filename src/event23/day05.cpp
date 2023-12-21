#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>
#include <aoc.h>

namespace event23::day05 {

constexpr int EVENT = 2023;
constexpr int DAY = 5;

constexpr int seeds_start = 7;

struct Mapping {
  unsigned long dest;
  unsigned long source;
  unsigned long range;
};

Mapping parseMapping(std::string &line) {
  Mapping mapping;
  unsigned short init = 0;
  int pos = -1;

  line += ' ';

  for (int idx = 0; idx < line.length(); idx++) {
    const char curr = line[idx];

    switch (curr) {
    case ' ':
      if (init == 0) {
        mapping.dest = std::stoul(line.substr(pos, idx - pos));
      } else if (init == 1) {
        mapping.source = std::stoul(line.substr(pos, idx - pos));
      } else {
        mapping.range = std::stoul(line.substr(pos, idx - pos));
      }

      pos = -1;
      init++;
      break;

    default:
      if (pos == -1) {
        pos = idx;
      }
      break;
    }
  }

  return mapping;
}

void convertSeeds(
  std::vector<unsigned long> &seeds,
  std::vector<bool> &converted,
  std::string &line
) {
  const auto &[dest, source, range] = parseMapping(line);

  for (int idx = 0; idx < seeds.size(); idx++) {
    if (converted.at(idx)) {
      continue;
    }

    const unsigned long seed = seeds.at(idx);

    if (source <= seed && seed <= source + range) {
      seeds.at(idx) = seed + dest - source;
      converted.at(idx) = true;
    }
  }
}

aoc::Answer solve(const std::string &filename = "input.txt") {
  unsigned long part1 = 0;
  int part2 = 0;

  std::ifstream input("inputs/event23/day05/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  std::vector<unsigned long> seeds;

  std::string first_line;
  std::getline(input, first_line);
  first_line += ' ';

  int pos = 0;

  for (int idx = seeds_start; idx < first_line.length(); idx++) {
    const char curr = first_line[idx];

    switch (curr) {
    case ' ':
      seeds.push_back(std::stoul(first_line.substr(pos, idx - pos)));
      pos = 0;
      break;

    default:
      if (!pos) {
        pos = idx;
      }
      break;
    }
  }

  pos = 0;

  std::vector<bool> converted(seeds.size(), false);

  for (std::string line; std::getline(input, line);) {
    if (line.empty()) {
      continue;
    }

    if (!std::isdigit(line[0])) {
      std::fill(converted.begin(), converted.end(), false);
    } else {
      convertSeeds(seeds, converted, line);
    }
  }

  auto min_value = std::min_element(seeds.begin(), seeds.end());

  if (min_value != seeds.end()) {
    part1 = *min_value;
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

#include <fstream>
#include <string>
#include <aoc.h>

namespace event23::day23 {

constexpr int EVENT = 2023;
constexpr int DAY = 23;

aoc::Answer solve() {
  int part1 = 0;
  int part2 = 0;

  std::ifstream input("inputs/event23/day23/example.txt");

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  for (std::string line; std::getline(input, line);) {
    // TODO
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

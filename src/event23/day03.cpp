#include <fstream>
#include <string>
#include <aoc.h>

namespace event23::day03 {

aoc::Answer solve() {
  int part1 = 0;
  int part2 = 0;

  std::ifstream input("inputs/event23/day03/example.txt");

  if (!input) {
    return aoc::Answer { 2023, 03, "", "" };
  }

  for (std::string line; std::getline(input, line);) {
    // TODO
  }

  return aoc::Answer {
    2023,
    03,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

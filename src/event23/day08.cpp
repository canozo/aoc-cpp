#include <fstream>
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include <aoc.h>

namespace event23::day08 {

constexpr int EVENT = 2023;
constexpr int DAY = 8;

aoc::Answer solve(const std::string &filename = "input.txt") {
  unsigned int part1 = 0;
  unsigned long long part2 = 0;

  std::ifstream input("inputs/event23/day08/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  std::string buffer;
  std::getline(input, buffer);

  const std::string sequence = buffer;
  std::getline(input, buffer);

  typedef std::pair<const std::string, const std::string> node;
  std::map<const std::string, const node> network;

  std::vector<std::string> ghosts;

  for (std::string line; std::getline(input, line);) {
    auto from = line.substr(0, 3);
    auto left = line.substr(7, 3);
    auto right = line.substr(12, 3);

    network.insert({ from, std::make_pair(left, right) });

    if (from.at(2) == 'A') {
      ghosts.push_back(from);
    }
  }

  // part 1
  std::string curr = "AAA";

  while (curr != "ZZZ") {
    const char route = sequence.at(part1++ % sequence.size());
    const node options = network.find(curr)->second;

    curr = route == 'L' ? options.first : options.second;
  }

  // part 2
  std::vector<unsigned long long> intervals;

  for (auto it = ghosts.begin(); it != ghosts.end(); ++it) {
    auto curr = *it;
    unsigned long long pos = 0;

    while (curr.at(2) != 'Z') {
      const char route = sequence.at(pos++ % sequence.size());
      const node options = network.find(curr)->second;

      curr = route == 'L' ? options.first : options.second;
    }

    intervals.push_back(pos);
  }

  part2 = intervals.at(0);

  for (std::size_t idx = 1; idx < intervals.size(); ++idx) {
    part2 = std::lcm(part2, intervals.at(idx));
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <aoc.h>
#include <vector>

namespace event23::day08 {

constexpr int EVENT = 2023;
constexpr int DAY = 8;

typedef std::pair<std::string, std::string> node;
std::map<const std::string, const node> network;

std::string stepNetwork(
  const std::string &curr,
  const char route
) {
  const node options = network.find(curr)->second;

  return route == 'L' ? options.first : options.second;
}

bool keepSearching(const std::vector<std::string> &ghosts) {
  for (const std::string &ghost : ghosts) {
    if (ghost.at(2) != 'Z') {
      return true;
    }
  }

  return false;
}

aoc::Answer solve(const std::string &filename = "input.txt") {
  unsigned int part1 = 0;
  unsigned int part2 = 0;

  std::ifstream input("inputs/event23/day08/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  std::string buffer;
  std::getline(input, buffer);

  const std::string sequence = buffer;
  std::getline(input, buffer);

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
    curr = stepNetwork(curr, route);
  }

  // part 2
  while (keepSearching(ghosts)) {
    const char route = sequence.at(part2++ % sequence.size());

    for (auto it = ghosts.begin(); it != ghosts.end(); ++it) {
      *it = stepNetwork(*it, route);
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

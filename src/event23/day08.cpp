#include <cstddef>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <aoc.h>

namespace event23::day08 {

constexpr int EVENT = 2023;
constexpr int DAY = 8;

bool keepSearching(
  const std::vector<std::size_t> &ghosts,
  const std::vector<std::string> &keys
) {
  for (const auto &ghost: ghosts) {
    if (keys.at(ghost).at(2) != 'Z') {
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

  typedef std::pair<const std::string, const std::string> raw_node;
  std::map<const std::string, const raw_node> raw_network;

  std::map<const std::string, const std::size_t> path_to_idx;

  std::vector<std::string> keys;
  std::vector<std::size_t> ghosts;

  std::size_t aaa = 0;
  std::size_t zzz = 0;

  for (std::string line; std::getline(input, line);) {
    auto from = line.substr(0, 3);
    auto left = line.substr(7, 3);
    auto right = line.substr(12, 3);

    keys.push_back(from);
    raw_network.insert({ from, std::make_pair(left, right) });

    const auto idx = keys.size() - 1;
    path_to_idx.insert({ from, idx });

    if (from == "AAA") {
      aaa = idx;
    } else if (from == "ZZZ") {
      zzz = idx;
    }

    if (from.at(2) == 'A') {
      ghosts.push_back(idx);
    }
  }

  typedef std::pair<const std::size_t, const std::size_t> node;
  std::map<const std::string, const node> network;

  for (const auto &[path, values] : raw_network) {
    network.insert({
      path,
      std::make_pair(
        path_to_idx.find(values.first)->second,
        path_to_idx.find(values.second)->second
      ),
    });
  }

  raw_network.clear();
  path_to_idx.clear();

  // part 1
  std::size_t curr = aaa;

  while (curr != zzz) {
    const char route = sequence.at(part1++ % sequence.size());
    const node options = network.find(keys.at(curr))->second;

    curr = route == 'L' ? options.first : options.second;
  }

  // part 2
  while (keepSearching(ghosts, keys)) {
    const char route = sequence.at(part2++ % sequence.size());

    for (std::size_t idx = 0; idx < ghosts.size(); ++idx) {
      const auto ghost = ghosts.at(idx);
      const node options = network.find(keys.at(ghost))->second;

      ghosts.at(idx) = route == 'L' ? options.first : options.second;
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

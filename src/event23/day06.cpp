#include <cctype>
#include <cmath>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <aoc.h>

namespace event23::day06 {

constexpr int EVENT = 2023;
constexpr int DAY = 6;

std::vector<int> parseLine(std::string &line) {
  std::vector<int> parsed;
  int pos = -1;

  line += ' ';

  for (int idx = 0; idx < line.length(); idx++) {
    const char curr = line[idx];

    switch (curr) {
    case ' ':
      if (pos == -1) {
        continue;
      }

      parsed.push_back(std::stoi(line.substr(pos, idx - pos)));
      pos = -1;
      break;

    default:
      if (std::isdigit(curr) && pos == -1) {
        pos = idx;
      }
      break;
    }
  }

  return parsed;
}

std::vector<std::pair<int, int>>
parseInput(std::string &time, std::string &distance) {
  std::vector<std::pair<int, int>> races;

  auto times = parseLine(time);
  auto distances = parseLine(distance);

  for (int idx = 0; idx < times.size(); idx++) {
    races.push_back(std::make_pair(times.at(idx), distances.at(idx)));
  }

  return races;
}

long long solveRace(const long long &time, const long long &dist) {
  const long long ntime = time * -1;

  long long extra = 1;
  const long double sqrt = std::sqrt(std::pow(ntime, 2) - 4 * dist);

  const long double flower = (ntime * -1 - sqrt) / 2;
  const long long lower = std::ceil(flower);

  const long double fupper = (ntime * -1 + sqrt) / 2;
  const long long upper = std::floor(fupper);

  if (std::truncl(flower) == flower && std::truncl(fupper) == fupper) {
    extra = -1;
  }

  return upper - lower + extra;
}

aoc::Answer solve(const std::string &filename = "input.txt") {
  int part1 = 1;
  long long part2 = 0;

  std::ifstream input("inputs/event23/day06/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  std::string time, distance;

  std::getline(input, time);
  std::getline(input, distance);

  auto races = parseInput(time, distance);

  std::string time_p2 = "";
  std::string dist_p2 = "";

  for (const auto &race : races) {
    const auto [time, dist] = race;
    part1 *= solveRace(time, dist);

    time_p2 += std::to_string(time);
    dist_p2 += std::to_string(dist);
  }

  part2 = solveRace(std::stoll(time_p2), std::stoll(dist_p2));

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

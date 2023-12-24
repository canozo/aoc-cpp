#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iterator>
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

struct SeedGroup {
  unsigned long fr;
  unsigned long to;
  bool converted = false;
  bool prune = false;
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

void aggregateSeedGroups(std::vector<SeedGroup> &seeds) {
  // seeds must be sorted
  std::sort(
    seeds.begin(),
    seeds.end(),
    [](const SeedGroup &l, const SeedGroup &r) {
      return l.fr < r.fr;
    });

  std::vector<SeedGroup> append;
  unsigned long ceiling = 0;

  int l = 0;
  int r = 1;

  while (l < seeds.size() && r < seeds.size()) {
    SeedGroup &start = seeds.at(l);
    SeedGroup &next = seeds.at(r);

    if (start.converted != next.converted) {
      l++;

      if (l == r) {
        r++;
      }

      continue;
    }

    if (ceiling && ceiling >= next.fr) {
      next.prune = true;
      ceiling = std::max(ceiling, next.to);
      r++;
      continue;
    }

    if (start.to >= next.fr) {
      start.prune = next.prune = true;
      ceiling = std::max(start.to, next.to);
      r++;
      continue;
    }

    if (ceiling) {
      append.push_back(SeedGroup { start.fr, ceiling, start.converted });
      ceiling = 0;
      l = r;
      r++;
    } else {
      l++;
      r++;
    }
  }

  if (ceiling) {
    const SeedGroup start = seeds.at(l);
    append.push_back(SeedGroup { start.fr, ceiling, start.converted });
  }

  seeds.erase(std::remove_if(
    seeds.begin(),
    seeds.end(),
    [](const SeedGroup &sg) { return sg.prune; }),
    seeds.end());

  seeds.insert(seeds.end(), append.begin(), append.end());
}

void convertSeeds(
  std::vector<unsigned long> &seeds,
  std::vector<bool> &converted,
  const Mapping &line
) {
  const auto &[dest, source, range] = line;

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

void convertSeedGroups(std::vector<SeedGroup> &seeds, const Mapping &line) {
  const auto &[dest, source, range] = line;

  std::vector<SeedGroup> append;

  for (SeedGroup &seed : seeds) {
    if (seed.converted) {
      continue;
    }

    const unsigned long map_fr = source;
    const unsigned long map_to = source + range;

    if (seed.fr > map_to || map_fr > seed.to) {
      continue;
    }

    const unsigned long diff = dest - source;

    // whole seed group is contained on the range
    if (map_fr <= seed.fr && map_to >= seed.to) {
      seed.fr += diff;
      seed.to += diff;
      seed.converted = true;
      continue;
    }

    const unsigned long og_fr = std::max(seed.fr, map_fr);
    const unsigned long og_to = std::min(seed.to, map_to);

    // either the end or the beginning of the seed group is in the range
    if (map_fr <= seed.fr) {
      append.push_back(SeedGroup { map_to + 1, seed.to });
    } else if (map_to >= seed.to) {
      append.push_back(SeedGroup { seed.fr, map_fr - 1 });
    }

    // a spot in the middle of the seed group is part of the range
    if (map_fr > seed.fr && map_to < seed.to) {
      append.push_back(SeedGroup { seed.fr + diff, map_fr + diff });
      append.push_back(SeedGroup { map_to + diff, seed.to + diff });
    }

    // move the intersection to the mapped spot
    seed.fr = og_fr + diff;
    seed.to = og_to + diff;
    seed.converted = true;
  }

  // append new seeds to main vector
  seeds.insert(seeds.end(), append.begin(), append.end());

  // sort and aggregate groups
  aggregateSeedGroups(seeds);
}

aoc::Answer solve(const std::string &filename = "input.txt") {
  unsigned long part1 = 0;
  unsigned long part2 = 0;

  std::ifstream input("inputs/event23/day05/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  std::vector<unsigned long> seeds;
  std::vector<SeedGroup> seedGroups;

  std::string first_line;
  std::getline(input, first_line);
  first_line += ' ';

  int pos = 0;

  // parse the seeds for part 1
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

  std::vector<bool> converted(seeds.size(), false);

  // parse the seeds groups for part 2
  for (auto it = seeds.begin(); it != seeds.end(); std::advance(it, 2)) {
    const unsigned long start = *it;

    auto dupe = it;
    std::advance(dupe, 1);
    const unsigned long range = *dupe;

    seedGroups.push_back(SeedGroup { start, start + range });
  }

  // iterate through almanac to solve puzzle
  for (std::string line; std::getline(input, line);) {
    if (line.empty()) {
      continue;
    }

    if (!std::isdigit(line[0])) {
      // reset part 1 flags
      std::fill(converted.begin(), converted.end(), false);

      // reset part 2 flags
      for (SeedGroup &seed : seedGroups) {
        seed.converted = false;
      }

      // try to aggregate values
      aggregateSeedGroups(seedGroups);
    } else {
      const Mapping m = parseMapping(line);
      convertSeeds(seeds, converted, m);
      convertSeedGroups(seedGroups, m);
    }
  }

  auto min_val_p1 = std::min_element(seeds.begin(), seeds.end());

  if (min_val_p1 != seeds.end()) {
    part1 = *min_val_p1;
  }

  auto min_val_p2 = std::min_element(seedGroups.begin(), seedGroups.end(),
    [](const SeedGroup &l, const SeedGroup &r) {
      return l.fr < r.fr;
    });

  if (min_val_p2 != seedGroups.end()) {
    part2 = (*min_val_p2).fr;
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

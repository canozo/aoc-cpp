#include <algorithm>
#include <array>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <aoc.h>
#include <vector>

namespace event23::day07 {

constexpr int EVENT = 2023;
constexpr int DAY = 7;

constexpr unsigned int FIVE_OF_A_KIND = 6;
constexpr unsigned int FOUR_OF_A_KIND = 5;
constexpr unsigned int FULL_HOUSE = 4;
constexpr unsigned int THREE_OF_A_KIND = 3;
constexpr unsigned int TWO_PAIR = 2;
constexpr unsigned int ONE_PAIR = 1;
constexpr unsigned int HIGH_CARD = 0;

constexpr unsigned int STEP_START = 12 + 1;

constexpr std::array<char, 14> cards = {
  'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2',
};

const std::map<char, unsigned int> values = {
  { 'A', 12 },
  { 'K', 11 },
  { 'Q', 10 },
  { 'J',  9 },
  { 'T',  8 },
  { '9',  7 },
  { '8',  6 },
  { '7',  5 },
  { '6',  4 },
  { '5',  3 },
  { '4',  2 },
  { '3',  1 },
  { '2',  0 },
};

struct Hand {
  std::string cards;
  unsigned int bid;
  unsigned int weight = 0;
};

std::map<unsigned int, unsigned int> calculated = {
  { 12,   1 },
  { 13,  13 },
  { 14, 182 },
};

unsigned int step_func(const unsigned int n) {
  auto it_was_calculated = calculated.find(n);

  if (it_was_calculated != calculated.end()) {
    return it_was_calculated->second;
  }

  if (n <= 12) {
    return 1;
  }

  auto result = n * step_func(n - 1);
  calculated.insert({ n, result });

  return result;
}

unsigned int w8_hand(std::string &hand) {
  unsigned int result = values.at(hand.at(4));
  unsigned int step = STEP_START;

  for (auto it = hand.rbegin() + 1; it != hand.rend(); ++it) {
    result += values.at(*it) * step_func(step++);
  }

  return result;
}

unsigned int combo(const std::string &hand) {
  unsigned int pairs = 0;
  bool has_three = false;
  char seen_pair_of = '0';

  for (const char &c : hand) {
    auto count = std::count(hand.begin(), hand.end(), c);

    switch (count) {
      case 5:
        return FIVE_OF_A_KIND;

      case 4:
        return FOUR_OF_A_KIND;

      case 3:
        has_three = true;
        break;

      case 2:
        if (c == seen_pair_of) {
          break;
        }

        if (++pairs == 2) {
          return TWO_PAIR;
        }

        seen_pair_of = c;
        break;

      default:
        break;
    }
  }

  if (has_three) {
    return pairs ? FULL_HOUSE : THREE_OF_A_KIND;
  }

  return pairs ? ONE_PAIR : HIGH_CARD;
}

aoc::Answer solve(const std::string &filename = "input.txt") {
  unsigned int part1 = 0;
  unsigned int part2 = 0;

  std::ifstream input("inputs/event23/day07/" + filename);

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  std::vector<Hand> hands;

  for (std::string line; std::getline(input, line);) {
    Hand hand {
      line.substr(0, 5),
      (unsigned int) std::stoul(line.substr(6)),
    };

    hand.weight = w8_hand(hand.cards);
    hand.weight = combo(hand.cards) * 10'000'000 + w8_hand(hand.cards);

    hands.push_back(hand);
  }

  std::sort(hands.begin(), hands.end(), [](auto const &l, auto const &r) {
    return l.weight < r.weight;
  });

  unsigned int rank = 1;

  for (auto const &hand : hands) {
    part1 += hand.bid * rank++;
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

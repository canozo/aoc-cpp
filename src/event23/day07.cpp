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

const std::map<char, unsigned int> normal_vals = {
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

const std::map<char, unsigned int> jokers_vals = {
  { 'A', 12 },
  { 'K', 11 },
  { 'Q', 10 },
  { 'T',  9 },
  { '9',  8 },
  { '8',  7 },
  { '7',  6 },
  { '6',  5 },
  { '5',  4 },
  { '4',  3 },
  { '3',  2 },
  { '2',  1 },
  { 'J',  0 },
};

struct Hand {
  std::string cards;
  unsigned int bid;
  unsigned int normal_weight = 0;
  unsigned int jokers_weight = 0;
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

unsigned int w8_hand(const std::string &hand, const bool jokers = false) {
  const auto c = hand.at(4);
  unsigned int result = jokers ? jokers_vals.at(c) : normal_vals.at(c);
  unsigned int step = STEP_START;

  for (auto it = hand.rbegin() + 1; it != hand.rend(); ++it) {
    auto card_value = jokers ? jokers_vals.at(*it) : normal_vals.at(*it);
    result += card_value * step_func(step++);
  }

  return result;
}

constexpr unsigned int
hasThree(
  const unsigned int pairs,
  const unsigned int jokers,
  const bool with_joker
) {
  if (!jokers || !with_joker) {
    return pairs ? FULL_HOUSE : THREE_OF_A_KIND;
  }

  switch (jokers) {
    case 3:
      return pairs ? FIVE_OF_A_KIND : FOUR_OF_A_KIND;

    case 2:
      return FIVE_OF_A_KIND;

    case 1:
      return FOUR_OF_A_KIND;

    default:
      break;
  }

  return THREE_OF_A_KIND;
}

constexpr unsigned int
hasTwoPairs(
  const unsigned int jokers,
  const bool with_joker
) {
  if (!jokers || !with_joker) {
    return TWO_PAIR;
  }

  return jokers == 2 ? FOUR_OF_A_KIND : FULL_HOUSE;
}

constexpr unsigned int
hasPairOrNothing(
  const unsigned int pairs,
  const unsigned int jokers,
  const bool with_joker
) {
  if (!jokers || !with_joker) {
    return pairs ? ONE_PAIR : HIGH_CARD;
  }

  return pairs ? THREE_OF_A_KIND : ONE_PAIR;
}

constexpr unsigned int
combo(const std::string &hand, const bool with_joker = false) {
  unsigned int pairs = 0;
  unsigned int jokers = 0;

  bool has_four = false;
  bool has_three = false;
  char seen_pair_of = '0';

  for (const char &c : hand) {
    auto count = std::count(hand.begin(), hand.end(), c);

    if (c == 'J') {
      jokers++;
    }

    switch (count) {
      case 5:
        return FIVE_OF_A_KIND;

      case 4:
        has_four = true;
        break;

      case 3:
        has_three = true;
        break;

      case 2:
        if (c == seen_pair_of || pairs == 2) {
          break;
        }

        pairs++;
        seen_pair_of = c;
        break;

      default:
        break;
    }
  }

  if (has_four) {
    return with_joker && jokers ? FIVE_OF_A_KIND : FOUR_OF_A_KIND;
  }

  if (has_three) {
    return hasThree(pairs, jokers, with_joker);
  }

  if (pairs == 2) {
    return hasTwoPairs(jokers, with_joker);
  }

  return hasPairOrNothing(pairs, jokers, with_joker);
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

    hand.normal_weight = combo(hand.cards) * 10'000'000
      + w8_hand(hand.cards);

    hand.jokers_weight = combo(hand.cards, true) * 10'000'000
      + w8_hand(hand.cards, true);

    hands.push_back(hand);
  }

  // part 1 sort
  std::sort(hands.begin(), hands.end(), [](auto const &l, auto const &r) {
    return l.normal_weight < r.normal_weight;
  });

  unsigned int rank = 1;

  for (auto const &hand : hands) {
    part1 += hand.bid * rank++;
  }

  // part 2 sort
  std::sort(hands.begin(), hands.end(), [](auto const &l, auto const &r) {
    return l.jokers_weight < r.jokers_weight;
  });

  rank = 1;

  for (auto const &hand : hands) {
    part2 += hand.bid * rank++;
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

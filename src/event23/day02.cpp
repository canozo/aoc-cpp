#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <aoc.h>

namespace event23::day02 {

constexpr int EVENT = 2023;
constexpr int DAY = 2;

constexpr int ID_BEGIN = 5;

constexpr int R_P1_MAX = 12;
constexpr int G_P1_MAX = 13;
constexpr int B_P1_MAX = 14;

aoc::Answer solve() {
  int part1 = 0;
  int part2 = 0;

  std::ifstream input("inputs/event23/day02/input.txt");

  if (!input) {
    return aoc::Answer { EVENT, DAY, "", "" };
  }

  for (std::string line; std::getline(input, line);) {
    int game_num = 0;
    int number_pos = -1;
    int r, g, b;
    r = g = b = 0;
    bool overflow = false;

    for (int idx = ID_BEGIN; idx < line.length(); idx++) {
      char curr = line[idx];
      int temp_r, temp_g, temp_b;
      temp_r = temp_g = temp_b = 0;

      switch (curr) {
      case ',':
      case ';':
        idx++;
        break;

      case ' ':
        continue;

      case ':':
        game_num = std::stoi(line.substr(ID_BEGIN, idx - ID_BEGIN));
        idx++;
        break;

      case 'r':
        temp_r = std::stoi(line.substr(number_pos, idx - number_pos - 1));
        r = std::max(r, temp_r);
        overflow |= temp_r > R_P1_MAX;
        idx += 2;
        number_pos = -1;
        break;

      case 'g':
        temp_g = std::stoi(line.substr(number_pos, idx - number_pos - 1));
        g = std::max(g, temp_g);
        overflow |= temp_g > G_P1_MAX;
        idx += 4;
        number_pos = -1;
        break;

      case 'b':
        temp_b = std::stoi(line.substr(number_pos, idx - number_pos - 1));
        b = std::max(b, temp_b);
        overflow |= temp_b > B_P1_MAX;
        idx += 3;
        number_pos = -1;
        break;

      default:
        if (game_num && number_pos == -1 && std::isdigit(curr)) {
          number_pos = idx;
        }
        break;
      }
    }

    if (!overflow) {
      part1 += game_num;
    }

    part2 += r * g * b;
  }

  return aoc::Answer {
    EVENT,
    DAY,
    std::to_string(part1),
    std::to_string(part2),
  };
}

}

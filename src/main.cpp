#include <iostream>
#include <format>
#include <sstream>
#include <vector>
#include <aoc.h>
#include "event23/day01.h"

void add_divider(std::stringstream &stream) {
  stream << std::format("+{0:->7}+{0:->5}+{0:->12}+{0:->12}+\n", '-');
}

void add_header(std::stringstream &stream) {
  add_divider(stream);
  stream << std::format("| event | day | part 1     | part 2     |\n");
  add_divider(stream);
}

int main(int argc, char *argv[]) {
  std::vector<aoc::Answer> answers {
    event23::day01::solve(),
  };

  std::stringstream output;
  add_header(output);

  for (auto answer : answers) {
    output << std::format(
      "| {:<5} | {:<3} | {:<10} | {:<10} |\n",
      answer.event,
      answer.day,
      answer.part1,
      answer.part2);
  }

  add_divider(output);
  std::cout << output.str();

  return 0;
}

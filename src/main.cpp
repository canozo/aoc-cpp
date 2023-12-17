#include <iostream>
#include <format>
#include <sstream>
#include <vector>
#include <aoc.h>
#include "event23/day01.h"
#include "event23/day02.h"
#include "event23/day03.h"
#include "event23/day04.h"
#include "event23/day05.h"
#include "event23/day06.h"
#include "event23/day07.h"
#include "event23/day08.h"
#include "event23/day09.h"
#include "event23/day10.h"
#include "event23/day11.h"
#include "event23/day12.h"
#include "event23/day13.h"
#include "event23/day14.h"
#include "event23/day15.h"
#include "event23/day16.h"
#include "event23/day17.h"
#include "event23/day18.h"
#include "event23/day19.h"
#include "event23/day20.h"
#include "event23/day21.h"
#include "event23/day22.h"
#include "event23/day23.h"
#include "event23/day24.h"
#include "event23/day25.h"

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
    event23::day02::solve(),
    event23::day03::solve(),
    event23::day04::solve(),
    event23::day05::solve(),
    event23::day06::solve(),
    event23::day07::solve(),
    event23::day08::solve(),
    event23::day09::solve(),
    event23::day10::solve(),
    event23::day11::solve(),
    event23::day12::solve(),
    event23::day13::solve(),
    event23::day14::solve(),
    event23::day15::solve(),
    event23::day16::solve(),
    event23::day17::solve(),
    event23::day18::solve(),
    event23::day19::solve(),
    event23::day20::solve(),
    event23::day21::solve(),
    event23::day22::solve(),
    event23::day23::solve(),
    event23::day24::solve(),
    event23::day25::solve(),
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

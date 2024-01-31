#include <array>
#include <iostream>
#include <format>
#include <sstream>
#include <string>
#include <aoc.h>
#include "event23/all.h"

void add_divider(std::stringstream &stream) {
  stream << std::format("+{0:->7}+{0:->5}+{0:->12}+{0:->12}+\n", '-');
}

void add_header(std::stringstream &stream) {
  add_divider(stream);
  stream << std::format("| event | day | part 1     | part 2     |\n");
  add_divider(stream);
}

int main(int argc, char *argv[]) {
  std::string input_filename = "input.txt";

  if (argc > 1) {
    input_filename = argv[1];
  }

  std::array<aoc::Answer, 8> answers {
    event23::day01::solve(input_filename),
    event23::day02::solve(input_filename),
    event23::day03::solve(input_filename),
    event23::day04::solve(input_filename),
    event23::day05::solve(input_filename),
    event23::day06::solve(input_filename),
    event23::day07::solve(input_filename),
    event23::day08::solve(input_filename),
    // event23::day09::solve(input_filename),
    // event23::day10::solve(input_filename),
    // event23::day11::solve(input_filename),
    // event23::day12::solve(input_filename),
    // event23::day13::solve(input_filename),
    // event23::day14::solve(input_filename),
    // event23::day15::solve(input_filename),
    // event23::day16::solve(input_filename),
    // event23::day17::solve(input_filename),
    // event23::day18::solve(input_filename),
    // event23::day19::solve(input_filename),
    // event23::day20::solve(input_filename),
    // event23::day21::solve(input_filename),
    // event23::day22::solve(input_filename),
    // event23::day23::solve(input_filename),
    // event23::day24::solve(input_filename),
    // event23::day25::solve(input_filename),
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

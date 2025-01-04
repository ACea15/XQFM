#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

// Extend the Config class accordingly.
class Config {
public:
  int num_paths = 1000;
  int num_steps = 100;
  float strike = 1.;
  float spot = 1.;
  float mu = 0.05;
  float sigma = 0.2;
  float periodT = 1.;

  // Config() { initializeHandlers(); }

  void loadFromFile(const std::string &filename);

private:
  std::unordered_map<std::string, std::function<void(const std::string &)>>
      handlers;

  void initializeHandlers();

  // Utility to strip whitespace
  static std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos)
      return ""; // Handles strings with only spaces
    return str.substr(first, (last - first + 1));
  }
};

template <typename T> T convertString(const std::string &value);

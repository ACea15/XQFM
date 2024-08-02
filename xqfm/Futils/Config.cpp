#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <set>

#include "Config.hpp"

using namespace std;

// Function to trim spaces from the beginning and end of a string
std::string ParseInput::trim(const std::string &str) {
  size_t first = str.find_first_not_of(' ');
  if (std::string::npos == first) {
    return str; // No non-space characters
  }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

void ParseInput::read_file(string file_name) {
  std::ifstream inputFile(file_name);

  if (!inputFile) {
    std::cerr << "Error opening the file." << std::endl;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::istringstream iss2(line);
    string key1, key2;
    char equalSign, underscoreSign;
    std::string valueStr;

    size_t posEq = line.find('=');

    if (posEq != std::string::npos) { // Check if '=' is found
      std::string beforeEqual = trim(line.substr(0, posEq));
      std::string afterEqual = trim(line.substr(posEq + 1));
      size_t pos_ = beforeEqual.find('_');
      if (pos_ != std::string::npos) { // Check if '=' is found
        std::string before_ = beforeEqual.substr(0, pos_);
        std::string after_ = beforeEqual.substr(pos_ + 1);
        map_containers[before_][after_] = afterEqual;
      } else {
        map_vars[beforeEqual] = afterEqual;
      }

    } else {
      std::cout << "Equal sign '=' not found in the input." << std::endl;
    }
  }
}

void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, int &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}
void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, unsigned long &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}
void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, double &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}
void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, std::string &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}


Config1::Config1(std::map<string, std::map<string, string>> map,
	  std::map<std::string, std::string> map_vars) {
    SetValues(map_vars);
    SetContainers(map);
  }
Config1::Config1(std::map<string, std::map<string, string>> map) {
    SetContainers(map);
  }
  
void Config1::SetContainers(std::map<string, std::map<string, string>> map) {
    for (const auto &mi : map) {
      const std::map<string, string> &innerMap = mi.second;
      std::string value = mi.first;
      if (value == "Cmc1")
	ct1 = new Cmc1(innerMap);
        std::cout << "*** Setting" << value << std::endl;
    }
  }
  
  void Config1::SetValues(std::map<std::string, std::string> mapvars) {
    if (!map_vars.empty())
      map_vars = mapvars;
  }
  void Config1::Serialise(std::map<char, std::string> map) {}
  
 Config1::~Config1() {
    if (ct1 != nullptr)
      delete ct1;
  }

Config1 buildConfig(std::string input){
  ParseInput parse = ParseInput();
  parse.read_file(input);
  Config1 config = Config1(parse.map_containers,
			   parse.map_vars);
  return config;
}

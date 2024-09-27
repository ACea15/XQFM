#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Containers.cpp"

// #include "Config.hpp"

using namespace std;



class Config{

  std::map<string, std::shared_ptr<Container>> mapvar;
  ContainerFactory factory;

public:
  std::shared_ptr<Container> mc1;

  Config(std::map<string, string>):
  {
  };
    
};


// template<typename T>
// Config1 buildConfig(std::string input) {
//   ParseInput parse = ParseInput();
//   parse.read_file(input);
//   Config1 config = Config1(parse.map_containers, parse.map_vars);
//   return config;
// }

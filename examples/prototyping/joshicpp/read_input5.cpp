#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>


struct CBlackScholes {
  
  double vol;
  double rate;
  
};

struct Csett {
  
  double a;
  double b;
  
};



struct Config {
  CBlackScholes* Gbs;
  Csett* Gsett;
  int a;
  float b;
  std::string c;

  
  void SetValues(std::map<char, std::string> map) {
    std::istringstream iss_a(map['a']);
    iss_a >> a;
    std::istringstream iss_b(map['b']);
    iss_b >> b;
    std::istringstream iss_c(map['c']);
    iss_c >> c;
  }

  
};




int main() {

  Config config = Config();
  std::ifstream inputFile("input.txt"); // Change 'input.txt' to your file name
  // std::map<char, std::map<char, std::unique_ptr<Value>>> myMap;
  std::map<char, std::string> myMap;
  if (!inputFile) {
    std::cerr << "Error opening the file." << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    char key1, key2, equalSign; //, underscoreSign;
    std::string valueStr;

    if (iss >> key1 >> equalSign >> valueStr && equalSign == '=') {
      myMap[key1] = valueStr;
    } else {
      std::cerr << "Error parsing line: " << line << std::endl;
    }
  }
  config.SetValues(myMap);
  for (auto const &x : myMap) {
    std::cout << x.first         // string (key)
              << ':' << x.second // string's value
              << std::endl;
  }
  std::cout << "###########" << std::endl;
  std::cout << "a " << config.a << std::endl;
  std::cout << "b " << config.b << std::endl;
  std::cout << "d " << config.b + config.a << std::endl;
    
  return 0;
}

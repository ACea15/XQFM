#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

struct Container {

  virtual void SetValues(std::map<std::string, std::string> map) = 0;
  virtual ~Container() = default;
  // Container(std::map<std::string, std::string> map) {
  //   SetValues(map);
  // }
  
  void writeValue(std::map<std::string, std::string> map,
		      std::string name,
		      int &value){
    std::istringstream iss(map[name]);
    iss >> value;
  }
  void writeValue(std::map<std::string, std::string> map,
		      std::string name,
		      double &value){
    std::istringstream iss(map[name]);
    iss >> value;
  }  
  void writeValue(std::map<std::string, std::string> map,
		      std::string name,
		      std::string &value){
    std::istringstream iss(map[name]);
    iss >> value;
  }
  
};


struct C1: Container {
  
  int a=9;
  string b;
  
  // void SetValues(std::map<std::string, std::string> map) override {
  //   std::istringstream iss_a(map[string("a")]);
  //   iss_a >> a;
  //   std::istringstream iss_b(map[string("b")]);
  //   iss_b >> b;
  
  // }

  C1(std::map<std::string, std::string> map) {
    SetValues(map);
  }
    
  void SetValues(std::map<std::string, std::string> map) override {
    writeValue(map, "a", a);
    writeValue(map, "b", b);      
  }
  
};


class Config {
public:
  virtual void SetContainers(std::map<string, std::map<string, string>> map) =0;
  virtual void SetValues(std::map<std::string, std::string> map_vars) = 0;
  virtual void Serialise(std::map<char, std::string> map) = 0;
  virtual ~Config() = default;
};


class Config1: public Config {
public:
  int a1 = 5;
  C1* ct1 = nullptr;
  
  Config1(std::map<string, std::map<string, string>> map,
	  std::map<std::string, std::string> map_vars) {
    SetValues(map_vars);
    SetContainers(map);
  }
  
  virtual void SetContainers(std::map<string, std::map<string, string>> map) override{
      ct1 = new C1(map["C1"]);
  }
  
  void SetValues(std::map<std::string, std::string> map_vars) override {
    std::istringstream iss_a1(map_vars[string("a1")]);
    iss_a1 >> a1;
  }
  
  virtual void Serialise(std::map<char, std::string> map) override {}
  virtual ~Config1() {
    delete ct1;
  }
};



/*!
 * \class ParseInput
 * \brief Parses and input file and groups inputs into a map
 */
class ParseInput {

  // Function to trim spaces from the beginning and end of a string
  std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
      return str; // No non-space characters
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
  }

  public:
  std::map<string, string> map_vars;
  std::map<string, std::map<string, string>> map;
  //std::set<string> input_groups;
  
  // void build_inputmaps(){
    
  //   for (auto const &x : input_map) {
  //     auto key = x.first;
  //     auto value = x.second;
  //     auto key1 = key.first;
  //     auto key2 = key.second;
  //     if 
  //     input_groups.insert(key1)
  //     std::cout << x.first         // string (key)
  // 		<< ':' << x.second // string's value
  // 		<< std::endl;
  //   }

  // }
  
  void read_file(string file_name) {
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
	    map[before_][after_] = afterEqual;
	  }
	  else {
	    map_vars[beforeEqual] = afterEqual;
	  }
	  
	}
	else {
	  std::cout << "Equal sign '=' not found in the input." << std::endl;
	}
    }
  }
  
};


int main() {

  ParseInput parse = ParseInput();
  parse.read_file("input4.txt");
  Config1 config = Config1(parse.map,
			   parse.map_vars);
  std::cout << " => Num elements map: " << parse.map.size() << std::endl;
  // Accessing elements in the map
  for (const auto &pair : parse.map) {
    const std::map<string, string> &innerMap = pair.second;
    std::string value = pair.first;
    std::cout << " => Group: " << value << std::endl;
    std::cout << "Inner Map: ";
    for (const auto &innerPair : innerMap) {
      std::cout << "{" << innerPair.first << ", " << innerPair.second << "} " << std::endl;
    }
    
    std::cout << "--------------" << std::endl;
  }

  // Accessing elements in the map
  for (const auto &pair : parse.map_vars) {
    std::string value = pair.first;
    std::cout << " =>  " << pair.first << ", " << pair.second << std::endl;    
    std::cout << "--------------" << std::endl;
  }

  std::cout << " =>  a1:" << config.a1 << ", "  << std::endl;
  std::cout << " =>  a:" << config.ct1->a << ", "  << std::endl;
  std::cout << " =>  b:" << config.ct1->b << ", "  << std::endl;    
  // config.SetValues(myMap);
  // for (auto const &x : myMap) {
  //   std::cout << x.first         // string (key)
  //             << ':' << x.second // string's value
  //             << std::endl;
  // }
  // std::cout << "###########" << std::endl;
  // std::cout << "a " << config.a << std::endl;
  // std::cout << "b " << config.b << std::endl;
  // std::cout << "d " << config.b + config.a << std::endl;
    
  return 0;
}

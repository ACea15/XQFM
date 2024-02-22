#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;


class Config {
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


/*!
 * \class ParseInput
 * \brief Parses and input file and groups inputs into a map
 */
class ParseInput {

  
  std::map<string, std::map<string, string>> input_map;
  std::vector<std::map<string, string>> input_maps;
  std::set<string> input_groups;
  void build_inputmaps(){
    
    for (auto const &x : input_map) {
      auto key1 = x.first;
      if 
      input_groups.insert()
      std::cout << x.first         // string (key)
		<< ':' << x.second // string's value
		<< std::endl;
    }

  }
  void read_file(string file_name) {
    std::ifstream inputFile(file_name);

    if (!inputFile) {
        std::cerr << "Error opening the file." << std::endl;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        string key1, key2;
	char equalSign, underscoreSign;
        std::string valueStr;

        if (iss >> key1 >> underscoreSign >> key2 >> equalSign >>  valueStr && equalSign == '='
	     && underscoreSign == '_') {
            input_map[key1][key2] = valueStr;
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }


  }
  
};

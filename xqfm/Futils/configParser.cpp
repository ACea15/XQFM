#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

#include <unordered_map>
#include <string>

using NestedMap = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

class ConfigParser {
public:
  bool parseFile(const std::string& filename);
  const NestedMap& getConfig() const;
  void printConfig() const;
  
private:
  NestedMap configMap;
  static std::string trim(const std::string& s);
};

std::string ConfigParser::trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;

    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

void ConfigParser::printConfig() const{

  for (const auto& [container, vars] : configMap) {
    std::cout << "[" << container << "]\n";
    for (const auto& [key, value] : vars) {
      std::cout << "  " << key << " = " << value << "\n";
    }
  }
}

bool ConfigParser::parseFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Could not open config file: " << filename << '\n';
        return false;
    }

    std::string line;
    size_t lineNum = 0;
    while (std::getline(infile, line)) {
        lineNum++;
        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue; // skip comments and empty lines
        }

        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos) {
            std::cerr << "Invalid line " << lineNum << ": no '=' found\n";
            continue;
        }

        std::string keyPart = trim(line.substr(0, eqPos));
        std::string valuePart = trim(line.substr(eqPos + 1));

        size_t dotPos = keyPart.find('.');
        if (dotPos == std::string::npos) {
            std::cerr << "Invalid line " << lineNum << ": no '.' in key\n";
            continue;
        }

        std::string container = trim(keyPart.substr(0, dotPos));
        std::string variable = trim(keyPart.substr(dotPos + 1));

        configMap[container][variable] = valuePart;
    }

    return true;
}

const NestedMap& ConfigParser::getConfig() const {
    return configMap;
}

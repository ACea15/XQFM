#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

template<typename T>
void parseValue(const std::string& valueStr, T& value) {
    std::istringstream iss(valueStr);
    iss >> value;
}

int main() {
    std::ifstream inputFile("input.txt"); // Change 'input.txt' to your file name
    std::map<char, std::map<char, std::variant<int, double, std::string>>> myMap;

    if (!inputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        char key1, key2, equalSign;
        std::string valueStr;

        if (iss >> key1 >> equalSign >> key2 >> valueStr && equalSign == '=') {
            std::variant<int, double, std::string> value;
            parseValue(valueStr, value);
            myMap[key1][key2] = value;
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    // Now you have the map filled with the data from the file
    // You can use it as needed.

    // Example: Printing the map
    for (const auto& outerPair : myMap) {
        for (const auto& innerPair : outerPair.second) {
            std::cout << "map['" << outerPair.first << "']['" << innerPair.first << "'] = ";

            // Using std::visit to handle different value types
            std::visit([](const auto& value) {
                std::cout << value;
            }, innerPair.second);

            std::cout << std::endl;
        }
    }

    return 0;
}

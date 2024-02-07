#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class Value {
public:
    virtual ~Value() {}
    virtual void parse(const std::string& valueStr) = 0;
};

class IntValue : public Value {
public:
    int value;
    void parse(const std::string& valueStr) override {
        std::istringstream iss(valueStr);
        iss >> value;
    }
};

class DoubleValue : public Value {
public:
    double value;
    void parse(const std::string& valueStr) override {
        std::istringstream iss(valueStr);
        iss >> value;
    }
};

class StringValue : public Value {
public:
    std::string value;
    void parse(const std::string& valueStr) override {
        value = valueStr;
    }
};

int main() {
    std::ifstream inputFile("input2.txt"); // Change 'input.txt' to your file name
    std::map<char, std::map<char, Value*>> myMap;

    if (!inputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        char key1, key2, equalSign, underscoreSign;
        std::string valueStr;

        if (iss >> key1 >> underscoreSign >> key2 >> equalSign >>  valueStr && equalSign == '=') {
            Value* value = nullptr;

            if (valueStr.find('.') != std::string::npos) {
                value = new DoubleValue();
            } else if (valueStr.find_first_not_of("0123456789") == std::string::npos) {
                value = new IntValue();
            } else {
                value = new StringValue();
            }

            value->parse(valueStr);
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

            // Using dynamic_cast to determine the actual type
            if (auto intValue = dynamic_cast<IntValue*>(innerPair.second)) {
                std::cout << intValue->value;
            } else if (auto doubleValue = dynamic_cast<DoubleValue*>(innerPair.second)) {
                std::cout << doubleValue->value;
            } else if (auto stringValue = dynamic_cast<StringValue*>(innerPair.second)) {
                std::cout << stringValue->value;
            }
	    // std::cout << innerPair.second->value;
            std::cout << std::endl;
        }
    }

    // Don't forget to clean up allocated memory
    for (auto& outerPair : myMap) {
        for (auto& innerPair : outerPair.second) {
            delete innerPair.second;
        }
    }

    return 0;
}

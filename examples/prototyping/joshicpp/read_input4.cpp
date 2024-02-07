#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>

class Value {
public:
    virtual ~Value() {}
    virtual void parse(const std::string& valueStr) = 0;
    virtual const void* getValue() const = 0;
};

class IntValue : public Value {
public:
    int value;
    void parse(const std::string& valueStr) override {
        std::istringstream iss(valueStr);
        iss >> value;
    }
    const void* getValue() const override {
        return &value;
    }
};

class DoubleValue : public Value {
public:
    double value;
    void parse(const std::string& valueStr) override {
        std::istringstream iss(valueStr);
        iss >> value;
    }
    const void* getValue() const override {
        return &value;
    }
};

class StringValue : public Value {
public:
    std::string value;
    void parse(const std::string& valueStr) override {
        value = valueStr;
    }
    const void* getValue() const override {
        return &value;
    }
};

std::unique_ptr<Value> createValue(const std::string& valueStr) {
    if (valueStr.find('.') != std::string::npos) {
        auto doubleValue = std::make_unique<DoubleValue>();
        doubleValue->parse(valueStr);
        return std::move(doubleValue);
    } else if (valueStr.find_first_not_of("0123456789") == std::string::npos) {
        auto intValue = std::make_unique<IntValue>();
        intValue->parse(valueStr);
        return std::move(intValue);
    } else {
        auto stringValue = std::make_unique<StringValue>();
        stringValue->parse(valueStr);
        return std::move(stringValue);
    }
}

int main() {
    std::ifstream inputFile("input2.txt"); // Change 'input.txt' to your file name
    std::map<char, std::map<char, std::unique_ptr<Value>>> myMap;

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
            myMap[key1][key2] = createValue(valueStr);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    // Now you have the map filled with the data from the file
    // You can use it as needed.

    // Example: Accessing the value directly
    // if (myMap['a']['l']) {
    //     const void* value = myMap['a']['b']->getValue();
    // 	std::cout << "done" << std::endl;
    //     // Now, value points to the stored value
    //     // You can use it as appropriate based on the type
    // }
    //if (myMap.count('a') && myMap['a'].count('l') && myMap['a']['l']) {
    if (myMap['a']['l']) {  
        const void* value = myMap['a']['l']->getValue();
	std::cout << "Value: " << *static_cast<const int*>(value) << std::endl;
	std::cout << "done" << std::endl;
        // Now, value points to the stored value
        // You can use it as appropriate based on the type
    }

    return 0;
}

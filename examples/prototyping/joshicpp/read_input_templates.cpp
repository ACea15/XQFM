#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

// Define a structure to hold the data
struct MyData {
    int a;
    double b;
    std::string c;
};

// Utility struct for type-to-string mapping
template <typename T>
struct TypeToString {
    static std::string value() {
        return "unknown";
    }
};

// Specializations for TypeToString to map types to their names
template <>
struct TypeToString<int> {
    static std::string value() {
        return "int";
    }
};

template <>
struct TypeToString<double> {
    static std::string value() {
        return "double";
    }
};

template <>
struct TypeToString<std::string> {
    static std::string value() {
        return "string";
    }
};

// Utility function to create a map of variable names and their types
template <typename StructType>
std::map<std::string, std::string> createVariableTypeMap() {
    std::map<std::string, std::string> variableTypes;

    variableTypes["a"] = TypeToString<decltype(StructType::a)>::value();
    variableTypes["b"] = TypeToString<decltype(StructType::b)>::value();
    variableTypes["c"] = TypeToString<decltype(StructType::c)>::value();

    return variableTypes;
}

int main() {
    std::string filename = "input.txt"; // Replace with your input file name
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    MyData myData;

    // Create a map of variable names and their types automatically from MyData
    std::map<std::string, std::string> variableTypes = createVariableTypeMap<MyData>();

    std::string line;
    while (std::getline(inputFile, line)) {
      std::string variableName, valueString;
        //char equalSign;

        //std::istringstream iss(line);
        //iss >> variableName >> equalSign >> valueString;
        // Split the line into variable name and value
        size_t equalPos = line.find('=');
        if (equalPos != std::string::npos) {
            std::string variableName = line.substr(0, equalPos);
            std::string valueString = line.substr(equalPos + 1);
            //data[variable] = value;
        }
    
        // Check if the variable is in the map of known types
        if (variableTypes.find(variableName) != variableTypes.end()) {
            // Determine the type of the variable
            const std::string& type = variableTypes[variableName];

            // Use the type information to convert the string to the appropriate type
            if (type == "int") {
                myData.a = std::stoi(valueString);
            } else if (type == "double") {
                myData.b = std::stod(valueString);
            } else if (type == "string") {
                myData.c = valueString;
            }
        }
    }

    inputFile.close(); // Close the input file

    // Access and use the initialized struct
    std::cout << "a: " << myData.a << std::endl;
    std::cout << "b: " << myData.b << std::endl;
    std::cout << "c: " << myData.c << std::endl;

    return 0;
}

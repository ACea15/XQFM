#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <map>

// Define a structure to hold the data
struct MyData {
  int a;
  double b;
  std::string c;
  MyData(int a_, float b_, std::string c_) : a(a_), b(b_), c(c_) {}
  MyData() : a(1), b(2.5), c(std::string("ll")) {}
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
    MyData try1 = MyData(1,2.5,std::string("ll"));
    variableTypes["a"] = TypeToString<decltype(try1.a)>::value();
    variableTypes["b"] = TypeToString<decltype(try1.b)>::value();
    variableTypes["c"] = TypeToString<decltype(try1.c)>::value();
    
    // variableTypes["a"] = TypeToString<decltype(StructTypea)>::value();
    // variableTypes["b"] = TypeToString<decltype(StructType::b)>::value();
    // variableTypes["c"] = TypeToString<decltype(StructType::c)>::value();

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
	std::istringstream iss(line);
        while (std::getline(iss, variableName, '=')) {
            // Remove leading and trailing spaces from variableName
            variableName.erase(variableName.find_last_not_of(" \t") + 1);
            variableName.erase(0, variableName.find_first_not_of(" \t"));

            // Remove leading and trailing spaces from the rest of the line
            //iss >> std::ws;

            if (std::getline(iss, valueString)) {
                // Remove leading and trailing spaces from valueString
                valueString.erase(valueString.find_last_not_of(" \t") + 1);
                valueString.erase(0, valueString.find_first_not_of(" \t"));

                // Process variableName and valueString
                // For example, you can convert valueString to the desired type (e.g., int, double, string)
                // and store it in a map or other data structure.
                std::cout << "Variable Name: " << variableName << " | Value: " << valueString << std::endl;
            } else {
                std::cerr << "Invalid line format: " << line << std::endl;
            }}	
        // if (std::getline(iss, variableName, '=') && std::getline(iss, valueString)) {
        //     // Process variableName and valueString
        //     // For example, you can convert valueString to the desired type (e.g., int, double, string)
        //     // and store it in a map or other data structure.
        //     std::cout << "Variable Name: " << variableName << " | Value: " << valueString << std::endl;
        // }
	// else if (std::getline(iss, variableName, '=') && std::getline(iss, valueString)) {
	//   std::cout << "Variable Name: " << variableName << " | Value: " << valueString << std::endl;
	// }
	// else {
        //     std::cerr << "Invalid line format: " << line << std::endl;
        // }

        // Check if the variable is in the map of known types
        //if (variableTypes.find(variableName) != variableTypes.end()) {
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

    inputFile.close(); // Close the input file

    // Access and use the initialized struct
    std::cout << "a: " << myData.a << std::endl;
    std::cout << "b: " << myData.b << std::endl;
    std::cout << "c: " << myData.c << std::endl;

    return 0;
}

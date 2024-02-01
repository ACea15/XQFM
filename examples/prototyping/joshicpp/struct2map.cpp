#include <iostream>
#include <map>
#include <string>

// Helper function to convert any type to string
template <typename T>
std::string to_string(const T& value) {
    return std::to_string(value);
}

// Overload for string type to avoid adding quotes
std::string to_string(const std::string& value) {
    return value;
}

// Struct to be processed
struct MyStruct {
    int age;
    double salary;
    std::string name;
};

// Function to convert struct to map
template <typename StructType>
std::map<std::string, std::string> structToMap(const StructType& myStruct) {
    std::map<std::string, std::string> result;

    // Helper lambda to add key-value pairs to the map
    auto addKeyValuePair = [&result](const std::string& key, const auto& value) {
        result[key] = to_string(value);
    };

    // Iterate through each member variable in the struct
    // and add its name and value to the map
    // Note: Requires C++17 or later for structured bindings
    for (const auto& [key, value] : myStruct) {
        addKeyValuePair(key, value);
    }

    return result;
}

int main() {
    MyStruct myObject{25, 50000.5, "John"};

    // Convert struct to map
    std::map<std::string, std::string> resultMap = structToMap(myObject);

    // Print the resulting map
    for (const auto& [key, value] : resultMap) {
        std::cout << key << ": " << value << std::endl;
    }

    return 0;
}

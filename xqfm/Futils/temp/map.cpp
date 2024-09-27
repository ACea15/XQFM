#include <iostream>
#include <map>
#include <string>

class MyClass {
public:
    std::map<std::string, int> myMap;
    int& a;
    int& b;

    MyClass()
        : a(insertAndGetReference("a", 0)),
          b(insertAndGetReference("b", 0)) {}

    void initializeMap() {
        myMap["a"] = 1;
        myMap["b"] = 2;
    }

    void print() const {
        std::cout << "a: " << a << "\n";
        std::cout << "b: " << b << "\n";
    }

private:
    int& insertAndGetReference(const std::string& key, int defaultValue) {
        myMap[key] = defaultValue; // Insert the key with a default value
        return myMap[key]; // Return reference to the inserted value
    }
};

int main() {
    MyClass obj;
    obj.initializeMap(); // Initialize the map with values

    obj.print(); // Print values

    obj.myMap["a"] = 10; // Modify the map
    obj.print(); // Should reflect the changes

    return 0;
}

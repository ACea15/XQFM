#include <iostream>
#include <memory>

class MyClass {
private:
    // Initialize shared pointers to nullptr
    std::shared_ptr<int> ptr1;
    std::shared_ptr<int> ptr2;

public:
    // MyClass() : ptr1(nullptr), ptr2(nullptr) { 
    //     // Constructor body
    // }

    void assignPtr1(int value) {
        ptr1 = std::make_shared<int>(value);
    }

    void assignPtr2(int value) {
        ptr2 = std::make_shared<int>(value);
    }

    void print() {
        if (ptr1) {
            std::cout << "ptr1 points to: " << *ptr1 << std::endl;
        } else {
            std::cout << "ptr1 is nullptr" << std::endl;
        }

        if (ptr2) {
            std::cout << "ptr2 points to: " << *ptr2 << std::endl;
        } else {
            std::cout << "ptr2 is nullptr" << std::endl;
        }
    }
};

int main() {
    MyClass obj;
    obj.print(); // Both ptr1 and ptr2 are nullptr

    obj.assignPtr1(10);
    obj.assignPtr2(20);
    obj.print(); // ptr1 points to 10, ptr2 points to 20

    return 0;
}

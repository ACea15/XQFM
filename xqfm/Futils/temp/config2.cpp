#include <iostream>
#include <string>
#include <map>
#include <variant>
#include <memory>

class MyContainer1 {
public:
    // ✅ These are real, public member variables
    int var1 = 0;
    float var2 = 0.0f;
    std::string var3 = "default";

    // 🎛️ Registry: string name -> pointer-to-member
    using IntPtr = int MyContainer1::*;
    using FloatPtr = float MyContainer1::*;
    using StringPtr = std::string MyContainer1::*;
    
    using ValueVariant = std::variant<int, float, std::string>;
    using MemberPtrVariant = std::variant<IntPtr, FloatPtr, StringPtr>;

    std::map<std::string, MemberPtrVariant> registry;

    MyContainer1() {
        // Register variable names to member pointers
        registry["var1"] = &MyContainer::var1;
        registry["var2"] = &MyContainer::var2;
        registry["var3"] = &MyContainer::var3;
    }

    void set_from_map(const std::map<std::string, ValueVariant>& values) {
        for (const auto& [key, val] : values) {
            auto it = registry.find(key);
            if (it == registry.end()) {
                std::cerr << "Unknown field: " << key << "\n";
                continue;
            }

            std::visit([&](auto&& memberPtr) {
                using MemberType = std::decay_t<decltype(*this.*memberPtr)>;
                if (auto valPtr = std::get_if<MemberType>(&val)) {
                    this->*memberPtr = *valPtr;
                } else {
                    std::cerr << "Type mismatch for field: " << key << "\n";
                }
            }, it->second);
        }
    }

    void print() const {
        std::cout << "var1 = " << var1 << "\n";
        std::cout << "var2 = " << var2 << "\n";
        std::cout << "var3 = " << var3 << "\n";
    }
};


class MyContainer2 {
public:
    // ✅ These are real, public member variables
    int var1 = 0;
    std::string var3 = "default";

    // 🎛️ Registry: string name -> pointer-to-member
    using IntPtr = int MyContainer2::*;
    using StringPtr = std::string MyContainer2::*;
    
    using ValueVariant = std::variant<int, float, std::string>;
    using MemberPtrVariant = std::variant<IntPtr, FloatPtr, StringPtr>;

    std::map<std::string, MemberPtrVariant> registry;

    MyContainer2() {
        // Register variable names to member pointers
        registry["var1"] = &MyContainer::var1;
        registry["var3"] = &MyContainer::var3;
    }

    void set_from_map(const std::map<std::string, ValueVariant>& values) {
        for (const auto& [key, val] : values) {
            auto it = registry.find(key);
            if (it == registry.end()) {
                std::cerr << "Unknown field: " << key << "\n";
                continue;
            }

            std::visit([&](auto&& memberPtr) {
                using MemberType = std::decay_t<decltype(*this.*memberPtr)>;
                if (auto valPtr = std::get_if<MemberType>(&val)) {
                    this->*memberPtr = *valPtr;
                } else {
                    std::cerr << "Type mismatch for field: " << key << "\n";
                }
            }, it->second);
        }
    }

    void print() const {
        std::cout << "var1 = " << var1 << "\n";
        std::cout << "var2 = " << var2 << "\n";
        std::cout << "var3 = " << var3 << "\n";
    }
};


class MyConfig {
public:
  std::unique_ptr<MyContainer1> myCont1 = nullptr;
  std::unique_ptr<MyContainer2> myCont2 = nullptr;
  

    // 🎛️ Registry: string name -> pointer-to-member
    using contPtr = int MyConfig::*;
    
    using ValueVariant = std::variant<int, float, std::string>;
    using MemberPtrVariant = std::variant<IntPtr, FloatPtr, StringPtr>;

    std::map<std::string, MemberPtrVariant> registry;

    MyConfig() {
        // Register variable names to member pointers
        registry["mycont1"] = &MyContainer::myCont1;
        registry["mycont2"] = &MyContainer::myCont2;
    }

    void set_from_map(const std::map<std::string, std::map<std::string, ValueVariant>>& values) {
        for (const auto& [key, val] : values) {
            auto it = registry.find(key);
            if (it == registry.end()) {
                std::cerr << "Unknown field: " << key << "\n";
                continue;
            }

            std::visit([&](auto&& memberPtr) {
                using MemberType = std::decay_t<decltype(*this.*memberPtr)>;
                if (auto valPtr = std::get_if<MemberType>(&val)) {
		  this->*memberPtr.set_from_map(*valPtr);
                } else {
                    std::cerr << "Type mismatch for field: " << key << "\n";
                }
            }, it->second);
        }
    }

};



int main() {
    Config config;

    std::map<std::string, std::map<std::string, Variant>> fileConfig = {
        {"MyContainer", {
            {"foo", 101},
            {"bar", 2.71f}
        }},
        {"OtherContainer", {
            {"name", std::string("Renderer")}
        }},
        {"NonexistentContainer", {
            {"dummy", 0}
        }}
    };

    config.load(fileConfig);
    config.print();

    return 0;
}


// int main() {
//     MyContainer2 obj;

//     std::map<std::string, MyContainer::ValueVariant> update_map = {
//         {"var1", 123},
//         {"var2", 3.14f},
//         {"var3", std::string("hello world")},
//         {"badField", 999}, // warning
//         {"var3", 42}       // type mismatch
//     };

//     obj.set_from_map(update_map);
//     obj.print();
    
// }

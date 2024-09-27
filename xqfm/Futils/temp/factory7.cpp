#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <map>
#include <stdexcept>

// Base container class
struct ContainerBase {
    virtual ~ContainerBase() = default;
    virtual void show() const = 0;
};

// Derived container structs
struct ContainerA : public ContainerBase {
    std::map<std::string, std::string> data;
    
    ContainerA(const std::map<std::string, std::string>& mapData) : data(mapData) {}
    
    void show() const override {
        std::cout << "ContainerA with data: " << std::endl;
        for (const auto& [key, value] : data) {
            std::cout << "  " << key << ": " << value << std::endl;
        }
    }
};

struct ContainerB : public ContainerBase {
    std::map<std::string, std::string> data;
    
    ContainerB(const std::map<std::string, std::string>& mapData) : data(mapData) {}
    
    void show() const override {
        std::cout << "ContainerB with data: " << std::endl;
        for (const auto& [key, value] : data) {
            std::cout << "  " << key << ": " << value << std::endl;
        }
    }
};

// Factory class for creating containers
class ContainerFactory {
public:
    template <typename T>
    void registerContainer(const std::string& name) {
        registry_[name] = [](const std::map<std::string, std::string>& args) -> std::unique_ptr<ContainerBase> {
            return std::make_unique<T>(args);
        };
    }

    std::unique_ptr<ContainerBase> createContainer(const std::string& name, const std::map<std::string, std::string>& args) {
        auto it = registry_.find(name);
        if (it != registry_.end()) {
            return it->second(args);
        }
        throw std::runtime_error("Container not registered.");
    }
    
private:
    using Constructor = std::function<std::unique_ptr<ContainerBase>(const std::map<std::string, std::string>&)>;
    std::unordered_map<std::string, Constructor> registry_;
};


class Config {

  ContainerFactory factory;
  
  void register_factory(){
    factory.registerContainer<ContainerA>("ContainerA");
    factory.registerContainer<ContainerB>("ContainerB");
       
  }
};
int main() {
    ContainerFactory factory;

    // Register container types
    factory.registerContainer<ContainerA>("ContainerA");
    factory.registerContainer<ContainerB>("ContainerB");

    // Create containers with map-based initialization parameters
    std::map<std::string, std::string> initA = { {"key1", "value1"}, {"key2", "value2"} };
    std::map<std::string, std::string> initB = { {"param1", "1.23"}, {"param2", "4.56"} };

    auto containerA = factory.createContainer("ContainerA", initA);
    auto containerB = factory.createContainer("ContainerB", initB);

    if (containerA) containerA->show();
    if (containerB) containerB->show();

    return 0;
}

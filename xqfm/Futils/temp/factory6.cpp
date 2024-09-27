#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <tuple>

// Base container class
struct ContainerBase {
    virtual ~ContainerBase() = default;
    virtual void show() const = 0;
};

// Derived container structs
struct ContainerA : public ContainerBase {
    int data;
    
    ContainerA(int value) : data(value) {}
    
    void show() const override {
        std::cout << "ContainerA with data: " << data << std::endl;
    }

    using ArgsTuple = std::tuple<int>;
};

struct ContainerB : public ContainerBase {
    double data;
    
    ContainerB(double value) : data(value) {}
    
    void show() const override {
        std::cout << "ContainerB with data: " << data << std::endl;
    }

    using ArgsTuple = std::tuple<double>;
};

// Factory class for creating containers
class ContainerFactory {
public:
    // Register a container type without initialization parameters
    template <typename T>
    void registerContainer(const std::string& name) {
        registry_[name] = [](void* args) -> std::unique_ptr<ContainerBase> {
            auto typedArgs = static_cast<typename T::ArgsTuple*>(args);
            return std::make_unique<T>(std::get<0>(*typedArgs));
        };
    }

    // Create and initialize a container with variadic parameters
    template <typename... Args>
    std::unique_ptr<ContainerBase> createContainer(const std::string& name, Args&&... args) {
        if (registry_.find(name) != registry_.end()) {
            typename std::tuple<Args...> arguments(std::forward<Args>(args)...);
            return registry_[name](&arguments);
        }
        return nullptr;
    }
    
private:
    using Constructor = std::function<std::unique_ptr<ContainerBase>(void*)>;
    std::unordered_map<std::string, Constructor> registry_;
};

int main() {
    ContainerFactory factory;

    // Register the containers 
    factory.registerContainer<ContainerA>("ContainerA");
    factory.registerContainer<ContainerB>("ContainerB");

    // Create containers with initialization parameters
    auto containerA = factory.createContainer("ContainerA", 5);
    //containerA.data = 99;
    auto containerB = factory.createContainer("ContainerB", 3.14);

    if (containerA) containerA->show();
    if (containerB) containerB->show();

    return 0;
}

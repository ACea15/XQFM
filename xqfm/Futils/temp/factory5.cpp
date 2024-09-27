#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

struct ContainerBase {
    virtual ~ContainerBase() = default;
    virtual void show() const = 0;
};

struct ContainerA : public ContainerBase {
  int data;
  std::string name;
  ContainerA(int value, std::string name_) : data(value), name(name_)  {}
    
    void show() const override {
        std::cout << "ContainerA with data: " << data << std::endl;
	std::cout << "ContainerA with name: " << name << std::endl;
    }
};

struct ContainerB : public ContainerBase {
    double data;
    
    ContainerB(double value) : data(value) {}
    
    void show() const override {
        std::cout << "ContainerB with data: " << data << std::endl;
    }
};

class ContainerFactory {
public:
    using Constructor = std::function<std::unique_ptr<ContainerBase>(void)>;

    template <typename T, typename... Args>
    void registerContainer(const std::string& name, Args... args) {
        registry_[name] = [=]() { return std::make_unique<T>(args...); };
    }

    std::unique_ptr<ContainerBase> createContainer(const std::string& name) {
        if (registry_.find(name) != registry_.end()) {
            return registry_[name]();
        }
        return nullptr;
    }
    
private:
    std::unordered_map<std::string, Constructor> registry_;
};

int main() {
    ContainerFactory factory;

    factory.registerContainer<ContainerA>("ContainerA", 42, "dd");
    factory.registerContainer<ContainerB>("ContainerB", 3.14);

    auto containerA = factory.createContainer("ContainerA");
    auto containerB = factory.createContainer("ContainerB");

    if (containerA) containerA->show();
    if (containerB) containerB->show();

    return 0;
}

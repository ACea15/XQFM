#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <functional>
#include <vector>
#include <list>
#include <deque>

// Base class
struct ContainerBase {
    virtual ~ContainerBase() = default;
    virtual void printType() const = 0;
};

// Derived container classes
struct VectorContainer : public ContainerBase {
    std::vector<int> data;
    VectorContainer(const std::vector<int>& initData) : data(initData) { 
        std::cout << "VectorContainer initialized with data\n"; 
    }
    void printType() const override {
        std::cout << "This is a VectorContainer, data size: " << data.size() << "\n";
    }
};

struct ListContainer : public ContainerBase {
    std::list<int> data;
    ListContainer(const std::list<int>& initData) : data(initData) { 
        std::cout << "ListContainer initialized with data\n"; 
    }
    void printType() const override {
        std::cout << "This is a ListContainer, data size: " << data.size() << "\n";
    }
};

struct DequeContainer : public ContainerBase {
    std::deque<int> data;
    DequeContainer(const std::deque<int>& initData) : data(initData) { 
        std::cout << "DequeContainer initialized with data\n"; 
    }
    void printType() const override {
        std::cout << "This is a DequeContainer, data size: " << data.size() << "\n";
    }
};

// Factory class
class ContainerFactory {
public:
    using CreatorFunc = std::function<std::shared_ptr<ContainerBase>(const std::shared_ptr<void>&)>;

    ContainerFactory() {
        // Register different container types in constructor
        registerContainerType("VectorContainer", [](const std::shared_ptr<void>& initData) {
            auto castedData = std::static_pointer_cast<std::vector<int>>(initData);
            return std::make_shared<VectorContainer>(*castedData);
        });
        registerContainerType("ListContainer", [](const std::shared_ptr<void>& initData) {
            auto castedData = std::static_pointer_cast<std::list<int>>(initData);
            return std::make_shared<ListContainer>(*castedData);
        });
        registerContainerType("DequeContainer", [](const std::shared_ptr<void>& initData) {
            auto castedData = std::static_pointer_cast<std::deque<int>>(initData);
            return std::make_shared<DequeContainer>(*castedData);
        });
    }

    template <typename T>
    std::shared_ptr<ContainerBase> createContainer(const std::string& name, const T& initData) {
        auto it = creators.find(name);
        if (it != creators.end()) {
            return it->second(std::make_shared<T>(initData));
        } else {
            throw std::runtime_error("Container type not registered: " + name);
        }
    }

private:
    void registerContainerType(const std::string& name, CreatorFunc func) {
        creators[name] = func; // Store the factory function in the map
    }

    std::map<std::string, CreatorFunc> creators; // Map to store factory functions
};

class Config {
public:
  std::shared_ptr<ContainerBase> vd = nullptr;
  std::shared_ptr<ContainerBase> ld;
  std::shared_ptr<ContainerBase> dd;
};

int main() {
    ContainerFactory factory;

    try {
        // Initialize containers with some data
        std::vector<int> vectorData = {1, 2, 3};
        std::list<int> listData = {4, 5, 6};
        std::deque<int> dequeData = {7, 8, 9};
	Config config = Config();
        //auto vectorContainer = factory.createContainer("VectorContainer", vectorData);
        config.vd = factory.createContainer("VectorContainer", vectorData);
        config.vd->printType();

        auto listContainer = factory.createContainer("ListContainer", listData);
        listContainer->printType();

        auto dequeContainer = factory.createContainer("DequeContainer", dequeData);
        dequeContainer->printType();

        // Uncommenting the following line will throw an exception
        // auto unknownContainer = factory.createContainer("NonExistentContainer", std::vector<int>{});
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

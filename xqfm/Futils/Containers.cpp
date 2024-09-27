#include <memory>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Containers.hpp"


void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, int &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}
void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, unsigned long &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}
void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, double &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}
void Container::writeValue(std::map<std::string, std::string> map,
                           std::string name, std::string &value) {
  std::istringstream iss(map[name]);
  iss >> value;
}

    
// Factory class
class ContainerFactory {
public:
    using CreatorFunc = std::function<std::shared_ptr<Container>(const std::shared_ptr<void>&)>;

    ContainerFactory() {
        // Register different container types in constructor
        registerContainerType("mc1", [](const std::map<std::string, std::string> container_map& initData) {
	  
        });
    }

    std::shared_ptr<Container> createContainer(const std::string& name, std::map<std::string, std::string>& initData) {
        auto it = creators.find(name);
        if (it != creators.end()) {
            return it->second(std::make_shared<Container>(initData));
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

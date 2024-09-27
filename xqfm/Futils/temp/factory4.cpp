#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <functional>

// Base class
class Product {
public:
    virtual void use() const = 0;  // Pure virtual function
    virtual ~Product() = default;  // Virtual destructor
};

// Concrete Product A
class ConcreteProductA : public Product {
public:
    ConcreteProductA() {
      std::cout << "Custom message for ConcreteProductA: " << std::endl;
    }
  
    void use() const override {
        std::cout << "Using Concrete Product A" << std::endl;
    }
};

// Concrete Product B
class ConcreteProductB : public Product {
public:
    ConcreteProductB(const std::map<std::string, std::string>& params) {
        if (params.find("customMessage") != params.end()) {
            std::cout << "Custom message for ConcreteProductB: " << params.at("customMessage") << std::endl;
        }
    }
  
    void use() const override {
        std::cout << "Using Concrete Product B" << std::endl;
    }
};

class ProductFactory {
public:
    using CreateProductFunc = std::function<std::unique_ptr<Product>(const std::map<std::string, std::string>&)>;

    static void registerProduct(const std::string& type, CreateProductFunc func) {
        getRegistry()[type] = std::move(func);
    }

    static std::unique_ptr<Product> createProduct(const std::string& type, const std::map<std::string, std::string>& params) {
        const auto& registry = getRegistry();
        auto it = registry.find(type);
        if (it != registry.end()) {
            return it->second(params);  // Call the factory method with params
        }
        return nullptr;
    }

private:
    // Get registry as a static function to ensure it's initialized once
    static std::map<std::string, CreateProductFunc>& getRegistry() {
        static std::map<std::string, CreateProductFunc> registry;
        return registry;
    }
};

void registerProducts() {
    ProductFactory::registerProduct("product_a", []()  {
        return std::make_unique<ConcreteProductA>();
    });
    ProductFactory::registerProduct("product_b", []()  {
        return std::make_unique<ConcreteProductB>();
    });
}

int main() {
    // Create product A using the factory with string input and additional parameters
    std::map<std::string, std::string> paramsA = { {"customMessage", "Hello from Product A"} };
    std::unique_ptr<Product> productA = ProductFactory::createProduct("product_a", paramsA);
    if (productA) {
        productA->use();
    } else {
        std::cerr << "Unknown product type: product_a" << std::endl;
    }

    // Create product B using the factory with string input and additional parameters
    std::map<std::string, std::string> paramsB = { {"customMessage", "Hello from Product B"} };
    std::unique_ptr<Product> productB = ProductFactory::createProduct("product_b", paramsB);
    if (productB) {
        productB->use();
    } else {
        std::cerr << "Unknown product type: product_b" << std::endl;
    }

    // Attempt to create a non-existent product type with parameters
    std::map<std::string, std::string> paramsUnknown = { {"customMessage", "This should fail"} };
    std::unique_ptr<Product> productUnknown = ProductFactory::createProduct("product_unknown", paramsUnknown);
    if (productUnknown) {
        productUnknown->use();
    } else {
        std::cerr << "Unknown product type: product_unknown" << std::endl;
    }

    return 0;
}

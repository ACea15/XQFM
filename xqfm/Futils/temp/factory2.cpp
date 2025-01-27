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
    ConcreteProductA() = default;

    void use() const override {
        std::cout << "Using Concrete Product A" << std::endl;
    }
};

// Concrete Product B
class ConcreteProductB : public Product {
public:
    ConcreteProductB() = default;

    void use() const override {
        std::cout << "Using Concrete Product B" << std::endl;
    }
};

class ProductFactory {
public:
    using CreateProductFunc = std::function<std::unique_ptr<Product>()>;

    static ProductFactory& getInstance() {
        static ProductFactory instance;
        return instance;
    }

    void registerProduct(const std::string& type, CreateProductFunc func) {
        registry_[type] = func;
    }

    std::unique_ptr<Product> createProduct(const std::string& type) {
        auto it = registry_.find(type);
        if (it != registry_.end()) {
            return it->second();  // Call the factory method
        }
        return nullptr;
    }

private:
    std::map<std::string, CreateProductFunc> registry_;
};
void registerProducts() {
    ProductFactory::getInstance().registerProduct("product_a", []() -> std::unique_ptr<Product> {
        return std::make_unique<ConcreteProductA>();
    });
    ProductFactory::getInstance().registerProduct("product_b", []() -> std::unique_ptr<Product> {
        return std::make_unique<ConcreteProductB>();
    });
}

int main() {
    // Register products
    registerProducts();

    // Create product A using the factory with string input
    std::unique_ptr<Product> productA = ProductFactory::getInstance().createProduct("product_a");
    if (productA) {
        productA->use();
    } else {
        std::cerr << "Unknown product type: product_a" << std::endl;
    }

    // Create product B using the factory with string input
    std::unique_ptr<Product> productB = ProductFactory::getInstance().createProduct("product_b");
    if (productB) {
        productB->use();
    } else {
        std::cerr << "Unknown product type: product_b" << std::endl;
    }

    // Attempt to create a non-existent product type
    std::unique_ptr<Product> productUnknown = ProductFactory::getInstance().createProduct("product_unknown");
    if (productUnknown) {
        productUnknown->use();
    } else {
        std::cerr << "Unknown product type: product_unknown" << std::endl;
    }

    return 0;
}

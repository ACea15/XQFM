#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <functional>

// Base class
class Product {
public:
    virtual void use() const = 0;  // Pure virtual function
    virtual void set(int a) = 0;
    virtual ~Product() = default;  // Virtual destructor
};

// Concrete Product A
class ConcreteProductA : public Product {
public:
  int a;
  void use() const override {
    std::cout << "Using Concrete Product A" << a  << std::endl;
  }
  void set(int a_) {
    a = a_;}
};

// Concrete Product B
class ConcreteProductB : public Product {
public:
  int b;
    void use() const override {
        std::cout << "Using Concrete Product B" << std::endl;
    }
    void set(int b_) {
    b = b_;}

};

class ProductFactory {
public:
    using CreateProductFunc = std::function<std::unique_ptr<Product>()>;

    static void registerProduct(const std::string& type, CreateProductFunc func) {
        getRegistry()[type] = std::move(func);
    }

    static std::unique_ptr<Product> createProduct(const std::string& type) {
        const auto& registry = getRegistry();
        auto it = registry.find(type);
        if (it != registry.end()) {
            return it->second();  // Call the factory method
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
    // Register products
    registerProducts();

    // Create product A using the factory with string input
    std::unique_ptr<Product> productA = ProductFactory::createProduct("product_a");
    if (productA) {
      productA->set(3);
      productA->use();
    } else {
        std::cerr << "Unknown product type: product_a" << std::endl;
    }

    // Create product B using the factory with string input
    std::unique_ptr<Product> productB = ProductFactory::createProduct("product_b");
    if (productB) {
        productB->use();
    } else {
        std::cerr << "Unknown product type: product_b" << std::endl;
    }

    // Attempt to create a non-existent product type
    std::unique_ptr<Product> productUnknown = ProductFactory::createProduct("product_unknown");
    if (productUnknown) {
        productUnknown->use();
    } else {
        std::cerr << "Unknown product type: product_unknown" << std::endl;
    }

    return 0;
}


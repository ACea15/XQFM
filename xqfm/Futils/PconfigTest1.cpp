#include <iostream>
#include "PConfig.hpp"

int main() {
    Config config;  // Start with default values
    try {
        config.loadFromFile("configtest1.txt");
        std::cout << "Port: " << config.port << "\n";
        std::cout << "Hostname: " << config.hostname << "\n";
        std::cout << "Max Connections: " << config.max_connections << "\n";
        std::cout << "Timeout: " << config.timeout << "\n";
        std::cout << "Use SSL: " << (config.use_ssl ? "true" : "false") << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }

    return 0;
}

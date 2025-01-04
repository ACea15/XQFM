#include <string>
#include <sstream>
#include <stdexcept>

#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

#include "PConfig.hpp"

template <>
int convertString<int>(const std::string& value) {
    return std::stoi(value);
}

template <>
double convertString<double>(const std::string& value) {
    return std::stod(value);
}

template <>
bool convertString<bool>(const std::string& value) {
    if (value == "true" || value == "1") return true;
    if (value == "false" || value == "0") return false;
    throw std::invalid_argument("Invalid value for boolean.");
}

template <>
std::string convertString<std::string>(const std::string& value) {
    return value;
}

void Config::initializeHandlers() {
    handlers["port"] = [this](const std::string& value) { port = convertString<decltype(port)>(value); };
    handlers["hostname"] = [this](const std::string& value) { hostname = convertString<decltype(hostname)>(value); };
    handlers["max_connections"] = [this](const std::string& value) { max_connections = convertString<decltype(max_connections)>(value); };
    handlers["timeout"] = [this](const std::string& value) { timeout = convertString<decltype(timeout)>(value); };
    handlers["use_ssl"] = [this](const std::string& value) { use_ssl = convertString<decltype(use_ssl)>(value); };
}

void Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open config file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            if (std::getline(iss, value)) {
                key = trim(key);
                value = trim(value);

                // Use a handler mapped to the key
                if (handlers.find(key) != handlers.end()) {
                    handlers[key](value);
                }
            }
        }
    }
}

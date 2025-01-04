#include <string>
#include <sstream>
#include <stdexcept>

#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

#include "DConfig.hpp"

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
    handlers["num_paths"] = [this](const std::string& value) {num_paths = convertString<decltype(num_paths)>(value); };
    handlers["num_steps"] = [this](const std::string& value) {num_steps = convertString<decltype(num_steps)>(value); };
    handlers["strike"] = [this](const std::string& value) {strike = convertString<decltype(strike)>(value); };
    handlers["spot"] = [this](const std::string& value) {spot = convertString<decltype(spot)>(value); };
    handlers["mu"] = [this](const std::string& value) {mu = convertString<decltype(mu)>(value); };
    handlers["sigma"] = [this](const std::string& value) {sigma = convertString<decltype(sigma)>(value); };
    handlers["periodT"] = [this](const std::string& value) {periodT = convertString<decltype(periodT)>(value); };
    
}

void Config::loadFromFile(const std::string& filename) {
    initializeHandlers();
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

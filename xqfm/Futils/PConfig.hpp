#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

// Extend the Config class accordingly.
class Config {
public:
    int port = 8080;
    std::string hostname = "localhost";
    int max_connections = 100;
    double timeout = 5.0;
    bool use_ssl = false;

    Config() {
        initializeHandlers();
    }

    void loadFromFile(const std::string& filename);

private:
    std::unordered_map<std::string, std::function<void(const std::string&)>> handlers;

    void initializeHandlers();

    // Utility to strip whitespace
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        if (first == std::string::npos || last == std::string::npos) return "";  // Handles strings with only spaces
        return str.substr(first, (last - first + 1));
    }
};

template <typename T>
T convertString(const std::string& value);

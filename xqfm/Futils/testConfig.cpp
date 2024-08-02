#include "Config.hpp"
#include <iostream>

int main() {

    std::map<std::string, std::string> mc1 = {
      {"strike", "1."}, {"spot", "100."},    {"vol", "0.3"},
      {"rate", "0."},   {"numSteps", "252"}, {"numPaths", "10000"},
      {"period", "1."},
    };

    std::map<string, std::map<string, string>> map1 = {{"Cmc1", mc1}};
    Config1 config1(map1);

    double strike = config1.ct1->strike;
    double spot = config1.ct1->spot;
    double vol = config1.ct1->vol;
    double rate = config1.ct1->rate;
    std::cout << "Estimated average final value: " << strike << std::endl;
    std::cout << "Estimated average final value: " << spot << std::endl;
    
    // auto start = std::chrono::high_resolution_clock::now();
    
    // // Perform the Euler-Maruyama simulation
    // double averageFinalValue = eulerMaruyama(numPaths, numSteps, T, mu, sigma, X0);

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;

    // std::cout << "Estimated average final value: " << averageFinalValue << std::endl;
    // std::cout << "Total paths: " << numPaths << std::endl;
    // std::cout << "Duration: " << duration.count() << " seconds" << std::endl;

    return 0;
}

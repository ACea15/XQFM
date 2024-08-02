#include "../Futils/Config.hpp"
#include "XMatrix.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

// Function to perform the Euler-Maruyama step for the SDE
XMatrix eulerMaruyama(unsigned long numPaths, unsigned long numSteps, double T,
                      double mu, double sigma, double S0) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0.0, 1.0);

  double dt = T / numSteps;
  double sqrt_dt = std::sqrt(dt);
  XMatrix S(numPaths, numSteps);

  for (unsigned long i = 0; i < numPaths; ++i) {
    S(i, 0) = S0;
    for (unsigned long j = 1; j < numSteps; ++j) {
      double dW = dis(gen) * sqrt_dt;
      S(i, j) = mu * S(i, j - 1) * dt + sigma * S(i, j - 1) * dW;
    };
  };

  return S;
}

XMatrix mcAnalytical(unsigned long numPaths, unsigned long numSteps, double T,
                      double mu, double sigma, double S0) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0.0, 1.0);

  double dt = T / numSteps;
  double sqrt_dt = std::sqrt(dt);
  XMatrix S(numPaths, numSteps);

  for (unsigned long i = 0; i < numPaths; ++i) {
    S(i, 0) = S0;
    for (unsigned long j = 1; j < numSteps; ++j) {
      double dW = dis(gen) * sqrt_dt;
      S(i, j) = S(i, j - 1) * std::exp((mu - 0.5*sigma*sigma)*dt + sigma*dW);
    };
  };

  return S;
}


// self.X[i + 1] = Xi * np.exp((self.mu -0.5 * self.sigma**2) * self.dt +
// self.sigma * dw)

int main() {

    std::map<std::string, std::string> mc1 = {
      {"strike", "1."}, {"spot", "100."},    {"vol", "0.3"},
      {"rate", "0."},   {"numSteps", "252"}, {"numPaths", "10000000"},
      {"period", "1."},
    };

    std::map<string, std::map<string, string>> map1 = {{"Cmc1", mc1}};
    Config1 config1(map1);

    double mu = config1.ct1->mu;    
    double strike = config1.ct1->strike;
    double spot = config1.ct1->spot;
    double vol = config1.ct1->vol;
    double rate = config1.ct1->rate;
    int numPaths = config1.ct1->numPaths;
    int numSteps = config1.ct1->numSteps;
    double T = config1.ct1->period;

    // std::cout << "Estimated average final value: " << strike << std::endl;
    // std::cout << "Estimated average final value: " << spot << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform the Euler-Maruyama simulation
    XMatrix averageFinalValue = eulerMaruyama(numPaths, numSteps, T, mu, vol, spot);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    auto start2 = std::chrono::high_resolution_clock::now();
    
    // Perform the Euler-Maruyama simulation
    XMatrix averageFinalValue2 = mcAnalytical(numPaths, numSteps, T, mu, vol, spot);

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    
    //std::cout << "Estimated average final value: " << averageFinalValue << std::endl;
    std::cout << "Total paths: " << numPaths << std::endl;
    std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
    std::cout << "Duration2: " << duration2.count() << " seconds" << std::endl;

    return 0;
}

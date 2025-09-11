#include "../../Futils/DConfig.hpp"
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

  
  Config config;

    
  auto start = std::chrono::high_resolution_clock::now();
    
  // Perform the Euler-Maruyama simulation
  XMatrix averageFinalValue = eulerMaruyama(config.num_paths, config.num_steps, config.periodT, config.mu, config.sigma, config.spot);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  // auto start2 = std::chrono::high_resolution_clock::now();
    
  // // Perform the Euler-Maruyama simulation
  // XMatrix averageFinalValue2 = mcAnalytical(numPaths, numSteps, T, mu, vol, spot);
  
  // auto end2 = std::chrono::high_resolution_clock::now();
  // std::chrono::duration<double> duration2 = end2 - start2;
    
  //std::cout << "Estimated average final value: " << averageFinalValue << std::endl;
  // std::cout << "Total paths: " << numPaths << std::endl;
  // std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
  // std::cout << "Duration2: " << duration2.count() << " seconds" << std::endl;

  return 0;
}

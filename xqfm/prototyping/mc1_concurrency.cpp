#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <cmath>

#include "../Futils/Config.hpp"
#include "XMatrix.hpp"

// Function to perform the Euler-Maruyama step for the SDE
XMatrix eulerMaruyama(unsigned long startPath, unsigned long numPaths, unsigned long numSteps, double T, double dt, double sqrt_dt,
                      double mu, double sigma, double S0, XMatrix& S) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0.0, 1.0);


  for (unsigned long i = 0; i < numPaths; ++i) {
    S(startPath +i, 0) = S0;
    for (unsigned long j = 1; j < numSteps; ++j) {
      double dW = dis(gen) * sqrt_dt;
      S(startPath +i, j) = mu * S(startPath +i, j - 1) * dt + sigma * S(startPath +i, j - 1) * dW;
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

int main() {
    unsigned long numPaths = 1e6; // Total number of paths
    unsigned long numSteps = 500; // Number of time steps
    double T = 1.0; // Total time
    double mu = 0.05; // Drift coefficient
    double sigma = 0.2; // Diffusion coefficient
    double S0 = 100.; // Initial value
    double dt = T / numSteps;
    double sqrt_dt = std::sqrt(dt);
    XMatrix S(numPaths, numSteps);

    unsigned int numThreads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;
    unsigned long pathsPerThread = numPaths / numThreads;

    auto start = std::chrono::high_resolution_clock::now();

    // Launch threads
    for (unsigned int i = 0; i < numThreads; ++i) {
        unsigned long startPath = i * pathsPerThread;
        threads.emplace_back(eulerMaruyama, startPath, pathsPerThread, numSteps, T, dt, sqrt_dt, mu, sigma, S0, std::ref(S));
    }

    // Join threads
    for (auto &t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Print results (optional)
    std::cout << "Simulation completed in " << duration.count() << " seconds." << std::endl;

    // For demonstration, print the first few paths
    // for (unsigned long i = 0; i < 5; ++i) {
    //     std::cout << "Path " << i << ": ";
    //     for (unsigned long j = 0; j < numSteps; ++j) {
    //         std::cout << S[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}

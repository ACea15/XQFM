#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <cmath>

// Function to perform the Euler-Maruyama step for the SDE in a single thread
void eulerMaruyama(unsigned long startPath, unsigned long numPaths, unsigned long numSteps, double T, double mu, double sigma, double X0, std::vector<std::vector<double>>& X) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0.0, 1.0);
    
    double dt = T / numSteps;
    double sqrt_dt = std::sqrt(dt);

    for (unsigned long i = 0; i < numPaths; ++i) {
        double X_value = X0;
        for (unsigned long j = 0; j < numSteps; ++j) {
            double dW = dis(gen) * sqrt_dt;
            X_value += mu * X_value * dt + sigma * X_value * dW;
            X[startPath + i][j] = X_value;
        }
    }
}

int main() {
    unsigned long numPaths = 1e6; // Total number of paths
    unsigned long numSteps = 1000; // Number of time steps
    double T = 1.0; // Total time
    double mu = 0.1; // Drift coefficient
    double sigma = 0.2; // Diffusion coefficient
    double X0 = 1.0; // Initial value

    unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::vector<double>> X(numPaths, std::vector<double>(numSteps, 0.0));

    std::vector<std::thread> threads;
    unsigned long pathsPerThread = numPaths / numThreads;

    auto start = std::chrono::high_resolution_clock::now();

    // Launch threads
    for (unsigned int i = 0; i < numThreads; ++i) {
        unsigned long startPath = i * pathsPerThread;
        threads.emplace_back(eulerMaruyama, startPath, pathsPerThread, numSteps, T, mu, sigma, X0, std::ref(X));
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
    for (unsigned long i = 0; i < 5; ++i) {
        std::cout << "Path " << i << ": ";
        for (unsigned long j = 0; j < numSteps; ++j) {
            std::cout << X[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

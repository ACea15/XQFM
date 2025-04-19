#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <thread>
#include <valarray>
#include <vector>

using vector2d = std::vector<std::vector<double>>;

double payoff(unsigned long startPath, unsigned long numPaths, vector2d &S, double strike) {
  double sum = 0.; 
  for (unsigned long i = 0; i < numPaths; ++i) {
    sum += std::max(strike - S[startPath + i].back(), 0.);

    }
  return sum / numPaths;
  }

void mcAnalyticalc(unsigned long startPath, unsigned long numPaths,
                   unsigned long numSteps, double T, double dt,
                   double sqrt_dt, double mu, double sigma, double S0,
                   vector2d &S) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0.0, 1.0);

  for (unsigned long i = 0; i < numPaths; ++i) {
    S[startPath + i][0] = S0;
    for (unsigned long j = 1; j < numSteps; ++j) {
      double dW = dis(gen) * sqrt_dt;
      S[startPath + i][j] = S[startPath + i][j - 1] *
          std::exp((mu - 0.5 * sigma * sigma) * dt + sigma * dW);
    };
  };
}

void eulerMaruyamac(unsigned long startPath, unsigned long numPaths,
                    unsigned long numSteps, double T, double dt,
                    double sqrt_dt, double mu, double sigma, double S0,
                    vector2d &S) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0.0, 1.0);

  for (unsigned long i = 0; i < numPaths; ++i) {
    S[startPath + i][0] = S0;
    for (unsigned long j = 1; j < numSteps; ++j) {
      double dW = dis(gen) * sqrt_dt;
      S[startPath + i][j] = mu * S[startPath + i][j - 1] * dt +
                            sigma * S[startPath + i][j - 1] * dW;
    };
  };
}

void fthread(double& output, unsigned long startPath, unsigned long numPaths,
               unsigned long numSteps, double T, double dt,
               double sqrt_dt, double mu, double sigma, double S0, double strike,
               vector2d &S) {
  mcAnalyticalc(startPath, numPaths,numSteps,  T,  dt,
                   sqrt_dt,  mu,  sigma,  S0,
                S);
  output = payoff(startPath, numPaths, S, strike);
  }

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  double strike = 100.0;
  double spot = 100.0;
  double vol = 0.3;
  double rate = 0.03;
  int numPaths = 10000000;
  int numSteps = 300;
  double T = 1.0;
  double dt = 0.0033333333333333335;
  double sqrt_dt = 0.05773502691896258;

  vector2d S(numPaths, std::vector<double>(numSteps, 0.));
  unsigned int numThreads = std::thread::hardware_concurrency();
  std::vector<double> partialSums(numThreads, 0.);
  std::vector<std::thread> threads;
  unsigned long pathsPerThread = numPaths / numThreads;
  // Launch threads
  for (unsigned int i = 0; i < numThreads; ++i) {
    unsigned long startPath = i * pathsPerThread;
    if (i == numThreads - 1) pathsPerThread = numPaths - startPath;
    threads.emplace_back(fthread, std::ref(partialSums[i]), startPath, pathsPerThread, numSteps, T,
                         dt, sqrt_dt, rate, vol, spot, strike, std::ref(S));
  }

  // Join threads
  for (auto &t : threads) {
    t.join();
  }
  double totalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0.);
  double price = totalSum / numThreads;
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;

  // std::cout << "Estimated average final value: " << averageFinalValue <<
  // std::endl;
  std::cout << "Totalpaths: " << numPaths << std::endl;
  std::cout << "Duration(seconds): " << duration.count() << std::endl;
  std::cout << "Price: " << price << std::endl;

  return 0;
}

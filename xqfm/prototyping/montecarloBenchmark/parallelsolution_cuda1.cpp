#include <iostream>
#include <curand_kernel.h>
#include <cuda_runtime.h>

__global__ void monteCarloSDE(double* d_samples, double* d_payoff, int numPaths, int numSteps, double dt, double mu, double sigma, double x0) {
    int pathIdx = blockIdx.x * blockDim.x + threadIdx.x;
    if (pathIdx >= numPaths * numSteps) return;

    monteCarloPath(pathIdx, d_samples, numSteps, dt, mu, sigma, x0)
    computed_payoff = payoff(int numSteps, int numPaths, double* d_samples, double strike)
    *d_payoff = computed_payoff
}

__global__ void monteCarloPaths(double* d_samples, int numPaths, int numSteps, double dt, double sqrt_dt, double mu, double sigma, double x0) {
    int pathIdx = blockIdx.x * blockDim.x + threadIdx.x;
    if (pathIdx >= numPaths * numSteps) return;

    monteCarloPath(pathIdx, d_samples, numSteps, dt, mu, sigma, x0)
    computed_payoff = payoff(int numSteps, int numPaths, double* d_samples, double strike)
    *d_payoff = computed_payoff
}

__device__  void monteCarloPath(int pathIdx, double* d_samples, int numSteps, double dt, double sqrt_dt, double mu, double sigma, double x0) {

    // Initialize the state of the random number generator for this thread
    curandState state;
    curand_init(1234, pathIdx, 0, &state);

    // Simulate the SDE for this path
    double x = x0;
    d_samples[pathIdx * numSteps] = x;
    for (int i = 1; i < numSteps; ++i) {
        double dW = curand_normal(&state) * sqrt_dt; // Wiener increment
        // x += mu * dt + sigma * dW; // Euler-Maruyama update
        x *= exp((mu - 0.5 * sigma * sigma) * dt + sigma * dW); //exact
        // Store the final value for this path
        d_samples[pathIdx * numSteps + i] = x;

    }

}

__device__ double payoff(int numSteps, int numPaths, double* d_samples, double strike) {
  double sum = 0.; 
  for (unsigned long i = 0; i < numPaths; ++i) {
    sum += max(strike - d_samples[numSteps * (i+1) -1], 0.);
    }
  return sum / numPaths;
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

    //double* final_payoff;
    // Allocate Unified Memory -- accessible from CPU or GPU
    // cudaMallocManaged(&final_payoff, sizeof(double));

    // Memory allocation (host and device)
    double* h_samples = new double[numPaths * numSteps];
    double* d_samples;
    cudaMalloc(&d_samples, numPaths * numSteps * sizeof(double));

     // Define CUDA kernel configuration
    int threadsPerBlock = 256;
    int numBlocks = (numPaths + threadsPerBlock - 1) / threadsPerBlock;

    // Launch kernel
    // monteCarloSDE>(d_samples,
    //                                               numPaths,
    //                                               numSteps,
    //                                               dt,
    //                                               sqrt_dt,
    //                                               rate,
    //                                               vol,
    //                                               spot);
    monteCarloPaths>(d_samples,
                                                    numPaths,
                                                    numSteps,
                                                    dt,
                                                    sqrt_dt,
                                                    rate,
                                                    vol,
                                                    spot);


    // Copy results back to host
    cudaMemcpy(h_samples, d_samples, numPaths * sizeof(double), cudaMemcpyDeviceToHost);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;      

    // Clean up
    delete[] h_samples;
    cudaFree(d_samples);
    cudaFree(final_payoff);


    // std::cout << "Estimated average final value: " << averageFinalValue <<
    // std::endl;
    std::cout << "Totalpaths: " << numPaths << std::endl;
    std::cout << "Duration(seconds): " << duration.count() << std::endl;
    std::cout << "Price: " << final_payoff << std::endl;

    return 0;
}

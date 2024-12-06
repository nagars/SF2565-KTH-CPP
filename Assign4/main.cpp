/*
main.cpp
Created on: Dec 6, 2024
    Author: Alessio/Shawn
*/

#include <random>

#define dt 1e-3  // time step


void dGamma(double b) {
    // Gamma probability distribution
    // C++ ref: https://en.cppreference.com/w/cpp/numeric/random/gamma_distribution
    // theory:  https://en.wikipedia.org/wiki/Gamma_distribution

    // alpha = 2
    // beta = 1/b
}


void serial(double M) {
    ////////////////////////////////////
    /* TASK I - Serial implementation */
    ////////////////////////////////////

    // Create a vector of b values (include 1)

    // Start timer
    // For each b value
        // Create a gamma(x; b) distribution
        // Draw M samples from gamma(b), store them in X0(b)
        // For each time value
            // Calculate P(t; b,X0)
        // Calculate best-fit f(t; lambda) = lambda*exp(-lambda*t)
        // Return lambda(b)
    // Stop timer
    // Return elapsed time

    // Generate data for plotting

    ///// Python code /////
    // For each b
        // Plot P(t; b) vs t
        // Plot best fit f(t)=lambda...
}


void parallel(double M, double b) {
    ///////////////////////////////////////
    /* TASK II - Parallel implementation */
    ///////////////////////////////////////

    // Create a vector of p: number of threads (include 1)
    // Create a vector of executionTimes
    // for each p value
        // Start timer
        // Run the same computation as Task I
        // Stop timer
        // append to executionTime

    // calculate speedUp
    // Generate data for plotting
    // Fit an Amdahl curve to the data

    ///// Python code /////
    // Plot speedUp vs executionTime
    // Superimpose Amdahl curve
}


int main() {
    // Create a vector of times

    // Set M = 1e4
    // execute serial(M)

    // pick a value of b = B from the results of Task I
    // Set M = 1e6 or more, as needed
    // execute parallel(M, B)

    return 0;
}
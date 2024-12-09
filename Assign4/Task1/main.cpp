/*
main.cpp
Created on: Dec 6, 2024
    Author: Alessio/Shawn
*/

#include <random>
#include <assert.h>

#define DT 1e-3  // time step
#define MAX_B	1000

// Generate M initial conditions for equation (1) in assignment
// iid sampled from a Gamma distribution with alpha=2, beta=1/b
// C++ ref: https://en.cppreference.com/w/cpp/numeric/random/gamma_distribution
std::vector<double> generateICSamples(std::vector<double>& ICsamples,
    const int samplesNo, const double b) {
	assert(b > 0);

    std::random_device rd;  	// Seed generator
    std::mt19937 gen(rd());  	// Random number generator
    const double shape_parameter = 2.0; 	// 'alpha' value as per assignment
    const double scale_parameter = 1/b; 	// 'beta' value as per assignment
    std::gamma_distribution<> dGamma(shape_parameter, scale_parameter);

    for (int i = 1; i<=samplesNo; ++i) {
        ICsamples.emplace_back(dGamma(gen));
    }

    return ICsamples;
}


// Cumulative probability of extinction - P(t>s)
// Calculate P(t>s), according to equation (2) in assignment
std::vector<double> pExtinctionTimes(std::vector<double>& times, double b) {

    // 'M' value defined in assignment
    constexpr int IC_SAMPLES = 1e4;

    // Initial conditions vector X0
    std::vector<double> ICsamples = generateICSamples(ICsamples, IC_SAMPLES, b);

    /* Calculate the extinction time for each IC
       using the  Euler-Maruyama scheme */
    std::vector<double> extinctionTimes;
    std::random_device rd; // Seed generator
    std::mt19937 gen(rd()); // Random number generator
    std::normal_distribution<> dStandard(0.0, 1.0); // Standard normal pdf
    // For each IC (m) in ICsamples (M)
        // start stepping using the 
        // if Xn<=0
            // record the extinction time Tm=n*dt
            // break out
    for (int i = 1; i <=IC_SAMPLES; ++i) {
        // TODO change index to match assignment formulas
    }


    // Calculation of probability
    std::vector<double> result;
    // for each time in times
        // 
    return result;
}


void serial(double M) {
    ////////////////////////////////////
    /* TASK I - Serial implementation */
    ////////////////////////////////////

    // Create a vector of b values (include 1)
	std::vector<double> b = {0};
	for(int i = 0; i < MAX_B; i++){
		b.emplace_back(i);
	}

    // Start timer
    // For each b value
        // Create a vector of timestamps
        // Calculate a vector P(t; b) for these timestamps 
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

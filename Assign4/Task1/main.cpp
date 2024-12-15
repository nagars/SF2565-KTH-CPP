/*
main.cpp
Created on: Dec 6, 2024
    Author: Alessio/Shawn
 */

#include <random>
#include <assert.h>
#include <cmath>
#include <fstream>
#include <iostream>

#define DT 1e-3  	// time step
#define MAX_B	10	// Max value of b values to use
#define B_VAL_INCREMENT 1	// b value increment


void printToFile(const std::vector<std::vector<double>> extinctionTimes,
		const std::vector<double> b_vals,
		const std::vector<double> timesteps){

	// Open a file for writing
	std::ofstream filex("xdata");
	std::ofstream filey("ydata");

	// Print to file
	// Print time steps to filex
	// for (const auto &element : timesteps) filex << element << " ";
	for (size_t i = 0; i < timesteps.size(); ++i) {
		filex << timesteps[i];
		if (i != timesteps.size() - 1) filex << " ";
	}
	filex << "\n";

	// Append b value for associated row
	// for (size_t i = 0; i < b_vals.size(); i++) {
	for (size_t i = 0; i < b_vals.size(); ++i) {
		filey << b_vals[i] << " ";
		// Print vectors of extinction times for various b values
		// for (const auto &elemente : extinctionTimes[i]){filey << elemente << " ";}
		for (size_t j = 0; j < extinctionTimes[i].size(); ++j) {
			filey << extinctionTimes[i][j];
			if (j != extinctionTimes[i].size() - 1) filey << " ";
		}
		filey << "\n";
	}

	// Close file stream
	// filex.std::ofstream::close();
	// filey.std::ofstream::close();
	filex.close();
	filey.close();
}



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
	std::vector<double> ICsamples;
	generateICSamples(ICsamples, IC_SAMPLES, b);

	/* Calculate the extinction time for each IC
       using the  Euler-Maruyama scheme */
	std::vector<double> extinctionTimes;
	std::random_device rd; // Seed generator
	std::mt19937 gen(rd()); // Random number generator
	std::normal_distribution<> dStandard(0.0, 1.0); // Standard normal pdf
	// For each IC (m) in ICsamples (M)
	for (int m = 0; m < IC_SAMPLES; m++) {
		// start stepping using the
		double Xn = ICsamples[m] ;
		for (int n = 0; ;n++) {
			Xn = Xn + (-b)*DT + sqrt(DT)*dStandard(gen);
			// if Xn<=0
			if (Xn <= 0) {
				// record the extinction time Tm=n*dt
				// break out
				extinctionTimes.emplace_back(n*DT);
				break;
			}
		}

		// // Calculation of probability
		// // for each time in times
		// std::vector<double> probability;
		// for(size_t n = 0; n < times.size(); n++){
		// 	double sum = 0;
		// 	for(int m = 0; m < IC_SAMPLES; m++){
		// 		sum += (extinctionTimes[m] > times[n]);
		// 	}
		// 	probability.emplace_back(sum / IC_SAMPLES);
		// }
		// return probability;
	}

	// Calculation of probability
	// for each time in times
	std::vector<double> probability;
	for (size_t n = 0; n < times.size(); n++) {
		double sum = 0;
		for (int m = 0; m < IC_SAMPLES; m++) {
			sum += (extinctionTimes[m] > times[n]);
		}
		probability.emplace_back(sum / IC_SAMPLES);
	}
	return probability;
}


void serial(std::vector<double> timestamps, double M) {
	////////////////////////////////////
	/* TASK I - Serial implementation */
	////////////////////////////////////

	// Create a vector of b values (include 1)
	std::vector<double> b;
	for(int i = 1; i < MAX_B; i+=B_VAL_INCREMENT){
		b.emplace_back(i);
	}

	// Create a vector of timestamps

	// Start timer
	// For each b value
	// Calculate a vector P(t; b) for these timestamps
	// Calculate best-fit f(t; lambda) = lambda*exp(-lambda*t)
	// Return lambda(b)
	// Stop timer
	// Return elapsed time

	std::vector<std::vector<double>> extinctionTimes;
	for(size_t n = 0; n < b.size(); n++){
		extinctionTimes.emplace_back(pExtinctionTimes(timestamps, b[n]));
	}


	// Generate data for plotting
	printToFile(extinctionTimes, b, timestamps);

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
	std::vector<double> timesteps;
	for(double i = 0; i < 1; i+=DT)
		timesteps.emplace_back(i);

	// Set M = 1e4
	// execute serial(M)
	serial(timesteps, 1e4);

	// pick a value of b = B from the results of Task I
	// Set M = 1e6 or more, as needed
	// execute parallel(M, B)

	return 0;
}

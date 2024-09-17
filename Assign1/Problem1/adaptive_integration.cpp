/*
 * adaptive_integration.cpp
 *
 *  Created on: Sep 16, 2024
 *      Author: Shawn
 */

#include "adaptive_integration.hpp"

////Simpsons functions////
double func_simpsons_rule( const std::function<double(double)>& func_f,
						  double begin_limit,
	                      double end_limit,
	                      double tolerance) {

	double midpoint = (begin_limit + end_limit) / 2;
	return (end_limit - begin_limit) / 6 * (func_f(begin_limit) + 4 * func_f(midpoint) + func_f(end_limit));

}


double func_ASI(double(*func_f)(double),
				double begin_limit,
	            double end_limit,
	            double tolerance,
	            uint32_t* func_call_counter) {

	// Initialisations
	double x = 0;			// fed to function to be tested
	double integral_1 = 0;	// I1 integration I(α,β)
	double integral_2 = 0;	// I2 integration  I2(α,β)
	double midpoint = 0;	// midpoint calculation for I2 (γ)
	double error = 0;		// error of simpsons calculation

	if (func_call_counter) {			// Check for null pointer
										// TODO need an error handler for: ptr == nullptr. See slides lecture 3 page 13
		(*func_call_counter)++;			// Increment function call
	}

	if (begin_limit > end_limit) { 		// Check if begin_limit < end_limit, else return with -1
		return -1;						// TODO should I return an error code, or handle the exception here?
	}

	double I1 = func_simpsons_rule(			// Calculate I1 (Call func_simpsons_rule)
		func_f,
		begin_limit,
		end_limit,
		tolerance
	);

	midpoint = (begin_limit + end_limit) / 2;		// Calculate half intervals  γ = 1 / 2 * (α+β)

	// Calculate I2 [ I2(α,β) := I(α,γ) + I(γ,β)]
	double I2 = func_simpsons_rule(func_f, begin_limit, midpoint, tolerance) 
		 + func_simpsons_rule(func_f, midpoint, end_limit, tolerance);
	

	// Calculate error [errest = 1 / 15 * (I2(α,β) − I(α,β))]

	// Check if within tolerance
	if (abs(error) < 15 * tolerance){
		return integral_2;
	}

	// Call function again [ASI(f,a,(a + b)/2,τ/2) + ASI(f,(a + b)/2,b,τ/2);]

}

/*
 * adaptive_integration.cpp
 *
 *  Created on: Sep 16, 2024
 *      Author: Shawn
 */

#include "adaptive_integration.hpp"

////Simpsons functions////
double func_simpsons_rule(double begin_limit, double end_limit, double tolerance){

	// Return [(β −α)/6 * (f(α)+4f((α+β)/2)+f(β))]

	// Alessio was here

}


double func_ASI(double(*f)(double), double begin_limit, double end_limit, double tolerance, uint32_t* func_call_counter){

	// Initialisations
	double x = 0;			// fed to function to be tested
	double integral_1 = 0;	// I1 integration I(α,β)
	double integral_2 = 0;	// I2 integration  I2(α,β)
	double midpoint = 0;	// midpoint calculation for I2 (γ)
	double error = 0;		// error of simpsons calculation

	// Check for null pointer

	// Increment function call counter
	*func_call_counter++;

	// Check if begin_limit < end_limit, else return with -1

	// Calculate I1 (Call func_simpsons_rule)

	// Calculate half intervals  γ = 1 / 2 * (α+β)

	// Calculate I2 [ I2(α,β) := I(α,γ) + I(γ,β)]

	// Calculate error [errest = 1 / 15 * (I2(α,β) − I(α,β))]

	// Check if within tolerance
	if (abs(error) < 15 * tolerance){
		return integral_2;
	}

	// Call function again [ASI(f,a,(a + b)/2,τ/2) + ASI(f,(a + b)/2,b,τ/2);]

}

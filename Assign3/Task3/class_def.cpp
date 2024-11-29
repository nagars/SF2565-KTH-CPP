/*
 * class_def.cpp
 *
 *  Created on: Nov 29, 2024
 *      Author: Shawn / Alessio
 */

#include "class_def.hpp"

/**EquationCurve**/
double EquationCurve::arcLength(double t) const {
	// No need to integrate if t is 0
	if (t == 0) return 0;

	// Define a lambda function
	// to generate the integrand for arc-length calculation
	auto normPdot = [this](double tau) -> double {
		Point Pdot = this->gammaprime(tau);
		return std::sqrt(Pdot.x * Pdot.x + Pdot.y * Pdot.y);
	};

	using namespace boost::math::quadrature;
	// Perform numerical integration over [0, t]
	return trapezoidal(normPdot, 0.0, t, TOL);
}

Point EquationCurve::at(double t) const {
	// Return cached value if previously computed
	if (cacheEnabled) {
		auto found = cache.find(t);
		if (found != cache.end()) {
			return found->second;
		}
	}
	// Compute s(1) if not already in cache
	if (!totalLengthComputed) {
		totalLength = arcLength(1.0);
		totalLengthComputed = true;
	} 
	double arcLengthTarget = t * totalLength; // Target arc-length value

	// Define the function f(t) = s(t) - sTarget
	auto f = [this, arcLengthTarget](double t) -> double {
		return arcLength(t) - arcLengthTarget;
	};

	// Define the function f'(t) = |dP/dt|
	auto f_prime = [this](double t) -> double {
		Point Pdot = this->gammaprime(t);
		return std::sqrt(Pdot.x * Pdot.x + Pdot.y * Pdot.y);
	};

	// Newton method to find root convergence
	double t_of_hatS = t;
	for(uintmax_t n = 0; n < MAX_ITER; n++) {
		t_of_hatS = t - f(t)/f_prime(t);

		// Upon convergence, cache and return the computed point
		if(fabs(t_of_hatS - t) < TOL) {
			Point result = gamma(t_of_hatS);
			// Store result in cache if required
			if (cacheEnabled)
				cache[t] = result;

			return result;
		}
		// update previous t value
		t = t_of_hatS;
	}
	throw std::runtime_error("Newton's method didn't converge");
}

/**StraightLine**/
Point StraightLine::at(double t) const {
	// Edge case for vertical line
	if(fabs(pointEnd.x - pointStart.x) < EPSILON) {
		Point p_toGet(pointStart.x,0);	// Init y point as 0 for now
		p_toGet.y = pointStart.y + t*(pointEnd.y - pointStart.y);
		return p_toGet;
	}// Edge case for horizontal line
	else if (fabs(pointEnd.y - pointStart.y) < EPSILON) {

		Point p_toGet(0,pointStart.y);	// Init x point as 0 for now
		p_toGet.x = pointStart.x + t*(pointEnd.x - pointStart.x);
		return p_toGet;
	} else {
		double pointOfInterest = pointStart.x + t*(pointEnd.x - pointStart.x);
		Point p_toGet(pointOfInterest,0);	// Init y point as 0 for now
		// p_toGet.y = pointStart.y + t*(pointEnd.x - pointStart.x);
		p_toGet.y = pointStart.y + t*(pointEnd.y - pointStart.y);
		return p_toGet;
	}
}

/**BottomCurve**/
double BottomCurve::x_of_t(double t) const {
	//Check for edge cases
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	// Describes domain (-10,5)
	double x = (1 - t) * (-10) + 5 * t;
	return x;
}

Point BottomCurve::gamma(double t) const {
	double x = x_of_t(t);
	Point p_of_t(x, eqFunc(x));
	return p_of_t;
};

Point BottomCurve::gammaprime(double t) const {
	using namespace boost::math::differentiation;

	// Calculates x-dot. Uses capture variable to access the x_of_t class method
	auto x_dot = finite_difference_derivative(
			[this](double t_val) { return x_of_t(t_val);}, t);

	// Calculates y-dot.
	auto y_dot = finite_difference_derivative(
			[this](double t_val) {
		double x = x_of_t(t_val);
		return eqFunc(x);
	}, t);

	return Point(x_dot, y_dot);
};

/**Domain**/
void Domain::GenerateGrid() {
	int divisions = grid.GetX().rows() - 1; // `numDivisions` intervals
	for (int i = 0; i <= divisions; ++i) {
		double eta = static_cast<double>(i) / divisions;
		for (int j = 0; j <= divisions; ++j) {
			double xi = static_cast<double>(j) / divisions;

			// Use TFI to compute coordinates
			Point p = TFI(xi, eta);
			grid.SetPoint(i, j, p.x, p.y);
		}
	}
}

Point Domain::TFI(double xi, double eta) {
	// Use the boundary curves to compute the x, y coordinates
	//
	auto [xBottom_atXi, yBottom_atXi] = bottom->at(xi);
	auto [xTop_atXi, yTop_atXi] = top->at(xi);
	auto [xRight_atEta, yRight_atEta] = right->at(eta);
	auto [xLeft_atEta, yLeft_atEta] = left->at(eta);
	auto [xBottom_atZero, yBottom_atZero] = bottom->at(0);
	auto [xTop_atZero, yTop_atZero] = top->at(0);
	auto [xBottom_atOne, yBottom_atOne] = bottom->at(1);
	auto [xTop_atOne, yTop_atOne] = top->at(1);

	double x = (1 - xi) * xLeft_atEta + xi * xRight_atEta
			+ (1 - eta) * xBottom_atXi + eta * xTop_atXi
			- (1 - xi) * (1 - eta) * xBottom_atZero
			- (1 - xi) * eta * xTop_atZero
			- (1 - eta) * xi * xBottom_atOne
			- xi * eta * xTop_atOne;

	double y = (1 - xi) * yLeft_atEta + xi * yRight_atEta
			+ (1 - eta) * yBottom_atXi + eta * yTop_atXi
			- (1 - xi) * (1 - eta) * yBottom_atZero
			- (1 - xi) * eta * yTop_atZero
			- (1 - eta) * xi * yBottom_atOne
			- xi * eta * yTop_atOne;

	return Point(x, y);
}

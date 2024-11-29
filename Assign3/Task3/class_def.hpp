/*
 * class_def.hpp
 *
 *  Created on: Nov 12, 2024
 *      Author: Shawn / Alessio
 */

#ifndef CLASS_DEF_HPP_
#define CLASS_DEF_HPP_

#include <cmath>
#include <vector>
#include <memory>
#include <cassert>
#include <limits>
#include <iostream>

#include "Eigen/Eigen"
#include <boost/math/quadrature/trapezoidal.hpp>
// #include <boost/math/tools/roots.hpp>
#include <boost/math/differentiation/finite_difference.hpp>


// Holds an x,y point
class Point {

public:
	// Default Constructor
	// Point();
	Point() : x(0.0), y(0.0) {}
	// Parameter Constructor
	Point(const double xCoord, const double yCoord)
	: x(xCoord), y(yCoord){}
	// Coordinate variables
	double x, y;

private:

protected:
};


// Used to represent the bottom curve
class Curve {
public:
	virtual ~Curve() = default;
	virtual Point at(double t) const = 0;

private:

protected:
};


class EquationCurve:public Curve {

public:
	virtual~EquationCurve() = default;

	// Compute reparametized curve
	// Option to use point cache to compare peformance
	Point at(double t) const override {
		if (cacheEnabled) {
			// Check if P(t) has been computed previously
			auto found = cache.find(t);
			if (found != cache.end()) {
				return found->second; // Return the cached point
			}
		}

		const double hatS = t; // use reference to keep same signature as Curve class
		// while avoiding confusion in below function equations
		const double arcLengthTotal = arcLength(1.0); // full curve length
		double arcLengthTarget = hatS * arcLengthTotal; // Target arc-length value

		// Define the function f(t) = s(t) - sTarget
		auto f = [this, arcLengthTarget](double t) -> double {
			double temp = arcLength(t) - arcLengthTarget;
			return temp;
		};

		// Define the function f'(t) = |dP/dt|
		auto f_prime = [this](double t) -> double {
			Point Pdot = this->gammaprime(t);
			double temp = std::sqrt(Pdot.x * Pdot.x + Pdot.y * Pdot.y);
			return temp;
		};

		// Newton method to find root convergence
		double t_of_hatS = t;
		for(uintmax_t n = 0; n < MAX_ITER; n++) {
			t_of_hatS = t - f(t)/f_prime(t);

			// Upon convergence, cache and return the computed point
			if(fabs(t_of_hatS - t) < TOL) {
				Point result = gamma(t_of_hatS);
				if (cacheEnabled) {
					cache[t] = result;
				}
				return result;
			}

			// update previous t value
			t = t_of_hatS;
		}

		throw std::runtime_error("Newton's method didn't converge");

	}
	
	// Activate point cache for performance testing
	void enableCache(bool enable) {
		cacheEnabled = enable;
	}

private:
	// Compute arc-length function s(t) using boost numerical integration
	double arcLength(double t) const {

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

	virtual Point gamma(double t) const = 0;
	virtual Point gammaprime (double t) const = 0;

	mutable std::unordered_map<double, Point> cache; // Cache of already computed points

	const double TOL = 1e-12; // Tolerance for numerical calculations
	const uintmax_t MAX_ITER = 10000;	// Max iterations for newton method

protected:
	std::function<double(double)> eqFunc;
	bool cacheEnabled = false; // point cache toggle status
};


// Used to represent the line boundaries of the top/left/right
class StraightLine : public Curve {

public:
	StraightLine(Point a, Point b):
		pointStart(a), pointEnd(b) { }

	// t = {0,1}. t = 0 -> pointStart. t = 1 -> pointEnd
	Point at(double t) const override {
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

	Point pointStart;		// Start of line
	Point pointEnd;			// End of line

private:
	// Tolerance to check for edge cases of vertical boundaries
	static constexpr double EPSILON = std::numeric_limits<double>::epsilon();

protected:
};


class BottomCurve : public EquationCurve {

public:
	BottomCurve(std::function<double(double)> func) {
		eqFunc = func;
	}

	double x_of_t(double t) const {
		//Check for edge cases
		if (t < 0) t = 0;
		if (t > 1) t = 1;
		// Describes domain (-10,5)
		double x = (1 - t) * (-10) + 5 * t;
		return x;
	}

	// Returns P(t)
	Point gamma(double t) const override {
		double x = x_of_t(t);
		Point p_of_t(x, eqFunc(x));
		return p_of_t;
	};

	// Calculates dP(t)/dt using finite differences
	Point gammaprime(double t) const override {
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

private:
};


//Class to hold the matrices of x and y coordinates generated by
//the Domain TFI method
class Grid {

public:
	// Constructor initializes grid with given dimensions
	Grid(int rows, int cols)
	: x(Eigen::MatrixXd::Zero(rows, cols)),
	  y(Eigen::MatrixXd::Zero(rows, cols))
	{ }

	// Getters for the x and y matrices
	const Eigen::MatrixXd& GetX() const { return x; }
	const Eigen::MatrixXd& GetY() const { return y; }

	// Setters for the x and y matrices
	void SetX(const Eigen::MatrixXd& newX) { x = newX; }
	void SetY(const Eigen::MatrixXd& newY) { y = newY; }

	// Access element in the grid
	void SetPoint(int row, int col,
			double xValue, double yValue) {
		x(row, col) = xValue;
		y(row, col) = yValue;
	}

private:
	Eigen::MatrixXd x; // Matrix holding x-coordinates
	Eigen::MatrixXd y; // Matrix holding y-coordinates

protected:
};


class Domain {

public:
	Domain(std::unique_ptr<Curve> bottom, std::unique_ptr<Curve> top, 
			std::unique_ptr<Curve> left, std::unique_ptr<Curve> right,
			int numDivisions)
	: bottom(std::move(bottom)), top(std::move(top)),
	  left(std::move(left)), right(std::move(right)),
	  grid(numDivisions + 1, numDivisions + 1)
	{ }

	// Grid-object generator
	// Generates the grid based on transfinite interpolation (TFI)
	void GenerateGrid() {
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

	// Generates an x, y pair based on xi and eta using TFI
	// Based on 'Basic structured grid generation (Farrashkhalvat, Miles) 
	// section 4.3.2
	Point TFI(double xi, double eta) {
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

	// Activate point cache of bottom boundary for performance testing
	void enableCache(bool enable) {
		auto* bottomBoundary = dynamic_cast<EquationCurve*>(bottom.get());
		bottomBoundary->enableCache(enable);
	}

	// Grid getter
	const Grid& GetGrid() const { return grid; }

private:
	std::unique_ptr <Curve> bottom;
	std::unique_ptr <Curve> top;
	std::unique_ptr <Curve> left;
	std::unique_ptr <Curve> right;
	Grid grid; // Grid that holds x and y coordinates

protected:
};


#endif /* CLASS_DEF_HPP_ */

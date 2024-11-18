/*
 * class_def.hpp
 *
 *  Created on: Nov 12, 2024
 *      Author: user
 */

#ifndef CLASS_DEF_HPP_
#define CLASS_DEF_HPP_

#include <cmath>
#include <vector>
#include <memory>
#include <cassert>
#include <limits>

#define EPSILON std::numeric_limits<double>::epsilon()

// Holds an x,y point
class Point {
public:
	// Default Constructor
	Point();
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
	virtual Point at_t(double t) const = 0;
private:
protected:
};

// Used to represent the line boundaries of the top/left/right
class StraightLine : public Curve{

public:
	StraightLine(Point a, Point b):
		pointStart(a), pointEnd(b){}

	// t = {0,1}. t = 0 -> pointStart. t = 1 -> pointEnd
	Point at_t(double t) const override {
		// Ensure points are not the same
		assert(fabs(pointEnd.x - pointStart.x) < EPSILON);
		assert(fabs(pointEnd.y - pointStart.y) < EPSILON);

		double pointOfInterest = pointStart.x + t*(pointEnd.x - pointStart.x);
		Point p_toGet(pointOfInterest,0);	// Init y point as 0 for now
		p_toGet.y = pointStart.y + t*(pointEnd.x - pointStart.x);
		return p_toGet;
	};

private:
	Point pointStart;		// Start of line
	Point pointEnd;			// End of line
};

// Any boundary that is not a straight line
class EquationCurve : public Curve {	
	public:
		virtual ~EquationCurve() = default; 
		Point at_t(double t) const override;
		virtual Point at_hatS(double hatS) const = 0;
	private:
		virtual Point gamma(double t) const = 0; 
		virtual Point gammaprime(double t) const = 0;
};

// A concrete implementation of the curved bottom boundary
class BottomCurve : public EquationCurve {
	public:
		// constructor (empty)
		// destructor (is it needed?)
		// 'at' methods
		Point at_t(double t) {
			return gamma(t);
		}
		Point at_hatS(double hatS) {
			// compute t* = t(hatS;s(1)), using Newton's method in lecture 8 slide 31,
			//                            which uses gammaprime
			// get gamma(t*)
		} 
	private:
		// domain of bottom curve in cartesian parametrisation
		static constexpr double X_MIN = -10;
		static constexpr double X_MID = -3;
		static constexpr double X_MAX = 5;
		static constexpr double X_DELTA = X_MAX - X_MIN;

		// TODO compute s(1)
			// use ASI
			// int_0^1 gammaprime(t) dt

		// Helper functions for gamma and gammaprime methods
		// Refer to assignment page 1 for symbols
		double x(double t) const {
			return X_MIN + X_DELTA*t; 
		}
		double g(double x) const {
			if (x < X_MID) {
				return 1 + std::exp(-3*(x+6)) ;
			} else {
				return 1 + std::exp(3*x);
			}
		}
		// returns P(t)=(x(t), y(t))
		Point gamma(double t) {
			// TODO add check for out-of-bounds argument
			double x_of_t = x(t);
			double g_of_x = g(x_of_t);
			// f{g[x(t)]}
			double f_of_x = 1/(2*g_of_x);
			return Point(x_of_t, f_of_x);
		}
		// returns P_dot(t)=(x_dot(t), y_dot(t))
		Point gammaprime(double t) {
			double x_of_t = x(t);
			double g_of_x = g(x_of_t);
			double x_dot = X_DELTA;
			double g_prime;
			if (x_of_t < X_MID) {
				g_prime = 1 + std::exp(-3*(x_of_t+6));
			} else {
				g_prime = 1 + std::exp(3*x_of_t);
			}
			double y_dot = x_of_t / (-2*g_of_x) * g_prime;
			return Point(x_dot, y_dot);
		}
};

// Used to represent the grid
class Domain {
public:
	Domain(Point bottomLeft, Point bottomRight,
			Point topLeft, Point topRight);
private:
	std::unique_ptr <StraightLine> top;
	std::unique_ptr <StraightLine> bottom;
	std::unique_ptr <StraightLine> left;
	std::unique_ptr <StraightLine> right;
protected:
};

#endif /* CLASS_DEF_HPP_ */

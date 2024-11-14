/*
 * class_def.hpp
 *
 *  Created on: Nov 12, 2024
 *      Author: user
 */

#ifndef CLASS_DEF_HPP_
#define CLASS_DEF_HPP_

#include <math.h>
#include <vector>
#include <memory>
#include <cassert>
#include <limits>

#include "Eigen/Eigen"


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
	virtual Point at(double t) const = 0;
private:
protected:
};

// Used to represent the line boundaries of the top/left/right
class StraightLine : public Curve{

public:
	StraightLine(Point a, Point b):
		pointStart(a), pointEnd(b){}

	// t = {0,1}. t = 0 -> pointStart. t = 1 -> pointEnd
	Point at(double t) const override {
		// Ensure points are not the same
		assert(fabs(pointEnd.x - pointStart.x) < EPSILON);
		assert(fabs(pointEnd.y - pointStart.y) < EPSILON);

		double pointOfInterest = pointStart.x + t*(pointEnd.x - pointStart.x);
		Point p_toGet(pointOfInterest,0);	// Init y point as 0 for now
		p_toGet.y = pointStart.y + t*(pointEnd.x - pointStart.x);
		return p_toGet;
	};

	Point pointStart;		// Start of line
	Point pointEnd;			// End of line
};

// Used to represent the grid
class Domain {
public:
	Domain(Point bottomLeft, Point bottomRight,
			Point topLeft, Point topRight);

	// Generates matrix of x,y in physical domain
	Eigen::MatrixXd Gen_Matrix(int num_division);

	// Generates an x,y pair based on xi and eta using tfi
	std::pair<double, double> TFI(double xi, double eta);

private:
	std::unique_ptr <StraightLine> top;
	std::unique_ptr <StraightLine> bottom;
	std::unique_ptr <StraightLine> left;
	std::unique_ptr <StraightLine> right;
protected:
};


#endif /* CLASS_DEF_HPP_ */

/*
 * class_def.hpp
 *
 *  Created on: Nov 12, 2024
 *      Author: user
 */

#ifndef CLASS_DEF_HPP_
#define CLASS_DEF_HPP_

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
class StraightLine : Curve{

public:
	StraightLine();
};

class Domain {
public:
	Domain();
private:
protected:
};

#endif /* CLASS_DEF_HPP_ */

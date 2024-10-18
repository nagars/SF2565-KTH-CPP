/*
 * class_definitions.h
 *
 *  Created on: Oct 18, 2024
 *      Author: root
 */

#ifndef CLASS_DEFINITIONS_H_
#define CLASS_DEFINITIONS_H_

#include <math.h>

class Point {
	public:
	// Default Constructor
	Point() : x(0), y(0){};

	// Parameter Constructor
	Point(const double xCoord, const double yCoord) : x(xCoord), y(yCoord){};

	// Coordinate variables
	double x,y;

	private:
	protected:

};


class Rectangle {
	public:

	//Default constructor
	Rectangle();

	// Rectangle boundaries
	Point bottomLeft, topRight;

	// Checks if a particular point is within the rectangle
	bool check_point_within_rect (Point p);

	private:
	protected:

};

#endif /* CLASS_DEFINITIONS_H_ */

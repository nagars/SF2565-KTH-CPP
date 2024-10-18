/*
 * class_definitions.h
 *
 *  Created on: Oct 18, 2024
 *      Author: root
 */

#ifndef CLASS_DEFINITIONS_H_
#define CLASS_DEFINITIONS_H_


class Point {
	public:
	// Default Constructor
	Point() : x(0), y(0){};

	// Parameter Constructor
	Point(const double xCoord, const double yCoord) : x(xCoord), y(yCoord){};

	double x,y;
	private:


	protected:

};


class Rectangle {
	public:

	//Default constructor
	Rectangle();

	Point bottomLeft, topRight;

	private:

	protected:

};

#endif /* CLASS_DEFINITIONS_H_ */

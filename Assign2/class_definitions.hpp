/*
 * class_definitions.h
 *
 *  Created on: Oct 18, 2024
 *      Author: root
 */

#ifndef CLASS_DEFINITIONS_HPP_
#define CLASS_DEFINITIONS_HPP_

#include <math.h>
#include <vector>

class Point {
public:
	// Default Constructor
	Point();

	// Parameter Constructor
	Point(const double xCoord, const double yCoord);

	// Coordinate variables
	double x, y;

private:
protected:

};


class Rectangle {
public:

	//Default constructor
	Rectangle();

	//Constructor that takes bottomleft, topright
	Rectangle(const Point bottomLeft, const Point topRight);

	// Checks if a particular point is within the rectangle
	bool check_point_within_rect (Point p);

	// Check if another rectangle intersects with this rectangle
	bool intersects (Rectangle rhs);

	// Rectangle boundaries
	Point bottomLeft, topRight;

private:
protected:

};

class Quadtree {

public :
	// Constructor for specified boundary
	Quadtree(const Rectangle& boundary, unsigned long bucketSize);

	// Constructor automatically calculating boundary
	Quadtree(std::vector<Point>& pointCollection, unsigned long bucketSize);

	// Destructor
	~Quadtree();

	// Insert a point in a unique quatrant
	bool insert(const Point &p);

	std::vector<Point> query(Rectangle rect);

private :

	// Subdivide the current node into 4 quadtrants
	void subdivide();

	// Check if leaf is over bucket size
	void exceedsBucketSize();

	unsigned long m_bucketSize;      // max. No of points per node allowed
	Rectangle m_boundary;            // boundary of node
	std::vector<Point> m_points;     // points in node
	//bool m_divided;                  // Flag to track if rectangle has children

	// Child quadtrees
	Quadtree* m_northWest;
	Quadtree* m_northEast;
	Quadtree* m_southWest;
	Quadtree* m_southEast;
};



#endif /* CLASS_DEFINITIONS */

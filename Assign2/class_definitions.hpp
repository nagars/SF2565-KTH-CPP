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

	// @Shawn: add constructor that takes bottomleft, topright
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
	Quadtree(const Rectangle& boundary, int bucketSize);

	// Constructor automatically calculating boundary
	Quadtree(std::vector<Point>& pointCollection, int bucketSize);

	// Destructor
	~Quadtree();

	// Check if leaf is over bucket size
	void exceedsBucketSize();

	// Insert a point
	bool insert(const Point &p);

	// Subdivide the current node
	void subdivide();

	std::vector<Point> query(Rectangle rect);

private :

	int m_bucketSize;                // max. No of points per leaf
	Rectangle m_boundary;            // boundary of whole quadtree
	std::vector<Point> m_points;     // points in leaf node
	bool m_divided;                  // has children

	// Child quadtrees
	Quadtree* m_northWest;
	Quadtree* m_northEast;
	Quadtree* m_southWest;
	Quadtree* m_southEast;
};



#endif /* CLASS_DEFINITIONS */

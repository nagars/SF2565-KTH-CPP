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

#include "utilities_v3/mpl_writer.hpp"

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
	bool containsPoint(Point p);

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

	// // Insert a point in a unique quatrant
	// bool insert(const std::vector<Point>& pointCollection);

	// For each node, collects the relevant boundary and points
	// Returns a vector of (boundaries, points) tuples
	void collectNodes(std::vector<Rectangle>& boundaries,
	 				  std::vector<std::vector<Point>>& points) const;

	// Returns all the points that fall within a specified rectangle
	void query(Rectangle& rect, std::vector<Point>& pointsInRect);

	// recursively create tree structure and load points in leaves
	void growTree();
	
	Rectangle m_boundary;            // boundary of node
	std::vector<Point> m_points;     // points in node

private :

	// Subdivide the current node into 4 quadrants
	void subdivide();

	// Loads all the input points, creating the tree structure
	void seedTree(std::vector<Point>& pointCollection);

	unsigned long m_bucketSize;      // max. No of points per node allowed
	bool m_isLeaf;                   // Flag to track if node is a leaf

	// Child quadtrees
	Quadtree* m_northWest;
	Quadtree* m_northEast;
	Quadtree* m_southWest;
	Quadtree* m_southEast;
	std::vector<Quadtree*> children;
};



#endif /* CLASS_DEFINITIONS */

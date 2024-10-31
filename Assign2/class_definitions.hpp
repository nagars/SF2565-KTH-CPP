/*
 * class_definitions.h
 *
 *  Created on: Oct 18, 2024
 *      Author: Shawn, Alessio
 */

#ifndef CLASS_DEFINITIONS_HPP_
#define CLASS_DEFINITIONS_HPP_

#include <math.h>
#include <vector>
#include <memory>

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
	bool check_point_within_rect (Point p);

	// Check if another rectangle overlaps with this rectangle
	bool overlaps (Rectangle rhs);

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

	// Recursively build the quadtree
	void build_tree(void);

	// For each node, collects the relevant boundary and points
	// Returns a vector of (boundaries, points) tuples
	void collectNodes(std::vector<Rectangle>& boundaries,
	 				  std::vector<std::vector<Point>>& points) const;

	// Returns all the points that fall within a specified rectangle
	void query(Rectangle& rect, std::vector<Point>& pointsInRect);

private :

	// Subdivide the current node into 4 quadtrants
	void subdivide();

	unsigned long m_bucketSize;      // max. No of points per node allowed
	Rectangle m_boundary;            // boundary of node
	std::vector<Point> m_points;     // points in node
	bool m_node_divided = false;     // Flag to track if rectangle has children

	// Child quadtrees
	std::unique_ptr<Quadtree> m_northWest;
	std::unique_ptr<Quadtree> m_northEast;
	std::unique_ptr<Quadtree> m_southWest;
	std::unique_ptr<Quadtree> m_southEast;
};



#endif /* CLASS_DEFINITIONS */

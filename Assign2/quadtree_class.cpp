/*
 * quadtree_class.cpp
 *
 *  Created on: Oct 18, 2024
 *      Author: Alessio Bacchiocchi
 */

#include <iostream>
#include "class_definitions.hpp"

Quadtree::Quadtree(const Rectangle& boundary, unsigned long bucketSize)
: m_bucketSize(bucketSize), m_boundary(boundary), m_divided(false),
  m_northWest(nullptr), m_northEast(nullptr),
  m_southWest(nullptr), m_southEast(nullptr){

}

// Constructor automatically calculating boundary
Quadtree::Quadtree(std::vector<Point>& pointCollection, unsigned long bucketSize)
: m_bucketSize(bucketSize), m_divided(false),
  m_northWest(nullptr), m_northEast(nullptr),
  m_southWest(nullptr), m_southEast(nullptr) {

	//	// TODO: better error handling, try-catch block
	//	if (pointCollection.empty()) {
	//		std::cerr << "Error: Cannot build quadtree with no points.\n";
	//		return;
	//	}

	// Initialise the variables with the largest possible values */
	double minX = std::numeric_limits<double>::max();
	double minY = std::numeric_limits<double>::max();
	double maxX = std::numeric_limits<double>::lowest();
	double maxY = std::numeric_limits<double>::lowest();

	// Determine the smallest containing box
	// Parse through vector of points. Assign dimensions of
	// current quadrant based on max value x and y across
	// All points
	for (const Point& p : pointCollection) {
		if (p.x < minX) minX = p.x;
		if (p.y < minY) minY = p.y;
		if (p.x > maxX) maxX = p.x;
		if (p.y > maxY) maxY = p.y;
	}

	// Create point objects with dimensions determined above
	// These will act as boundary of our rectangle
	Point bottomLeft(minX, minY);
	Point topRight(maxX, maxY);

	// Create rectangle object with above dimensions
	m_boundary = Rectangle(bottomLeft, topRight);

	// Insert all points into the quadtree
	for (const Point& p : pointCollection) {
		insert(p);
	}

}

// Destructor
Quadtree::~Quadtree() {
	delete m_northWest;
	delete m_northEast;
	delete m_southWest;
	delete m_southEast;
}

// Insert a point
bool Quadtree::insert(const Point &p) {

	// Check if the point falls within the boundary of
	// the current rectangle
	// Return false if not inside
	if (false == m_boundary.check_point_within_rect(p)) {
		return false;
	}

	// Check if max capacity of the rectangle is exceeded
	if (m_points.size() < m_bucketSize) {
		m_points.push_back(p);
		return true;
	}

	// If point falls inside current node but exceeds max number
	// of points allowed, divide node further
	if (!m_divided) {
		subdivide();
	}

	// Insert point into newly generated quadrants
	// Recursively continue until successful
	if (m_northWest->insert(p)) return true;
	if (m_northEast->insert(p)) return true;
	if (m_southWest->insert(p)) return true;
	if (m_southEast->insert(p)) return true;

	return false;
}

// Traverse the tree, get the (boundary, points) pair for each node,
// and return a vector of (boundary, points) pairs.
void Quadtree::collectNodes(std::vector<Rectangle>& boundaries,
	 			  std::vector<std::vector<Point>>& points) const {
	
	// Collect this node's boundary and point
	
	// Recursively collect from subdivided quadrants if they exist
    if (!m_divided) {
		boundaries.push_back(m_boundary);
		points.push_back(m_points);
    }
	else {
        m_northWest->collectNodes(boundaries, points);
        m_northEast->collectNodes(boundaries, points);
        m_southWest->collectNodes(boundaries, points);
        m_southEast->collectNodes(boundaries, points);
	}

}

// Subdivide the current node
void Quadtree::subdivide() {

	// Find midpoint of current rectangle boundary
	double midX = (m_boundary.bottomLeft.x
			+ m_boundary.topRight.x) / 2.0;
	double midY = (m_boundary.bottomLeft.y
			+ m_boundary.topRight.y) / 2.0;

	// Split rectangle into 4 quadrants
	m_northWest = new Quadtree(Rectangle(
			Point(m_boundary.bottomLeft.x, midY),
			Point(midX, m_boundary.topRight.y)),
			m_bucketSize);

	m_northEast = new Quadtree(Rectangle(
			Point(midX, midY),
			m_boundary.topRight),
			m_bucketSize);

	m_southWest = new Quadtree(Rectangle(
			m_boundary.bottomLeft,
			Point(midX, midY)),
			m_bucketSize);

	m_southEast = new Quadtree(Rectangle(
			Point(midX, m_boundary.bottomLeft.y),
			Point(m_boundary.topRight.x, midY)),
			m_bucketSize);

	// Set flag that quad has been divided
	m_divided = true;
}

std::vector<Point> Quadtree::query(Rectangle rect) {
	// query logic - assignment task #4;
	// recursively searches the tree through paths with possible overlap
	// at leaf: loops over all points in leaf, checking overlap with given
	//          rectangle.
	// returns vector of points that fall within given
	return m_points;
}


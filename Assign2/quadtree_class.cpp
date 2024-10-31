/*
 * quadtree_class.cpp
 *
 *  Created on: Oct 18, 2024
 *      Author: Alessio Bacchiocchi
 */

#include <iostream>
#include "class_definitions.hpp"

// Constructor for empty quadtree of specified boundary
Quadtree::Quadtree(const Rectangle& boundary, unsigned long bucketSize)
: m_bucketSize(bucketSize), m_boundary(boundary), m_isLeaf(true),
  m_northWest(nullptr), m_northEast(nullptr),
  m_southWest(nullptr), m_southEast(nullptr){

}


// Constructor for specified points collection, automatically calculating the 
// smallest quatree boundary that contains all the given points
Quadtree::Quadtree(std::vector<Point>& pointCollection, unsigned long bucketSize)
: m_bucketSize(bucketSize), m_isLeaf(true),
//   m_northWest(nullptr), m_northEast(nullptr),
//   m_southWest(nullptr), m_southEast(nullptr) {
  children(4) {

	// Initialise the variables with the largest possible values
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
	
	seedTree(pointCollection);
}


// Destructor
Quadtree::~Quadtree() {
	delete m_northWest;
	delete m_northEast;
	delete m_southWest;
	delete m_southEast;
}


// Loads all the input points in the root, then creates the tree
void Quadtree::seedTree(std::vector<Point>& pointCollection) {
	// load all data in root
	for (auto const& p : pointCollection)
		m_points.push_back(p);
	growTree();
}


// Recursively create tree structure and load points in leaves
void Quadtree::growTree() {
	if (m_points.size() > m_bucketSize) {
		if (m_isLeaf)
			subdivide();
		for (auto const& p : m_points) {
			for (auto const& c : children) {
				if (c->m_boundary.containsPoint(p)) {
					c->m_points.push_back(p);
					break;
				}
			}
		}
		m_points.clear();
		for (auto const& c : children)
			c->growTree();
	}
}


// Traverse the tree, get the (boundary, points) pair for each node,
// and return a vector of (boundary, points) pairs.
void Quadtree::collectNodes(std::vector<Rectangle>& boundaries,
	 			            std::vector<std::vector<Point>>& points) const {	
	// If this node is a leaf, collect its boundary and points
    if (m_isLeaf) {
		if (!m_points.empty()) {
			boundaries.push_back(m_boundary);
			points.push_back(m_points);
		}
    } else {
		// Recursively collect from subdivided quadrants if they exist	
		for (auto const& c : children)
        	c->collectNodes(boundaries, points);
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
	
	// Populate the children vector with the pointers
    children = { m_northWest, m_northEast, m_southWest, m_southEast };

	// Set flag that quad has been divided
	m_isLeaf = false;
}

// Returns all the points within a specified region
void Quadtree::query(Rectangle& rect,
					 std::vector<Point>& pointsInRect) {
	// Searches the tree through paths with possible overlap
	// Returns vector of points that fall within given rectangle
	
	// check if query box intersects with Qtree boundary
	if (m_boundary.intersects(rect)) {
		// check if leafnode
		if (m_isLeaf) {
			// check if a point of this leaf is inside the query box
			// if so, collect it
			for (const auto& p : m_points) {
				if (rect.containsPoint(p)) {
					pointsInRect.push_back(p);
				}
			}
		// if not a leaf node, call query on the children
		} else {
			for (auto const& c : children)
				c->query(rect, pointsInRect);
		}		 
	}
}
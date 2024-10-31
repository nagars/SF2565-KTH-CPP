/*
 * quadtree_class.cpp
 *
 *  Created on: Oct 18, 2024
 *      Author: Shawn, Alessio Bacchiocchi
 */

#include <iostream>
#include "class_definitions.hpp"


Quadtree::Quadtree(const Rectangle& boundary, unsigned long bucketSize)
: m_bucketSize(bucketSize), m_boundary(boundary), m_node_divided(false),
  m_northWest(nullptr), m_northEast(nullptr),
  m_southWest(nullptr), m_southEast(nullptr){

}

// Constructor automatically calculating boundary
Quadtree::Quadtree(std::vector<Point>& pointCollection, unsigned long bucketSize)
: m_bucketSize(bucketSize), m_node_divided(false),
  m_northWest(nullptr), m_northEast(nullptr),
  m_southWest(nullptr), m_southEast(nullptr) {

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
		//insert(p);
		m_points.push_back(p);
	}

	// Recursively build tree
	build_tree();

}


// Destructor
Quadtree::~Quadtree() {

}

// Recursively build the tree
void Quadtree::build_tree(void){

	// Check if points to be allotted exceed
	// max size of current node
	if (m_points.size() > m_bucketSize) {
		// If node is a leaf, divide it
		if (!m_node_divided)
			subdivide();

		// Allot points in created children
		for (auto const& p : m_points) {

			if (m_northWest->m_boundary.check_point_within_rect(p)){
				m_northWest->m_points.push_back(p);
			} else if (m_northEast->m_boundary.check_point_within_rect(p)){
				m_northEast->m_points.push_back(p);
			} else if (m_southWest->m_boundary.check_point_within_rect(p)){
				m_southWest->m_points.push_back(p);
			} else if (m_southEast->m_boundary.check_point_within_rect(p)){
				m_southEast->m_points.push_back(p);
			}
		}

		// Clear points from current node
		m_points.clear();

		// Continue to build the tree from each node
		m_northWest->build_tree();
		m_northEast->build_tree();
		m_southWest->build_tree();
		m_southEast->build_tree();

	}

}

// Traverse the tree, get the (boundary, points) pair for each node,
// and return a vector of (boundary, points) pairs.
void Quadtree::collectNodes(std::vector<Rectangle>& boundaries,
		std::vector<std::vector<Point>>& points) const {

	// Collect leaf node's boundary and points
	if (!m_node_divided) {
		boundaries.push_back(m_boundary);
		points.push_back(m_points);
		return;
	}

	// Recursively collect from subdivided quadrants if they exist
	m_northWest->collectNodes(boundaries, points);
	m_northEast->collectNodes(boundaries, points);
	m_southWest->collectNodes(boundaries, points);
	m_southEast->collectNodes(boundaries, points);

}

// Subdivide the current node into 4 quadrants
void Quadtree::subdivide() {

	// Find midpoint of current rectangle boundary
	double midX = (m_boundary.bottomLeft.x
			+ m_boundary.topRight.x) / 2.0;
	double midY = (m_boundary.bottomLeft.y
			+ m_boundary.topRight.y) / 2.0;

	// Split rectangle into 4 quadrants
	m_northWest = std::make_unique<Quadtree>(Rectangle(
			Point(m_boundary.bottomLeft.x, midY),
			Point(midX, m_boundary.topRight.y)),
			m_bucketSize);

	m_northEast = std::make_unique<Quadtree>(Rectangle(
			Point(midX, midY),
			m_boundary.topRight),
			m_bucketSize);

	m_southWest = std::make_unique<Quadtree>(Rectangle(
			m_boundary.bottomLeft,
			Point(midX, midY)),
			m_bucketSize);

	m_southEast = std::make_unique<Quadtree>(Rectangle(
			Point(midX, m_boundary.bottomLeft.y),
			Point(m_boundary.topRight.x, midY)),
			m_bucketSize);

	// Set flag that quad has been divided
	m_node_divided = true;
}

// Used to return all points within a given boundary provided
void Quadtree::query(Rectangle& rect, std::vector<Point>& pointsInRect) {

	// check if query box intersects with Quadtree boundary
	if (m_boundary.overlaps(rect)) {
		// check if leafnode
		if (!m_node_divided) {
			// check if points are within boundary and if so, collect them
			for (const auto& point : m_points) {
				if (rect.check_point_within_rect(point)) {
					pointsInRect.push_back(point);
				}
			}
		}
		// if not a leaf node, call query on the children
		else {
			m_northWest->query(rect, pointsInRect);
			m_northEast->query(rect, pointsInRect);
			m_southWest->query(rect, pointsInRect);
			m_southEast->query(rect, pointsInRect);
		}

	}
}


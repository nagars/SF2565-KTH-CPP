/*
 * quadtree_class.cpp
 *
 *  Created on: Oct 18, 2024
 *      Author: Alessio Bacchiocchi
 */

#pragma once

#include <vector>
#include "class_definitions.h"

class Quadtree {

    public :
        // Constructor
        Quadtree(std::vector<Point> vec,
                 int bucketCapacity) {
            // constructor logic
        }

        // Destructor
        ~Quadtree() {
            // Destructor logic
        }

        std::vector<Point> query(Rectangle rect) {
            // query logic - assignment task #4
            // recursively searches the tree through paths with possible overlap
            // at leaf: loops over all points in leaf, checking overlap with given
            //          rectangle.
            // returns vector of points that fall within given 
        }

    private :

        // Check if leaf is over bucket size
        void exceedsBucketSize() {
            // bucket size check logic
        }

        int m_bucketSize;               // max. No of points per leaf
        Rectangle boundary;             // boundary of whole quadtree
        std::vector<Point> points;      // points in leaf node

            // Child quadtrees
        Quadtree *northWest;
        Quadtree *northEast;
        Quadtree *southWest;
        Quadtree *southEast;

};
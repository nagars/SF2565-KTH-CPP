/*
 * class_imp.cpp
 *
 *  Created on: Nov 29, 2024
 *      Author: Shawn / Alessio
 */

#include "class_def.hpp"

// Compute reparametized curve
// Option to use point cache to compare peformance
Point EquationCurve::(double t) const override {
    if (cacheEnabled) {
        // Check if P(t) has been computed previously
        auto found = cache.find(t);
        if (found != cache.end()) {
            return found->second; // Return the cached point
        }
    }

    const double hatS = t; // use reference to keep same signature as Curve class
    // while avoiding confusion in below function equations
    const double arcLengthTotal = arcLength(1.0); // full curve length
    double arcLengthTarget = hatS * arcLengthTotal; // Target arc-length value

    // Define the function f(t) = s(t) - sTarget
    auto f = [this, arcLengthTarget](double t) -> double {
        double temp = arcLength(t) - arcLengthTarget;
        return temp;
    };

    // Define the function f'(t) = |dP/dt|
    auto f_prime = [this](double t) -> double {
        Point Pdot = this->gammaprime(t);
        double temp = std::sqrt(Pdot.x * Pdot.x + Pdot.y * Pdot.y);
        return temp;
    };

    // Newton method to find root convergence
    double t_of_hatS = t;
    for(uintmax_t n = 0; n < MAX_ITER; n++) {
        t_of_hatS = t - f(t)/f_prime(t);

        // Upon convergence, cache and return the computed point
        if(fabs(t_of_hatS - t) < TOL) {
            Point result = gamma(t_of_hatS);
            if (cacheEnabled) {
                cache[t] = result;
            }
            return result;
        }

        // update previous t value
        t = t_of_hatS;
    }

    throw std::runtime_error("Newton's method didn't converge");

};

double EquationCurve::arcLength(double t) const {

    // No need to integrate if t is 0
    if (t == 0) return 0;

    // Define a lambda function
    // to generate the integrand for arc-length calculation
    auto normPdot = [this](double tau) -> double {
        Point Pdot = this->gammaprime(tau);
        return std::sqrt(Pdot.x * Pdot.x + Pdot.y * Pdot.y);
    };

    using namespace boost::math::quadrature;
    // Perform numerical integration over [0, t]
    return trapezoidal(normPdot, 0.0, t, TOL);
};

// t = {0,1}. t = 0 -> pointStart. t = 1 -> pointEnd
Point StraightLine::(double t) const override {
    // Edge case for vertical line
    if(fabs(pointEnd.x - pointStart.x) < EPSILON) {
        Point p_toGet(pointStart.x,0);	// Init y point as 0 for now
        p_toGet.y = pointStart.y + t*(pointEnd.y - pointStart.y);
        return p_toGet;
    }// Edge case for horizontal line
    else if (fabs(pointEnd.y - pointStart.y) < EPSILON) {

        Point p_toGet(0,pointStart.y);	// Init x point as 0 for now
        p_toGet.x = pointStart.x + t*(pointEnd.x - pointStart.x);
        return p_toGet;
    } else {
        double pointOfInterest = pointStart.x + t*(pointEnd.x - pointStart.x);
        Point p_toGet(pointOfInterest,0);	// Init y point as 0 for now
        // p_toGet.y = pointStart.y + t*(pointEnd.x - pointStart.x);
        p_toGet.y = pointStart.y + t*(pointEnd.y - pointStart.y);
        return p_toGet;
    }
};
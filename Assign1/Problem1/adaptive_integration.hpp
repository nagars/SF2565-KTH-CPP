/*
 * adaptive_integration.h
 *
 *  Created on: Sep 16, 2024
 *      Author: Shawn
 */

#ifndef ADAPTIVE_INTEGRATION_HPP_
#define ADAPTIVE_INTEGRATION_HPP_

#include <cmath>
#include <stdint.h>

double func_simpsons_rule(double begin_limit, double end_limit, double tolerance);
double func_ASI(double(*f)(double), double begin_limit, double end_limit, double tolerance, uint32_t* func_call_counter);

#endif /* ADAPTIVE_INTEGRATION_HPP_ */

#pragma once
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

const double max_distance = 10000;//max detectable distance for sensor


struct pair{
    double x,y;
};

struct linear_function{
    double m,c;
};

/**
 * @brief calculate a vector(arrow)
 * @param angle the angle of the angle compared to the x axis
 * @param lenght is the length of the vector(arrow)
 * @return 2D vector
**/
extern pair VectorFromAngle(const double &angle, const double &length);

/**
 * @brief check if two linear functions do intersect
**/
extern bool DoIntersect(const linear_function &first, const linear_function &second);
/**
 * @brief check if two functions always intersect
**/
extern bool DoAlwaysInersect(const linear_function &first, const linear_function &second);
/**
 * @brief calculate where two linear functions interect NOTE: check if they DoIntersect before using this function
 * @return location where the two functions intersect
**/
extern pair IntersectionPoint(const linear_function &first, const linear_function &second);
/**
 * @brief check if an value is in a range of numbers
 * @param max is the maximum for value
 * @param min is the minimum for value
**/
extern bool IsInRange(const double &value, const double &max, const double &min);

/**
 * @brief get the sloope from an angle
 * @param angle the angle of the sloope
 * @return the sloope m in a linear function
**/
extern double GetSloope(const double &angle);

/**
 * @brief check the closest intersection a line with other lines
 * @param angle is the angle of the line on which the distance is measured
 * @param position is the start position of the line on which the distance is measured
 * @param lines are the lines to which the distance is measured
 * @return the closest non negative distance to a line if it doesn't intersect any it will return max_distance
**/
extern double DoIntersect(const double angle, const SDL_Point position, const std::vector<SDL_Point> &lines);

/**
 * @brief return difference to 0
**/
extern double GetPositive(const double &value);

/**
 * @brief calculate the total lenght of an vector
 * @param vector to caluclate lenght
 * @return lenght of vector
**/
extern double GetVectorLenght(const pair &vector);
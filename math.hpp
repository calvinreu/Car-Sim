#pragma once
#include <math.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

constexpr double max_distance = 10000;//max detectable distance for sensor
constexpr double angleToPi = 0.017453293;//pi divided by 180


struct pair{
    double x,y;
};

struct linear_function{
    double m,c;
};

struct rect{
    double x, y, w ,h;
};

/**
 * @brief calculate a vector(arrow)
 * @param angle the angle of the angle compared to the x axis
 * @param lenght is the length of the vector(arrow)
 * @return 2D vector
**/
extern constexpr pair VectorFromAngle(const double &angle, const double &length);

/**
 * @brief check if two linear functions do intersect
**/
extern constexpr bool DoIntersect(const linear_function &first, const linear_function &second);
/**
 * @brief check if two functions always intersect
**/
extern constexpr bool DoAlwaysIntersect(const linear_function &first, const linear_function &second);
/**
 * @brief calculate where two linear functions interect NOTE: check if they DoIntersect before using this function
 * @return location where the two functions intersect
**/
extern constexpr pair IntersectionPoint(const linear_function &first, const linear_function &second);
/**
 * @brief check if an value is in a range of numbers
 * @param max is the maximum for value
 * @param min is the minimum for value
**/
extern constexpr bool IsInRange(const double &value, const double &max, const double &min);

/**
 * @brief get the sloope from an angle
 * @param angle the angle of the sloope
 * @return the sloope m in a linear function
**/
extern constexpr double GetSloope(const double &angle);

/**
 * @brief return difference to 0
**/
extern constexpr double GetPositive(const double &value);

/**
 * @brief calculate the total lenght of an vector
 * @param vector to caluclate lenght
 * @return lenght of vector
**/
extern constexpr double GetVectorLenght(const pair &vector);
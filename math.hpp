#include <math.h>


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
extern pair& VectorFromAngle(const double &angle, const double &length);

/**
 * @brief check if two linear functions do intersect
**/
extern bool DoInersect(const linear_function &first, const linear_function &second);
/**
 * @brief calculate where two linear functions interect NOTE: check if they DoIntersect before using this function
 * @return location where the two functions intersect
**/
extern pair& IntersectionPoint(const linear_function &first, const linear_function &second);
/**
 * @brief check if an value is in a range of numbers
 * @param max is the maximum for value
 * @param min is the minimum for value
**/
extern bool IsInRange(const double &value, const double &max, const double &min);
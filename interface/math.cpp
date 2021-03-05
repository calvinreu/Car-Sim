#include "math.hpp"

pair& VectorFromAngle(const double &angle, const double &length) {
    pair vector;
    vector.x = sin(angle);
    vector.y = cos(angle);
    //vector with length 1
    vector.x *= length;
    vector.y *= length;

    return vector;
}

bool DoIntersect(const linear_function &first, const linear_function &second) { return first.m != second.m || first.c == second.c; }

pair& IntersectionPoint(const linear_function &first, const linear_function &second) {
    pair position;
    position.x = (first.m-second.m)/(second.c-first.c);
    position.y = first.c + (first.m*position.x);
    return position;
}

bool IsInRange(const double &value, const double &max, const double &min){ return value < max && min < value; }
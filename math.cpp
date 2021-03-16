#include "math.hpp"

bool DoIntersect(const linear_function &first, const linear_function &second) { return first.m != second.m || first.c == second.c; }
bool DoAlwaysIntersect(const linear_function &first, const linear_function & second) { return first.m == second.m && first.c == second.c; }
bool IsInRange(const double &value, const double &max, const double &min){ return value < max && min < value; }
double GetSloope(const double &angle) { return tan(angle*angleToPi); }
double GetPositive(const double &value) { return value < 0 ? -1*value : value; }

double GetVectorLenght(const pair &vector) { return sqrt((vector.x*vector.x)+(vector.y*vector.y)); }

pair VectorFromAngle(const double &angle, const double &length) {
    pair vector;
    vector.x =  sin(angle*angleToPi);
    vector.y =  cos(angle*angleToPi);
    //vector with length 1
    vector.x *= length;
    vector.y *= length;

    return vector;
}

pair IntersectionPoint(const linear_function &first, const linear_function &second) {
    pair position;

    position.x = (second.c-first.c)/(first.m-second.m);
    position.y = first.c + (first.m*position.x);
    return position;
}

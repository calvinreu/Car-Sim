#include "math.hpp"

constexpr bool DoIntersect(const linear_function &first, const linear_function &second) { return first.m != second.m || first.c == second.c; }
constexpr bool DoAlwaysIntersect(const linear_function &first, const linear_function & second) { return first.m == second.m && first.c == second.c; }
constexpr bool IsInRange(const double &value, const double &max, const double &min){ return value < max && min < value; }
constexpr double GetSloope(const double &angle) { return tan(angle*angleToPi); }
constexpr double GetPositive(const double &value) { return value < 0 ? -1*value : value; }
constexpr double GetVectorLenght(const pair &vector) { return sqrt((vector.x*vector.x)+(vector.y*vector.y)); }

constexpr pair VectorFromAngle(const double &angle, const double &length) {
    pair vector = {.x =  sin(angle*angleToPi)*length, .y =  cos(angle*angleToPi)*length};

    return vector;
}

constexpr pair IntersectionPoint(const linear_function &first, const linear_function &second) {
    pair position = {.x = (second.c-first.c)/(first.m-second.m), .y = first.c + (first.m*position.x)};

    return position;
}

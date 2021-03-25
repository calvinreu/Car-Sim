#include "math.hpp"

const bool DoIntersect(const linear_function &first, const linear_function &second) { return first.m != second.m || first.c == second.c; }
const bool DoAlwaysIntersect(const linear_function &first, const linear_function & second) { return first.m == second.m && first.c == second.c; }
const bool IsInRange(const double &value, const double &max, const double &min){ return value < max && min < value; }
const double GetSloope(const double &angle) { return tan(angle*angleToPi); }
const double GetPositive(const double &value) { return value < 0 ? -1*value : value; }
const double GetVectorLenght(const pair &vector) { return sqrt((vector.x*vector.x)+(vector.y*vector.y)); }
pair pair::operator-(const pair &other) const {return pair{.x = this->x-other.x, .y = this->y - other.y}; }
pair pair::operator+(const pair &other) const {return pair{.x = this->x+other.x, .y = this->y + other.y}; }
void pair::operator=(const pair &other){this->x = other.x, this->y = other.y; }
void pair::operator+=(const pair &other){this->x += other.x, this->y += other.y; }
void pair::operator-=(const pair &other){this->x -= other.x, this->y -= other.y; }

const pair VectorFromAngle(const double &angle, const double &length) {
    pair vector = {.x =  sin(angle*angleToPi)*length, .y =  cos(angle*angleToPi)*length};

    return vector;
}

const pair IntersectionPoint(const linear_function &first, const linear_function &second) {
    pair position = {.x = (second.c-first.c)/(first.m-second.m), .y = first.c + (first.m*position.x)};

    return position;
}

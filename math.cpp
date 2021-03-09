#include "math.hpp"

const double angleToPi = 0.017453293;//pi divided by 180

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

double DoIntersect(const double angle, const SDL_Point position, const std::vector<SDL_Point> &lines) {
    linear_function main_line;
    linear_function temp_line;
    pair temp_vec;
    double temp_distance;
    double distance = max_distance; //smallest distance
    main_line.m = GetSloope(angle);
    main_line.c = position.y - (main_line.m*position.x);

    for(auto i = lines.begin() + 1; i < lines.end(); i++) {
        temp_line.m = (i->y - (i-1)->y)/(i->x - (i-1)->x);
        temp_line.c = i->y - (temp_line.m * i->x);
        if (DoIntersect(main_line, temp_line)) {
            if(DoAlwaysIntersect(main_line, temp_line)) {
                
                //check if postion is on line
                if(i->x > position.x) {
                    if((i-1)->x <= position.x)
                        return 0;
                }else if(i->x < position.x){
                    if((i-1)->x >= position.x)
                        return 0;
                }else{
                    return 0;//point position is on line
                }

                temp_vec.x = GetPositive(i->x - position.x);
                temp_vec.y = GetPositive((i-1)->x - position.x);

                if(temp_vec.x < temp_vec.y){
                    temp_vec.x = temp_vec.x;
                    temp_vec.y = i->y - position.y;
                }else{
                    temp_vec.x = temp_vec.y;
                    temp_vec.y = (i-1)->y - position.y;
                }
            }else{
                temp_vec = IntersectionPoint(main_line, temp_line);
                
                //sometimes random skip fix for efficienzy
                //if((temp_vec.x > i->x && temp_vec.x > (i-1)->x) || (temp_vec.x < i->x && temp_vec.x < (i-1)->x))
                //    continue;

                temp_vec.x -= position.x;
                temp_vec.y -= position.y;//distance vector from position to IntersectionPoint
            }

            //check if point is in the direction of angle
            if( sin(angle*angleToPi) > 0) {
                if(temp_vec.y > 0) {
                    temp_distance = GetVectorLenght(temp_vec);
                    if(temp_distance < distance)
                        distance = temp_distance;
                }
            }else if( sin(angle*angleToPi) < 0) {
                if(temp_vec.y < 0) {
                    temp_distance = GetVectorLenght(temp_vec);
                    if(temp_distance < distance)
                        distance = temp_distance;
                }
            }else if( cos(angle*angleToPi) > 0) {
                if(temp_vec.x > 0) {
                    temp_distance = GetVectorLenght(temp_vec);
                    if(temp_distance < distance)
                        distance = temp_distance;
                }
            }else{
                if(temp_vec.x < 0) {
                    temp_distance = GetVectorLenght(temp_vec);
                    if(temp_distance < distance)
                        distance = temp_distance;
                }
            }
        }
    }

    return distance;
}
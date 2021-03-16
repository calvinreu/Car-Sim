#include "car.hpp"

extern const double angleToPi;//pi divided by 180

sensornet::sensornet(double* sensorOutput, const double &carAngle, const std::vector<SDL_Point> &map, const SDL_Point &carPos) : sensorOutput(sensorOutput), sensorAngle(sensorOutput+SENSOR_COUNT), carAngle(&carAngle), map(&map), carPos(&carPos) {}

bool sensornet::refresh() {
    linear_function main_line[SENSOR_COUNT];
    linear_function temp_line;
    pair sensorPos[SENSOR_COUNT];
    double angle[SENSOR_COUNT];
    pair temp_vec;
    double temp_distance;
    double distance = max_distance; //smallest distance

    for (size_t i = 0; i < SENSOR_COUNT; i++)
    {
        sensorAngle[i] += ANGLE_CHANGE[i];
        angle[i] = SENSOR_POSITION[i].x+(*carAngle);
        sensorPos[i]= VectorFromAngle(angle[i], SENSOR_POSITION[i].y);
        sensorPos[i].x += carPos->x;
        sensorPos[i].y += carPos->y;

        // sensorOutput[i] = this->Intersect(, sensorPos, *map);
        main_line[i].m = GetSloope(sensorAngle[i]+SENSOR_POSITION[i].x+(*carAngle));
        main_line[i].c = sensorPos[i].y - (main_line[i].m*sensorPos[i].x);
    }
    
    for(auto i = map->begin() + 1; i < map->end(); i++) {
        temp_line.m = (i->y - (i-1)->y)/(i->x - (i-1)->x);
        temp_line.c = i->y - (temp_line.m * i->x);
        for(size_t j = 0; j < SENSOR_COUNT ;j++) {
            if (DoIntersect(main_line[j], temp_line)) {
                if(DoAlwaysIntersect(main_line[j], temp_line)) {
                
                    //check if postion is on line
                    if(i->x > sensorPos[j].x) {
                        if((i-1)->x <= sensorPos[j].x)
                            return false;
                    }else if(i->x < sensorPos[j].x){
                        if((i-1)->x >= sensorPos[j].x)
                            return false;
                    }else{
                        return false;//point sensorPos[j] is on line
                    }

                    temp_vec.x = GetPositive(i->x - sensorPos[j].x);
                    temp_vec.y = GetPositive((i-1)->x - sensorPos[j].x);

                    if(temp_vec.x < temp_vec.y){
                        temp_vec.x = temp_vec.x;
                        temp_vec.y = i->y - sensorPos[j].y;
                    }else{
                        temp_vec.x = temp_vec.y;
                        temp_vec.y = (i-1)->y - sensorPos[j].y;
                    }
                }else{
                    temp_vec = IntersectionPoint(main_line[j], temp_line);

                    temp_vec.x -= sensorPos[j].x;
                    temp_vec.y -= sensorPos[j].y;//distance vector from position to IntersectionPoint
                }

                //check if point is in the direction of angle
                if( sin(angle[j]*angleToPi) > 0) {
                    if(temp_vec.y > 0) {
                        temp_distance = GetVectorLenght(temp_vec);
                        if(temp_distance < distance)
                            distance = temp_distance;
                    }
                }else if( sin(angle[j]*angleToPi) < 0) {
                    if(temp_vec.y < 0) {
                        temp_distance = GetVectorLenght(temp_vec);
                        if(temp_distance < distance)
                            distance = temp_distance;
                    }
                }else if( cos(angle[j]*angleToPi) > 0) {
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

            sensorOutput[j] = distance;
        }
    }

    return true;
}
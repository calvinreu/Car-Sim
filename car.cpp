#pragma once
#include "car.hpp"
#include "log.hpp"

extern const double angleToPi;//pi divided by 180
extern const SDL_Rect car_sRect;

constexpr double SensorDistanceToCenter(const double &angle) {
    pair carCenter = {.x = car_sRect.w/2, .y = car_sRect.h/2};
    linear_function sensorLine = {.m = GetSloope(angle), .c = carCenter.y - (GetSloope(angle)*carCenter.x)};
    linear_function top = {.m = 0, .c = car_sRect.h};
    linear_function bot = {.m = 0, .c = 0};

    if(DoIntersect(sensorLine, top)){//has to intersect with bot too because bot and top are ||
        pair topIntersect = IntersectionPoint(sensorLine, top);
        pair botIntersect = IntersectionPoint(sensorLine, bot);
        if(botIntersect.x < car_sRect.w && botIntersect.x > 0)
            return GetVectorLenght(pair{.x = carCenter.x - botIntersect.x, .y = carCenter.y - botIntersect.y});
        else if(topIntersect.x < car_sRect.w && topIntersect.x > 0)
            return GetVectorLenght(pair{.x = carCenter.x - topIntersect.x, .y = carCenter.y - topIntersect.y});
    }

    return GetVectorLenght(pair{.x = carCenter.x, .y = carCenter.x/cos(angle*angleToPi)*sin(angle*angleToPi)});
}

constexpr pair SensorPosition(const double &angle) 
{
    pair carCenter = {.x = car_sRect.w/2, .y = car_sRect.h/2};
    linear_function sensorLine = {.m = GetSloope(angle), .c = carCenter.y - (GetSloope(angle)*carCenter.x)};
    linear_function top = {.m = 0, .c = car_sRect.h};
    linear_function bot = {.m = 0, .c = 0};

    if(DoIntersect(sensorLine, top)){//has to intersect with bot too because bot and top are ||
        pair topIntersect = IntersectionPoint(sensorLine, top);
        pair botIntersect = IntersectionPoint(sensorLine, bot);
        if(botIntersect.x < car_sRect.w && botIntersect.x > 0)
            return pair{.x = carCenter.x - botIntersect.x, .y = carCenter.y - botIntersect.y};
        else if(topIntersect.x < car_sRect.w && topIntersect.x > 0)
            return pair{.x = carCenter.x - topIntersect.x, .y = carCenter.y - topIntersect.y};
    }

    return pair{.x = carCenter.x, .y = carCenter.x/cos(angle*angleToPi)*sin(angle*angleToPi)};
}

const pair SENSOR_POSITION[SENSOR_COUNT] = {{.x = 0, .y = SensorDistanceToCenter(0)}};//.x angle relative to car .y distance to car center
const sensor_angle_change ANGLE_CHANGE[SENSOR_COUNT] = {{.ammount = 30, .max_angle = 90, .min_angle = -90}};

sensornet::sensornet(const double &carAngle, const std::vector<SDL_Point> &map, const SDL_Point &carPos) : carAngle(&carAngle), map(&map), carPos(&carPos) {}

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
        if(sensors[i].direction) {
            sensors[i].angle += ANGLE_CHANGE[i].ammount;
            if(sensors[i].angle > ANGLE_CHANGE[i].max_angle){
                sensors[i].direction = false;
                sensors[i].angle -= 2*ANGLE_CHANGE[i].ammount;
            }
        }else{
            sensors[i].angle -= ANGLE_CHANGE[i].ammount;
            if(sensors[i].angle < ANGLE_CHANGE[i].min_angle){
                sensors[i].direction = true;
                sensors[i].angle += 2*ANGLE_CHANGE[i].ammount;
            }
        }

        angle[i] = SENSOR_POSITION[i].x+(*carAngle);
        sensorPos[i]= VectorFromAngle(angle[i], SENSOR_POSITION[i].y);
        sensorPos[i].x += carPos->x;
        sensorPos[i].y += carPos->y;
        angle[i] += sensors[i].angle;
        // sensorOutput[i] = this->Intersect(, sensorPos, *map);
        main_line[i].m = GetSloope(angle[i]);
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
                        continue;
                    }
                }else if( sin(angle[j]*angleToPi) < 0) {
                    if(temp_vec.y < 0) {
                        temp_distance = GetVectorLenght(temp_vec);
                        if(temp_distance < distance)
                            distance = temp_distance;
                        continue;
                    }
                }else if( cos(angle[j]*angleToPi) > 0) {
                    if(temp_vec.x > 0) {
                        temp_distance = GetVectorLenght(temp_vec);
                        if(temp_distance < distance)
                            distance = temp_distance;
                        continue;
                    }
                }else{
                    if(temp_vec.x < 0) {
                        temp_distance = GetVectorLenght(temp_vec);
                        if(temp_distance < distance)
                            distance = temp_distance;
                        continue;
                    }
                }
            }

            if(GetVectorLenght(temp_vec) < 40){//lenght which definetly is in the car
                return false;
            }

            logfile::log(std::to_string(distance));//just for testing

            sensors[j].distance = distance;
        }
    }

    return true;
}
#include <iostream>
#include "math.hpp"


const size_t SENSOR_COUNT = 4;
const pair SENSOR_POSITION[SENSOR_COUNT] = {{.x = 0, .y = 0}};//.x angle relative to car .y distance to car center
const double ANGLE_CHANGE[SENSOR_COUNT] = {1, 1, 1, 1};


class car
{
private:
    //some tensorflow AI
    double output[2];//[0]turn [1]speedchange

    double input[(SENSOR_COUNT*2)+1];//first half sensor distance second half sensor angle last for current speed

    double angle;
    pair carPos;
    SDL_FPoint carPosRender;//car position for rendering

public:
    void refresh();

    car(/* args */);
    ~car();
};

class sensornet
{
private:
    double* sensorOutput;
    double* sensorAngle;
    const double* carAngle;
    const std::vector<SDL_Point>* map;
    const SDL_Point* carPos;
public:
    /**
     * @brief get new sensor data and set it to sensorOutput
    **/
    bool refresh();
    
    /**
     * @param sensorOutput output array for sensor data
     * @param map map to use to calculate sensor output
     * @param carPosition position of the car in the current map 
    **/
    sensornet(double* sensorOutput, const double &carAngle, const std::vector<SDL_Point> &map, const SDL_Point &carPosition);
};
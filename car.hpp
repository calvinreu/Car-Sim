#include <iostream>
#include "math.hpp"
#include "interface/graphic.hpp"

constexpr size_t SENSOR_COUNT = 1;

struct sensor{
    double angle, distance;
    bool direction;//true change angle + else -
};

struct sensor_angle_change{
    double ammount, max_angle, min_angle;
};

class car
{
private:
    //some tensorflow AI
    double output[2];//[0]turn [1]speedchange

    double input[(SENSOR_COUNT*2)+1];//first half sensor distance second half sensor angle last for current speed

    double angle;
    pair carPos;

public:
    void refresh();

    car(/* args */);
    ~car();
};

//sensornetwork for 1 car note sensornet may not work if multiple instances are created
class sensornet
{
private:
    sensor sensors[SENSOR_COUNT];
    const double* carAngle;
    const std::vector<SDL_Point>* map;
    const pair* carPos;
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
    sensornet(const double &carAngle, const std::vector<SDL_Point> &map, const pair &carPosition);
};
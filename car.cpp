#include "car.hpp"


sensornet::sensornet(double* sensorOutput, const double &carAngle, const std::vector<SDL_Point> &map, const SDL_Point &carPos) : sensorOutput(sensorOutput), sensorAngle(sensorOutput+SENSOR_COUNT), carAngle(&carAngle), map(&map), carPos(&carPos) {}

void sensornet::refresh(){
    pair sensorPos;

    for (size_t i = 0; i < SENSOR_COUNT; i++)
    {
        sensorAngle[i] += ANGLE_CHANGE[i];
        sensorPos = VectorFromAngle(SENSOR_POSITION[i].x+(*carAngle), SENSOR_POSITION[i].y);
        sensorPos.x += carPos->x;
        sensorPos.y += carPos->y;

        sensorOutput[i] = DoIntersect(sensorAngle[i]+SENSOR_POSITION[i].x+(*carAngle), sensorPos, *map);
    }
}
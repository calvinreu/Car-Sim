#include <iostream>


class car
{
private:
    //some tensorflow AI
    size_t output[2];//[0]turn [1]speedchange
    long speed;//current speed input for AI
public:
    long input[5];
    car(/* args */);
    ~car();
};

car::car(/* args */)
{
}

car::~car()
{
}
